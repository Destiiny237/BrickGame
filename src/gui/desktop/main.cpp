#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include "../../GameView.h"
#include "../../adapters/snakeConsoleAdapter.h"

void startSnakeDesktop()
{
    s21::SnakeModel *model = new s21::SnakeModel();
    s21::SnakeView *view = new s21::SnakeView();

    model->gameInit();
    // qDebug() << "Field address after gameInit: " << model->getGameInfo_t()->field;
    model->addObserver(view);
    model->startGameLoop();

    s21::Controller *controller = new s21::Controller(view, model);

    view->resize(800, 1030);
    view->show();
}

void startSnakeConsole()
{
    s21::SnakeModel *model = new s21::SnakeModel();
    GameView *view = new SnakeConsoleAdapter(*model);

    model->gameInit();
    model->startGameLoop();

    s21::SnakeModel::getGameInfo_t()->field();

    if (winTet)
        frontend(game, winTet);

    view->render();
}

void startTetrisDesktop()
{
    s21::SnakeView *view = new s21::SnakeView();
    TetGame_t *game = initGame();
    while (game->gameStatus != Terminate)
    {
        int ch = getch();
        userAction(game, ch);
        if (game->gameStatus != Pause)
        {
            updateCurrentState(game);
        }
        usleep(2000);

        // if (winTet) frontend(game, winTet);
        view->updateMap(); // передать информацию о поле сюда и отрисовать
    }

    freeGame(game);

    if (winTet)
    {
        freeWindows(winTet);
        endwin();
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (false)
    {
        QApplication app(argc, argv);
        startSnakeDesktop();
        return app.exec();
    }
    else
    {
        startSnakeConsole();
    }
}