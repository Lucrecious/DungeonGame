#include "bdpotion.h"
#include "boostdef.h"

BDPotion::BDPotion() : Potion(BDPotionKind) { }

Effect* BDPotion::getEffect(Effect* effect) const {
	return new BoostDef(effect);
}
