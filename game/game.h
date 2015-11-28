#ifndef GAME_H
#define GAME_H

#include <vector>
#include "livingentity.h"
#include "gameobject.h"

class Game {
public:
	int getObjectAmount() const;
	int getLivingAmount() const;
	GameObject* getObjectAt() const;
	LivingEntity* getLivingAt() const;
	void addObject(GameObject*);
private:
	vector<GameObject>* objects;
	vector<LivingEntity>* livings;
};


#endif
