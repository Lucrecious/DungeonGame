#ifndef ENEMY_H
#define ENEMY_H

#include <Game/livingentity.hpp>
#include <Game/player.hpp>

class Enemy : public LivingEntity {
public:
	Enemy(Kind, int, int, int);
	Turn getTurn();

	// To check if the player is around to attack him!
	//   Unless the entity is a merchant...
	virtual Player* isPlayerAround() const;
};

#endif
