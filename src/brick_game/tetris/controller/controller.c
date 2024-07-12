#ifndef CONTROLLER_C
#define CONTROLLER_C

#include "controller.h"  // Включение заголовочного файла контроллера

#include "../bonus/bonus.h"  // Включение заголовочного файла бонусов
#include "../model/backend.h"  // Включение заголовочного файла бэкенда игры
#include "../model/model.h"  // Включение заголовочного файла модели игры
#include "ncurses.h"  // Включение заголовочного файла ncurses

/**
 * @brief Функция для просчета одной итерации игры
 *
 * @param game Указатель на структуру TetGame_t, представляющую текущее
 * состояние игры
 */
void calculateTet(TetGame_t *game) {
  // Проверка, достигли ли необходимого количества итераций для движения фигуры
  // вниз
  if (game->counterIter >= COUNT_ITERATION * 15 / game->gameInfo->speed) {
    game->counterIter = 0;
    moveFigureDown(game->figure);  // Движение фигуры вниз

    // Проверка столкновения фигуры
    if (collisionFigure(game)) {
      moveFigureUp(game->figure);  // Откатить фигуру назад
      placeFigure(game);  // Установить фигуру на поле
      int count_rows = eraseLines(
          game);  // Удалить заполненные линии и подсчитать их количество
      game->gameInfo->score = game->gameInfo->score +
                              converterScore(count_rows);  // Обновить счет игры
      levelUp(game);       // Увеличить уровень игры
      updateFigure(game);  // Обновить текущую фигуру
      if (collisionFigure(game))  // Проверка столкновения новой фигуры
      {
        game->gameStatus = GameOver;  // Игра окончена
      }
    }
  } else {
    // Обработка действий пользователя
    switch (game->action) {
      case Right:  // Перемещение фигуры вправо
      {
        moveFigureRight(game->figure);
        if (collisionFigure(game))  // Проверка столкновения
          moveFigureLeft(game->figure);  // Откатить фигуру назад
        break;
      }
      case Left:  // Перемещение фигуры влево
      {
        moveFigureLeft(game->figure);
        if (collisionFigure(game))  // Проверка столкновения
          moveFigureRight(game->figure);  // Откатить фигуру назад
        break;
      }
      case Up:  // Поворот фигуры
      {
        rotateFigure(game->figure);
        if (collisionFigure(game))  // Проверка столкновения
          for (int i = 0; i < 3; i++) {
            rotateFigure(game->figure);
          }
        break;
      }
      case Down:  // Ускорение движения фигуры вниз
      {
        moveFigureDown(game->figure);
        if (collisionFigure(game))  // Проверка столкновения
        {
          moveFigureUp(game->figure);  // Откатить фигуру назад
          placeFigure(game);  // Установить фигуру на поле
          int count_rows = eraseLines(
              game);  // Удалить заполненные линии и подсчитать их количество
          game->gameInfo->score =
              game->gameInfo->score +
              converterScore(count_rows);  // Обновить счет игры
          levelUp(game);       // Увеличить уровень игры
          updateFigure(game);  // Обновить текущую фигуру
          if (collisionFigure(game))  // Проверка столкновения новой фигуры
          {
            game->gameStatus = GameOver;  // Игра окончена
          }
        }
        break;
      }
      case Action:  // Действие по умолчанию
      default:
        break;
    }
    game->counterIter++;  // Увеличить счетчик итераций
  }
}

/**
 * @brief Изменение состояния игры в зависимости от действий игрока
 *
 * @param game Указатель на структуру TetGame_t, представляющую текущее
 * состояние игры
 * @param ch Код символа, представляющего действие игрока
 */
void userAction(TetGame_t *game, int ch) {
  // Обработка действий игрока
  switch (ch) {
    case KEY_UP:  // Нажата клавиша вверх
      game->action = Up;
      break;
    case KEY_DOWN:  // Нажата клавиша вниз
      game->action = Down;
      break;
    case KEY_LEFT:  // Нажата клавиша влево
      game->action = Left;
      break;
    case KEY_RIGHT:  // Нажата клавиша вправо
      game->action = Right;
      break;
    case 'q':  // Нажата клавиша 'q' (выход из игры)
      game->gameStatus = Terminate;
      break;
    case 'p':  // Нажата клавиша 'p' (пауза)
      if (game->gameStatus == Pause)
        game->gameStatus = Start;  // Возобновление игры
      else if ((game->gameStatus != GameOver))
        game->gameStatus = Pause;  // Установка игры на паузу
      break;
    case '+':  // Нажата клавиша '+' (ускорение)
    case '=':
      if (game->gameInfo->speed > 0 && game->gameInfo->speed < 10)
        game->gameInfo->speed++;  // Увеличение скорости игры
      break;
    case '_':  // Нажата клавиша '-' (замедление)
    case '-':
      if (game->gameInfo->speed > 1 && game->gameInfo->speed <= 10 &&
          game->gameInfo->speed > game->gameInfo->level)
        game->gameInfo->speed--;  // Уменьшение скорости игры
      break;
    default:
      game->action = Action;
      break;
  }
}

/**
 * @brief Обновляет текущее состояние игры
 *
 * @param game Указатель на структуру TetGame_t, представляющую текущее
 * состояние игры
 * @return TetGame_t* Указатель на обновленную структуру TetGame_t
 */
TetGame_t *updateCurrentState(TetGame_t *game) {
  calculateTet(game);  // Просчет текущего состояния игры

  // Обновление рекорда
  if (game->gameInfo->score > game->gameInfo->record) {
    game->gameInfo->record = game->gameInfo->score;
    writeDataBase(game->gameInfo->record);
  }
  return game;
}

/**
 * @brief Инициализирует новую игру
 *
 * @return TetGame_t* Указатель на структуру TetGame_t, представляющую новую
 * игру
 */
TetGame_t *initGame() {
  srand((unsigned)time(NULL));  // Инициализация генератора случайных чисел

  TetGame_t *game = createGame();  // Создание новой игры

  game->figure = createRandomFigure(0);  // Создание случайной фигуры
  game->figure->x = FIGURE_START_X;  // Установка начальной позиции фигуры

  game->figureNext =
      createRandomFigure(0);  // Создание следующей случайной фигуры
  game->field = createField();  // Создание игрового поля

  game->action = Start;  // Установка начального состояния игры

  game->gameInfo->level = 1;  // Установка начального уровня игры
  game->gameInfo->record = readDataBase();  // Чтение рекорда из базы данных

  game->gameInfo->score = 0;  // Установка начального счета игры
  game->gameInfo->speed = START_SPEED;  // Установка начальной скорости игры

  game->counterIter = 1;  // Установка начального значения счетчика итераций

  return game;
}
#endif
