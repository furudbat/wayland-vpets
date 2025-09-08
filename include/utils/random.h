#ifndef BONGOCAT_RANDOM_H_
#define BONGOCAT_RANDOM_H_

#include <cstdint>
#include <limits>

namespace bongocat::platform {

/*  Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */
// class based on https://www.etlcpp.com/random.html
class random_xoshiro128 {
public:
  //***************************************************************************
  /// Default constructor.
  /// Attempts to come up with a unique non-zero seed.
  //***************************************************************************
  random_xoshiro128() {
    // An attempt to come up with a unique non-zero seed,
    // based on the address of the instance.
    const auto n = reinterpret_cast<uintptr_t>(this);
    const auto seed = static_cast<uint32_t>(n);
    initialise(seed);
  }
  ~random_xoshiro128() = default;

  constexpr random_xoshiro128(const random_xoshiro128& other) {
    for (size_t i = 0; i < 4; ++i) {
      state[i] = other.state[i];
    }
  }
  constexpr random_xoshiro128& operator=(const random_xoshiro128& other) {
    if (this != &other) {
      for (size_t i = 0; i < 4; ++i) {
        state[i] = other.state[i];
      }
    }
    return *this;
  }

  constexpr random_xoshiro128(random_xoshiro128&& other) noexcept {
    for (size_t i = 0; i < 4; ++i) {
      state[i] = other.state[i];
      other.state[i] = 0;
    }
  }
  constexpr random_xoshiro128& operator=(random_xoshiro128&& other) noexcept {
    if (this != &other) {
      for (size_t i = 0; i < 4; ++i) {
        state[i] = other.state[i];
        other.state[i] = 0;
      }
    }
    return *this;
  }

  //***************************************************************************
  /// Constructor with seed value.
  ///\param seed The new seed value.
  //***************************************************************************
  constexpr explicit random_xoshiro128(uint32_t seed) { initialise(seed); }

  //***************************************************************************
  /// Initialises the sequence with a new seed value.
  ///\param seed The new seed value.
  //***************************************************************************
  constexpr void initialise(uint32_t seed) {
    // Add the first four primes to ensure that the seed isn't zero.
    state[0] = seed + 3;
    state[1] = seed + 5;
    state[2] = seed + 7;
    state[3] = seed + 11;
  }

  //***************************************************************************
  /// Get the next random_xoshiro128 number.
  //***************************************************************************
  [[nodiscard]] constexpr uint32_t operator()() { return next(); }

  //***************************************************************************
  /// Get the next random_xoshiro128 number in a specified inclusive range.
  //***************************************************************************
  [[nodiscard]] constexpr uint32_t range(uint32_t low, uint32_t high) {
    const uint32_t r = high - low + 1;
    return (operator()() % r) + low;
  }

  [[nodiscard]] constexpr inline uint32_t range_max() {
    return range(std::numeric_limits<uint32_t>::min(), std::numeric_limits<uint32_t>::max());
  }

  [[nodiscard]] constexpr inline uint32_t range_min(uint32_t min) { return range(min, std::numeric_limits<uint32_t>::max()); }

private:
  uint32_t state[4]{};

  /* This is xoshiro128** 1.1, one of our 32-bit all-purpose, rock-solid
     generators. It has excellent speed, a state size (128 bits) that is
     large enough for mild parallelism, and it passes all tests we are aware
     of.

     Note that version 1.0 had mistakenly s[0] instead of s[1] as state
     word passed to the scrambler.

     For generating just single-precision (i.e., 32-bit) floating-point
     numbers, xoshiro128+ is even faster.

     The state must be seeded so that it is not everywhere zero. */

  static inline constexpr uint32_t rotl(const uint32_t x, int k) { return (x << k) | (x >> (32 - k)); }

  constexpr uint32_t next() {
    const uint32_t result = rotl(state[1] * 5, 7) * 9;

    const uint32_t t = state[1] << 9U;

    state[2] ^= state[0];
    state[3] ^= state[1];
    state[1] ^= state[2];
    state[0] ^= state[3];

    state[2] ^= t;

    state[3] = rotl(state[3], 11);

    return result;
  }


  /* This is the jump function for the generator. It is equivalent
    to 2^64 calls to next(); it can be used to generate 2^64
    non-overlapping subsequences for parallel computations. */
  /*
  constexpr void jump() {
    constexpr uint32_t JUMP[] = {0x8764000b, 0xf542d2d3, 0x6fa035c3, 0x77f2db5b};

    uint32_t s0 = 0;
    uint32_t s1 = 0;
    uint32_t s2 = 0;
    uint32_t s3 = 0;
    for (size_t i = 0; i < sizeof JUMP / sizeof *JUMP; i++) {
      for (size_t b = 0; b < 32; b++) {
        if (JUMP[i] & UINT32_C(1) << b) {
          s0 ^= state[0];
          s1 ^= state[1];
          s2 ^= state[2];
          s3 ^= state[3];
        }
        next();
      }
    }

    state[0] = s0;
    state[1] = s1;
    state[2] = s2;
    state[3] = s3;
  }
  */


  /* This is the long-jump function for the generator. It is equivalent to
    2^96 calls to next(); it can be used to generate 2^32 starting points,
    from each of which jump() will generate 2^32 non-overlapping
    subsequences for parallel distributed computations. */
  /*
  constexpr void long_jump() {
    constexpr uint32_t LONG_JUMP[] = {0xb523952e, 0x0b6f099f, 0xccf5a0ef, 0x1c580662};

    uint32_t s0 = 0;
    uint32_t s1 = 0;
    uint32_t s2 = 0;
    uint32_t s3 = 0;
    for (size_t i = 0; i < sizeof LONG_JUMP / sizeof *LONG_JUMP; i++) {
      for (size_t b = 0; b < 32; b++) {
        if (LONG_JUMP[i] & UINT32_C(1) << b) {
          s0 ^= state[0];
          s1 ^= state[1];
          s2 ^= state[2];
          s3 ^= state[3];
        }
        next();
      }
    }

    state[0] = s0;
    state[1] = s1;
    state[2] = s2;
    state[3] = s3;
  }
  */
};

}

#endif