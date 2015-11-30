#include "woundatk.h"

WoundAtk::WoundAtk(Effect* effect) : NetEffect(effect), poisonAtk(-5) { }

int WoundAtk::getAtkNet() {
	return NetEffect::getAtkNet() + this->poisonAtk;
}

int WoundAtk::getDefNet() {
	return NetEffect::getDefNet();
}
