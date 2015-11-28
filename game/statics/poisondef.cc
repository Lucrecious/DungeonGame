#include "poisondef.h"

PoisonDef::PoisonDef(Effect* effect) :  NetEffect(effect), poisonDef(-5) { }

int PoisonDef::getAtkNet() {
	return NetEffect::getAtkNet();
}

int PoisonDef::getDefNet() {
	return NetEffect::getDefNet() + this->poisonDef;
}
