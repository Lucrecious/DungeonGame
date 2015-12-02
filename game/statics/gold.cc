#include "gold.h" 
#include "../../globals/global.h"


Gold::Gold(Kind kind)
	: StaticEntity(GoldKind), goldKind(kind),
	  value(getValueFrom(kind)) {	
	GameObject::ghost = true;
	
	switch (kind) {
		case GoldSmallKind:
			this->setName("Small Gold Pile");
			break;
		case GoldNormalKind:
			this->setName("Normal Gold Pile");
			break;
		case GoldMerchantKind:
			this->setName("Merchant Gold Pile");
			break;
		default:
			break;
	}
}

const int Gold::getValueFrom(Kind k) const {
	switch (k) {
		case GoldSmallKind:
			return Global::SmallGold;
		case GoldNormalKind:
			return Global::NormalGold;
		case GoldMerchantKind:
			return Global::MerchantGold;
		default:
			return 0;
	}
}