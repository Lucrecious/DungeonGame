#include "poisonatk.h"

PoisonAtk::PoisonAtk(Effect* effect) : NetEffect(effect), poisonAtk(-5) { }

int PoisonAtk::getAtkNet() {
	return NetEffect::getAtkNet() + this->poisonAtk;
}

int PoisonAtk::getDefNet() {
	return NetEffect::getDefNet();
}
