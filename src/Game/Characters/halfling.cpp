#include <Game/Characters/halfling.hpp>
#include <Global/global.hpp>

Halfling::Halfling() : Enemy(HalflingKind, 15, 20, 100) {
	this->setName("Halfling");
}

bool Halfling::receiveAttack(LivingEntity* le, int dam) {
	if (Global::hitChance(0.5)) {
		return Enemy::receiveAttack(le, dam);
	}
	else {
		return false;
	}
}
