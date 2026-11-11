#ifndef BONGOCAT_AUDIO_SHARED_CONTEXT_H
#define BONGOCAT_AUDIO_SHARED_CONTEXT_H

#include "config/config.h"
#include "module.h"

#include <cstddef>
#include <cstdint>

namespace bongocat::platform::audio {

BONGOCAT_STUBS_BEGIN

struct audio_shared_memory_t {
  /// @TODO: add BPM, peak and other audio viluilizer values for animation (trigger)
};

BONGOCAT_STUBS_END

}  // namespace bongocat::platform::audio

#endif