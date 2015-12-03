#include "troll.h"

Troll::Troll() : Player(TrollKind, 25, 15, 120) {
	this->setName("Troll");
}


void Troll::turnSucceeded(Turn, bool, GameObject*) {
	this->setHP(this->getHP() + 5);
}
