#include <ncurses.h>  // Включение заголовочного файла ncurses

#include "../gui/console/consoleView.h"  // Включение заголовочного файла представления
#include "ncurses.h"  // Включение заголовочного файла ncurses
#include "tetris/bonus/bonus.h"  // Включение заголовочного файла бонусов игры тетрис
#include "tetris/controller/tetris_controller.h"  // Включение заголовочного файла контроллера игры тетрис
#include "tetris/model/backend.h"  // Включение заголовочного файла бэкэнда игры тетрис
#include "tetris/model/tetris_model.h"  // Включение заголовочного файла модели игры тетрис

// Главная функция, управляющая игрой тетрис
int tetrisGame(TetWindows_t *winTet);

/**
 * @brief Основная функция программы
 *
 * @return Возвращает 0 в случае успешного завершения программы
 */
int main() {
  // Инициализация окна игры
  TetWindows_t *winTet = tetrisGUI();
  // Запуск игры тетрис
  tetrisGame(winTet);

  return 0;
}

/**
 * @brief Функция управления игрой тетрис
 *
 * @param winTet Указатель на окно игры
 * @return Возвращает 0 в случае успешного завершения игры
 */
int tetrisGame(TetWindows_t *winTet) {
  // Инициализация игры
  TetGame_t *game = initGame();
  // Цикл работы игры, пока не будет прерван пользователем
  while (game->gameStatus != Terminate) {
    // Получение пользовательского ввода
    int ch = getch();
    // Обработка пользовательского действия
    userAction(game, ch);
    // Обновление текущего состояния игры
    if (game->gameStatus != Pause) {
      updateCurrentState(game);
    }
    // Задержка для корректного отображения
    usleep(2000);
    // Отображение игры
    if (winTet) frontend(game, winTet);
  }
  // Освобождение ресурсов игры
  freeGame(game);
  // Освобождение ресурсов окна
  if (winTet) {
    freeWindows(winTet);
    endwin();
  }

  return 0;
}
