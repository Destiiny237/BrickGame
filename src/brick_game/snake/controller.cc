#include "headers/controller.h"

s21::Controller::Controller(SnakeView *view, SnakeModel *model) : QObject(), view(view)
{
    view->installEventFilter(this);
    this->model = model;
    connect(&timer, &QTimer::timeout, this, &Controller::update);
    timer.start(500);
}

s21::Controller::~Controller()
{
    timer.stop();
    disconnect(&timer, &QTimer::timeout, this, &s21::Controller::update);
}

bool s21::Controller::eventFilter(QObject *obj, QEvent *event)
{
    bool isRelease = event->type() == QEvent::KeyRelease;

    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        switch (keyEvent->key())
        {
        case Qt::Key_Up:
            model->userInput(s21::SnakeModel::UserAction_t::Up, !isRelease);
            break;
        case Qt::Key_Down:
            model->userInput(s21::SnakeModel::UserAction_t::Down, !isRelease);
            break;
        case Qt::Key_Left:
            model->userInput(s21::SnakeModel::UserAction_t::Left, !isRelease);
            break;
        case Qt::Key_Right:
            model->userInput(s21::SnakeModel::UserAction_t::Right, !isRelease);
            break;
        }
        return true;
    }
    return QObject::eventFilter(obj, event);
}


void s21::Controller::update()
{
    view->update();
}

