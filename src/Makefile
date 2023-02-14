GCC = g++ -std=c++17 -g -Wall -Werror -Wextra
TEST = tests/*.cc
GCOV =--coverage
SOURCE = /sequence/vector/s21_list.h
LIBA = tests.a
LIBO = tests.o


OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lstdc++ -lgtest_main
else
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest -lgtest_main`
endif

all:
	clear
	$(GCC) $(TEST) $(LIBFLAGS)  -o test
	./test

clean:
	rm -rf *.o *.a  *.out test *.dSYM  report coverage.info *.gcda *.gcno *.txt

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
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config sequence/*.h
	clang-format -n container_adaptor/*.h sequence/*.h sorted_container/*.h tests/*.cc *.h

ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif
