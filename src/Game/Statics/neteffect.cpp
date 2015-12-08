#include <Game/Statics/neteffect.hpp>

NetEffect::NetEffect(Effect* effect) {
	this->effect = effect;
}

NetEffect::~NetEffect() {
	delete this->effect;
}

int NetEffect::getAtkNet() {
	return this->effect->getAtkNet();
}

int NetEffect::getDefNet() {
	return this->effect->getDefNet();
}
