#ifndef BACKEND_C
#define BACKEND_C

#include "backend.h"

#include "tetris_model.h"

/**
 * @file backend.c
 * @brief Реализация функций, относящихся к игровой логике.
 */

/**
 * @brief Создать фигуру, заполненную нулями.
 *
 * @return Указатель на структуру TetFigure_t.
 */
TetFigure_t *createFigure() {
  TetFigure_t *figure = (TetFigure_t *)malloc(sizeof(TetFigure_t));
  figure->blocks = (int **)calloc(FIGURE_SIZE, sizeof(int *));
  for (int row = 0; row < FIGURE_SIZE; row++) {
    figure->blocks[row] = (int *)calloc(FIGURE_SIZE, sizeof(int));
  }
  figure->y = 0;
  return figure;
}

/**
 * @brief Освободить память, выделенную для фигуры.
 *
 * @param figure Указатель на структуру TetFigure_t.
 */
void freeFigure(TetFigure_t *figure) {
  if (figure) {
    if (figure->blocks) {
      for (int row = 0; row < FIGURE_SIZE; row++) {
        if (figure->blocks[row]) {
          free(figure->blocks[row]);
        }
      }
      free(figure->blocks);
    }
    free(figure);
  }
}

/**
 * @brief Создать игровое поле, заполненное нулями.
 *
 * @return Указатель на структуру TetField_t.
 */
TetField_t *createField() {
  TetField_t *field = (TetField_t *)malloc(sizeof(TetField_t));
  field->blocks = (int **)calloc(HEIGHT_FIELD, sizeof(int *));
  for (int row = 0; row < HEIGHT_FIELD; row++) {
    field->blocks[row] = (int *)calloc(WIDTH_FIELD, sizeof(int));
  }
  return field;
}

/**
 * @brief Освободить память, выделенную для игрового поля.
 *
 * @param field Указатель на структуру TetField_t.
 */
void freeField(TetField_t *field) {
  if (field) {
    if (field->blocks) {
      for (int row = 0; row < HEIGHT_FIELD; row++) {
        if (field->blocks[row]) {
          free(field->blocks[row]);
        }
      }
      free(field->blocks);
    }
    free(field);
  }
}

/**
 * @brief Создать игру.
 *
 * @return Указатель на структуру TetGame_t.
 */
TetGame_t *createGame() {
  TetGame_t *game = (TetGame_t *)malloc(sizeof(TetGame_t));
  game->gameInfo = (GameInfo_t *)malloc(sizeof(GameInfo_t));

  return game;
}

/**
 * @brief Освободить память, выделенную для игры.
 *
 * @param game Указатель на структуру TetGame_t.
 */
void freeGame(TetGame_t *game) {
  if (game) {
    freeFigure(game->figure);
    freeFigure(game->figureNext);
    freeField(game->field);
    free(game->gameInfo);
    free(game);
  }
}

/**
 * @brief Создать фигуру из паттернов.
 *
 * @param number Номер шаблона фигуры.
 * @return Указатель на структуру TetFigure_t.
 */
TetFigure_t *createRandomFigure(int number) {
  TetFigure_t *figure = createFigure();

  if (number == 0) number = rand() % 7 + 1;

  char fileName[20];
  sprintf(fileName, "./templates/%d.txt", number);
  FILE *file = fopen(fileName, "r");
  if (file) {
    char ch;
    int elem = 0;
    while ((ch = fgetc(file)) != EOF) {
      int number = ch - '0';
      if (number == 1 || number == 0) {
        figure->blocks[elem / 5][elem % 5] = number;
        elem++;
      }
    }
  }
  figure->color = (number + rand()) % 4 + 3;
  fclose(file);
  return figure;
}

/**
 * @brief Переместить фигуру вниз по оси Y.
 *
 * @param figure Указатель на структуру TetFigure_t.
 */
void moveFigureDown(TetFigure_t *figure) { figure->y++; }

/**
 * @brief Переместить фигуру вверх по оси Y.
 *
 * @param figure Указатель на структуру TetFigure_t.
 */
void moveFigureUp(TetFigure_t *figure) { figure->y--; }

/**
 * @brief Переместить фигуру влево по оси X.
 *
 * @param figure Указатель на структуру TetFigure_t.
 */
void moveFigureLeft(TetFigure_t *figure) { figure->x--; }

/**
 * @brief Переместить фигуру вправо по оси X.
 *
 * @param figure Указатель на структуру TetFigure_t.
 */
void moveFigureRight(TetFigure_t *figure) { figure->x++; }

/**
 * @brief Повернуть фигуру.
 *
 * @param figure Указатель на структуру TetFigure_t.
 */
void rotateFigure(TetFigure_t *figure) {
  TetFigure_t *figureTmp = createFigure();
  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      figureTmp->blocks[col][row] = figure->blocks[row][FIGURE_SIZE - col - 1];
    }
  }
  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      figure->blocks[col][row] = figureTmp->blocks[col][row];
    }
  }

  freeFigure(figureTmp);
}

/**
 * @brief Обновить текущую и следующую фигуры в игре.
 *
 * @param game Указатель на структуру TetGame_t.
 */
void updateFigure(TetGame_t *game) {
  freeFigure(game->figure);
  game->figure = game->figureNext;
  game->figure->x = FIGURE_START_X;

  game->figure->y = -5;
  game->figureNext = createRandomFigure(0);
}

/**
 * @brief Проверить, находится ли блок в пределах игрового поля.
 *
 * @param row Координата строки блока.
 * @param col Координата столбца блока.
 * @param fy Координата Y фигуры.
 * @param fx Координата X фигуры.
 * @return 1, если блок находится в пределах игрового поля, иначе 0.
 */
int checkBoundaries(int row, int col, int fy, int fx) {
  int result = 1;
  if ((row + fy > HEIGHT_FIELD - 1 || row + fy < 0) ||
      (col + fx > WIDTH_FIELD - 1 || col + fx < 0))
    result = 0;
  return result;
}

/**
 * @brief Установить фигуру на игровое поле.
 *
 * @param game Указатель на структуру TetGame_t.
 */
void placeFigure(TetGame_t *game) {
  int fy = game->figure->y;
  int fx = game->figure->x;

  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      int fgr = game->figure->blocks[row][col];
      if (fgr != 0 && fy + row >= 0) {
        game->field->blocks[fy + row][fx + col] = fgr;
      }
    }
  }
}

/**
 * @brief Проверить, заполнена ли линия под указанным индексом.
 *
 * @param field Указатель на структуру TetField_t, представляющую игровое поле.
 * @param row Индекс строки, которую необходимо проверить.
 * @return 1, если линия заполнена, иначе 0.
 */
int lineIsFill(TetField_t *field, int row) {
  int result = 1;
  for (int col = 0; col < WIDTH_FIELD; col++) {
    int block = field->blocks[row][col];
    if (block == 0) result = 0;
  }
  return result;
}

/**
 * @brief Удалить строку из игрового поля.
 *
 * @param field Указатель на структуру TetField_t, представляющую игровое поле.
 * @param row Индекс строки, которую необходимо удалить.
 */
void dropLine(TetField_t *field, int row) {
  if (row == HEIGHT_FIELD) {
    for (int col = 0; col < WIDTH_FIELD; col++) field->blocks[row][col] = 0;
  } else {
    for (int i = row; i > 0; i--) {
      for (int col = 0; col < WIDTH_FIELD; col++) {
        field->blocks[i][col] = field->blocks[i - 1][col];
      }
    }
  }
}

/**
 * @brief Удалить заполненные строки из игрового поля и подсчитать количество
 * удаленных строк.
 *
 * @param game Указатель на структуру TetGame_t.
 * @return Количество удаленных строк.
 */
int eraseLines(TetGame_t *game) {
  int counter = 0;
  for (int row = HEIGHT_FIELD - 1; row >= 0; row--) {
    while (lineIsFill(game->field, row)) {
      dropLine(game->field, row);
      counter++;
    }
  }
  return counter;
}

/**
 * @brief Проверить, произошло ли столкновение фигуры с другими блоками на
 * игровом поле.
 *
 * @param game Указатель на структуру TetGame_t.
 * @return 1, если столкновение произошло, иначе 0.
 */
int collisionFigure(TetGame_t *game) {
  int result = 0;

  int fx = game->figure->x;
  int fy = game->figure->y;

  int **figure = game->figure->blocks;
  int **field = game->field->blocks;

  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      int fgr = figure[row][col];

      if (fgr == 1) {
        if (fy + row < 0)
          continue;

        else if (checkBoundaries(row, col, fy, fx)) {
          int fld = field[fy + row][fx + col];

          if (fgr != 0 && fld != 0) {
            result = 1;

            if (fy + row == 0) game->gameStatus = GameOver;

            break;
          }
        }

        else if (!checkBoundaries(row, col, fy, fx)) {
          result = 1;
          break;
        }
      }
    }
    if (result) break;
  }
  return result;
}
#endif