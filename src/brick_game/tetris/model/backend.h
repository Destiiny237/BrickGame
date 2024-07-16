#ifndef BACKEND_H
#define BACKEND_H

#include "tetris_model.h"

/**
 * @brief Создать фигуру заполненную нулями
 *
 * @return Указатель на созданную фигуру
 */
TetFigure_t *createFigure();

/**
 * @brief Освободить выделенную для фигуры память
 *
 * @param figure Указатель на фигуру
 */
void freeFigure(TetFigure_t *figure);

/**
 * @brief Создать поле размером HEIGHT_FIELD на WIGHT_FIELD заполненное нулями
 *
 * @return Указатель на созданное поле
 */
TetField_t *createField();

/**
 * @brief Освободить выделенную для поля память
 *
 * @param field Указатель на поле
 */
void freeField(TetField_t *field);

/**
 * @brief Создать игру
 *
 * @return Указатель на созданную игру
 */
TetGame_t *createGame();

/**
 * @brief Освободить выделенную для игры память
 *
 * @param game Указатель на игру
 */
void freeGame(TetGame_t *game);

/**
 * @brief Создать фигуру из паттернов
 *
 * @param number Номер паттерна
 * @return Указатель на созданную фигуру
 */
TetFigure_t *createRandomFigure(int number);

/**
 * @brief Движение фигуры по Y вниз
 *
 * @param figure Указатель на фигуру
 */
void moveFigureDown(TetFigure_t *figure);

/**
 * @brief Движение фигуры по Y вверх
 *
 * @param figure Указатель на фигуру
 */
void moveFigureUp(TetFigure_t *figure);

/**
 * @brief Движение фигуры по X влево
 *
 * @param figure Указатель на фигуру
 */
void moveFigureLeft(TetFigure_t *figure);

/**
 * @brief Движение фигуры по X вправо
 *
 * @param figure Указатель на фигуру
 */
void moveFigureRight(TetFigure_t *figure);

/**
 * @brief Поворот фигуры
 *
 * @param figure Указатель на фигуру
 */
void rotateFigure(TetFigure_t *figure);

/**
 * @brief Выкинуть новую фигуру
 *
 * @param game Указатель на игру
 */
void updateFigure(TetGame_t *game);

/**
 * @brief Проверяет находится ли блок в пределах игрового поля
 *
 * @param row Координата строки
 * @param col Координата столбца
 * @param fy Смещение по Y
 * @param fx Смещение по X
 * @return 1, если блок находится в пределах поля, иначе 0
 */
int checkBoundaries(int row, int col, int fy, int fx);

/**
 * @brief Проверка столкновения фигуры
 *
 * @param game Указатель на игру
 * @return 1, если произошло столкновение, иначе 0
 */
int collisionFigure(TetGame_t *game);

/**
 * @brief Установить фигуру на поле
 *
 * @param game Указатель на игру
 */
void placeFigure(TetGame_t *game);

/**
 * @brief Проверяет заполнена ли линия под индексом row
 *
 * @param field Указатель на поле
 * @param row Индекс строки
 * @return 1, если линия заполнена, иначе 0
 */
int lineIsFill(TetField_t *field, int row);

/**
 * @brief Удаляет строку
 *
 * @param field Указатель на поле
 * @param row Индекс строки
 */
void dropLine(TetField_t *field, int row);

/**
 * @brief Удаляет строки и подсчитывает результат
 *
 * @param game Указатель на игру
 * @return Количество удаленных строк
 */
int eraseLines(TetGame_t *game);

#endif
