#include "player.h"
#include <iostream>
using namespace std;

Player::Player(Kind subKind, int atk = 0, int def = 0, int hp = 1)
	: LivingEntity(PlayerKind, subKind, atk, def, hp) { }

Turn Player::getTurn() {
	return this->controller->getInput();
}
