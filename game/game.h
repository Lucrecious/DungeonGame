#ifndef GAME_H
#define GAME_H

#include "level.h"
#include "../globals/kind.h"
#include <vector>
#include <string>
#include <iostream>

class Controller;
class LivingEntity;
class StaticEntity;
class GameObject;
class Player;
struct Turn;

class Game {
public:
	const static int levelAmt = 5;
	Game();
	~Game();
	int getStaticAmount() const;
	int getLivingAmount() const;
	StaticEntity* getStaticAt(int) const;
	LivingEntity* getLivingAt(int) const;
	GameObject* addObject(Kind);
	void update();
	void buildLevel(std::istream&);
	void setController(Controller*);
	void setPlayer(Kind);
	Player* getPlayer() const;

	void passInformationText() const;
	void passFlavorText(std::string) const;

	void printNearByPotionsIfAny(LivingEntity*, std::ostream&);
private:
	bool doTurn(Turn, LivingEntity*, std::ostream&, GameObject*&);
	void clearNonPlayerObjects();
	void notifyWholeLevel();
	Controller* controller;
	std::vector<StaticEntity*>* statics;
	std::vector<LivingEntity*>* livings;
	int levelNumber;
	Level* level;
	Player* player;
};


#endif
