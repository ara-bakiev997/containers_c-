GCC = g++  -std=c++17 -g -Wall -Werror -Wextra
TEST = ../../tests/tests_vector.cc
GCOV =--coverage
SOURCE = ../src/sequence/vector/s21_vector.h
LIBA = tests_vector.a
LIBO = tests_vector.o


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
	rm -rf *.o *.a  *.out test *.dSYM  report coverage.info tests_vector.gcda tests_vector.gcno *.txt

s21_vector.a: clean
	$(GCC) -c $(TEST)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

gcov_report: s21_vector.a
	$(GCC) $(GCOV) $(TEST) $(LIBA) -L. $(LIBA)  $(LIBFLAGS) -o test
	./test
	lcov -t "test" -c -d  ./ --no-external --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/
	open ./report/index.html

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.h *.tpp

ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif
