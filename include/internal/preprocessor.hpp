#pragma once

#define MEASURE_PP_CAT(a, b) MEASURE_PP_CAT_I(a, b)
#define MEASURE_PP_CAT_I(a, b) a##b

#define MEASURE_PP_STR(s) MEASURE_PP_STR_I(s)
#define MEASURE_PP_STR_I(s) #s
