#ifndef LEVEL_H
#define LEVEL_H

#include "../utils/stack.h"
#include "../globals/global.h"
#include "../globals/kind.h"
#include "../utils/vector.h"
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

	Vector getPlayerSpawn();
	
	void move(Vector, Vector);
	void place(GameObject*, Vector);
	bool isFree(Vector, GameObject*) const;
	GameObject* get(Vector) const;
	void remove(Vector);
	Kind getKindAt(Vector) const;
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
