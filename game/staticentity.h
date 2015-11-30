#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "gameobject.h"

class StaticEntity : public GameObject {
public:
	StaticEntity(Kind kind) : GameObject(StaticKind, kind) {
		if (kind == FloorKind || kind == PassageKind) {
			GameObject::ghost = true;
		}
	}
};


#endif
