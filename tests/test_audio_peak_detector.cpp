#include "platform/audio/audio_peak_detector.h"

#include <doctest.h>

namespace {
using namespace bongocat::platform;
using namespace bongocat::platform::audio::details;

inline constexpr size_t TEST_BARS = 32;
inline constexpr timestamp_ms_t TEST_HOP_MS = 10;
inline constexpr double TEST_THRESHOLD = 0.6;  // default audio_happy_peak

struct test_signal_t {
  size_t first_bar{0};
  size_t num_bars{0};
  double level{0.0};
};

// bars pulse on every beat (jump up, then fall off), only bars in [first_bar, first_bar + num_bars) get energy
int run(peak_detector_t& detector, timestamp_ms_t& now, test_signal_t signal, double bpm, timestamp_ms_t duration_ms,
        double *max_fraction = nullptr) {
  double bars[TEST_BARS]{};
  const auto beat_ms = static_cast<timestamp_ms_t>(60000.0 / bpm);
  int peaks = 0;
  const timestamp_ms_t end = now + duration_ms;
  for (; now < end; now += TEST_HOP_MS) {
    const double env = 1.0 - 0.6 * static_cast<double>(now % beat_ms) / static_cast<double>(beat_ms);  // 1.0 -> 0.4
    for (size_t i = 0; i < TEST_BARS; i++) {
      bars[i] = (i >= signal.first_bar && i < signal.first_bar + signal.num_bars) ? signal.level * env : 0.02;
    }
    peaks +=
        peak_detector_process(detector, bars, TEST_BARS, now, TEST_THRESHOLD) == peak_detector_process_result_t::Peaked
            ? 1
            : 0;
    if (max_fraction != nullptr && detector.fraction > *max_fraction) {
      *max_fraction = detector.fraction;
    }
  }
  return peaks;
}
}  // namespace

TEST_CASE("audio peak detector") {
  const test_signal_t verse{.first_bar = 0, .num_bars = 8, .level = 0.9};         // kick + bass: few bars
  const test_signal_t drop{.first_bar = 0, .num_bars = TEST_BARS, .level = 0.9};  // wall of sound: all bars
  const test_signal_t click{.first_bar = 12, .num_bars = 3, .level = 1.0};        // metronome click: few bars

  SUBCASE("narrow-band music / metronome: no peak") {
    peak_detector_t detector{};
    timestamp_ms_t now = 0;
    CHECK(run(detector, now, verse, 120.0, 30000) == 0);
    peak_detector_reset(detector);
    now = 0;
    CHECK(run(detector, now, click, 240.0, 30000) == 0);
    peak_detector_reset(detector);
    now = 0;
    CHECK(run(detector, now, click, 60.0, 30000) == 0);
  }
  SUBCASE("most bars at the top (drop): peaks on hits, limited by cooldown") {
    peak_detector_t detector{};
    timestamp_ms_t now = 0;
    CHECK(run(detector, now, verse, 120.0, 8000) == 0);
    double max_fraction = 0.0;
    const int peaks = run(detector, now, drop, 120.0, 6000, &max_fraction);
    CHECK(peaks >= 2);
    CHECK(peaks <= 6000 / PEAK_COOLDOWN_MS + 1);
    CHECK(max_fraction >= 0.9);
  }
  SUBCASE("sparse transients with silence in between (slow metronome, autosens saturation): no peak") {
    peak_detector_t detector{};
    double bars[TEST_BARS]{};
    int peaks = 0;
    for (timestamp_ms_t now = 0; now < 20000; now += TEST_HOP_MS) {
      const bool transient = now % 1000 < 150;  // all bars saturated for 150 ms, then silence
      for (double& bar : bars) {
        bar = transient ? 1.0 : 0.0;
      }
      peaks += peak_detector_process(detector, bars, TEST_BARS, now, TEST_THRESHOLD) ==
                       peak_detector_process_result_t::Peaked
                   ? 1
                   : 0;
    }
    CHECK(peaks == 0);
  }
  SUBCASE("sustained wall of sound without dips: one peak") {
    peak_detector_t detector{};
    timestamp_ms_t now = 0;
    run(detector, now, verse, 120.0, 8000);
    double bars[TEST_BARS]{};
    int peaks = 0;
    for (const timestamp_ms_t end = now + 6000; now < end; now += TEST_HOP_MS) {
      for (double& bar : bars) {
        bar = 0.9;  // constant: always at the top, never re-armed
      }
      peaks += peak_detector_process(detector, bars, TEST_BARS, now, TEST_THRESHOLD) ==
                       peak_detector_process_result_t::Peaked
                   ? 1
                   : 0;
    }
    CHECK(peaks == 1);
  }
  SUBCASE("second drop after a quieter part: peak again") {
    peak_detector_t detector{};
    timestamp_ms_t now = 0;
    run(detector, now, verse, 120.0, 8000);
    CHECK(run(detector, now, drop, 120.0, 6000) >= 1);
    CHECK(run(detector, now, verse, 120.0, 8000) == 0);
    CHECK(run(detector, now, drop, 120.0, 6000) >= 1);
  }
  SUBCASE("no peak during warm-up (autosens settling)") {
    peak_detector_t detector{};
    timestamp_ms_t now = 0;
    CHECK(run(detector, now, drop, 120.0, PEAK_WARMUP_MS - 100) == 0);
  }
  SUBCASE("threshold 0 disables peaks") {
    peak_detector_t detector{};
    double bars[TEST_BARS]{};
    for (double& bar : bars) {
      bar = 0.9;
    }
    for (timestamp_ms_t now = 0; now < 10000; now += TEST_HOP_MS) {
      CHECK_FALSE(peak_detector_process(detector, bars, TEST_BARS, now, 0.0));
    }
  }
  SUBCASE("bars at top: fraction and noise floor") {
    peak_detector_t detector{};
    double bars[TEST_BARS]{};
    for (size_t i = 0; i < TEST_BARS; i++) {
      bars[i] = i < TEST_BARS / 2 ? 0.8 : 0.05;  // upper half is noise (below PEAK_BAR_MIN)
    }
    CHECK(peak_detector_bars_at_top(detector, bars, TEST_BARS, TEST_HOP_MS) == doctest::Approx(0.5));
    // bars fall below 90% of their cap: not at the top anymore
    for (size_t i = 0; i < TEST_BARS / 2; i++) {
      bars[i] = 0.5;
    }
    CHECK(peak_detector_bars_at_top(detector, bars, TEST_BARS, TEST_HOP_MS) == doctest::Approx(0.0));
  }
}
