#include "platform/update.h"
#include "graphics/animation.h"
#include "utils/memory.h"
#include "platform/wayland.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <pthread.h>
#include <linux/input.h>
#include <unistd.h>
#include <cassert>
#include <fcntl.h>
#include <poll.h>
#include <sys/eventfd.h>
#include <cstdio>

namespace bongocat::platform::update {
    inline static constexpr int MAX_ATTEMPTS = 2048;

    static inline constexpr auto UPDATE_POOL_TIMEOUT_MS = 1000;

    inline static constexpr time_ms_t COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS = 5000;
    inline static constexpr time_ms_t COND_RELOAD_CONFIGS_TIMEOUT_MS = 5000;

    static void cleanup_update_thread(void* arg) {
        assert(arg);
        animation::animation_session_t& trigger_ctx = *static_cast<animation::animation_session_t *>(arg);
        assert(trigger_ctx._update);
        update_context_t& input = *trigger_ctx._update;

        atomic_store(&input._running, false);

        input.config_updated.notify_all();

        BONGOCAT_LOG_INFO("Update thread cleanup completed (via pthread_cancel)");
    }


    static void* update_thread(void* arg) {
        assert(arg);
        animation::animation_session_t& trigger_ctx = *static_cast<animation::animation_session_t *>(arg);

        // from thread context
        //animation_context_t& anim = trigger_ctx.anim;
        // wait for input context (in animation start)
        trigger_ctx.init_cond.timedwait([&]() {
            return atomic_load(&trigger_ctx.ready);
        }, COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS);
        assert(trigger_ctx._input != nullptr);
        update_context_t& upd = *trigger_ctx._update;

        // sanity checks
        assert(upd._config != nullptr);
        assert(upd._configs_reloaded_cond != nullptr);

        // keep local copies of device_paths
        {
            // read-only config
            assert(upd._local_copy_config != nullptr);
            const config::config_t& current_config = *upd._local_copy_config;

            /// @TODO: init fd and CPU listeners
        }

        // trigger initial render
        wayland::request_render(trigger_ctx);

        pthread_cleanup_push(cleanup_update_thread, arg);

        // @TODO: init local thread context varaibles

        /// event poll
        // 0:       reload config event
        // 1 - n:   ???
        constexpr size_t nfds = 1;
        pollfd pfds[nfds];

        atomic_store(&upd._running, true);
        while (atomic_load(&upd._running)) {
            pthread_testcancel();  // optional, but makes cancellation more responsive

            // read from config
            int timeout = UPDATE_POOL_TIMEOUT_MS;
            bool enable_debug = false;
            {
                // read-only config
                assert(upd._local_copy_config != nullptr);
                const config::config_t& current_config = *upd._local_copy_config;

                enable_debug = current_config.enable_debug;

                if (current_config.input_fps > 0) {
                    /// @TODO: use update_fps from confg or "harthbeat" for update rate
                    //timeout = 1000 / current_config.update_fps;
                } else if (current_config.fps > 0) {
                    timeout = 1000 / current_config.fps * 2;
                }
            }

            // init pfds
            constexpr size_t fds_update_config_index = 0;
            pfds[fds_update_config_index] = { .fd = upd.update_config_efd._fd, .events = POLLIN, .revents = 0 };

            // poll events
            const int poll_result = poll(pfds, nfds, timeout);
            if (poll_result < 0) {
                if (errno == EINTR) continue; // Interrupted by signal
                BONGOCAT_LOG_ERROR("Poll error: %s", strerror(errno));
                break;
            }

            // cancel pooling (when not running anymore)
            if (!atomic_load(&upd._running)) {
                // draining pools
                for (size_t i = 0;i < nfds;i++) {
                    if (pfds[i].revents & POLLIN) {
                        int attempts = 0;
                        uint64_t u;
                        while (read(pfds[i].fd, &u, sizeof(uint64_t)) == sizeof(uint64_t) && attempts < MAX_ATTEMPTS) {
                            attempts++;
                        }
                    }
                }
                break;
            }

            // Handle config update
            assert(upd._config_generation != nullptr);
            bool reload_config = false;
            uint64_t new_gen{atomic_load(upd._config_generation)};
            if (pfds[fds_update_config_index].revents & POLLIN) {
                BONGOCAT_LOG_DEBUG("Receive update config event");
                int attempts = 0;
                while (read(upd.update_config_efd._fd, &new_gen, sizeof(uint64_t)) == sizeof(uint64_t) && attempts < MAX_ATTEMPTS) {
                    attempts++;
                    // continue draining if multiple writes queued
                }
                // supress compiler warning
#if EAGAIN == EWOULDBLOCK
                if (errno != EAGAIN) {
                    BONGOCAT_LOG_ERROR("Error reading reload eventfd: %s", strerror(errno));
                }
#else
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    BONGOCAT_LOG_ERROR("Error reading reload eventfd: %s", strerror(errno));
                }
#endif

                reload_config = new_gen > 0;
            }

            // Handle device events
            {
                platform::LockGuard guard (upd.update_lock);
                assert(upd.shm != nullptr);
                //auto& input_shm = *upd.shm;

                // update shm data
            }

            // handle update config
            if (reload_config) {
                assert(upd._config_generation != nullptr);
                assert(upd._configs_reloaded_cond != nullptr);
                assert(upd._config != nullptr);

                update_config(upd, *upd._config, new_gen);

                // wait for reload config to be done (all configs)
                const int rc = upd._configs_reloaded_cond->timedwait([&] {
                    return atomic_load(upd._config_generation) >= new_gen;
                }, COND_RELOAD_CONFIGS_TIMEOUT_MS);
                if (rc == ETIMEDOUT) {
                    BONGOCAT_LOG_WARNING("Input: Timed out waiting for reload eventfd: %s", strerror(errno));
                }
                assert(atomic_load(&upd.config_seen_generation) == atomic_load(upd._config_generation));
                atomic_store(&upd.config_seen_generation, atomic_load(upd._config_generation));
                BONGOCAT_LOG_INFO("Input config reloaded (gen=%u)", new_gen);
            }
        }

        atomic_store(&upd._running, false);

        // Will run only on normal return
        pthread_cleanup_pop(1);  // 1 = call cleanup even if not canceled

        BONGOCAT_LOG_INFO("Update monitoring stopped");

        return nullptr;
    }

    created_result_t<AllocatedMemory<update_context_t>> create(const config::config_t& config) {
        AllocatedMemory<update_context_t> ret = make_allocated_memory<update_context_t>();
        assert(ret != nullptr);
        if (ret == nullptr) {
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }

        ret->_running = false;

        BONGOCAT_LOG_INFO("Initializing update monitoring system");

        // Initialize shared memory
        ret->shm = make_allocated_mmap<update_shared_memory_t>();
        if (!ret->shm.ptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for update monitoring: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }

        // Initialize shared memory for local config
        ret->_local_copy_config = make_allocated_mmap<config::config_t>();
        if (!ret->_local_copy_config) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for update monitoring: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(ret->_local_copy_config != nullptr);
        *ret->_local_copy_config = config;

        ret->update_config_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
        if (ret->update_config_efd._fd < 0) {
            BONGOCAT_LOG_ERROR("Failed to create notify pipe for update update config: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
        }

        BONGOCAT_LOG_INFO("Input monitoring started");
        return ret;
    }

    bongocat_error_t start(update_context_t& upd, animation::animation_session_t& trigger_ctx, const config::config_t& config, CondVariable& configs_reloaded_cond, atomic_uint64_t& config_generation) {
        BONGOCAT_LOG_INFO("Initializing update monitoring");

        // Initialize shared memory for key press flag
        upd.shm = make_allocated_mmap<update_shared_memory_t>();
        if (!upd.shm.ptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }

        // Initialize shared memory for local config
        upd._local_copy_config = make_allocated_mmap<config::config_t>();
        if (!upd._local_copy_config) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(upd._local_copy_config != nullptr);
        update_config(upd, config, atomic_load(&config_generation));

        // wait for animation trigger to be ready (input should be the same)
        int cond_ret = trigger_ctx.init_cond.timedwait([&]() {
            return atomic_load(&trigger_ctx.ready);
        }, COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS);
        if (cond_ret == ETIMEDOUT) {
            BONGOCAT_LOG_ERROR("Failed to initialize input monitoring: waiting for animation thread to start in time");
        } else {
            assert(trigger_ctx._update == &upd);
        }
        // set extern/global references
        trigger_ctx._update = &upd;
        trigger_ctx.init_cond.notify_all();
        upd._config = &config;
        upd._configs_reloaded_cond = &configs_reloaded_cond;
        upd._config_generation = &config_generation;
        atomic_store(&upd.ready, true);
        upd.init_cond.notify_all();

        upd._configs_reloaded_cond->notify_all();

        // start update thread
        const int result = pthread_create(&upd._update_thread, nullptr, update_thread, &trigger_ctx);
        if (result != 0) {
            BONGOCAT_LOG_ERROR("Failed to start update thread: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_THREAD;
        }

        BONGOCAT_LOG_INFO("Update monitoring started");
        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    bongocat_error_t restart(update_context_t& upd, animation::animation_session_t& trigger_ctx, const config::config_t& config, CondVariable& configs_reloaded_cond, atomic_uint64_t& config_generation) {
        BONGOCAT_LOG_INFO("Restarting update system");
        // Stop current monitoring
        if (upd._update_thread) {
            BONGOCAT_LOG_DEBUG("Update thread");
            atomic_store(&upd._running, false);
            //pthread_cancel(ctx->_update_thread);
            if (stop_thread_graceful_or_cancel(upd._update_thread, upd._running) != 0) {
                BONGOCAT_LOG_ERROR("Failed to join update thread: %s", strerror(errno));
            }
            BONGOCAT_LOG_DEBUG("Update thread terminated");
        }

        cleanup(upd);

        // Start new monitoring (reuse shared memory if it exists)
        if (upd.shm == nullptr) {
            upd.shm = make_allocated_mmap<update_shared_memory_t>();
            if (upd.shm.ptr == MAP_FAILED) {
                BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
                return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
            }
        }

        if (!upd._local_copy_config) {
            upd._local_copy_config = make_unallocated_mmap_value<config::config_t>(config);
            if (!upd._local_copy_config) {
                BONGOCAT_LOG_ERROR("Failed to create shared memory for update: %s", strerror(errno));
                return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
            }
        }
        assert(upd._local_copy_config != nullptr);
        update_config(upd, config, atomic_load(&config_generation));

        //if (trigger_ctx._update != ctx._update) {
        //    BONGOCAT_LOG_DEBUG("Update context in animation differs from animation trigger update context");
        //}

        // set extern/global references
        trigger_ctx._update = &upd;
        upd._config = &config;
        upd._configs_reloaded_cond = &configs_reloaded_cond;
        upd._config_generation = &config_generation;
        atomic_store(&upd.config_seen_generation, atomic_load(&config_generation));
        upd.init_cond.notify_all();
        upd._configs_reloaded_cond->notify_all();

        // start update monitoring
        const int result = pthread_create(&upd._update_thread, nullptr, update_thread, &trigger_ctx);
        if (result != 0) {
            BONGOCAT_LOG_ERROR("Failed to start update thread: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_THREAD;
        }

        BONGOCAT_LOG_INFO("Update thread restarted");
        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    void stop(update_context_t& ctx) {
        atomic_store(&ctx._running, false);
        if (ctx._update_thread) {
            BONGOCAT_LOG_DEBUG("Stopping update thread");
            //pthread_cancel(ctx->_update_thread);
            if (stop_thread_graceful_or_cancel(ctx._update_thread, ctx._running) != 0) {
                BONGOCAT_LOG_ERROR("Failed to join update thread: %s", strerror(errno));
            }
            BONGOCAT_LOG_DEBUG("Update thread terminated");
        }
        ctx._update_thread = 0;

        ctx._config = nullptr;
        ctx._configs_reloaded_cond = nullptr;
        ctx._config_generation = nullptr;

        ctx.config_updated.notify_all();
        atomic_store(&ctx.ready, false);
        ctx.init_cond.notify_all();
    }

    void trigger_update_config(update_context_t& upd, const config::config_t& config, uint64_t config_generation) {
        upd._config = &config;
        if (write(upd.update_config_efd._fd, &config_generation, sizeof(uint64_t)) >= 0) {
            BONGOCAT_LOG_VERBOSE("Write update trigger update config");
        } else {
            BONGOCAT_LOG_ERROR("Failed to write to notify pipe in update: %s", strerror(errno));
        }
    }

    void update_config(update_context_t& upd, const config::config_t& config, uint64_t new_gen) {
        assert(upd._local_copy_config != nullptr);

        *upd._local_copy_config = config;

        atomic_store(&upd.config_seen_generation, new_gen);
        // Signal main that reload is done
        upd.config_updated.notify_all();
    }
}
