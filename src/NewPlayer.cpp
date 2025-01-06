#include "NewPlayer.h"

NewPlayer::NewPlayer() {}

NewPlayer::NewPlayer(Vector position, Vector dimensions) : NewEntity(position, dimensions, 3, 10000, 10, "textures/better-player1.png", Vector(14, 18)) {}

int NewPlayer::getScore() { return this->score; }

void NewPlayer::behaviorUpdate() {}