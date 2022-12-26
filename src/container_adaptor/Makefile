GCC = g++  -std=c++17 -g -Wall -Werror -Wextra
TEST = ../../tests/tests_queue.cc
GCOV =--coverage
SOURCE = ../src/sequence/list/s21_queue.h
LIBA = tests_list.a
LIBO = tests_list.o


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
	rm -rf *.o *.a  *.out test *.dSYM  report coverage.info tests_list.gcda tests_list.gcno *.txt

s21_list.a: clean
	$(GCC) -c $(TEST)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

gcov_report: s21_list.a
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
