#include "headers/snake.h"
#include "headers/model.h"

s21::Snake::Snake()
{
    snakePart head(1, 1);
    snakeParts.push_front(head);
    addCell(snakeParts.front().x + 1, snakeParts.back().y);
}

s21::Snake::~Snake()
{
    snakeParts.clear();
}

void s21::Snake::addCell(int x, int y)
{
    snakePart newPart(x, y);
    snakeParts.push_front(newPart);
}

void s21::Snake::increaseSize()
{
    switch (currentDirection)
    {
    case RIGHT:
        GoRight();
        break;
    case LEFT:
        GoLeft();
        break;
    case UP:
        GoUp();
        break;
    case DOWN:
        GoDown();
        break;
    }
}

void s21::Snake::GoRight()
{
    addCell(snakeParts.front().x, snakeParts.front().y + 1);
}

void s21::Snake::GoLeft()
{
    addCell(snakeParts.front().x, snakeParts.front().y - 1);
}

void s21::Snake::GoUp()
{
    addCell(snakeParts.front().x - 1, snakeParts.front().y);
}

void s21::Snake::GoDown()
{
    addCell(snakeParts.front().x + 1, snakeParts.front().y);
}

void s21::Snake::setHeadPosition(int x, int y) {
    if (snakeParts.size() > 0) {
        snakeParts.front().x = x;
        snakeParts.front().y = y;
    }
}

s21::Snake::snakePart s21::Snake::getHeadPosition() const {
    if (!snakeParts.empty()) {
        return snakeParts.front();
    } else {
        return {0, 0}; // Возвращаем координаты по умолчанию, если змея пуста
    }
}

void s21::Snake::addBodyPart(int x, int y) {
    snakeParts.push_back({x, y});
}

void s21::Snake::snakeMovement()
{
    switch (currentDirection)
    {
    case RIGHT:
        GoRight();
        break;
    case LEFT:
        GoLeft();
        break;
    case UP:
        GoUp();
        break;
    case DOWN:
        GoDown();
        break;
    }
    snakeParts.pop_back();
}
