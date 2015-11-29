#ifndef LEVEL_H
#define LEVEL_H

#include "../utils/stack.h"
#include "../globals/global.h"
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

	Stack<GameObject*>* tiles[Global::levelHeight][Global::levelWidth];
	Game* game;
private:
	// true for empty level, false otherwise
	void load(std::istream&, bool);
	void charToObject(int, int, char, bool);
};

#endif
