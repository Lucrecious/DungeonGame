#include "player.h"

Player::Player(Kind kind) : LivingEntity(kind) { }

Turn Player::getTurn() {
	Vector vec;
	return Turn(Attack, vec);
}
