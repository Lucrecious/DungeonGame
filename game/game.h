#ifndef GAME_H
#define GAME_H

#include "level.h"
#include "../globals/kind.h"
#include <vector>

class Controller;
class LivingEntity;
class StaticEntity;
class GameObject;

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
	void init();
	void setController(Controller*);
private:
	Controller* controller;
	std::vector<StaticEntity*>* statics;
	std::vector<LivingEntity*>* livings;
	Level* currentLevel;
};


#endif
