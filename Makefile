.PHONY: default
default: main.o

TEST_SRCS=src/measure_main.cpp src/measurement_base.cpp

main.o: samples/*.cpp $(TEST_SRCS)
	g++ $^ -std=c++23 -o $@ -Wall -Wextra -Iinclude/

simple.o: samples/simple.cpp $(TEST_SRCS)
	g++ $^ -std=c++23 -o $@ -Wall -Wextra -Iinclude/

fixture.o: samples/fixture.cpp $(TEST_SRCS)
	g++ $^ -std=c++23 -o $@ -Wall -Wextra -Iinclude/

typed.o: samples/typed.cpp $(TEST_SRCS)
	g++ $^ -std=c++23 -o $@ -Wall -Wextra -Iinclude/

.PHONY: clean
clean:
	rm -f *.o
