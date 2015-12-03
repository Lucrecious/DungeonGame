#include "livingentity.h"
#include <math.h>
#include "statics/noeffect.h"
#include "../globals/global.h"
using namespace std;

LivingEntity::LivingEntity(Kind topKind, Kind subKind,
		int atk = 0, int def = 0, int hp = 0)
	: GameObject(topKind, subKind), effect(0), currentHP(hp), 
	  numKnownPotions(0), atkStat(atk), defStat(def),
	  maxHP(hp){
		  for (int i = 0; i < MAXKNOWNPOTS; i++) {
			  this->knownPotions[i] = NoneKind;
		  }

		  this->effect = new NoEffect();
}

LivingEntity::~LivingEntity() {
	delete this->effect;
}

int LivingEntity::getAtkStat() const {
	int newStat = this->defStat + this->effect->getAtkNet();
	return newStat < 0 ? 0 : newStat;
}

int LivingEntity::getDefStat() const {
	int newStat = this->defStat + this->effect->getDefNet();
	return newStat < 0 ? 0 : newStat;
}

int LivingEntity::getMaxHP() const {
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
	int damage = ceil((100 / (100 + (double)entity->getDefStat()))) *
		this->getAtkStat();

	return damage;
}

bool LivingEntity::receiveAttack(LivingEntity* entity, int dam) {
	this->setHP(this->getHP() - dam);
	
	return true;
}

void LivingEntity::drink(Potion* potion) {
	this->addNewKnownPotion(potion->potionKind);
	switch(potion->potionKind) {
		case BAPotionKind:
		case BDPotionKind:
		case WAPotionKind:
		case WDPotionKind:
			this->effect = potion->getEffect(this->effect);
			break;
		
		case RHPotionKind:
			this->setHP(this->getHP() + 10);
			break;
		case PHPotionKind:
			this->setHP(this->getHP() - 10);
			break;
		default:
			break;
	}
}

void LivingEntity::addNewKnownPotion(Kind kind) {
	if (this->isPotionKnown(kind)) {
		return;
	}

	this->knownPotions[this->numKnownPotions++] = kind;
}

void LivingEntity::move(Vector movement) {
	Vector newPosition = this->getPosition();
	newPosition.x += movement.x;
	newPosition.y += movement.y;
	this->setPosition(newPosition);
}

void LivingEntity::turnSucceeded(Turn, bool, GameObject*, ostream&) {
}

bool LivingEntity::isDead() const {
	return this->getHP() <= 0;
}

bool LivingEntity::isPotionKnown(Kind kind) {
	for (int i = 0; i < this->numKnownPotions; i++) {
		if (kind == this->knownPotions[i]) {
			return true;
		}
	}

	return false;
}

void LivingEntity::resetEffect() {
	delete this->effect;
	this->effect = new NoEffect();
}

void LivingEntity::drop() {
}

int LivingEntity::slainGold() const {
	if (Global::hitChance(0.5)) {
		return Global::NormalGold;
	}
	else {
		return Global::SmallGold;
	}
}


