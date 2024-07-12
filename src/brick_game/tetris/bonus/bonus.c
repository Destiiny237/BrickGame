#ifndef BONUS_C
#define BONUS_C

#include "bonus.h"

#include "../model/model.h"

/**
 * @brief Увеличивает уровень в зависимости от текущего счета игры.
 *
 * @param game Указатель на структуру TetGame_t, представляющую текущее
 * состояние игры.
 */
void levelUp(TetGame_t *game) {
  int sc = game->gameInfo->score;
  game->gameInfo->level = 1 + sc / 600;

  while (game->gameInfo->speed < game->gameInfo->level) {
    game->gameInfo->speed++;
  }
}

/**
 * @brief Переводит количество уничтоженных строк в количество очков.
 *
 * @param count_rows Количество уничтоженных строк.
 * @return int Количество очков, полученных за уничтоженные строки.
 */
int converterScore(int count_rows) {
  int result = 0;
  if (count_rows == 1)
    result = 100;
  else if (count_rows == 2)
    result = 300;
  else if (count_rows == 3)
    result = 700;
  else if (count_rows >= 4)
    result = 1500;

  return result;
}

/**
 * @brief Читает из базы данных максимальный счет.
 *
 * @return int Максимальный счет, считанный из базы данных.
 */
int readDataBase() {
  int score = 0;
  char fileName[] = "./database/database.txt";
  FILE *file = fopen(fileName, "r");
  if (file) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
      if (ch >= '0' && ch <= '9') {
        score = score * 10 + (ch - '0');
      } else {
        break;
      }
    }
  }

  fclose(file);
  return score;
}

/**
 * @brief Записывает в базу данных максимальный счет.
 *
 * @param score Максимальный счет для записи в базу данных.
 * @return int Возвращает 0 в случае успешной записи.
 */
int writeDataBase(int score) {
  char fileName[] = "./database/database.txt";
  FILE *file = fopen(fileName, "w");
  if (file) {
    // Используем fprintf для записи целого числа в файл с символом новой строки
    fprintf(file, "%d\n", score);
  }

  fclose(file);
  return 0;
}

#endif
