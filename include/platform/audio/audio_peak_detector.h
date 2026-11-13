#ifndef BONGOCAT_AUDIO_PEAK_DETECTOR_H
#define BONGOCAT_AUDIO_PEAK_DETECTOR_H

#include "utils/time.h"

#include <cassert>
#include <cmath>
#include <cstddef>

namespace bongocat::platform::audio::details {

inline static constexpr size_t PEAK_DETECTOR_MAX_BARS = 64;

inline static constexpr double PEAK_CAP_FALL_TAU_MS = 4000.0;  // peak cap falls slowly (exponential)
inline static constexpr double PEAK_BAR_TOP_RATIO = 0.9;       // bar >= 90% of its peak cap: "at the top"
inline static constexpr double PEAK_BAR_MIN = 0.15;            // ignore (almost) empty bars (noise)
inline static constexpr time_ms_t PEAK_WARMUP_MS = 4000;       // autosens settling: every bar reaches new tops
inline static constexpr time_ms_t PEAK_COOLDOWN_MS = 2000;     // min. time between peaks (rate limit)
inline static constexpr double PEAK_REARM_RATIO = 0.75;        // re-arm below threshold * ratio ...
// ... for this long: a short dip between two hits is enough (heavy music: happy on hits, limited by cooldown)
inline static constexpr time_ms_t PEAK_REARM_HOLD_MS = 150;
// sustained sound: the mean of all bars must not have dropped to (almost) silence within the last window,
// sparse transients (e.g. slow metronome clicks) briefly saturate all bars because of cava's autosens
inline static constexpr size_t PEAK_SUSTAIN_BLOCKS = 10;
inline static constexpr time_ms_t PEAK_SUSTAIN_BLOCK_MS = 100;  // window = 10 * 100 ms = 1 s
inline static constexpr double PEAK_SUSTAIN_MIN_MEAN = 0.02;
static_assert(PEAK_SUSTAIN_BLOCKS > 0);

struct peak_detector_t {
  double caps[PEAK_DETECTOR_MAX_BARS]{};  // peak cap per bar
  timestamp_ms_t start{-1};               // first frame (warm-up)
  timestamp_ms_t last_frame{0};
  timestamp_ms_t last_peak{0};
  bool has_peak{false};
  bool armed{true};
  time_ms_t below_ms{0};  // time below re-arm level (while disarmed)
  double fraction{0};     // last fraction of bars at the top (for debugging)
  // sustained sound: min. mean of the bars per block (last PEAK_SUSTAIN_BLOCKS blocks)
  double sustain_min[PEAK_SUSTAIN_BLOCKS]{};
  size_t sustain_block{0};
  time_ms_t sustain_block_ms{0};
  size_t sustain_blocks_filled{0};
};

inline void peak_detector_reset(peak_detector_t& detector) {
  detector = {};
}

// fraction of bars at their peak cap (updates the caps)
[[nodiscard]] inline double peak_detector_bars_at_top(peak_detector_t& detector, const double *bars, size_t bars_count,
                                        time_ms_t dt_ms) {
  if (bars == nullptr || bars_count == 0) {
    return 0.0;
  }
  if (bars_count > PEAK_DETECTOR_MAX_BARS) {
    bars_count = PEAK_DETECTOR_MAX_BARS;
  }
  const double fall = dt_ms > 0 ? std::exp(-static_cast<double>(dt_ms) / PEAK_CAP_FALL_TAU_MS) : 1.0;
  size_t at_top = 0;
  for (size_t i = 0; i < bars_count; i++) {
    const double v = bars[i] < 0.0 ? 0.0 : (bars[i] > 1.0 ? 1.0 : bars[i]);
    const double cap = detector.caps[i] * fall;
    detector.caps[i] = v > cap ? v : cap;
    if (v >= PEAK_BAR_MIN && v >= detector.caps[i] * PEAK_BAR_TOP_RATIO) {
      at_top++;
    }
  }
  return static_cast<double>(at_top) / static_cast<double>(bars_count);
}

enum class peak_detector_sustained_result_t : bool {
  SilentMoment = false,
  SustainDetected = true,
};
// track the mean of the bars, returns true when there was no (almost) silent moment within the last window
[[nodiscard]] inline peak_detector_sustained_result_t peak_detector_sustained(peak_detector_t& detector, const double *bars, size_t bars_count, time_ms_t dt_ms) {
  double mean = 0.0;
  if (bars != nullptr && bars_count > 0) {
    for (size_t i = 0; i < bars_count; i++) {
      mean += bars[i] < 0.0 ? 0.0 : (bars[i] > 1.0 ? 1.0 : bars[i]);
    }
    mean /= static_cast<double>(bars_count);
  }
  if (detector.sustain_blocks_filled == 0) {
    detector.sustain_min[detector.sustain_block] = mean;
    detector.sustain_blocks_filled = 1;
  }
  detector.sustain_block_ms += dt_ms > 0 ? dt_ms : 0;
  int attempts = 0;
  while (detector.sustain_block_ms >= PEAK_SUSTAIN_BLOCK_MS && attempts < static_cast<int>(PEAK_SUSTAIN_BLOCKS) * 2) {
    detector.sustain_block_ms -= PEAK_SUSTAIN_BLOCK_MS;
    detector.sustain_block = (detector.sustain_block + 1) % PEAK_SUSTAIN_BLOCKS;
    detector.sustain_min[detector.sustain_block] = mean;
    if (detector.sustain_blocks_filled < PEAK_SUSTAIN_BLOCKS) {
      detector.sustain_blocks_filled++;
    }
    attempts++;
  }
  if (mean < detector.sustain_min[detector.sustain_block]) {
    detector.sustain_min[detector.sustain_block] = mean;
  }
  for (size_t i = 0; i < detector.sustain_blocks_filled; i++) {
    if (detector.sustain_min[i] < PEAK_SUSTAIN_MIN_MEAN) {
      return peak_detector_sustained_result_t::SilentMoment;
    }
  }
  return peak_detector_sustained_result_t::SustainDetected;
}

enum class peak_detector_process_result_t : bool {
  None = false,
  Peaked = true,
};
// feed one frame of bars, returns true when a peak (most bars at the top) was reached
[[nodiscard]] inline peak_detector_process_result_t peak_detector_process(peak_detector_t& detector, const double *bars, size_t bars_count, timestamp_ms_t now, double threshold) {
  if (detector.start < 0) {
    detector.start = now;
    detector.last_frame = now;
  }
  const time_ms_t dt_ms = now - detector.last_frame;
  detector.last_frame = now;

  const double fraction = peak_detector_bars_at_top(detector, bars, bars_count, dt_ms);
  detector.fraction = fraction;
  const bool sustained = peak_detector_sustained(detector, bars, bars_count, dt_ms) == peak_detector_sustained_result_t::SustainDetected;

  if (threshold <= 0.0 || now - detector.start < PEAK_WARMUP_MS) {
    return peak_detector_process_result_t::None;
  }

  // re-arm when the peak is over
  if (!detector.armed) {
    if (fraction < threshold * PEAK_REARM_RATIO) {
      detector.below_ms += dt_ms;
      if (detector.below_ms >= PEAK_REARM_HOLD_MS) {
        detector.armed = true;
      }
    } else {
      detector.below_ms = 0;
    }
  }

  const bool cooldown_over = !detector.has_peak || now - detector.last_peak >= PEAK_COOLDOWN_MS;
  if (detector.armed && cooldown_over && sustained && fraction >= threshold) {
    detector.has_peak = true;
    detector.last_peak = now;
    detector.armed = false;
    detector.below_ms = 0;
    return peak_detector_process_result_t::Peaked;
  }
  return peak_detector_process_result_t::None;
}

}  // namespace bongocat::platform::audio::details

#endif  // BONGOCAT_AUDIO_PEAK_DETECTOR_H
