#ifndef ENEMY_H
#define ENEMY_H

#include "livingentity.h"
#include "player.h"

class Enemy : public LivingEntity {
public:
	Enemy(Kind, int, int, int);
	Turn getTurn();

	virtual Player* isPlayerAround() const;
};

#endif
