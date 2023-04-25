CPP=g++
CFLAGS=-std=c++17 -Wall -Werror -Wextra
LIB_NAME=my_matrix_oop.a
CLEAN=rm -rf
# ADDITIONAL
TEST_FLAG=-fsanitize=address -g
ADDITIONAL=#$(TEST_FLAG)

ifeq ($(shell uname), Linux)
	OPEN=xdg-open
	CHECK_LIBS=-lgtest -lm -lpthread -lsubunit -lrt
	LEAKS=valgrind $(BUILD_DIR)/test
else
	OPEN=open
	CHECK_LIBS=-lgtest -lm -lpthread
	LEAKS=CK_FORK=no leaks --atExit -- $(BUILD_DIR)/test
endif

# FOLDERS
SRC_DIR=.
TEST_DIR=$(SRC_DIR)/../tests
BUILD_DIR=$(SRC_DIR)/../build
REPORT_DIR=$(BUILD_DIR)/report

# SOURCES
SOURCES=*.cc
HEADERS=*.h
OBJ=*.o


# GOALS_START
all: $(LIB_NAME)

rebuild: clean all

$(LIB_NAME): $(SRC_DIR)/$(SOURCES) $(SRC_DIR)/$(HEADERS)
	$(CPP) $(CFLAGS) $(ADDITIONAL) -c $(SRC_DIR)/$(SOURCES)
	ar rc $(LIB_NAME) $(OBJ)
	$(CLEAN) $(OBJ)

# TESTS
test: clean $(LIB_NAME)
	mkdir -p $(BUILD_DIR)
	$(CPP) $(CFLAGS) $(ADDITIONAL) $(TEST_DIR)/tests.cc -L. $(LIB_NAME) $(CHECK_LIBS) -o $(BUILD_DIR)/$@
	$(BUILD_DIR)/$@	

# COVERAGE
gcov_report: clean
	mkdir -p $(BUILD_DIR)
	$(CPP) $(CFLAGS) $(ADDITIONAL) --coverage -c $(SRC_DIR)/$(SOURCES)
	ar rc $(LIB_NAME) $(OBJ)
	$(CPP) $(CFLAGS) $(TEST_DIR)/tests.cc -L. $(LIB_NAME) $(CHECK_LIBS) -lgcov -o $(BUILD_DIR)/test
	$(CLEAN) $(OBJ)
	$(BUILD_DIR)/test
	gcov *.gcda
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	mkdir -p $(REPORT_DIR)
	genhtml -o $(REPORT_DIR) gcov_report.info
	$(OPEN) $(REPORT_DIR)/index.html

# CHECK
check: cppcheck codestyle leaks

codestyle:
	clang-format -i $(SOURCES) ./../tests/$(SOURCES)
	clang-format -i $(HEADERS)
	clang-format -n $(SOURCES) ./../tests/$(SOURCES)
	clang-format -n $(HEADERS)


cppcheck:
	cppcheck --std=c++17 --enable=all --suppress=missingIncludeSystem $(SRC_DIR) $(TEST_DIR)

leaks: clean test
	$(LEAKS)

# CLEAN
clean:
	$(CLEAN) $(OBJ) *.a *.gcno *.gcda *.gcov *.info
	$(CLEAN) $(BUILD_DIR)
