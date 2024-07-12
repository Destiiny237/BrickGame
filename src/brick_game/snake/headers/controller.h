#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QKeyEvent>
#include <QTimer>

#include "model.h"
#include "snake.h"
#include "../../../gui/desktop/desktopView.h"

namespace s21
{
    /**
     * @class Controller
     * @brief Класс, управляющий взаимодействием между моделью и представлением в игре "Змейка".
     */
    class Controller : public QObject
    {
        Q_OBJECT
    private:
        SnakeModel *model;          /**< Указатель на модель игры. */
        SnakeView *view;       /**< Указатель на представление игры. */
        QTimer timer;          /**< Таймер для обновления игрового процесса. */

    public:
        /**
         * @brief Конструктор класса Controller.
         * @param view Указатель на представление игры.
         * @param model Указатель на модель игры.
         */
        Controller(SnakeView *view, SnakeModel *model);

        /**
         * @brief Деструктор класса Controller.
         */
        ~Controller();
        
        /**
         * @brief Фильтр событий для обработки нажатий клавиш.
         * @param obj Указатель на объект, генерирующий событие.
         * @param event Указатель на событие.
         * @return true, если событие обработано, иначе false.
         */
        bool eventFilter(QObject *obj, QEvent *event) override;

    private slots:
        /**
         * @brief Слот для обновления состояния игры.
         */
        void update();
    };
}

#endif // CONTROLLER_H
