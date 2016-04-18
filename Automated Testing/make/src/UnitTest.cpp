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

//stop10s stop1s
//velocity.y=0 velocity.x=0
TEST_F(InputTest, StopStop) {
  
  for(int i = 0; i < 60*10; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_EQ(vx1, 0.0f);
  
  st->processKB(GLFW_KEY_A, 0, GLFW_RELEASE, 0);
  st->processKB(GLFW_KEY_D, 0, GLFW_RELEASE, 0);
  
  for(int i = 0; i < 60; i++){
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx2 = cpBodyGetVelocity(heroBody).x;
  
  EXPECT_EQ(vx2, 0.0f);
  
}

//stop 10s left 1s
//velocity.y=0 velocity.x=decress
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

//stop 10s right 1s
//velocity.y=0 velocity.x=increase
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

//left 10s stop 1s
//velocity.y=0 velocity.x=0
TEST_F(InputTest, LeftStop) {
  
  for(int i = 0; i < 60*10; i++){
	st->processKB(GLFW_KEY_A, 0, GLFW_PRESS, 0);
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
  
  EXPECT_EQ(vx2, 0.0f);
  
}


//left 10s left 1s
//velocity.y=0 velocity.x=unchanged
TEST_F(InputTest, LeftLeft) {
  
  for(int i = 0; i < 60*10; i++){
	st->processKB(GLFW_KEY_A, 0, GLFW_PRESS, 0);
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_LT(vx1, 0.0f);
    
  for(int i = 0; i < 60; i++){
	st->processKB(GLFW_KEY_A, 0, GLFW_PRESS, 0);
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx2 = cpBodyGetVelocity(heroBody).x;
  
  EXPECT_EQ(vx2, vx1);
  
}

//left 10 right 1
//velocity.y=0 velocity.x=increse
TEST_F(InputTest, LeftRight) {
  
  for(int i = 0; i < 60*10; i++){
	st->processKB(GLFW_KEY_A, 0, GLFW_PRESS, 0);
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_LT(vx1, 0.0f);
    
  for(int i = 0; i < 60; i++){
	st->processKB(GLFW_KEY_D, 0, GLFW_PRESS, 0);
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx2 = cpBodyGetVelocity(heroBody).x;
  
  EXPECT_GT(vx2, vx1);
  
}

//right 10 stop 1
//velocity.y=0 velocity.x=0
TEST_F(InputTest, RightStop) {
  
  for(int i = 0; i < 60*10; i++){
	st->processKB(GLFW_KEY_D, 0, GLFW_PRESS, 0);
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
  
  EXPECT_EQ(vx2, 0.0f);
  
}


//right 10 left 1
//velocity.y=0 velocity.x=decress
TEST_F(InputTest, RightLeft) {
  
  for(int i = 0; i < 60*10; i++){
	st->processKB(GLFW_KEY_D, 0, GLFW_PRESS, 0);
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_GT(vx1, 0.0f);
  
  for(int i = 0; i < 60; i++){
	st->processKB(GLFW_KEY_A, 0, GLFW_PRESS, 0);
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx2 = cpBodyGetVelocity(heroBody).x;
  
  EXPECT_LT(vx2, vx1);
  
}


//right 10s right 1s
//velocity.y=0 velocity.x=unchanged
TEST_F(InputTest, RightRight) {
  
  for(int i = 0; i < 60*10; i++){
	st->processKB(GLFW_KEY_D, 0, GLFW_PRESS, 0);
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx1 = cpBodyGetVelocity(heroBody).x;
  EXPECT_GT(vx1, 0.0f);
  
  for(int i = 0; i < 60; i++){
	st->processKB(GLFW_KEY_D, 0, GLFW_PRESS, 0);
    st->processContinuousInput();
    st->updateEnvironment(1.0f/60.0f);
  }
  
  float vx2 = cpBodyGetVelocity(heroBody).x;
  
  EXPECT_EQ(vx2, vx1);
  
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
