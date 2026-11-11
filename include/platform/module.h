#ifndef BONGOCAT_BASE_MODULE_H
#define BONGOCAT_BASE_MODULE_H

#define BONGOCAT_PP_CAT_(a, b) a##b
#define BONGOCAT_PP_CAT(a, b)  BONGOCAT_PP_CAT_(a, b)

#define BONGOCAT_STUB_INLINE_1
#define BONGOCAT_STUB_INLINE_0        inline
#define BONGOCAT_STUB_INLINE(enabled) BONGOCAT_PP_CAT(BONGOCAT_STUB_INLINE_, enabled)

#define BONGOCAT_STUB_BODY_1
#define BONGOCAT_STUB_BODY_0 \
  {}                         \
  static_assert(true, "dummy assert allow semicolon")
#define BONGOCAT_STUB_BODY(enabled) BONGOCAT_PP_CAT(BONGOCAT_STUB_BODY_, enabled)

#define BONGOCAT_STUB_RETURN_1(...)
#define BONGOCAT_STUB_RETURN_0(...) \
  { return __VA_ARGS__; }           \
  static_assert(true, "dummy assert allow semicolon")
#define BONGOCAT_STUB_RETURN(enabled, ...) BONGOCAT_PP_CAT(BONGOCAT_STUB_RETURN_, enabled)(__VA_ARGS__)

#define BONGOCAT_STUBS_BEGIN _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
#define BONGOCAT_STUBS_END   _Pragma("GCC diagnostic pop")

#endif