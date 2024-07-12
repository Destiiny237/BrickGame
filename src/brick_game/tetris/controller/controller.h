#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../../view/view.h"
#include "../model/model.h"

/**
 * @brief Функция для просчета одной итерации игры.
 *
 * @param game Указатель на структуру TetGame_t, представляющую текущее
 * состояние игры.
 */
void calculateTet(TetGame_t *game);

/**
 * @brief Обновляет текущее состояние игры.
 *
 * @param game Указатель на структуру TetGame_t, представляющую текущее
 * состояние игры.
 * @return TetGame_t* Указатель на обновленную структуру TetGame_t.
 */
TetGame_t *updateCurrentState(TetGame_t *game);

/**
 * @brief Изменяет состояния игры в зависимости от действий игрока.
 *
 * @param game Указатель на структуру TetGame_t, представляющую текущее
 * состояние игры.
 * @param ch Код клавиши, нажатой пользователем.
 */
void userAction(TetGame_t *game, int ch);

/**
 * @brief Инициализирует новую игру.
 *
 * @return TetGame_t* Указатель на структуру TetGame_t, представляющую новую
 * игру.
 */
TetGame_t *initGame();

#endif
