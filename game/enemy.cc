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
				this->getPosition() - gobj->getPosition());
	}

	// make a random direction
	Vector direction;
	direction.x = 0;
	direction.y = -1;

	cout << "end of turn for the enemy -- enemy.cc" << endl;
	
	return Turn(Move, direction);
}

Player* Enemy::isPlayerAround() const{
	cout << "game: " << this->game << " -- enemy.cc" << endl;
	Player* player = this->game->getPlayer();
	cout << "player: " << player << " -- enemy.cc" << endl;
	Vector diff = player->getPosition() - this->getPosition();
	int distance = diff.x*diff.x + diff.y*diff.y;
	cout << "before distance check -- enemy.cc" << endl;
	if (distance <= 2) {
		return player;
	}

	return 0;
}




