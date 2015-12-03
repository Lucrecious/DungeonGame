#include "dragon.h"
#include "../statics/dragongold.h"

Dragon::Dragon() : Enemy(DragonKind, 20, 20, 150) {
	this->setName("Dragon");
}

void Dragon::pair(DragonGold* gold) {
	this->gold = gold;
}

Turn Dragon::getTurn() {
	Vector ppos = this->game->getPlayer()->getPosition();

	Vector diffDragon = this->getPosition() - ppos;
	Vector diffGold = this->gold->getPosition() - ppos;

	int distDragon = diffDragon.x * diffDragon.x +
					 diffDragon.y * diffDragon.y;
	int distGold = diffGold.x * diffGold.x +
				   diffGold.y * diffGold.y;

	if (distDragon <= 2 || distGold <= 2) {
		return Turn(Attack, diffDragon);
	}

	Vector v;
	v.x = 0;
	v.y = 0;
	return Turn(Move, v);
}

void Dragon::turnSucceeded(Turn, bool) {
	if (this->isDead()) {
		this->gold->unghost();
	}
}
