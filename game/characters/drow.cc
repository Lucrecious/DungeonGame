#include "drow.h"

Drow::Drow() : Player(DrowKind, 25, 15, 150) {
	this->setName("Drow");
}

int Drow::getAtkStat() const {
	return this->atkStat + this->effect->getAtkNet() * 1.5;
}

int Drow::getDefStat() const {
	return this->defStat + this->effect->getDefNet() * 1.5;
}