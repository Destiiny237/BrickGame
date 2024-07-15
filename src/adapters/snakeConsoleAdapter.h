#ifndef SNAKECONSOLEADAPTER_H
#define SNAKECONSOLEADAPTER_H

#include "../GameView.h"
#include "../brick_game/snake/headers/model.h"
extern "C"
{
#include "../gui/console/consoleView.h"
}

class SnakeConsoleAdapter : public GameView
{
private:
    s21::SnakeModel &snakeModel;

public:
    SnakeConsoleAdapter(s21::SnakeModel &model) : snakeModel(model)
    {
        // console_view_init();
    }

    void render() override
    {
        // frontend(game, winTet);
    }

    void update() override
    {
        snakeModel.gameLoop();
    }

    // int getInput() override {
    //     return console_view_get_input();
    // }
};

#endif // SNAKECONSOLEADAPTER_H
