#include <Game/enemy.hpp>
#include "math.h"
#include <iostream>
#include <Global/global.hpp>
#include <Game/game.hpp>
#include <Game/player.hpp>
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
		cout << "segmentation here? -- enemy.cc" << endl;
		v = this->game->getPlayer()->getPosition() - this->getPosition();
		int dist = v.x*v.x + v.y*v.y;
		v.x = (v.x*v.x)/dist;
		v.y = (v.y*v.y)/dist;
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
	cout << "in squared -- enemy.cc" << endl;
	Vector diff = player->getPosition() - this->getPosition();
	cout << "in squared (after) --enemy.cc" << endl;

	return diff.x*diff.x + diff.y*diff.y;
}


