#ifndef ENEMY_H
#define ENEMY_H

#include <Game/livingentity.hpp>

class Player;

class Enemy : public LivingEntity {
public:
	Enemy(Kind, int, int, int);
	Turn getTurn();
	virtual Player* isPlayerReachable() const;
	virtual Player* isPlayerAround() const;
private:
	int getSquaredDistanceFromPlayer() const;
};

#endif
