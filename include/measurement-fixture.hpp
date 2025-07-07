#pragma once

#include "measurement-base.hpp"

#define MEASURE_F(suite_name, name)                                            \
  MEASURE_CONSTRUCT(suite_name, name, MEASURE_SUITE_NAME(suite_name, name),    \
                    suite_name)
