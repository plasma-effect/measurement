.PHONY: default
default: simple.o

TEST_SRCS=src/measure_main.cpp src/measurement_base.cpp

simple.o: samples/simple.cpp $(TEST_SRCS)
	g++ $^ -std=c++23 -o $@ -Wall -Wextra -Iinclude/

.PHONY: clean
clean:
	rm -f *.o
