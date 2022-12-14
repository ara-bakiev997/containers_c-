GCC =  g++ -g #-Wall -Werror -Wextra
TEST = ../../../tests/tests_list.cc
GCOV =--coverage

OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lstdc++
else
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest`
endif

all:
	clear
	$(GCC) $(TEST) $(LIBFLAGS)  -o test
	./test


clean:
	rm -rf *.o *.a  *.out test *.dSYM

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.h *.tpp

ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif
