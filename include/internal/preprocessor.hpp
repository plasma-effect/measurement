#pragma once

#define MEASURE_PP_CAT(a, b) MEASURE_PP_CAT_I(a, b)
#define MEASURE_PP_CAT_I(a, b) a##b

#define MEASURE_PP_CAT2(a0, a1) MEASURE_PP_CAT(a0, a1)
#define MEASURE_PP_CAT3(a0, a1, a2) MEASURE_PP_CAT2(MEASURE_PP_CAT2(a0, a1), a2)
#define MEASURE_PP_CAT4(a0, a1, a2, a3)                                        \
  MEASURE_PP_CAT2(MEASURE_PP_CAT2(a0, a1), MEASURE_PP_CAT2(a2, a3))
#define MEASURE_PP_CAT5(a0, a1, a2, a3, a4)                                    \
  MEASURE_PP_CAT3(MEASURE_PP_CAT2(a0, a1), MEASURE_PP_CAT2(a2, a3), a4)

#define MEASURE_PP_STR(s) MEASURE_PP_STR_I(s)
#define MEASURE_PP_STR_I(s) #s
