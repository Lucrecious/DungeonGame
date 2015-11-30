#include "bapotion.h"
#include "boostatk.h"

BAPotion::BAPotion() : Potion(BAPotionKind) { }

Effect* BAPotion::getEffect(Effect* effect) const {
	return new BoostAtk(effect);
}
