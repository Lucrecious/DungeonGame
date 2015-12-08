#include <Game/Characters/dragon.hpp>
#include <Game/Statics/dragongold.hpp>
#include <iostream>
using namespace std;

Dragon::Dragon() : Enemy(DragonKind, 20, 20, 150), dgold(0) {
	this->setName("Dragon");
}

void Dragon::pair(DragonGold* gold) {
	if (this->dgold) {
		return;
	}

	this->dgold = gold;
}

Turn Dragon::getTurn() {
	Vector ppos = this->game->getPlayer()->getPosition();

	Vector diffDragon = ppos - this->getPosition();
	Vector diffGold = this->dgold->getPosition() - ppos;

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
