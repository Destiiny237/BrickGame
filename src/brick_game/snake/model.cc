#include <fstream>
#include "headers/model.h"

void s21::SnakeModel::gameInit()
{
    speedMultiplier = 1; // +0.05 per level
    gameLoopInterval = STANDARTSPEED;

    initilizeField();

    createSnake();
    snake->increaseSize();
    snake->increaseSize();
    createApple();

    readHighScore();

    currentState = Moving;
}

void s21::SnakeModel::gameLoop()
{
    switch (currentState)
    {
    case Moving:
        handleMovingState();
        updateGrid();
        break;
    case EatApple:
        handleEatAppleState();
        updateGrid();
        break;
    case Collided:
        handleCollidedState();
        break;
    case GameOver:
        writeHighScore();
        break;
    case WinGame:
        break;
    }

    gameLoopInterval = (hold ? ACCELERATESPEED : STANDARTSPEED) / speedMultiplier;

    notifyObservers();
}

void s21::SnakeModel::readHighScore() {
    std::ifstream inFile("Game/high_score.txt");
    if (inFile.is_open()) {
        inFile >> SnakeModel::getGameInfo_t()->high_score;
        inFile.close();
    } else {
        SnakeModel::getGameInfo_t()->high_score = 0;
    }
}

void s21::SnakeModel::writeHighScore() {
    std::ofstream outFile("Game/high_score.txt");
    if (outFile.is_open()) {
        outFile << SnakeModel::getGameInfo_t()->high_score;
        outFile.close();
    }
}

void s21::SnakeModel::levelUp()
{
    if (s21::SnakeModel::getGameInfo_t()->level != 10){
        s21::SnakeModel::getGameInfo_t()->level += 1;
        speedMultiplier += 0.05;
    }
}

void s21::SnakeModel::handleMovingState()
{
    bool collisionDetected = checkCollisionWithBorders() || checkCollisionWithSnake();
    if (collisionDetected)
    {
        currentState = Collided;
    }
    else
    {
        snake->snakeMovement();
    }

    if (checkCollisionWithApple())
    {
        currentState = EatApple;
    }
    if (checkWin())
    {
        currentState = WinGame;
    }
}

void s21::SnakeModel::handleEatAppleState()
{
    snake->increaseSize();
    SnakeModel::getGameInfo_t()->score += 1;
    
    if(SnakeModel::getGameInfo_t()->score > SnakeModel::getGameInfo_t()->high_score)
    {
        SnakeModel::getGameInfo_t()->high_score++;
    }
    
    if (SnakeModel::getGameInfo_t()->score % 10 == 0)
    {
        levelUp();
    }

    currentState = Moving;
}

void s21::SnakeModel::handleCollidedState()
{
    currentState = GameOver;
}

void s21::SnakeModel::setApplePosition(const s21::Snake::snakePart &position)
{
    if (apple == nullptr)
    {
        apple = new Apple_t();
    }
    apple->x = position.x;
    apple->y = position.y;
}

void s21::SnakeModel::startGameLoop()
{
    std::thread gameLoopThread([this]()
                               {
        while (true) {
            gameLoop();
            std::this_thread::sleep_for(std::chrono::milliseconds(gameLoopInterval));
        } });

    gameLoopThread.detach();
}

void s21::SnakeModel::userInput(UserAction_t action, bool hold)
{
    this->hold = hold;
    switch (action)
    {
    case Up:
        if (snake->currentDirection != s21::Snake::DOWN)
            snake->currentDirection = s21::Snake::UP;
        break;
    case Down:
        if (snake->currentDirection != s21::Snake::UP)
            snake->currentDirection = s21::Snake::DOWN;
        break;
    case Left:
        if (snake->currentDirection != s21::Snake::RIGHT)
            snake->currentDirection = s21::Snake::LEFT;
        break;
    case Right:
        if (snake->currentDirection != s21::Snake::LEFT)
            snake->currentDirection = s21::Snake::RIGHT;
        break;
    default:
        break;
    }
}

void s21::SnakeModel::createApple()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int randX, randY;
    if (apple)
    {
        delete apple;
    }
    do
    {
        randX = rand() % HEIGHT;
        randY = rand() % WIDTH;
    } while (s21::SnakeModel::isSnakeCell(randX, randY));
    apple = new Apple_t();
    apple->x = randX;
    apple->y = randY;
}

bool s21::SnakeModel::checkCollisionWithApple()
{
    if (snake->snakeParts.front().x == apple->x && snake->snakeParts.front().y == apple->y)
    {
        createApple();
        return true;
    }
    return false;
}

bool s21::SnakeModel::checkCollisionWithBorders()
{
    int headX = snake->snakeParts.front().x;
    int headY = snake->snakeParts.front().y;

    switch (snake->currentDirection)
    {
    case Snake::LEFT:
        headY -= 1;
        break;
    case Snake::RIGHT:
        headY += 1;
        break;
    case Snake::UP:
        headX -= 1;
        break;
    case Snake::DOWN:
        headX += 1;
        break;
    }

    if (headX < 0 || headX >= 20 || headY < 0 || headY >= 10)
    {
        return true;
    }
    return false;
}

bool s21::SnakeModel::isSnakeCell(int x, int y)
{
    auto it = ++snake->snakeParts.begin();

    for (; it != snake->snakeParts.end(); ++it)
    {
        if (x == it->x && y == it->y)
        {
            return true;
        }
    }
    return false;
}

bool s21::SnakeModel::checkCollisionWithSnake()
{
    s21::Snake::snakePart head = snake->snakeParts.front();

    if (s21::SnakeModel::isSnakeCell(head.x, head.y))
    {
        return true;
    }
    return false;
}

bool s21::SnakeModel::checkWin()
{
    if (snake->snakeParts.size() >= 200)
    {
        return true;
    }
    return false;
}

void s21::SnakeModel::addObserver(IObserver *observer)
{
    observers.push_back(observer);
}

void s21::SnakeModel::removeLastObserver()
{
    observers.pop_back();
}

void s21::SnakeModel::notifyObservers()
{
    for (IObserver *observer : observers)
    {
        observer->render();
    }
}

void s21::SnakeModel::createSnake()
{
    snake = new s21::Snake();
}

void s21::SnakeModel::updateSnake()
{
    for (s21::Snake::snakePart part : snake->snakeParts)
    {
        SnakeModel::getGameInfo_t()->field[part.x][part.y] = 1;
    }
}

void s21::SnakeModel::initilizeField()
{
    SnakeModel::getGameInfo_t()->field = new int *[HEIGHT];

    for (int row = 0; row < HEIGHT; row++)
    {
        SnakeModel::getGameInfo_t()->field[row] = new int[WIDTH];
        for (int col = 0; col < WIDTH; col++)
        {
            SnakeModel::getGameInfo_t()->field[row][col] = 0;
        }
    }
}

void s21::SnakeModel::updateGrid()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            SnakeModel::getGameInfo_t()->field[i][j] = 0;
        }
    }
    updateSnake();
    SnakeModel::getGameInfo_t()->field[apple->x][apple->y] = 2;
}

s21::SnakeModel::~SnakeModel()
{
    if (snake != nullptr)
    {
        delete snake;
        snake = nullptr;
    }

    for (int row = 0; row < HEIGHT; ++row)
    {
        delete[] SnakeModel::getGameInfo_t()->field[row];
    }
    delete[] SnakeModel::getGameInfo_t()->field;

    observers.clear();
}
