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

TEST_F(InputTest, MoveLeft) {
  
  for(int i = 0; i < 60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_EQ(vx1, 0.0f);
  
  st->processKB(GLFW_KEY_A, 0, GLFW_PRESS, 0);
  
  for(int i = 0; i < 5*60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx2 = cpBodyGetVelocity(heroBody).x;
  
  EXPECT_LT(vx2, 0.0f);
  
}


TEST_F(InputTest, MoveRight) {
  
  for(int i = 0; i < 60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_EQ(vx1, 0.0f);
  
  st->processKB(GLFW_KEY_D, 0, GLFW_PRESS, 0);
  
  for(int i = 0; i < 5*60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx2 = cpBodyGetVelocity(heroBody).x;
  
  EXPECT_GT(vx2, 0.0f);
  
}

// Tests platform support.
TEST_F(CollisionTest, SupportedByPlatform) {
  
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
