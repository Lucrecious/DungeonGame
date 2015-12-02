#ifndef PLAYER_H
#define PLAYER_H

#include "livingentity.h"

class Player : public LivingEntity {
public:
	Player(Kind, int, int, int);
	Turn getTurn();
	bool isDead() const { return false; } //TODO: later
};




#endif
