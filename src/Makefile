CC=g++
CFLAGS=-std=c++17 -g -Wall -Wextra -Werror
GTEST_FLAGS=-lgtest -lgtest_main -pthread
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

MODEL=brick_game/snake/model.cc
SNAKE=brick_game/snake/snake.cc
CONTROLLER=brick_game/snake/controller.cc

TESTS_FILES=brick_game/snake/Tests/testMain.cc

INSTALL_DIR=Game

DESKTOP_SRCS=$(wildcard gui/desktop/*.cpp)

all: install

launch: $(INSTALL_DIR)/desktop
	./$(INSTALL_DIR)/desktop

$(INSTALL_DIR)/desktop:
	mkdir -p $(INSTALL_DIR)
	cd gui/desktop && qmake
	cd gui/desktop && make
	mv gui/desktop/desktop $(INSTALL_DIR)

$(INSTALL_DIR)/high_score.txt:
	touch $@

install: uninstall $(INSTALL_DIR)/desktop $(INSTALL_DIR)/high_score.txt

uninstall: clean
	rm -rf Game

test: clean
	$(CC) $(CFLAGS) $(TESTS_FILES) $(MODEL) $(SNAKE) -o test $(GTEST_FLAGS)
	./test

gcov_report: test 
	$(CC) $(GCOV_FLAGS) $(TESTS_FILES) $(MODEL) $(SNAKE) -o coverage.out $(GTEST_FLAGS)
	./coverage.out
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_html

dist: uninstall install
	tar cvzf Snake.tgz Game/

dvi:
	doxygen Doxyfile

clean:
	cd gui/desktop/ && qmake
	cd gui/desktop/ && make clean
	cd gui/desktop/ && make distclean
	rm -rf coverage_html test html latex *.gcda *.gcno *.out *.info *.tgz

rebuild: clean all