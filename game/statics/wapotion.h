#ifndef WAPOTION_H
#define WAPOTION_H

#include "potion.h"

class WAPotion : public Potion {
public:
	WAPotion();
	Effect* getEffect(Effect*) const;
};

#endif
