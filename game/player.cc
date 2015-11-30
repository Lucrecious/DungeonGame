#include "player.h"
#include <iostream>
using namespace std;

Player::Player(Kind kind) : LivingEntity(kind) { }

Turn Player::getTurn() {
	cout << this->controller << endl;
	return this->controller->getInput();
}
