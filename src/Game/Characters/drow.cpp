#include <Game/Characters/drow.hpp>

Drow::Drow() : Player(DrowKind, 25, 15, 150) {
	this->setName("Drow");
}

int Drow::getAtkStat() const {
	int newStat = this->atkStat + this->effect->getAtkNet() * 1.5;
	return newStat < 0 ? 0 : newStat;
}

int Drow::getDefStat() const {
	int newStat = this->defStat + this->effect->getDefNet() * 1.5;
	return newStat < 0 ? 0 : newStat;
}
