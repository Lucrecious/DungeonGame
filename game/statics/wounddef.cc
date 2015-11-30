#include "wounddef.h"

WoundDef::WoundDef(Effect* effect) :  NetEffect(effect), poisonDef(-5) { }

int WoundDef::getAtkNet() {
	return NetEffect::getAtkNet();
}

int WoundDef::getDefNet() {
	return NetEffect::getDefNet() + this->poisonDef;
}
