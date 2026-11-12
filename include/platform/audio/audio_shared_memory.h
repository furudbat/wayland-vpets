#ifndef BONGOCAT_AUDIO_SHARED_CONTEXT_H
#define BONGOCAT_AUDIO_SHARED_CONTEXT_H

#include "config/config.h"
#include "module.h"
#include "utils/time.h"

#include <cstddef>
#include <cstdint>

namespace bongocat::platform::audio {

BONGOCAT_STUBS_BEGIN

// Only derived, aggregated values are shared with other threads.
// Raw samples and spectrum bars never leave the audio thread (privacy).
struct audio_shared_memory_t {
  bool active{false};                     // non-silent audio is currently playing
  double level{0.0};                      // 0..1 smoothed, autosens-normalized loudness
  bool peak{false};                       // latched peak (happy), cleared by the audio thread after cooldown
  timestamp_ms_t last_peak_timestamp{0};  // last time a peak was reached
  double bpm{0.0};                        // estimated beats per minute; 0 = unknown
  double speed_factor{1.0};               // animation speed factor based on BPM; 1.0 = normal
};

BONGOCAT_STUBS_END

}  // namespace bongocat::platform::audio

#endif