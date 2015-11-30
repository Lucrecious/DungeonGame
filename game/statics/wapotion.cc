#include "wapotion.h"
#include "woundatk.h"

WAPotion::WAPotion() : Potion(WAPotionKind) { }

Effect* WAPotion::getEffect(Effect* effect) const {
	return new WoundAtk(effect);
}
