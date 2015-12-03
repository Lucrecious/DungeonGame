#include "vampire.h"

Vampire::Vampire() : Player(VampireKind, 25, 25, 50) {
	this->setName("Vampire");
}

void Vampire::turnSucceeded(Turn turn, bool s, GameObject* gobj){
	if (turn.kind == Attack && s) {
		if (gobj && gobj->subKind == DwarfKind) {
			this->setHP(this->getHP() - 5);
		}
		else {
			this->setHP(this->getHP() + 5);
		}
	}
}

void Vampire::setHP(int hp) {
	this->currentHP = hp;
	if (hp < 0) {
		this->currentHP = 0;
	}
}
