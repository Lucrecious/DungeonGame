#include <Game/livingentity.hpp>
#include <math.h>
#include <Game/Statics/noeffect.hpp>
#include <Global/global.hpp>
using namespace std;

const int LivingEntity::DefaultHeals;

LivingEntity::LivingEntity(Kind topKind, Kind subKind,
		int atk = 0, int def = 0, int hp = 0)
	: GameObject(topKind, subKind), effect(0), currentHP(hp), 
	  atkStat(atk), defStat(def), maxHP(hp),
	  numKnownPotions(0), healsLeft(LivingEntity::DefaultHeals), healAmount(hp/2) {
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

int LivingEntity::getHealsLeft() const {
	return this->healsLeft;
}

void LivingEntity::useHeal() {
	this->setHP(this->getHP() + this->healAmount);
	this->healsLeft--;
}
