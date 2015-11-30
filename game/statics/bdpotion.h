#ifndef BDPOTION_H
#define BDPOTION_H

#include "potion.h"

class BDPotion : public Potion {
public:
	BDPotion();
	Effect* getEffect(Effect*) const;
};

#endif
