#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "../../brick_game/snake/headers/model.h"
#include "../../brick_game/snake/headers/IObserver.h"
#include "../../brick_game/snake/headers/controller.h"
#include "../../brick_game/snake/headers/snake.h"

#include "desktopView.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
