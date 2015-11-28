#ifndef GAME_H
#define GAME_H

#include "livingentity.h"
#include "staticentity.h"
#include "gameobject.h"
#include <vector>

class Game {
public:
	Game();
	~Game();
	int getStaticAmount() const;
	int getLivingAmount() const;
	StaticEntity* getStaticAt(int) const;
	LivingEntity* getLivingAt(int) const;
	GameObject* addObject(Kind);
	void update();
	void setController(Controller*);
private:
	Controller* controller;
	std::vector<StaticEntity*>* statics;
	std::vector<LivingEntity*>* livings;
};


#endif
