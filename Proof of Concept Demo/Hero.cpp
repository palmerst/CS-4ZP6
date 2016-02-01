#include "Hero.h"

Hero::Hero(float x, float y) : DynamicObject(glm::vec2(x, y), 100, 200, 0, 0, OBJ_HERO,
                                              "./data/obj/testchar",
                                              "./data/shader/vObject.glsl",
                                              "./data/shader/fUniversal.glsl",
                                              true) {}
