#ifndef BONGOCAT_AUDIO_BEAT_DETECTOR_H
#define BONGOCAT_AUDIO_BEAT_DETECTOR_H

#include "utils/time.h"

#include <cassert>
#include <cstddef>
#include <cstdint>

namespace bongocat::platform::audio::details {

inline static constexpr int MAX_ATTEMPTS = 4096;

inline static constexpr double MIN_BPM = 40.0;              // slower gets doubled (half time)
inline static constexpr double MAX_BPM = 300.0;             // faster gets halved (double time)
static_assert(MAX_BPM >= MIN_BPM);

inline static constexpr size_t BEAT_DETECTOR_MAX_BARS = 64;
inline static constexpr size_t BEAT_DETECTOR_ONSET_HISTORY = 16;


inline static constexpr double ONSET_FLUX_FACTOR = 1.5;           // flux must exceed avg * factor ...
inline static constexpr double ONSET_MIN_FLUX = 0.005;
inline static constexpr double ONSET_FLUX_AVG_EMA_ALPHA = 0.1;    // adaptive threshold (slow average)
inline static constexpr time_ms_t ONSET_MIN_INTERVAL_MS = 200;    // refractory time, max. 300 BPM
inline static constexpr time_ms_t ONSET_MAX_INTERVAL_MS = 2000;   // min. 30 BPM (folded into range)
inline static constexpr size_t MIN_INTERVALS_FOR_BPM = 3;         // 4 onsets: fast first estimate (refined with every onset)
inline static constexpr double BPM_MEDIAN_TOLERANCE = 0.1;        // intervals within +-10% of the median are averaged
// off-beat check: for fast tempos, if every other onset is much weaker (e.g. off-beat hi-hats between kicks),
// the weaker onsets are off-beats -> half tempo
inline static constexpr double ACCENT_CHECK_MIN_BPM = 150.0;
inline static constexpr double ACCENT_WEAK_RATIO = 0.6;           // weak group strength < 60% of strong group
inline static constexpr size_t ACCENT_CHECK_MIN_ONSETS = 6;
inline static constexpr double ACCENT_REGULAR_TOLERANCE = 0.25;   // intervals within +-25% of the beat interval

// Bar normalizer (gain independent beat detection): bars / max of the bars in the last BAR_NORM_WINDOW_MS.
// cava's autosens rises slowly after loud audio (quiet audio stays almost invisible for many seconds),
// the windowed max adapts after BAR_NORM_WINDOW_MS; window > longest beat interval (no amplified gaps between beats)
inline static constexpr size_t BAR_NORM_MAX_BARS = 64;
inline static constexpr size_t BAR_NORM_BLOCKS = 20;
inline static constexpr double BAR_NORM_BLOCK_MS = 100.0;  // window = 20 * 100 ms = 2 s
inline static constexpr double BAR_NORM_FLOOR = 0.02;      // don't amplify (almost) empty bars/noise
static_assert(BAR_NORM_BLOCKS > 0);


struct beat_detector_t {
  double prev_bars[BEAT_DETECTOR_MAX_BARS]{};
  bool has_prev{false};
  double flux{0};      // last onset strength (for debugging)
  double flux_avg{0};  // adaptive threshold base
  timestamp_ms_t onsets[BEAT_DETECTOR_ONSET_HISTORY]{};
  double onset_strengths[BEAT_DETECTOR_ONSET_HISTORY]{};  // peak flux of each onset
  size_t onsets_head{0};
  size_t onsets_count{0};
  double bpm{0};            // 0 = unknown
};

inline void beat_detector_reset(beat_detector_t& detector) {
  detector = {};
}

BONGOCAT_NODISCARD inline timestamp_ms_t beat_detector_last_onset(const beat_detector_t& detector) {
  if (detector.onsets_count == 0) {
    return 0;
  }
  return detector.onsets[(detector.onsets_head + BEAT_DETECTOR_ONSET_HISTORY - 1) % BEAT_DETECTOR_ONSET_HISTORY];
}

// median interval between recent onsets -> BPM (folded into MIN_BPM..MAX_BPM); 0 = unknown
BONGOCAT_NODISCARD inline double beat_detector_estimate_bpm(const beat_detector_t& detector) {
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

  // off-beat check (fast tempo): compare strength of every other onset (newest onset excluded, still rising)
  if (bpm >= ACCENT_CHECK_MIN_BPM && detector.onsets_count >= ACCENT_CHECK_MIN_ONSETS + 1) {
    const size_t count = detector.onsets_count - 1;
    // use the most recent regular run of onsets (consistent parity)
    double group_sum[2]{0.0, 0.0};
    size_t group_n[2]{0, 0};
    size_t parity = 0;
    for (size_t k = 0; k < count; k++) {
      // walk backwards from the second newest onset
      const size_t idx = (detector.onsets_head + 2 * BEAT_DETECTOR_ONSET_HISTORY - 2 - k) % BEAT_DETECTOR_ONSET_HISTORY;
      if (k > 0) {
        const size_t newer_idx = (idx + 1) % BEAT_DETECTOR_ONSET_HISTORY;
        const auto delta = static_cast<double>(detector.onsets[newer_idx] - detector.onsets[idx]);
        if (delta < beat_interval * (1.0 - ACCENT_REGULAR_TOLERANCE) ||
            delta > beat_interval * (1.0 + ACCENT_REGULAR_TOLERANCE)) {
          break;  // irregular (missed onset): stop, parity would be wrong
        }
      }
      group_sum[parity] += detector.onset_strengths[idx];
      group_n[parity]++;
      parity ^= 1u;
    }
    if (group_n[0] + group_n[1] >= ACCENT_CHECK_MIN_ONSETS && group_n[0] > 0 && group_n[1] > 0) {
      const double a = group_sum[0] / static_cast<double>(group_n[0]);
      const double b = group_sum[1] / static_cast<double>(group_n[1]);
      const double strong = a > b ? a : b;
      const double weak = a > b ? b : a;
      if (strong > 0.0 && weak < strong * ACCENT_WEAK_RATIO && bpm / 2.0 >= MIN_BPM) {
        bpm /= 2.0;  // weak onsets are off-beats
      }
    }
  }
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
BONGOCAT_NODISCARD inline beat_detector_process_t beat_detector_process(beat_detector_t& detector, const double *bars, size_t bars_count,
                                                     timestamp_ms_t now) {
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
  const bool onset = flux > threshold && (detector.onsets_count == 0 || now - last_onset >= ONSET_MIN_INTERVAL_MS);
  detector.flux_avg = (1.0 - ONSET_FLUX_AVG_EMA_ALPHA) * detector.flux_avg + ONSET_FLUX_AVG_EMA_ALPHA * flux;

  if (!onset && detector.onsets_count > 0 && now - last_onset < ONSET_MIN_INTERVAL_MS) {
    // track peak strength of the last onset (flux keeps rising for a few frames)
    const size_t last_idx = (detector.onsets_head + BEAT_DETECTOR_ONSET_HISTORY - 1) % BEAT_DETECTOR_ONSET_HISTORY;
    if (flux > detector.onset_strengths[last_idx]) {
      detector.onset_strengths[last_idx] = flux;
    }
  }

  if (onset) {
    // forget old beats after a long pause (tempo may have changed)
    if (detector.onsets_count > 0 && now - last_onset > ONSET_MAX_INTERVAL_MS * 2) {
      detector.onsets_head = 0;
      detector.onsets_count = 0;
    }
    detector.onsets[detector.onsets_head] = now;
    detector.onset_strengths[detector.onsets_head] = flux;
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

struct bar_normalizer_t {
  double block_max[BAR_NORM_BLOCKS]{};
  size_t block{0};
  double block_ms{0};
  double bars[BAR_NORM_MAX_BARS]{};  // normalized bars (output)
};

inline void bar_normalizer_reset(bar_normalizer_t& normalizer) {
  normalizer = {};
}

// normalized bars (0..1)
inline const double *bar_normalizer_process(bar_normalizer_t& normalizer, const double *bars, size_t bars_count,
                                            double dt_ms) {
  if (bars_count > BAR_NORM_MAX_BARS) {
    bars_count = BAR_NORM_MAX_BARS;
  }
  // next block
  normalizer.block_ms += dt_ms;
  int attempts = 0;
  while (normalizer.block_ms >= BAR_NORM_BLOCK_MS && attempts < MAX_ATTEMPTS) {
    normalizer.block_ms -= BAR_NORM_BLOCK_MS;
    normalizer.block = (normalizer.block + 1) % BAR_NORM_BLOCKS;
    normalizer.block_max[normalizer.block] = 0.0;
    attempts++;
  }
  double frame_max = 0.0;
  for (size_t i = 0; i < bars_count; i++) {
    frame_max = bars[i] > frame_max ? bars[i] : frame_max;
  }
  if (frame_max > normalizer.block_max[normalizer.block]) {
    normalizer.block_max[normalizer.block] = frame_max;
  }
  double norm = BAR_NORM_FLOOR;
  for (const double m : normalizer.block_max) {
    norm = m > norm ? m : norm;
  }
  for (size_t i = 0; i < bars_count; i++) {
    const double v = bars[i] / norm;
    normalizer.bars[i] = v < 0.0 ? 0.0 : (v > 1.0 ? 1.0 : v);
  }
  return normalizer.bars;
}

}  // namespace bongocat::platform::audio::details

#endif
