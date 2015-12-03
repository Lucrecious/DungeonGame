#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H


#include "gameobject.h"
#include "turn.h"
#include "statics/effect.h"
#include "statics/potion.h"


const int MAXKNOWNPOTS = 6;

class LivingEntity : public GameObject {
public:
	LivingEntity(Kind, Kind, int, int, int);
	~LivingEntity();

	int getAtkStat() const;
	int getDefStat() const;
	int getMaxHP() const;
	virtual void setHP(int); // virtual for vampire, no hp cap
	int getHP() const;

	virtual Turn getTurn() = 0;

	// These methods are only called by Game when
	//   iterating through the LivingEntity objects
	//   to get the Turn.

	// get the attack damage this entity will give
	//   to the given living entity
	virtual int getAttackDamage(LivingEntity*) const;

	// receive an attack from the given living entity
	//   with the damage given
	virtual bool receiveAttack(LivingEntity*, int);

	// we drink the potion given, this method also
	//   kills the given potion object
	virtual void drink(Potion*);

	// move us by the given vector
	virtual void move(Vector);

	virtual void turnSucceeded(Turn, bool, GameObject*);

	virtual bool isDead() const;

	virtual bool isPotionKnown(Kind);

	void resetEffect();

	// drop whatever needs to be dropped
	virtual void drop();

	virtual int slainGold() const;

protected:
	Effect* effect;

private:
	Kind knownPotions[MAXKNOWNPOTS];
	int numKnownPotions;
	void addNewKnownPotion(Kind);
	
	const int atkStat;
	const int defStat;
	const int maxHP;
	int currentHP;
};




#endif




