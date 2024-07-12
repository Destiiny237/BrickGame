#ifndef GAMEVIEW_H
#define GAMEVIEW_H

class GameView {
public:
    virtual void render() = 0;
    virtual void update() = 0;
    // virtual int getInput() = 0;
    virtual ~GameView() {}
};

#endif // GAMEVIEW_H
