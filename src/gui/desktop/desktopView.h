#ifndef VIEW_H
#define VIEW_H

#include "ui_mainwindow.h"
#include "qpainter.h"
#include "../../brick_game/snake/headers/IObserver.h"
#include "../../brick_game/snake/headers/model.h"

namespace s21
{
    class SnakeView : public QWidget, public IObserver
    {
    public:
        SnakeView(QWidget *parent);
        SnakeView();

        void render() override;

    private:
        virtual void paintEvent(QPaintEvent *event) override;

        void updateMap();
        void setText(QString text, int x, int y);
        void addStats();
    };
}
#endif // VIEW_H