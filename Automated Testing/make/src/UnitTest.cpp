#include "Stage.h"
#include "gtest/gtest.h"

class InputTest : public testing::Test {
 protected:

  virtual void SetUp() {
    st = new Stage("./data/stage/testInput.stage");
    heroBody = st->getUserControl()->body;
  }

  virtual void TearDown() {
    delete(st);
  }

  Stage* st;
  cpBody* heroBody;
};


class CollisionTest : public testing::Test {
 protected:

  virtual void SetUp() {
    st = new Stage("./data/stage/testCollision.stage");
    heroBody = st->getUserControl()->body;
  }

  virtual void TearDown() {
    delete(st);
  }

  Stage* st;
  cpBody* heroBody;
};


// test move left input
TEST_F(InputTest, MoveLeft) {

  for(int i = 0; i < 60*10; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_EQ(vx1, 0.0f);

  st->processKB(GLFW_KEY_A, 0, GLFW_PRESS, 0);

  for(int i = 0; i < 60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float vx2 = cpBodyGetVelocity(heroBody).x;

  EXPECT_LT(vx2, 0.0f);

}

// test move right input
TEST_F(InputTest, MoveRight) {

  for(int i = 0; i < 60*10; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_EQ(vx1, 0.0f);

  st->processKB(GLFW_KEY_D, 0, GLFW_PRESS, 0);

  for(int i = 0; i < 60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float vx2 = cpBodyGetVelocity(heroBody).x;

  EXPECT_GT(vx2, 0.0f);

}

// test stop moving left
TEST_F(InputTest, StopMoveLeft) {

  st->processKB(GLFW_KEY_A, 0, GLFW_PRESS, 0);

  for(int i = 0; i < 60*10; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_LT(vx1, 0.0f);

  st->processKB(GLFW_KEY_A, 0, GLFW_RELEASE, 0);

  for(int i = 0; i < 60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float vx2 = cpBodyGetVelocity(heroBody).x;

  EXPECT_NEAR(vx2, 0.0f, 0.01f);

}


// test stop moving right
TEST_F(InputTest, RightStop) {

  st->processKB(GLFW_KEY_D, 0, GLFW_PRESS, 0);

  for(int i = 0; i < 60*10; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_GT(vx1, 0.0f);

  st->processKB(GLFW_KEY_D, 0, GLFW_RELEASE, 0);

  for(int i = 0; i < 60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float vx2 = cpBodyGetVelocity(heroBody).x;

  EXPECT_NEAR(vx2, 0.0f, 0.01f);

}


// jump test
TEST_F(InputTest, JumpFromPlatform) {

  for(int i = 0; i < 60*10; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float vy1 = cpBodyGetVelocity(heroBody).y;
  EXPECT_NEAR(vy1, 0.0f, 0.01f);

  st->processKB(GLFW_KEY_SPACE, 0, GLFW_PRESS, 0);
  st->processKB(GLFW_KEY_SPACE, 0, GLFW_RELEASE, 0);

  for(int i = 0; i < 60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float vy2 = cpBodyGetVelocity(heroBody).y;

  EXPECT_GT(vy2, 0.0f);

}




// Tests platform support.
TEST_F(CollisionTest, BlockByWallMovingLeft) {

  st->processKB(GLFW_KEY_A, 0, GLFW_PRESS, 0);

  float xInit = cpBodyGetPosition(heroBody).x;

  EXPECT_NEAR(xInit, 0.0f, 0.01f);

  for(int i = 0; i < 5*60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float x1 = cpBodyGetPosition(heroBody).x;

  EXPECT_NE(x1, 0.0f);

  for(int i = 0; i < 5*60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float x2 = cpBodyGetPosition(heroBody).x;


  EXPECT_NEAR(x1, x2, 0.01f);

}

// Tests platform support.
TEST_F(CollisionTest, BlockByWallMovingRight) {

  st->processKB(GLFW_KEY_D, 0, GLFW_PRESS, 0);

  float xInit = cpBodyGetPosition(heroBody).x;

  EXPECT_NEAR(xInit, 0.0f, 0.01f);

  for(int i = 0; i < 5*60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float x1 = cpBodyGetPosition(heroBody).x;

  EXPECT_NE(x1, 0.0f);

  for(int i = 0; i < 5*60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }

  float x2 = cpBodyGetPosition(heroBody).x;


  EXPECT_NEAR(x1, x2, 0.01f);

}

// Tests platform support.
TEST_F(CollisionTest, SupportedByPlatformStationary) {

  for(int i = 0; i < 60; i++){
    st->updateEnvironment(1.0f/60.0f);
  }

  float y1 = cpBodyGetPosition(heroBody).y;

  for(int i = 0; i < 5*60; i++){
    st->updateEnvironment(1.0f/60.0f);
  }

  float y2 = cpBodyGetPosition(heroBody).y;

  EXPECT_NEAR(y1, y2, 0.01f);

}

// Tests platform support from freefall.
TEST_F(CollisionTest, SupportedByPlatformFreefall) {

  for(int i = 0; i < 60; i++){
    st->updateEnvironment(1.0f/60.0f);
  }

  float y1 = cpBodyGetPosition(heroBody).y;
  cpBodySetVelocity(heroBody, cpv(0, -100));

  for(int i = 0; i < 5*60; i++){
    st->updateEnvironment(1.0f/60.0f);
  }

  float y2 = cpBodyGetPosition(heroBody).y;

  EXPECT_NEAR(y1, y2, 0.01f);

}
