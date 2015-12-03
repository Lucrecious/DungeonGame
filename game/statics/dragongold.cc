#include "dragongold.h"
#include "../characters/dragon.h"

DragonGold::DragonGold() : Gold(GoldDragonKind), dragon(0) {
	GameObject::ghost = false;
}

void DragonGold::pair() {
	
	if (this->dragon) {
		return;
	}

	Vector freeSpace;

	GameObject* gobj = 0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) {
				continue;
			}
			Vector v;
			v.x = i;
			v.y = j;
			gobj = this->game->getLevel()->get(v);
			if (gobj && gobj->subKind == DragonKind) {
				break;
			}
			else if (gobj && gobj->subKind == FloorKind) {
				freeSpace = gobj->getPosition();
			}

			gobj = 0;
		}
	}
	
	if (!gobj) {
		gobj = this->game->addObject(DragonKind);
	}

	this->dragon = static_cast<Dragon*>(gobj);
	this->dragon->pair(this);
	this->game->getLevel()->place(this->dragon, freeSpace);

}

void DragonGold::unghost() {
	GameObject::ghost = true;
}





