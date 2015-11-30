#include "livingentity.h"
#include <math.h>

LivingEntity::LivingEntity(Kind kind)
	: GameObject(LivingKind, kind), effect(0),
	  numKnownPotions(0), atkStat(0), defStat(0),
	  maxHP(0), currentHP(0) {
		  for (int i = 0; i < MAXKNOWNPOTS; i++) {
			  this->knownPotions[i] = NoneKind;
		  }
}

int LivingEntity::getAtkStat() const {
	return this->atkStat + this->effect->getAtkNet();
}

int LivingEntity::getDefStat() const {
	return this->defStat + this->effect->getDefNet();
}

int LivingEntity::getMaxHP() const {
	// TODO: I don't think anything affects this...
	return this->maxHP;
}

void LivingEntity::setHP(int hp) {
	this->currentHP = hp;

	if (hp > this->getMaxHP()) {
		this->currentHP = this->getMaxHP();
	}
	else if (hp < 0) {
		this->currentHP = 0;
	}
}

int LivingEntity::getHP() const{
	return this->currentHP;
}

int LivingEntity::getAttackDamage(LivingEntity* entity) const{
	int damage = ceil((100 / (100 + entity->getDefStat()))) *
		this->getAtkStat();

	return damage;
}

void LivingEntity::receiveAttack(LivingEntity* entity, int dam) {
	this->setHP(this->getHP() - dam);
}

void LivingEntity::drink(Potion* potion) {
	//TODO: we need a different implementation for health pots
	if (true) {
		this->effect = potion->getEffect(this->effect);
		this->addNewKnownPotion(potion->subKind);
	}
}

void LivingEntity::addNewKnownPotion(Kind kind) {
	for (int i = 0; i < this->numKnownPotions; i++) {
		if (kind == this->knownPotions[i]) {
			return;
		}
	}

	this->knownPotions[this->numKnownPotions++] = kind;
}

void LivingEntity::move(Vector movement) {
	Vector newPosition = this->getPosition();
	newPosition.x += movement.x;
	newPosition.y += movement.y;
	this->setPosition(newPosition);
}


void LivingEntity::turnSucceeded(Turn, bool) {
}






