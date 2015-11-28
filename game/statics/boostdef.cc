#include "boostdef.h"

BoostDef::BoostDef(Effect* effect) : NetEffect(effect), boostDef(5) { }

int BoostDef::getAtkNet() {
	return NetEffect::getAtkNet();
}

int BoostDef::getDefNet() {
	return NetEffect::getDefNet() + this->boostDef;
}
