TARGET = tetris
CC = gcc
CFLAGS = -std=c99 
TEST_FLAGS = -std=c11 -g `pkg-config --cflags --libs check`

SRC = src/brick_game/tetris/*.c
BONUS = src/brick_game/tetris/bonus/*.c
MODEL = src/brick_game/tetris/model/*.c
CONTROLLER = src/brick_game/tetris/controller/*.c
VIEW = src/view/*.c
OBJ = *.o
TEST = ./tests/tests.c
TEST_PATH = ./tests/
MAIN = src/brick_game/main.c

OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
	OPEN_CMD = xdg-open
else
	CHECK_FLAGS = -lcheck
	OPEN_CMD = open
endif

all: clean install
	./$(TARGET) 

create_tests:
	checkmk clean_mode=1 $(TEST_PATH)*.check >$(TEST_PATH)tests.c 

gcov_report: clean test
	$(CC) $(CFLAGS) $(TEST_FLAGS) -fprofile-arcs -ftest-coverage $(OBJ) $(TEST) -o test -lncurses $(CHECK_FLAGS)
	lcov -t test -o rep.info -c -d .
	genhtml rep.info --output-directory report
	genhtml -o report rep.info 
	$(OPEN_CMD) ./report/index.html
	rm -f *.gcno *.info *.gcda 

test: clean backend.o model.o controller.o bonus.o create_tests
	$(CC) $(CFLAGS) $(TEST_FLAGS) -fprofile-arcs -ftest-coverage $(MODEL) $(CONTROLLER) $(BONUS) $(TEST) -o test -lncurses $(CHECK_FLAGS)
	./test
	
install: frontend.o model.o controller.o bonus.o
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(MAIN) -lncurses
	rm -rf *.o

uninstall:
	rm -f $(TARGET)


bonus.a: bonus.o
	ar rcs $(TARGET).a *.o
	ranlib $(TARGET).a

bonus.o: 
	$(CC) $(CFLAGS) -c $(BONUS)

controller.a: model.o
	ar rcs $(TARGET).a *.o
	ranlib $(TARGET).a

controller.o: 
	$(CC) $(CFLAGS) -c $(CONTROLLER)

model.a: model.o
	ar rcs $(TARGET).a *.o
	ranlib $(TARGET).a

model.o: 
	$(CC) $(CFLAGS) -c $(MODEL)

frontend.o: 
	$(CC) $(CFLAGS) -c $(VIEW)

uninstall: clean

check: install
	leaks -atExit -- ./$(TARGET) 

clean:
	rm -f $(TARGET) $(OBJ) a.out
	rm -f *.gcno *.info *.gcda 
	rm -rf report
	rm -f test 
	rm -rf test.dSYM

dvi:
	cd /Users/egornedelkin/school/C7_BrickGame_v1.0-1/src && doxygen Doxyfile

dist:
	mkdir -p dist
	cp -r src include Makefile README.md dist
	tar -czf dist/project.tar.gz dist

.PHONY: backend.o frontend.o
