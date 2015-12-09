#include <Game/Characters/drow.hpp>

Drow::Drow() : Player(DrowKind, 25, 15, 150) {
	this->setName("Drow");
}

int Drow::getAtkStat() const {
	int newStat = this->atkStat + this->effect->getAtkNet() * Drow::scale;
	return newStat < 0 ? 0 : newStat;
}

int Drow::getDefStat() const {
	int newStat = this->defStat + this->effect->getDefNet() * Drow::scale;
	return newStat < 0 ? 0 : newStat;
}

void Drow::drink(Potion* potion) {
	switch(potion->potionKind) {
		case RHPotionKind:
			this->setHP(this->getHP() + Drow::heal);
			break;
		case PHPotionKind:
			this->setHP(this->getHP() - Drow::heal);
			break;
		default:
			break;
	}
}
