#include "desktopView.h"

s21::SnakeView::SnakeView(QWidget *parent) : QWidget(parent) {}

s21::SnakeView::SnakeView() : QWidget(nullptr) {}

void s21::SnakeView::render()
{
    update();
}

void s21::SnakeView::paintEvent(QPaintEvent *event)
{
    updateMap();
    QWidget::paintEvent(event);
}

void s21::SnakeView::updateMap()
{
    int **field = SnakeModel::getGameInfo_t()->field;

    if (field == nullptr) {
        return;
    }

    QPainter painter(this);

    int cellSize = 50;
    int spacing = 1;

    for (int row = 0; row < 20; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            int x = col * (cellSize + spacing);
            int y = row * (cellSize + spacing);

            int element = field[row][col];

            switch (element)
            {
            case 0: // Пустая область
                painter.setBrush(Qt::gray);
                break;
            case 1: // Часть змейки
                painter.setBrush(Qt::green);
                break;
            case 2: // Яблоко
                painter.setBrush(Qt::red);
                break;
            }

            painter.drawRect(x, y, cellSize, cellSize);
        }
    }
    addStats();
}

void s21::SnakeView::addStats()
{
    int score = SnakeModel::getGameInfo_t()->score;
    QString scoreText = "Score: " + QString::number(score);
    setText(scoreText, 550, 100);

    int highScore = SnakeModel::getGameInfo_t()->high_score;
    QString highScoreText = "High Score: " + QString::number(highScore);
    setText(highScoreText, 550, 150);

    int level = SnakeModel::getGameInfo_t()->level;
    QString levelText = "Level: " + QString::number(level);
    setText(levelText, 550, 200);
}

void s21::SnakeView::setText(QString text, int x, int y){
    QPainter painter(this);
    int textX = x;
    int textY = y;

    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(14);
    painter.setFont(font);

    painter.drawText(textX, textY, text);
}
