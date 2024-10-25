CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
CHECKFL=-lcheck -lpthread
GCFLAGS=-fprofile-arcs -ftest-coverage
SRC=$(wildcard functions/*.c)
ADDSRS=$(wildcard addfunc/*.c)
FRONT=$(wildcard frontend/*.cpp)
TESTS=$(wildcard tests/*.c)
OBJ=$(SRC:.c=.o)
TEST_OBJ=$(TESTS:.c=.o)

ifeq ($(shell uname -s), Linux)
  CHECKFL += -lrt -lsubunit -lm
  OPEN_CMD=xdg-open
endif
ifeq ($(shell uname -s), Darwin)
	LDFLAGS = -lcheck -lm
	OPEN_CM = open
endif

all: clean s21_smartcalc.a

s21_smartcalc.a: $(OBJ)
	ar cr $@ $?

%.o: %.c
	$(CC) $(FLAGS) -c $? -o $@

install: uninstall
	mkdir build
	cmake -B build
	cmake --build build

uninstall: 
	rm -rf build	

launch:  
	build/SmartCalculator

clang:
	clang-format -style=Google -n $(SRC) $(TESTS) $(ADDSRS) $(FRONT)

clang_edit:
	clang-format -style=Google -i $(SRC) $(TESTS) $(ADDSRS) $(FRONT)

dvi: dvi/readme.html
	chmod +x $<
	$(OPEN_CMD) $<

dvi/readme.html:

dist: clean
	mkdir dist_smartcalc/
	cp -R functions/ dvi/ addfunc/ frontend/ Makefile s21_smart_calc.h CMakeLists.txt.user CMakeLists.txt dist_smartcalc/
	tar -czvf s21_smartcalc.tgz dist_smartcalc/
	rm -rf dist_smartcalc/

test: clean
	$(CC) $(FLAGS) $(SRC) $(TESTS) -o test_cases $(CHECKFL) $(GCFLAGS)
	./test_cases
	mkdir -p coverage_data
	mv *.gcda *.gcno coverage_data

gcov_report: test
	lcov --capture --directory coverage_data/ --output-file coverage.info --rc lcov_branch_coverage=1
	genhtml coverage.info --output-directory html_report --title "Coverage Report" --num-spaces 4 --legend

check_memory_leaks: test
	valgrind --leak-check=full --show-leak-kinds=all ./test_cases 2>&1 | tee valgrind_output.txt
	mkdir -p coverage_data
	mv *.gcda *.gcno coverage_data

clean: uninstall
	rm -rf *.a test_cases coverage* html* functions/*.o functions/*.out *.gcda *.gcno valgrind_output.txt build dist_smartcalc/ s21_smartcalc.tgz
