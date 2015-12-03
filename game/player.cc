#include "player.h"
#include <iostream>
#include "../globals/global.h"
using namespace std;

Player::Player(Kind subKind, int atk = 0, int def = 0, int hp = 1)
	: LivingEntity(PlayerKind, subKind, atk, def, hp),
	  goldValue(0) { }

Turn Player::getTurn() {
	return this->controller->getInput();
}

void Player::addGold(Gold* gold) {
	this->goldValue += gold->value;
}

void Player::addGold(int gold) {
	this->goldValue += gold;
}

int Player::getGold() const {
	return this->goldValue;
}

bool Player::receiveAttack(LivingEntity* le, int d) {
	if (Global::hitChance(0.5)) {
		return false;
	}

	LivingEntity::receiveAttack(le, d);
	return true;
}
