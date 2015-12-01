#ifndef POTION_H
#define POTION_H

#include "../staticentity.h"
#include "effect.h"
#include <iostream>

class Potion : public StaticEntity {
public:
	const Kind potionKind;
	Potion(Kind);
	Effect* getEffect(Effect*) const;
};

#endif
