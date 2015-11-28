#include "boostatk.h"

BoostAtk::BoostAtk(Effect* effect) : NetEffect(effect), atkBoost(5) { }

int BoostAtk::getAtkNet() {
	return NetEffect::getAtkNet() + this->atkBoost;
}

int BoostAtk::getDefNet() {
	return NetEffect::getDefNet();
}
