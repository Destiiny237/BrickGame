#ifndef MODEL_H
#define MODEL_H

#define WIDTH 10
#define HEIGHT 20

#define STANDARTSPEED 250
#define ACCELERATESPEED 150

#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "snake.h"
#include "IObserver.h"

namespace s21
{
  /**
   * @class SnakeModel
   * @brief Класс, представляющий модель игры "Змейка".
   */
  class SnakeModel
  {
  public:
    friend class ModelTest; /**< Класс ModelTest является другом класса SnakeModel. */

    /**
     * @struct GameInfo_t
     * @brief Структура, содержащая информацию об игре.
     */
    typedef struct
    {
      int **field;    /**< Игровое поле. */
      int **next;     /**< Следующий элемент. */
      int score;      /**< Текущий счет. */
      int high_score; /**< Рекордный счет. */
      int level;      /**< Уровень игры. */
      int speed;      /**< Скорость игры. */
      int pause;      /**< Флаг паузы. */
    } GameInfo_t;

    /**
     * @struct Apple_t
     * @brief Структура, представляющая яблоко в игре.
     */
    typedef struct
    {
      int x; /**< Координата x яблока. */
      int y; /**< Координата y яблока. */
    } Apple_t;

    /**
     * @enum State_t
     * @brief Перечисление состояний игры.
     */
    typedef enum
    {
      Moving,    /**< Состояние движения змейки. */
      EatApple,  /**< Состояние, когда змейка ест яблоко. */
      Collided,  /**< Состояние столкновения змейки. */
      GameOver,  /**< Состояние окончания игры. */
      WinGame    /**< Состояние победы в игре. */
    } State_t;

    std::vector<IObserver *> observers; /**< Вектор наблюдателей. */
    State_t currentState;               /**< Текущее состояние игры. */
    Apple_t *apple;                     /**< Указатель на яблоко. */

    bool hold;                          /**< Флаг удержания. */
    int gameLoopInterval;               /**< Интервал игрового цикла. */
    double speedMultiplier;             /**< Множитель скорости. */

    /**
     * @brief Создает змейку.
     */
    void createSnake();

    /**
     * @brief Создает яблоко.
     */
    void createApple();

    /**
     * @brief Обновляет состояние змейки.
     */
    void updateSnake();

    /**
     * @brief Обновляет игровое поле.
     */
    void updateGrid();

    /**
     * @brief Повышает уровень игры.
     */
    void levelUp();

    /**
     * @brief Считывает рекордный счет из файла.
     */
    void readHighScore();

    /**
     * @brief Записывает рекордный счет в файл.
     */
    void writeHighScore();

    /**
     * @brief Проверяет, находится ли клетка на змейке.
     * @param x Координата x клетки.
     * @param y Координата y клетки.
     * @return true, если клетка находится на змейке, иначе false.
     */
    bool isSnakeCell(int x, int y);

    /**
     * @brief Проверяет столкновение с яблоком.
     * @return true, если произошло столкновение, иначе false.
     */
    bool checkCollisionWithApple();

    /**
     * @brief Проверяет столкновение с границами поля.
     * @return true, если произошло столкновение, иначе false.
     */
    bool checkCollisionWithBorders();

    /**
     * @brief Проверяет столкновение со змейкой.
     * @return true, если произошло столкновение, иначе false.
     */
    bool checkCollisionWithSnake();

    /**
     * @brief Проверяет победу в игре.
     * @return true, если достигнута победа, иначе false.
     */
    bool checkWin();

    /**
     * @brief Обрабатывает состояние движения змейки.
     */
    void handleMovingState();

    /**
     * @brief Обрабатывает состояние поедания яблока.
     */
    void handleEatAppleState();

    /**
     * @brief Обрабатывает состояние столкновения змейки.
     */
    void handleCollidedState();

    /**
     * @brief Устанавливает позицию яблока.
     * @param position Позиция яблока.
     */
    void setApplePosition(const s21::Snake::snakePart &position);

  public:
    /**
     * @brief Деструктор класса SnakeModel.
     */
    ~SnakeModel();

    s21::Snake *snake; /**< Указатель на змейку. */

    /**
     * @enum UserAction_t
     * @brief Перечисление действий пользователя.
     */
    typedef enum
    {
      Start,     /**< Начало игры. */
      Pause,     /**< Пауза игры. */
      Terminate, /**< Завершение игры. */
      Left,      /**< Движение влево. */
      Right,     /**< Движение вправо. */
      Up,        /**< Движение вверх. */
      Down,      /**< Движение вниз. */
      Action     /**< Действие. */
    } UserAction_t;

    /**
     * @brief Получает информацию об игре.
     * @return Указатель на структуру GameInfo_t.
     */
    static GameInfo_t *getGameInfo_t()
    {
      static GameInfo_t GameInfo;
      return &GameInfo;
    }

    /**
     * @brief Обрабатывает ввод пользователя.
     * @param action Действие пользователя.
     * @param hold Флаг удержания.
     */
    void userInput(UserAction_t action, bool hold);

    // GameInfo_t updateCurrentState();

    /**
     * @brief Инициализирует игровое поле.
     */
    void initilizeField();

    /**
     * @brief Инициализирует игру.
     */
    void gameInit();

    /**
     * @brief Запускает игровой цикл.
     */
    void gameLoop();

    /**
     * @brief Запускает игровой цикл в отдельном потоке.
     */
    void startGameLoop();

    // Observer Pattern
    /**
     * @brief Добавляет наблюдателя.
     * @param observer Указатель на наблюдателя.
     */
    void addObserver(IObserver *observer);

    /**
     * @brief Удаляет последнего наблюдателя.
     */
    void removeLastObserver();

    /**
     * @brief Уведомляет всех наблюдателей.
     */
    void notifyObservers();
  };
}

#endif
