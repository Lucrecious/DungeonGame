#ifndef GAME_H
#define GAME_H

#include <Game/level.hpp>
#include <Global/kind.hpp>
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
	
	GameObject* addObject(Kind);

	void update();

	void buildLevel(std::istream&);
	void buildRandomLevel();

	void setController(Controller*);

	void setPlayer(Kind);
	Player* getPlayer() const;

	void passInformationText() const;
	void passFlavorText(std::string) const;
	void printNearByPotionsIfAny(LivingEntity*, std::ostream&) const;

	bool goToNextLevel() const;

	bool isPlayerDead() const;
	int getLevelNumber() const;
	int getCurrentScore() const;
	Level* getLevel() const;

	bool merchantsHostile() const;
	void makeMerchantsHostile();
	
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

	bool merchantsAttack;

	void preInitLevel();
	void postInitLevel();
};


#endif
