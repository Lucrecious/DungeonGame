#include <Game/Characters/merchant.hpp>
#include <Global/global.hpp>

Merchant::Merchant() : Enemy(MerchantKind, 70, 5, 30) {
	this->setName("Merchant");
}

bool Merchant::receiveAttack(LivingEntity* le, int dam) {
	this->game->makeMerchantsHostile();
	return Enemy::receiveAttack(le, dam);
}

Turn Merchant::getTurn() {
	if (this->game->merchantsHostile()) {
		return Enemy::getTurn();
	}
	
	Vector v;
	v.x = 0;
	v.y = 0;
	
	while (v.x == 0 && v.y == 0) {
		v.x = Global::irand(-1, 1);
		v.y = Global::irand(-1, 1);
	}

	return Turn(Move, v);
}

void Merchant::drop() {
	GameObject* gold = this->game->addObject(GoldMerchantKind);
	this->game->getLevel()->place(gold, this->getPosition());
}



