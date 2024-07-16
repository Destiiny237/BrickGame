#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>  // Ввод/вывод стандартных потоков
#include <stdlib.h>  // Стандартные функции общей полезности
#include <time.h>    // Функции работы со временем
#include <unistd.h>  // Доступ к POSIX-системным функциям

#define FIGURE_SIZE 5    // Размер фигуры
#define HEIGHT_FIELD 20  // Высота игрового поля
#define WIDTH_FIELD 10   // Ширина игрового поля

#define FIGURE_START_Y 0  // Начальная координата Y для фигуры
#define FIGURE_START_X \
  (WIDTH_FIELD / 2 - 3)  // Начальная координата X для фигуры
#define SHIFT_FIELD_X 5  // Смещение по X для отображения игрового поля
#define SHIFT_FIELD_Y 5  // Смещение по Y для отображения игрового поля

#define COUNT_ITERATION 30  // Количество итераций
#define START_SPEED 1       // Начальная скорость

/**
 * @brief Структура, представляющая фигуру тетриса
 */
typedef struct TetFigure_t {
  int **blocks; /**< Массив блоков фигуры */
  int color;    /**< Цвет фигуры */
  int x;        /**< Координата X фигуры */
  int y;        /**< Координата Y фигуры */

} TetFigure_t;

/**
 * @brief Структура, представляющая игрока
 */
typedef struct TetPlayer_t {
  int action; /**< Действие игрока */

} TetPlayer_t;

/**
 * @brief Структура, представляющая игровое поле
 */
typedef struct TetField_t {
  int **blocks; /**< Массив блоков игрового поля */

} TetField_t;

/**
 * @brief Перечисление для действий пользователя
 */
typedef enum {
  Start,     /**< Начало игры */
  Pause,     /**< Пауза */
  GameOver,  /**< Конец игры */
  Terminate, /**< Прерывание */
  Left,      /**< Влево */
  Right,     /**< Вправо */
  Up,        /**< Вверх */
  Down,      /**< Вниз */
  Action     /**< Действие */

} UserAction_t;

/**
 * @brief Структура, представляющая информацию об игре
 */
typedef struct GameInfo_t {
  int speed;  /**< Скорость игры */
  int score;  /**< Очки */
  int record; /**< Рекорд */
  int level;  /**< Уровень */

} GameInfo_t;

/**
 * @brief Структура, представляющая игровой процесс
 */
typedef struct TetGame_t {
  TetFigure_t *figure;     /**< Фигура */
  TetFigure_t *figureNext; /**< Следующая фигура */
  TetPlayer_t *player;     /**< Игрок */
  TetField_t *field;       /**< Игровое поле */
  GameInfo_t *gameInfo;    /**< Информация об игре */

  int action;      /**< Действие */
  int counterIter; /**< Счетчик итераций */
  int gameStatus;  /**< Состояние игры */

} TetGame_t;

#endif
