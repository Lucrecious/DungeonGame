#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H


#include <Game/gameobject.hpp>
#include <Game/turn.hpp>
#include <Game/Statics/effect.hpp>
#include <Game/Statics/potion.hpp>
#include <iostream>


const int MAXKNOWNPOTS = 6;
 
class LivingEntity : public GameObject {
public:
	const static int DefaultHeals = 3;

	LivingEntity(Kind, Kind, int, int, int);
	~LivingEntity();

	virtual int getAtkStat() const;
	virtual int getDefStat() const;
	int getMaxHP() const;
	virtual void setHP(int);
	int getHP() const;

	virtual Turn getTurn() = 0;

	virtual int getAttackDamage(LivingEntity*) const;
	virtual bool receiveAttack(LivingEntity*, int);
	virtual void drink(Potion*);

	virtual void turnSucceeded(Turn, bool, GameObject*, std::ostream& flavor);

	virtual bool isDead() const;

	virtual bool isPotionKnown(Kind);

	void resetEffect();

	virtual void drop();
	virtual int slainGold() const;

	virtual bool canUseHeal() const;
	virtual void useHeal();

protected:
	Effect* effect;
	int currentHP;
	const int atkStat;
	const int defStat;
	const int maxHP;

private:
	Kind knownPotions[MAXKNOWNPOTS];
	int numKnownPotions;
	void addNewKnownPotion(Kind);

	int maxHeals;
	int usedHeals;
	int healAmount;
	
};




#endif




