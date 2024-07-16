CC=g++
С=gcc
CCFLAGS=-std=c++17 -g -Wall -Wextra -Werror
CFLAGS=-std=c99

GTEST_FLAGS=-lgtest -lgtest_main -pthread
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

# ---------
# SnakeGame
# ---------
SNAKE_MODEL=brick_game/snake/model.cc
SNAKE_CONTROLLER=brick_game/snake/controller.cc
SNAKE=brick_game/snake/snake.cc
SNAKE_TESTS_FILES=brick_game/snake/Tests/testMain.cc

# ---------
# TetrisGame
# ---------
BONUS = src/brick_game/tetris/bonus/*.c
MODEL = src/brick_game/tetris/model/*.c
CONTROLLER = src/brick_game/tetris/controller/*.c
VIEW = src/view/*.c

INSTALL_DIR=Game

all: install

# launch: $(INSTALL_DIR)/desktop/brickGame
# 	./$(INSTALL_DIR)/desktop/brickGame

$(INSTALL_DIR)/desktop/brickGame: $(INSTALL_DIR)
	cd gui/desktop && qmake
	cd gui/desktop && make
	mv gui/desktop/desktop $(INSTALL_DIR)/desktop/snakeobj
# $(CC) $(MODEL) $(CONTROLLER) $(VIEW) $(BONUS) -o $(INSTALL_DIR)/desktop/tetrisobj -lncurses -std=c++17
	echo
	echo
	echo
	echo
	echo
	$(CC) -o brickGame $(INSTALL_DIR)/desktop/snakeobj $(INSTALL_DIR)/desktop/tetrisobj

$(INSTALL_DIR)/desktop/high_score.txt: $(INSTALL_DIR)
	touch $@

$(INSTALL_DIR):
	mkdir -p $@

install: uninstall $(INSTALL_DIR)/desktop/brickGame $(INSTALL_DIR)/desktop/high_score.txt

uninstall: clean
	rm -rf $(INSTALL_DIR)

test: clean
	$(CC) $(CCFLAGS) $(SNAKE_TESTS_FILES) $(SNAKE_MODEL) $(SNAKE) -o test $(GTEST_FLAGS)
	./test

gcov_report: test 
	$(CC) $(GCOV_FLAGS) $(SNAKE_TESTS_FILES) $(SNAKE_MODEL) $(SNAKE) -o coverage.out $(GTEST_FLAGS)
	./coverage.out
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_html

dist: uninstall install
	tar cvzf Snake.tgz $(INSTALL_DIR)

dvi:
	doxygen Doxyfile

clean:
	cd gui/desktop/ && qmake
	cd gui/desktop/ && make clean
	cd gui/desktop/ && make distclean
	rm -rf coverage_html test html latex *.gcda *.gcno *.out *.info *.tgz

rebuild: clean all