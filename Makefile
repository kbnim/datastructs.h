CC     = gcc
CFLAGS = -W -Wall -Wextra -pedantic

# directories
OBJ_DIR   = obj
SRC_DIR   = src
TESTS_DIR = tests

# data types, data structures
CSTRING = $(SRC_DIR)/cstring.c

# tests
CSTRING_TEST_BASIC_BIN      = $(TESTS_DIR)/cstring/cstring_test_basic
CSTRING_TEST_BASIC_SRC      = $(TESTS_DIR)/cstring/cstring_test_basic.c
CSTRING_TEST_IMMUTATIVE_BIN = $(TESTS_DIR)/cstring/cstring_test_immutative
CSTRING_TEST_IMMUTATIVE_SRC = $(TESTS_DIR)/cstring/cstring_test_immutative.c
CSTRING_TEST_MUTATIVE_BIN   = $(TESTS_DIR)/cstring/cstring_test_mutative
CSTRING_TEST_MUTATIVE_SRC   = $(TESTS_DIR)/cstring/cstring_test_mutative.c

$(CSTRING_TEST_BASIC_BIN): $(CSTRING) $(CSTRING_TEST_BASIC_SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(CSTRING_TEST_IMMUTATIVE_BIN): $(CSTRING) $(CSTRING_TEST_IMMUTATIVE_SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(CSTRING_TEST_MUTATIVE_BIN): $(CSTRING) $(CSTRING_TEST_MUTATIVE_SRC)
	$(CC) $(CFLAGS) $^ -o $@