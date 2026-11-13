#include "platform/audio/audio_beat_detector.h"

#include <doctest/doctest.h>

namespace {
using namespace bongocat::platform;
using namespace bongocat::platform::audio::details;
using namespace bongocat::platform::audio::details;

inline constexpr size_t TEST_BARS = 32;
inline constexpr timestamp_ms_t TEST_FRAME_MS = 21;  // ~48 fps, like the audio thread

// simulate kick (strong, bass bars) on the beat + hi-hat (weak, high bars) on the off-beat
double run_beats_with_offbeat(double bpm, double offbeat_strength, timestamp_ms_t duration_ms) {
  beat_detector_t detector{};
  double bars[TEST_BARS]{};
  const double beat_interval_ms = 60000.0 / bpm;
  double next_beat_ms = 500.0;
  double next_offbeat_ms = 500.0 + beat_interval_ms / 2.0;
  for (timestamp_ms_t now = 0; now < duration_ms; now += TEST_FRAME_MS) {
    for (double& bar : bars) {
      bar *= 0.6;  // falloff
    }
    if (static_cast<double>(now) >= next_beat_ms) {
      for (size_t i = 0; i < 6; i++) {
        bars[i] = 0.9;
      }
      next_beat_ms += beat_interval_ms;
    }
    if (static_cast<double>(now) >= next_offbeat_ms) {
      for (size_t i = TEST_BARS - 6; i < TEST_BARS; i++) {
        bars[i] = 0.9 * offbeat_strength;
      }
      next_offbeat_ms += beat_interval_ms;
    }
    beat_detector_process(detector, bars, TEST_BARS, now);
  }
  return detector.bpm;
}

// simulate cavacore-like bars: on each beat a few bars jump up, then fall off smoothly
// (a metronome click only hits some mid/high bars, no bass)
double run_beats(double bpm, size_t first_bar, size_t num_bars, timestamp_ms_t duration_ms) {
  beat_detector_t detector{};
  double bars[TEST_BARS]{};
  const double beat_interval_ms = 60000.0 / bpm;
  double next_beat_ms = 500.0;
  for (timestamp_ms_t now = 0; now < duration_ms; now += TEST_FRAME_MS) {
    for (double& bar : bars) {
      bar *= 0.75;  // falloff
    }
    if (static_cast<double>(now) >= next_beat_ms) {
      for (size_t i = first_bar; i < first_bar + num_bars && i < TEST_BARS; i++) {
        bars[i] = 0.9;
      }
      next_beat_ms += beat_interval_ms;
    }
    beat_detector_process(detector, bars, TEST_BARS, now);
  }
  return detector.bpm;
}
}  // namespace

TEST_CASE("audio beat detector") {
  SUBCASE("metronome click without bass") {
    // mid/high bars only, bass-based detection would never trigger here
    CHECK(run_beats(60.0, 8, 3, 15000) == doctest::Approx(60.0).epsilon(0.03));
    CHECK(run_beats(120.0, 8, 3, 15000) == doctest::Approx(120.0).epsilon(0.03));
    CHECK(run_beats(174.0, 8, 3, 15000) == doctest::Approx(174.0).epsilon(0.03));
  }
  SUBCASE("fast tempo (> 200 BPM)") {
    CHECK(run_beats(220.0, 8, 3, 15000) == doctest::Approx(220.0).epsilon(0.04));
    CHECK(run_beats(240.0, 8, 3, 15000) == doctest::Approx(240.0).epsilon(0.04));
  }
  SUBCASE("weak off-beats (hi-hat) are not counted as beats") {
    // 120 BPM kick + weak off-beat hi-hat would look like 240 BPM without the off-beat check
    CHECK(run_beats_with_offbeat(120.0, 0.3, 15000) == doctest::Approx(120.0).epsilon(0.04));
    CHECK(run_beats_with_offbeat(140.0, 0.3, 15000) == doctest::Approx(140.0).epsilon(0.04));
  }
  SUBCASE("equally strong off-beats: double time is kept") {
    CHECK(run_beats_with_offbeat(120.0, 1.0, 15000) == doctest::Approx(240.0).epsilon(0.04));
  }
  SUBCASE("kick drum (bass bars)") {
    CHECK(run_beats(90.0, 0, 2, 15000) == doctest::Approx(90.0).epsilon(0.03));
    CHECK(run_beats(128.0, 0, 2, 15000) == doctest::Approx(128.0).epsilon(0.03));
  }
  SUBCASE("slow tempo is not folded near the range boundary") {
    // 60 BPM with frame jitter (e.g. 59.8) must not be doubled to ~120
    CHECK(run_beats(59.5, 8, 3, 20000) == doctest::Approx(59.5).epsilon(0.03));
  }
  SUBCASE("silence/constant signal: no beats, unknown bpm") {
    beat_detector_t detector{};
    double bars[TEST_BARS]{};
    for (double& bar : bars) {
      bar = 0.5;
    }
    int onsets = 0;
    for (timestamp_ms_t now = 0; now < 10000; now += TEST_FRAME_MS) {
      onsets += beat_detector_process(detector, bars, TEST_BARS, now) == beat_detector_process_t::OnSetDetected ? 1 : 0;
    }
    CHECK(onsets == 0);
    CHECK(detector.bpm == doctest::Approx(0.0));
  }
  SUBCASE("too few beats: bpm unknown") {
    CHECK(run_beats(120.0, 8, 3, 2000) == doctest::Approx(0.0));
  }
  SUBCASE("reset") {
    beat_detector_t detector{};
    detector.bpm = 120.0;
    detector.onsets_count = 5;
    beat_detector_reset(detector);
    CHECK(detector.bpm == doctest::Approx(0.0));
    CHECK(detector.onsets_count == 0);
  }
}

TEST_CASE("bar normalizer") {
  SUBCASE("quiet bars are scaled up to the recent max") {
    bar_normalizer_t normalizer{};
    double bars[TEST_BARS]{};
    bars[3] = 0.1;
    bars[4] = 0.05;
    const double *out = bar_normalizer_process(normalizer, bars, TEST_BARS, 10.0);
    CHECK(out[3] == doctest::Approx(1.0));
    CHECK(out[4] == doctest::Approx(0.5));
    CHECK(out[0] == doctest::Approx(0.0));
  }
  SUBCASE("adapts to quiet audio after loud audio within the window") {
    bar_normalizer_t normalizer{};
    double bars[TEST_BARS]{};
    for (double& bar : bars) {
      bar = 1.0;
    }
    for (int i = 0; i < 300; i++) {
      bar_normalizer_process(normalizer, bars, TEST_BARS, 10.0);  // 3 s loud
    }
    for (double& bar : bars) {
      bar = 0.05;
    }
    const double *out = bar_normalizer_process(normalizer, bars, TEST_BARS, 10.0);
    CHECK(out[0] == doctest::Approx(0.05));  // still loud max (window)
    for (int i = 0; i < 210; i++) {
      out = bar_normalizer_process(normalizer, bars, TEST_BARS, 10.0);  // > 2 s quiet
    }
    CHECK(out[0] == doctest::Approx(1.0));
  }
  SUBCASE("noise floor: (almost) empty bars are not amplified") {
    bar_normalizer_t normalizer{};
    double bars[TEST_BARS]{};
    bars[0] = 0.001;
    const double *out = bar_normalizer_process(normalizer, bars, TEST_BARS, 10.0);
    CHECK(out[0] == doctest::Approx(0.001 / BAR_NORM_FLOOR));
  }
  SUBCASE("quiet metronome after loud audio: beats detected again") {
    beat_detector_t detector{};
    bar_normalizer_t normalizer{};
    double bars[TEST_BARS]{};
    const double beat_interval_ms = 500.0;  // 120 BPM
    double next_beat_ms = 0.0;
    int quiet_onsets = 0;
    for (timestamp_ms_t now = 0; now < 12000; now += TEST_FRAME_MS) {
      const bool loud = now < 4000;
      for (double& bar : bars) {
        bar *= 0.75;
      }
      if (static_cast<double>(now) >= next_beat_ms) {
        for (size_t i = 0; i < TEST_BARS; i++) {
          bars[i] = loud ? 1.0 : (i >= 8 && i < 11 ? 0.01 : bars[i]);  // ~-40 dB click (low cava gain)
        }
        next_beat_ms += beat_interval_ms;
      }
      const double *out = bar_normalizer_process(normalizer, bars, TEST_BARS, static_cast<double>(TEST_FRAME_MS));
      if (beat_detector_process(detector, out, TEST_BARS, now) == beat_detector_process_t::OnSetDetected && !loud) {
        quiet_onsets++;
      }
    }
    // 16 clicks in the quiet part, ~2 s window to adapt
    CHECK(quiet_onsets >= 10);
    CHECK(detector.bpm == doctest::Approx(120.0).epsilon(0.03));
  }
}
