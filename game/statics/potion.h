#ifndef POTION_H
#define POTION_H

#include "../staticentity.h"

class Effect;

class Potion : public StaticEntity {
public:
	Potion(Kind k) : StaticEntity(k) { };
	virtual Effect* getEffect(Effect*) const = 0;
};

#endif
