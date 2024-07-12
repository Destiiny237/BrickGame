#include <gtest/gtest.h>

#include "../headers/model.h"
#include "../headers/snake.h"

class ModelTest : public ::testing::Test {
protected:
  void SetUp() override {
    model.gameInit();
  }

  s21::SnakeModel model;
};

TEST_F(ModelTest, CreateSnake) {
  ASSERT_NE(model.snake, nullptr);
}

TEST_F(ModelTest, CreateApple) {
  ASSERT_NE(model.apple, nullptr);
}

TEST_F(ModelTest, InitializeField) {
  s21::SnakeModel::GameInfo_t* gameInfo = s21::SnakeModel::getGameInfo_t();
  ASSERT_NE(gameInfo, nullptr);
  ASSERT_NE(gameInfo->field, nullptr);
}

TEST_F(ModelTest, CheckCollisionWithBorders) {
  // Test for collision with borders
  model.snake->setHeadPosition(30, 30);
  ASSERT_TRUE(model.checkCollisionWithBorders());

  model.snake->setHeadPosition(20, 10);
  ASSERT_TRUE(model.checkCollisionWithBorders());

  // Test for no collision with borders
  model.snake->setHeadPosition(5, 5);
  ASSERT_FALSE(model.checkCollisionWithBorders());
}

TEST_F(ModelTest, CheckCollisionWithApple) {
  // Test for collision with apple
  model.setApplePosition(model.snake->getHeadPosition());
  ASSERT_TRUE(model.checkCollisionWithApple());

  // Test for no collision with apple
  model.setApplePosition({5, 5});
  ASSERT_FALSE(model.checkCollisionWithApple());
}

TEST_F(ModelTest, CheckCollisionWithSnake) {
  // Test for collision with snake
  model.snake->addBodyPart(5, 5);
  ASSERT_FALSE(model.checkCollisionWithSnake());

  // Test for no collision with snake
  model.snake->setHeadPosition(5, 5);
  ASSERT_TRUE(model.checkCollisionWithSnake());
}

TEST_F(ModelTest, CheckWin) {
  // Test for winning condition
  for (int i = 0; i < 200; ++i) {
    model.snake->increaseSize();
  }
  ASSERT_TRUE(model.checkWin());
}

TEST_F(ModelTest, CheckNonWin) {
  // Test for non-winning condition
  ASSERT_FALSE(model.checkWin());
}

TEST_F(ModelTest, StateTransitionMovingToEatApple) {
  model.currentState = s21::SnakeModel::Moving;
  model.snake->setHeadPosition(5, 5);
  model.snake->currentDirection = s21::Snake::RIGHT;
  s21::Snake::snakePart applePos(5, 6);
  model.setApplePosition(applePos);
  model.gameLoop();
  ASSERT_EQ(model.currentState, s21::SnakeModel::EatApple);
}

TEST_F(ModelTest, StateTransitionMovingToCollided) {
  model.currentState = s21::SnakeModel::Moving;
  model.snake->setHeadPosition(19, 0);  // Simulate collision with border
  model.snake->currentDirection = s21::Snake::DOWN;
  model.gameLoop();
  ASSERT_EQ(model.currentState, s21::SnakeModel::Collided);
}
///
TEST_F(ModelTest, StateTransitionMovingToCollidedWithSnake) {
  model.currentState = s21::SnakeModel::Moving;
  model.snake->setHeadPosition(5, 5);
  model.snake->addBodyPart(5, 5);  // Simulate collision with snake
  model.snake->currentDirection = s21::Snake::DOWN;
  model.gameLoop();
  ASSERT_EQ(model.currentState, s21::SnakeModel::Collided);
}

TEST_F(ModelTest, StateTransitionEatAppleToMoving) {
  model.currentState = s21::SnakeModel::EatApple;
  model.gameLoop();
  ASSERT_EQ(model.currentState, s21::SnakeModel::Moving);
}

TEST_F(ModelTest, StateTransitionCollidedToGameOver) {
  model.currentState = s21::SnakeModel::Collided;
  model.gameLoop();
  ASSERT_EQ(model.currentState, s21::SnakeModel::GameOver);
}

TEST_F(ModelTest, StateTransitionMovingWithoutCollision) {
  model.currentState = s21::SnakeModel::Moving;
  model.snake->setHeadPosition(5, 5);
  model.snake->currentDirection = s21::Snake::RIGHT;
  model.gameLoop();
  ASSERT_EQ(model.currentState, s21::SnakeModel::Moving);
}

TEST_F(ModelTest, UserInputChangeDirectionUp) {
    model.snake->currentDirection = s21::Snake::RIGHT;
    model.userInput(s21::SnakeModel::UserAction_t::Up, false);
    ASSERT_EQ(model.snake->currentDirection, s21::Snake::UP);
}

TEST_F(ModelTest, UserInputChangeDirectionDown) {
    model.snake->currentDirection = s21::Snake::RIGHT;
    model.userInput(s21::SnakeModel::UserAction_t::Down, false);
    ASSERT_EQ(model.snake->currentDirection, s21::Snake::DOWN);
}

TEST_F(ModelTest, UserInputChangeDirectionLeft) {
    model.snake->currentDirection = s21::Snake::UP;
    model.userInput(s21::SnakeModel::UserAction_t::Left, false);
    ASSERT_EQ(model.snake->currentDirection, s21::Snake::LEFT);
}

TEST_F(ModelTest, UserInputChangeDirectionRight) {
    model.snake->currentDirection = s21::Snake::UP;
    model.userInput(s21::SnakeModel::UserAction_t::Right, false);
    ASSERT_EQ(model.snake->currentDirection, s21::Snake::RIGHT);
}

TEST_F(ModelTest, UserInputHoldTrue) {
    model.userInput(s21::SnakeModel::UserAction_t::Up, true);
    ASSERT_TRUE(model.hold);
}

TEST_F(ModelTest, UserInputHoldFalse) {
    model.userInput(s21::SnakeModel::UserAction_t::Up, false);
    ASSERT_FALSE(model.hold);
}

TEST_F(ModelTest, UserInputPreventReverseUp) {
    model.snake->currentDirection = s21::Snake::DOWN;
    model.userInput(s21::SnakeModel::UserAction_t::Up, false);
    ASSERT_EQ(model.snake->currentDirection, s21::Snake::DOWN);
}

TEST_F(ModelTest, UserInputPreventReverseDown) {
    model.snake->currentDirection = s21::Snake::UP;
    model.userInput(s21::SnakeModel::UserAction_t::Down, false);
    ASSERT_EQ(model.snake->currentDirection, s21::Snake::UP);
}

TEST_F(ModelTest, UserInputPreventReverseLeft) {
    model.snake->currentDirection = s21::Snake::RIGHT;
    model.userInput(s21::SnakeModel::UserAction_t::Left, false);
    ASSERT_EQ(model.snake->currentDirection, s21::Snake::RIGHT);
}

TEST_F(ModelTest, UserInputPreventReverseRight) {
    model.snake->currentDirection = s21::Snake::LEFT;
    model.userInput(s21::SnakeModel::UserAction_t::Right, false);
    ASSERT_EQ(model.snake->currentDirection, s21::Snake::LEFT);
}

TEST_F(ModelTest, SnakeMoveUp) {
    model.snake->setHeadPosition(5, 5);
    model.snake->currentDirection = s21::Snake::UP;
    model.gameLoop();
    ASSERT_EQ(model.snake->getHeadPosition().x, 4);
}

TEST_F(ModelTest, SnakeMoveDown) {
    model.snake->setHeadPosition(5, 5);
    model.snake->currentDirection = s21::Snake::DOWN;
    model.gameLoop();
    ASSERT_EQ(model.snake->getHeadPosition().x, 6);
}

TEST_F(ModelTest, SnakeMoveLeft) {
    model.snake->setHeadPosition(5, 5);
    model.snake->currentDirection = s21::Snake::LEFT;
    model.gameLoop();
    ASSERT_EQ(model.snake->getHeadPosition().y, 4);
}

TEST_F(ModelTest, SnakeMoveRight) {
    model.snake->setHeadPosition(5, 5);
    model.snake->currentDirection = s21::Snake::RIGHT;
    model.gameLoop();
    ASSERT_EQ(model.snake->getHeadPosition().y, 6);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
