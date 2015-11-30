#include "player.h"
#include <iostream>
using namespace std;

Player::Player(Kind kind, int atk = 0, int def = 0, int hp = 1)
	: LivingEntity(kind, atk, def, hp) { }

Turn Player::getTurn() {
	cout << this->controller << endl;
	return this->controller->getInput();
}
