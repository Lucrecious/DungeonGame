#include "orc.h"
#include "../../globals/kind.h"
#include <iostream>
using namespace std;

Orc::Orc() : Enemy(OrcKind, 30, 25, 180) {
	this->setName("Orc");
}

int Orc::getAttackDamage(LivingEntity* le) const {
	double factor = 1;
	if (le->subKind == GoblinKind) {
		factor = 1.5;
	}

	return Enemy::getAttackDamage(le) * factor;
}
