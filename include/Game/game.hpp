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
	
	// For the objects outside of game to access the amount
	//   of static objects
	int getStaticAmount() const;

	// For the objects outside of game to access the amount
	//   of living objects
	int getLivingAmount() const;

	// For objects outside of game to access an object in
	//   the static vector
	StaticEntity* getStaticAt(int) const;

	// For the objects outside of game to access an object in
	//   the living vector
	LivingEntity* getLivingAt(int) const;

	// Adds an object of the given Kind, and keeps track
	//   of whether it is a static entity or living entity
	GameObject* addObject(Kind);

	// Calls getTurn on all living entities to get them to
	//   do their turn and progress the game
	void update();

	// Makes a level out of a file stream
	void buildLevel(std::istream&);

	// Makes a level randomly
	void buildRandomLevel();

	// Sets the controller
	void setController(Controller*);

	// Makes the player and sets it
	void setPlayer(Kind);

	// A way for game and outside objects to keep track of the
	//   player object
	Player* getPlayer() const;

	// A way to pass player information to the controller
	void passInformationText() const;

	// A way to pass the flavor text to the controller
	void passFlavorText(std::string) const;

	// Adds to the flavor text all the potions that are nearby the player
	void printNearByPotionsIfAny(LivingEntity*, std::ostream&);

	// Pushes the game into the next level
	bool goToNextLevel() const;

	// Gets whether or not the player is dead to end the game
	bool isPlayerDead() const;

	// Gets the level/floor number to deterine when the game
	//   is over
	int getLevelNumber() const;

	// Gets the amount of gold the player has to determine score
	int getCurrentScore() const;

	// Gets the level the player is on
	Level* getLevel() const;

	// Keeps track of whether or not the merchants have become hostile
	bool merchantsHostile() const;

	// Makes all the merchants hostile
	void makeMerchantsHostile();
	
private:
	// Plays out of a turn of a given game object, and keeps track of what's
	//   happening in the flavor text
	bool doTurn(Turn, LivingEntity*, std::ostream&, GameObject*&);

	// Kills all objects in the game except for the player object
	//   which is persistent
	void clearNonPlayerObjects();

	// Notifies the controller that the entire level has changed
	void notifyWholeLevel();

	// A ptr to the controller
	Controller* controller;

	// All the static objects in the game
	std::vector<StaticEntity*>* statics;

	// All the living objects in the game
	std::vector<LivingEntity*>* livings;

	// The level number we're on
	int levelNumber;

	// The level we're on
	Level* level;

	// The player
	Player* player;

	// Whether or not the merchants are hostile
	bool merchantsAttack;

	// Things that must happen before a level builds
	void preInitLevel();

	// Things that must happen after a level builds
	void postInitLevel();
};


#endif
