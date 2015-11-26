#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H


#include "gameobject.h"
#include "turn.h"

class Potion;
class Effect;

class LivingEntity : public GameObject {
public:
	LivingEntity(Kind);
	int getAtkStat();
	int getDefStat();
	int getMaxHP();
	virtual void setHP(int); // virtual for vampire, no hp cap
	int getHP();

	virtual Turn getTurn() = 0;

	// These methods are only called by Game when
	//   iterating through the LivingEntity objects
	//   to get the Turn.

	// get the attack damage this entity will give
	//   to the given living entity
	virtual int getAttackDamage(LivingEntity*);

	// receive an attack from the given living entity
	//   with the damage given
	virtual void receiveAttack(LivingEntity*, int);

	// we drink the potion given, this method also
	//   kills the given potion object
	virtual void drink(Potion*);

	// move us by the given vector
	virtual void move(Vector);

protected:
	Effect* effect;

private:
	// TODO: need a better add structure for this
	Kind knownPotions;
	void addNewKnownPotion(Kind);
	
	const int atkStat;
	const int defStat;
	const int maxHP;
	int currentHP;
};




#endif




