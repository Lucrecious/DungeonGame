#include "merchant.h"

Merchant::Merchant() : Enemy(MerchantKind, 70, 5, 30) {
	this->setName("Merchant");
}

/* TODO 
bool Merchant::isHostile(){
	//if one merchant is attacked, all merchants in the level
	//change from neutral to aggressive
}


*/

