#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H


#include "gameobject.h"
#include "turn.h"
#include "statics/effect.h"
#include "statics/potion.h"
#include <iostream>


const int MAXKNOWNPOTS = 6;
 
// Originally my ideas for DLC were to allow enemies to drink potions,
//   which is why the entirety of livingentity can technically drink potions
//   given the correct logic!
//   I also thought I was going to have more than one player for the game as DLC
class LivingEntity : public GameObject {
public:
	LivingEntity(Kind, Kind, int, int, int);
	~LivingEntity();

	virtual int getAtkStat() const;
	virtual int getDefStat() const;
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

	// Runs at the end of the turn for all living entities
	virtual void turnSucceeded(Turn, bool, GameObject*, std::ostream& flavor);

	// returns whether or not this living entity is dead
	virtual bool isDead() const;

	// Checks whether or not a given potion is known
	virtual bool isPotionKnown(Kind);

	// resets the effect of the potions
	void resetEffect();

	// drop whatever needs to be dropped
	virtual void drop();

	// gold given when the entity is slain
	virtual int slainGold() const;

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
	
};




#endif




