#ifndef BONUS_H
#define BONUS_H

#include "../model/tetris_model.h"

/**
 * @brief Увеличивает уровень игры в зависимости от текущего счета.
 *
 * @param game Указатель на структуру TetGame_t, представляющую текущее
 * состояние игры.
 */
void levelUp(TetGame_t *game);

/**
 * @brief Переводит количество уничтоженных строк в количество очков.
 *
 * @param count_rows Количество уничтоженных строк.
 * @return int Количество очков, полученных за уничтоженные строки.
 */
int converterScore(int count_rows);

/**
 * @brief Читает максимальный счет из базы данных.
 *
 * @return int Максимальный счет, считанный из базы данных.
 */
int readDataBase();

/**
 * @brief Записывает максимальный счет в базу данных.
 *
 * @param score Максимальный счет для записи в базу данных.
 * @return int Возвращает 0 в случае успешной записи.
 */
int writeDataBase(int score);

#endif
