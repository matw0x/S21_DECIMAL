SHELL = /bin/bash
FLAGS = -Wall -Werror -Wextra -std=c11
FLAG_COV = --coverage 
UNAME_S = $(shell uname -s)

BUILD_DIR := build/
TEST_DIR := test/

SRC := $(wildcard $(DIR)*.c)
TEST_SRC := $(wildcard $(TEST_DIR)case_*.c)

OBJ := $(addprefix $(BUILD_DIR), $(notdir $(SRC:.c=.o)))
TEST_OBJ := $(addprefix $(BUILD_DIR)$(TEST_DIR), $(notdir $(TEST_SRC:.c=.o)))

ifeq (${UNAME_S}, Linux)
	TEST_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
	OPEN_CMD = xdg-open
else
	TEST_FLAGS = -lcheck
	OPEN_CMD = open
endif

all: clean gcov_report

s21_decimal.a: $(OBJ)
	ar rc s21_decimal.a $(OBJ)
	ranlib s21_decimal.a

test: s21_decimal.a $(TEST_OBJ)
	gcc -c $(TEST_DIR)test.c -o $(BUILD_DIR)test.o
	gcc $(FLAGS) $(FLAG_COV) -o $(BUILD_DIR)tests $(TEST_OBJ) $(BUILD_DIR)test.o $(SRC) ${TEST_FLAGS}
	./$(BUILD_DIR)tests

$(BUILD_DIR)%.o: %.c
	@mkdir -p $(BUILD_DIR)$(TEST_DIR)
	gcc -c $<  -o $@;

gcov_report: test
	lcov -t "test" -o $(BUILD_DIR)test.info -c -d $(BUILD_DIR)
	genhtml -o $(BUILD_DIR)report $(BUILD_DIR)test.info
	$(OPEN_CMD) $(BUILD_DIR)report/index.html

clang_format:
	find . -name "*.c" -or -name "*.h" | xargs clang-format -i -style=Google

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BUILD_DIR)tests

clean:
	rm -rf $(BUILD_DIR) s21_decimal.a
