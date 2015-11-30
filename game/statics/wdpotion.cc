#include "wdpotion.h"
#include "wounddef.h"

WDPotion::WDPotion() : Potion(WDPotionKind) { }

Effect* WDPotion::getEffect(Effect* effect) const {
	return new WoundDef(effect);
}
