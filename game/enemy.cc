#include "enemy.h"
#include "math.h"
#include <iostream>
#include "../globals/global.h"
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

	Vector v;
	v.x = 0;
	v.y = 0;

	while (v.x == 0 && v.y == 0) {
		v.x = Global::irand(-1, 1);
		v.y = Global::irand(-1, 1);
	}

	return Turn(Move, v);
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




