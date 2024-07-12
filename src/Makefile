CC=g++
CFLAGS=-std=c++17 -g -Wall -Wextra -Werror
GTEST_FLAGS=-lgtest -lgtest_main -pthread
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

MODEL=brick_game/snake/model.cc
SNAKE=brick_game/snake/snake.cc
CONTROLLER=brick_game/snake/controller.cc

TESTS_FILES=brick_game/snake/Tests/testMain.cc

all: install

install: uninstall
	mkdir Game
	touch Game/high_score.txt
	cd gui/desktop/ && qmake
	cd gui/desktop/ && make
	mv gui/desktop/desktop Game

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

##########################################
# all: install

# install: uninstall
# 	mkdir Game
# 	mkdir Game/cli
# 	mkdir Game/desktop
# 	touch Game/cli/high_score_tetris.txt
# 	touch Game/desktop/high_score_tetris.txt
# 	echo "0" >> Game/cli/high_score_tetris.txt
# 	echo "0" >> Game/desktop/high_score_tetris.txt
# 	cd Game/desktop/ && qmake ../../gui/desktop/brick_game && make
# 	g++ brick_game/tetris/s21_tetris.c brick_game/snake/*.cc gui/cli/*.cc -o Game/cli/BrickGame -lncurses -std=c++17

# uninstall:
# 	rm -rf Game

# test: clean
# 	$(CC) tests/test_snake.cc brick_game/snake/s21_controller.cc brick_game/snake/s21_model.cc -o tests/testing -lgtest -pthread
# 	./tests/testing


# gcov_report: clean
# 	$(CC) tests/test_snake.cc brick_game/snake/s21_controller.cc brick_game/snake/s21_model.cc-o tests/testing -lgtest -pthread --coverage
# 	./tests/testing
# 	lcov -d ./ --capture --output-file snake.info --ignore-errors mismatch --ignore-errors inconsistent
# 	genhtml snake.info --output-directory report
# 	open report/index.html
	
# dist: uninstall install
# 	tar cvzf Snake.tgz Game/

# dvi:
# 	doxygen Doxyfile
# 	open html/index.html

# clang-check:
# 	cp ../materials/linters/.clang-format .
# 	clang-format -n brick_game/snake/*.cc brick_game/snake/*.h brick_game/tetris/*.h brick_game/tetris/*.c gui/cli/*.cc gui/cli/*.h gui/desktop/brick_game/*.cpp gui/desktop/brick_game/*.h tests/*.cc tests/*.c
# 	rm ./.clang-format

# clang-formatting:
# 	cp ../materials/linters/.clang-format .
# 	clang-format -i brick_game/snake/*.cc brick_game/snake/*.h brick_game/tetris/*.h brick_game/tetris/*.c gui/cli/*.cc gui/cli/*.h gui/desktop/brick_game/*.cpp gui/desktop/brick_game/*.h tests/*.cc tests/*.c
# 	rm ./.clang-format

# clean:
# 	rm -rf *.a *.out *.o test *.html *.css
# 	rm -rf *.g* *.info report *.txt *.tgz
# 	rm -rf tests/testing tests/*.gcda tests/*.gcno snake.info report
# 	rm -rf high_score_tetris.txt high_score_snake.txt
# 	rm -rf html latex