#ifndef WDPOTION_H
#define WDPOTION_H

#include "potion.h"

class WDPotion : public Potion {
public:
	WDPotion();
	Effect* getEffect(Effect*) const;
};

#endif
