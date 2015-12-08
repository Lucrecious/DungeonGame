#ifndef LEVEL_H
#define LEVEL_H

#include <Utils/stack.hpp>
#include <Global/global.hpp>
#include <Global/kind.hpp>
#include <Utils/vector.hpp>
#include <fstream>
#include <vector>

class Game;
class GameObject;

class Level {
public:
	Level(Game*);
	~Level();

	// Loads an empty level
	void init(std::istream&);

	// Loads the items onto an empty level
	void load(std::istream&);

	// Makes a randomly generated level
	void randomize();

	Game* game;

	// Gets where the player is supposed to spawn
	Vector getPlayerSpawn();
	
	// move the top of the stack at the first given Vector
	//   to the second given Vector
	void move(Vector, Vector);

	// places a given GameObject on the stack of the stack
	//   at the given Vector
	void place(GameObject*, Vector);

	// Checks whether or not the given position is free for the 
	//   incoming GameObject
	bool isFree(Vector, GameObject*) const;

	// Gets the GameObject at the given Vector
	GameObject* get(Vector) const;

	// Takes whatever is at the give Vector
	//   off the floor
	void remove(Vector);

	// Gives the Kind at the given Vector
	Kind getKindAt(Vector) const;

	// Gives the stairs
	GameObject* getStairs() const;

private:
	GameObject* stairs;
	Stack<GameObject*>* tiles[Global::levelHeight][Global::levelWidth];
	// true for empty level, false otherwise
	void load(std::istream&, bool);
	Vector spawn;
	void charToObject(int, int, char, bool);
	Stack<GameObject*>* getStackAt(Vector) const;

	void addKindInRandomLocation(Kind);
	Vector getRandomFloorLocation(int chamber) const;
	int getRandomChamber() const;

	std::vector<Vector> chambers[Global::maxChambers];
};

#endif
