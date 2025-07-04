#pragma once

#define MEASURE_DUMMY(value) asm volatile("" : : "r"(value) :)
