#include <Game/enemy.hpp>
#include "math.h"
#include <iostream>
#include <Global/global.hpp>
#include <Game/game.hpp>
#include <Game/player.hpp>
#include <math.h>
using namespace std;

Enemy::Enemy(Kind kind, int atk, int def, int hp)
	 : LivingEntity(EnemyKind, kind, atk, def, hp) {
}

Turn Enemy::getTurn() {
	if (this->isPlayerReachable()) {
		return Turn(Attack, this->game->getPlayer()->getPosition() - this->getPosition());
	}

	Vector v = { 0, 0 };

	if (this->isPlayerAround()) {
		v = this->game->getPlayer()->getPosition() - this->getPosition();
		int dist = v.x*v.x + v.y*v.y;
		int signx = v.x > 0 ? 1 : -1;
		int signy = v.y > 0 ? 1 : -1;
		v.x = round(signx*(v.x*v.x)/(double)dist);
		v.y = round(signy*(v.y*v.y)/(double)dist);
	} else {
		while (v.x == 0 && v.y == 0) {
			v.x = Global::irand(-1, 1);
			v.y = Global::irand(-1, 1);
		}
	}

	return Turn(Move, v);
}

Player* Enemy::isPlayerReachable() const {
	if (this->getSquaredDistanceFromPlayer() <= 2) {
		return this->game->getPlayer();
	}

	return 0;
}

Player* Enemy::isPlayerAround() const {
	if (this->getSquaredDistanceFromPlayer() <= 10) {
		return this->game->getPlayer();
	}

	return 0;
}

int Enemy::getSquaredDistanceFromPlayer() const {
	Player* player = this->game->getPlayer();
	Vector diff = player->getPosition() - this->getPosition();

	return diff.x*diff.x + diff.y*diff.y;
}


