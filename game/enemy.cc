#include "enemy.h"
#include "math.h"
#include <iostream>
using namespace std;

Enemy::Enemy(Kind kind, int atk, int def, int hp)
	 : LivingEntity(EnemyKind, kind, atk, def, hp) {
}

Turn Enemy::getTurn() {
	Player* gobj = this->isPlayerAround();

	if (gobj) {
		return Turn(Attack,
				 gobj->getPosition() - this->getPosition());
	}

	// make a random direction
	Vector direction;
	direction.x = 0;
	direction.y = -1;

	return Turn(Move, direction);
}

Player* Enemy::isPlayerAround() const{
	Player* player = this->game->getPlayer();
	Vector diff = player->getPosition() - this->getPosition();
	int distance = diff.x*diff.x + diff.y*diff.y;
	if (distance <= 2) {
		return player;
	}

	return 0;
}




