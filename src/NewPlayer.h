#ifndef NEW_PLAYER_INCLUDE
#define NEW_PLAYER_INCLUDE

#include "NewEntity.h"

class NewPlayer : public NewEntity {
protected:
  int score;

public:
  NewPlayer();
  NewPlayer(Vector position, Vector dimensions);
  int getScore();

  void behaviorUpdate();
};

#endif