#include "livingentity.h"
#include <math.h>

LivingEntity::LivingEntity(Kind kind)
	: GameObject(kind), atkStat(0), defStat(0), maxHP(0),
	  currentHP(0), effect(0) {
}

int LivingEntity::getAtkStat() {
	// TODO: effects need to affect this
	return this->atkStat;
}

int LivingEntity::getDefStat() {
	//TODO: effects need to affect this
	return this->defStat;
}

int LivingEntity::getMaxHP() {
	// TODO: make sure nothing affects this?
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

int LivingEntity::getHP() {
	return this->currentHP;
}

int LivingEntity::getAttackDamage(LivingEntity* entity) {
	int damage = ceil((100 / (100 + entity->getDefStat()))) *
		this->getAtkStat();

	return damage;
}

void LivingEntity::receiveAttack(LivingEntity* entity, int dam) {
	this->setHP(this->getHP() - dam);
}

void LivingEntity::drink(Potion* potion) {
	// TODO: do something with the potion...
	// TODO: add an effect decorator
}

void LivingEntity::move(Vector movement) {
	Vector newPosition = this->getPosition();
	newPosition.x += movement.x;
	newPosition.y += movement.y;
	this->setPosition(newPosition);
}









