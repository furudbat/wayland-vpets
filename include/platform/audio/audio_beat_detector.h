#ifndef BONGOCAT_AUDIO_BEAT_DETECTOR_H
#define BONGOCAT_AUDIO_BEAT_DETECTOR_H

#include "utils/time.h"

#include <cstddef>
#include <cstdint>

namespace bongocat::platform::audio::details {

// Beat (onset) detection + BPM estimation on spectrum bars (e.g. cavacore output, normalized 0..1).
// for testing

inline static constexpr int MAX_ATTEMPTS = 4096;

inline static constexpr size_t BEAT_DETECTOR_MAX_BARS = 64;
inline static constexpr size_t BEAT_DETECTOR_ONSET_HISTORY = 16;

inline static constexpr double ONSET_FLUX_FACTOR = 1.5;           // flux must exceed avg * factor ...
inline static constexpr double ONSET_MIN_FLUX = 0.005;
inline static constexpr double ONSET_FLUX_AVG_EMA_ALPHA = 0.1;    // adaptive threshold (slow average)
inline static constexpr time_ms_t ONSET_MIN_INTERVAL_MS = 300;    // refractory time, max. 200 BPM
inline static constexpr time_ms_t ONSET_MAX_INTERVAL_MS = 2000;   // min. 30 BPM (folded into range)
inline static constexpr size_t MIN_INTERVALS_FOR_BPM = 4;
inline static constexpr double BPM_MEDIAN_TOLERANCE = 0.1;        // intervals within +-10% of the median are averaged
inline static constexpr double MIN_BPM = 40.0;                    // slower gets doubled (half time)
inline static constexpr double MAX_BPM = 200.0;
static_assert(MAX_BPM >= MIN_BPM);

struct beat_detector_t {
  double prev_bars[BEAT_DETECTOR_MAX_BARS]{};
  bool has_prev{false};
  double flux{0};      // last onset strength (for debugging)
  double flux_avg{0};  // adaptive threshold base
  timestamp_ms_t onsets[BEAT_DETECTOR_ONSET_HISTORY]{};
  size_t onsets_head{0};
  size_t onsets_count{0};
  double bpm{0};          // 0 = unknown
};

inline void beat_detector_reset(beat_detector_t& detector) {
  detector = {};
}

inline timestamp_ms_t beat_detector_last_onset(const beat_detector_t& detector) {
  if (detector.onsets_count == 0) {
    return 0;
  }
  return detector.onsets[(detector.onsets_head + BEAT_DETECTOR_ONSET_HISTORY - 1) % BEAT_DETECTOR_ONSET_HISTORY];
}

// median interval between recent onsets -> BPM (folded into MIN_BPM..MAX_BPM); 0 = unknown
inline double beat_detector_estimate_bpm(const beat_detector_t& detector) {
  if (detector.onsets_count < MIN_INTERVALS_FOR_BPM + 1) {
    return 0.0;
  }
  // collect intervals between consecutive onsets (oldest -> newest)
  time_ms_t intervals[BEAT_DETECTOR_ONSET_HISTORY]{};
  size_t n = 0;
  const size_t start =
      (detector.onsets_head + BEAT_DETECTOR_ONSET_HISTORY - detector.onsets_count) % BEAT_DETECTOR_ONSET_HISTORY;
  for (size_t i = 1; i < detector.onsets_count; i++) {
    const timestamp_ms_t prev = detector.onsets[(start + i - 1) % BEAT_DETECTOR_ONSET_HISTORY];
    const timestamp_ms_t cur = detector.onsets[(start + i) % BEAT_DETECTOR_ONSET_HISTORY];
    const time_ms_t delta = cur - prev;
    if (delta >= ONSET_MIN_INTERVAL_MS && delta <= ONSET_MAX_INTERVAL_MS) {
      intervals[n++] = delta;
    }
  }
  if (n < MIN_INTERVALS_FOR_BPM) {
    return 0.0;
  }
  // median (insertion sort, n <= 16)
  for (size_t i = 1; i < n; i++) {
    const time_ms_t key = intervals[i];
    size_t j = i;
    while (j > 0 && intervals[j - 1] > key) {
      intervals[j] = intervals[j - 1];
      j--;
    }
    intervals[j] = key;
  }
  const auto median = static_cast<double>(intervals[n / 2]);
  if (median <= 0) {
    return 0.0;
  }
  // average intervals close to the median
  double sum = 0.0;
  size_t used = 0;
  for (size_t i = 0; i < n; i++) {
    const auto interval = static_cast<double>(intervals[i]);
    if (interval >= median * (1.0 - BPM_MEDIAN_TOLERANCE) && interval <= median * (1.0 + BPM_MEDIAN_TOLERANCE)) {
      sum += interval;
      used++;
    }
  }
  const double beat_interval = used > 0 ? sum / static_cast<double>(used) : median;
  constexpr double bpm_lower_limit = 60000.0;
  assert(beat_interval > 0);
  double bpm = bpm_lower_limit / beat_interval;
  // fold into range
  {
    int attempts = 0;
    while (bpm < MIN_BPM && attempts < MAX_ATTEMPTS) {
      bpm *= 2.0;
      attempts++;
    }
  }
  {
    int attempts = 0;
    while (bpm > MAX_BPM && attempts < MAX_ATTEMPTS) {
      bpm /= 2.0;
      attempts++;
    }
  }
  return bpm;
}

// feed one frame of bars (values are clamped to 0..1)
enum class beat_detector_process_t : bool {
  None = false,
  OnSetDetected = true,
};
inline beat_detector_process_t beat_detector_process(beat_detector_t& detector, const double *bars, size_t bars_count, timestamp_ms_t now) {
  if (bars == nullptr || bars_count == 0) {
    return beat_detector_process_t::None;
  }
  if (bars_count > BEAT_DETECTOR_MAX_BARS) {
    bars_count = BEAT_DETECTOR_MAX_BARS;
  }

  // spectral flux: average positive change of all bars
  double flux = 0.0;
  for (size_t i = 0; i < bars_count; i++) {
    const double v = bars[i] < 0.0 ? 0.0 : (bars[i] > 1.0 ? 1.0 : bars[i]);
    if (detector.has_prev) {
      const double diff = v - detector.prev_bars[i];
      if (diff > 0.0) {
        flux += diff;
      }
    }
    detector.prev_bars[i] = v;
  }
  flux /= static_cast<double>(bars_count);
  const bool first_frame = !detector.has_prev;
  detector.has_prev = true;
  detector.flux = flux;
  if (first_frame) {
    return beat_detector_process_t::None;
  }

  // adaptive threshold
  const double threshold = detector.flux_avg * ONSET_FLUX_FACTOR + ONSET_MIN_FLUX;
  const timestamp_ms_t last_onset = beat_detector_last_onset(detector);
  const bool onset =
      flux > threshold && (detector.onsets_count == 0 || now - last_onset >= ONSET_MIN_INTERVAL_MS);
  detector.flux_avg = (1.0 - ONSET_FLUX_AVG_EMA_ALPHA) * detector.flux_avg + ONSET_FLUX_AVG_EMA_ALPHA * flux;

  if (onset) {
    // forget old beats after a long pause (tempo may have changed)
    if (detector.onsets_count > 0 && now - last_onset > ONSET_MAX_INTERVAL_MS * 2) {
      detector.onsets_head = 0;
      detector.onsets_count = 0;
    }
    detector.onsets[detector.onsets_head] = now;
    static_assert(BEAT_DETECTOR_ONSET_HISTORY > 0);
    detector.onsets_head = (detector.onsets_head + 1) % BEAT_DETECTOR_ONSET_HISTORY;
    if (detector.onsets_count < BEAT_DETECTOR_ONSET_HISTORY) {
      detector.onsets_count++;
    }
    const double bpm = beat_detector_estimate_bpm(detector);
    if (bpm > 0.0) {
      detector.bpm = bpm;
    }
  }

  return onset ? beat_detector_process_t::OnSetDetected : beat_detector_process_t::None;
}

}

#endif
