#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "gameobject.h"

class StaticEntity : public GameObject {
public:
	virtual StaticEntity(Kind) = 0;
};


#endif
