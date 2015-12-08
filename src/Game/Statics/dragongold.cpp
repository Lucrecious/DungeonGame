#include <Game/Statics/dragongold.hpp>
#include <Game/Characters/dragon.hpp>
#include <iostream>
using namespace std;

DragonGold::DragonGold() : Gold(GoldDragonKind), dragon(0) {
	//GameObject::ghost = false;
	GameObject::ghost = true;
}

GameObject* DragonGold::findDragon(Vector& freeSpace) {
	GameObject* gobj = 0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) {
				continue;
			}

			Vector v;
			v.x = i;
			v.y = j;
			gobj = this->game->getLevel()->get(this->getPosition() + v);
			if (gobj && gobj->subKind == DragonKind) {
				return gobj;
			}
			else if (gobj && gobj->subKind == FloorKind) {
				freeSpace.x = gobj->getPosition().x;
				freeSpace.y = gobj->getPosition().y;
			}
		}
	}

	return 0;
}

void DragonGold::pair() {
	if (this->dragon) {
		return;
	}

	Vector freeSpace;

	GameObject* gobj = this->findDragon(freeSpace);
	
	if (!gobj) {
		gobj = this->game->addObject(DragonKind);
		this->game->getLevel()->place(gobj, freeSpace);
	}

	this->dragon = static_cast<Dragon*>(gobj);
	this->dragon->pair(this);

}

void DragonGold::unghost() {
	GameObject::ghost = true;
}





