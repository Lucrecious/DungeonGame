#include "player.h"

Player::Player(Kind kind) : LivingEntity(kind) { }

Turn Player::getTurn() {
	return this->controller->getInput();
}
