#ifndef VIEW_H
#define VIEW_H

#include <ncurses.h>  // Включение заголовочного файла ncurses

#include "../../brick_game/tetris/model/tetris_model.h"  // Включение заголовочного файла модели игры тетрис

#define WHITE 1    // Константа для цвета белого
#define GREEN 2    // Константа для цвета зеленого
#define BLUE 3     // Константа для цвета синего
#define RED 4      // Константа для цвета красного
#define CYAN 5     // Константа для цвета голубого
#define MAGNETA 6  // Константа для цвета пурпурного

/**
 * @brief Структура TetWindows_t, представляющая окна игры тетрис
 */
typedef struct TetWindows_t {
  WINDOW *winField;  /**< Окно игрового поля */
  WINDOW *winFigure; /**< Окно для отображения текущей и следующей фигур */
  WINDOW *winInfo; /**< Окно для вывода информации о текущем состоянии игры */
  WINDOW *winButtons; /**< Окно с кнопками управления игрой */
} TetWindows_t;

/**
 * @brief Выводит фигуру на указанное окно
 *
 * @param figure Указатель на структуру TetFigure_t, представляющую фигуру
 * @param win Указатель на окно, куда будет выводиться фигура
 */
void outputFigure(TetFigure_t *figure, WINDOW *win);

/**
 * @brief Выводит игровое поле на указанное окно
 *
 * @param field Указатель на структуру TetField_t, представляющую игровое поле
 * @param win Указатель на окно, куда будет выводиться игровое поле
 */
void outputField(TetField_t *field, WINDOW *win);

/**
 * @brief Очищает все символы в указанных координатах окна
 *
 * @param win Указатель на окно, в котором нужно очистить символы
 * @param size_y Размер по вертикали
 * @param size_x Размер по горизонтали
 */
void cleanSymbols(WINDOW *win, int size_y, int size_x);

/**
 * @brief Выводит информацию о текущем состоянии игры
 *
 * @param game Указатель на структуру TetGame_t, представляющую игровое
 * состояние
 * @param win Указатель на окно, куда будет выводиться информация
 */
void ouputInfoGame(TetGame_t *game, WINDOW *win);

/**
 * @brief Выводит окно с кнопками управления игрой
 *
 * @param win Указатель на окно, куда будет выводиться окно с кнопками
 */
void outputButtons(WINDOW *win);

/**
 * @brief Инициализирует окна для игры
 *
 * @return Возвращает указатель на структуру TetWindows_t, содержащую окна
 */
TetWindows_t *createWindows();

/**
 * @brief Освобождает память, выделенную под окна
 *
 * @param winTet Указатель на структуру TetWindows_t
 */
void freeWindows(TetWindows_t *winTet);

/**
 * @brief Выводит GAME OVER на указанное окно
 *
 * @param win Указатель на окно, куда будет выводиться GAME OVER
 * @param game Указатель на структуру TetGame_t, представляющую текущее
 * состояние игры
 */
void outpuGameOver(WINDOW *win, TetGame_t *game);

/**
 * @brief Выводит все элементы игры на экран
 *
 * @param game Указатель на структуру TetGame_t, представляющую текущее
 * состояние игры
 * @param winTet Указатель на структуру TetWindows_t, содержащую окна игры
 */
void frontend(TetGame_t *game, TetWindows_t *winTet);

/**
 * @brief Главная функция для создания графического интерфейса игры тетрис
 *
 * @return Возвращает указатель на структуру TetWindows_t, содержащую окна игры
 */
TetWindows_t *tetrisGUI();

#endif
