#ifndef SNAKE_H
#define SNAKE_H

#include <list>

namespace s21
{
    /**
     * @class Snake
     * @brief Класс, представляющий змейку в игре.
     */
    class Snake
    {
    public:
        friend class ModelTest;

        /**
         * @struct snakePart
         * @brief Структура, представляющая часть змейки.
         */
        struct snakePart
        {
            int x;  /**< Координата x части змейки */
            int y;  /**< Координата y части змейки */

            /**
             * @brief Конструктор структуры snakePart.
             * @param x Координата x.
             * @param y Координата y.
             */
            snakePart(int x, int y)
            {
                this->x = x;
                this->y = y;
            }
        };

        /**
         * @enum direction
         * @brief Перечисление направлений движения змейки.
         */
        enum direction
        {
            LEFT,  /**< Влево */
            RIGHT, /**< Вправо */
            UP,    /**< Вверх */
            DOWN   /**< Вниз */
        };

        /**
         * @brief Конструктор класса Snake.
         */
        Snake();

        /**
         * @brief Деструктор класса Snake.
         */
        ~Snake();

        std::list<snakePart> snakeParts; /**< Список частей змейки. */
        direction currentDirection = DOWN; /**< Текущее направление движения змейки. */

        /**
         * @brief Перемещение змейки.
         */
        void snakeMovement();

        /**
         * @brief Увеличение размера змейки.
         */
        void increaseSize();

        /**
         * @brief Добавление новой части к змейке.
         * @param x Координата x новой части.
         * @param y Координата y новой части.
         */
        void addCell(int x, int y);

        /**
         * @brief Движение змейки вправо.
         */
        void GoRight();

        /**
         * @brief Движение змейки влево.
         */
        void GoLeft();

        /**
         * @brief Движение змейки вверх.
         */
        void GoUp();

        /**
         * @brief Движение змейки вниз.
         */
        void GoDown();

        // For tests
        /**
         * @brief Установить позицию головы змейки.
         * @param x Координата x головы.
         * @param y Координата y головы.
         */
        void setHeadPosition(int x, int y);

        /**
         * @brief Получить позицию головы змейки.
         * @return Позиция головы змейки.
         */
        snakePart getHeadPosition() const;

        /**
         * @brief Добавить часть тела к змейке.
         * @param x Координата x новой части.
         * @param y Координата y новой части.
         */
        void addBodyPart(int x, int y);
    };
}

#endif
