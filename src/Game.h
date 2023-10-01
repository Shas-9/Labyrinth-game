#ifndef GAME_INCLDUE
#define GAME_INCLUDE

#include "RenderedObject.h"
#include "Player.h"

class Game {
 private:
  int objects_num;
  RenderedObject *objects;
  Player player;
  bool isGamePaused;

 public:
  Game();
  void updateAll();
  void renderAll();
  void pause();
};

#endif