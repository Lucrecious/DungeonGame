#ifndef LEVEL_H
#define LEVEL_H

#include "../utils/stack.h"
#include "../globals/global.h"
#include "../globals/kind.h"
#include "../utils/vector.h"
#include <fstream>

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

	Game* game;

	Vector getPlayerSpawn();
	
	void move(Vector, Vector);
	void place(GameObject*, Vector);
	bool isFree(Vector, GameObject*) const;
	GameObject* get(Vector) const;
	void remove(Vector);
	Kind getKindAt(Vector) const;

private:
	Stack<GameObject*>* tiles[Global::levelHeight][Global::levelWidth];
	// true for empty level, false otherwise
	void load(std::istream&, bool);
	Vector spawn;
	void charToObject(int, int, char, bool);
	Stack<GameObject*>* getStackAt(Vector) const;
};

#endif
