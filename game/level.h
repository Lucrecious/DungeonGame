#ifndef LEVEL_H
#define LEVEL_H

#include "../utils/stack.h"

class Game;
class GameObject;

const int LEVELSIZE = 4;
class Level {
public:
	Level(Game*);
	~Level();
	Stack<GameObject*>* tiles[LEVELSIZE][LEVELSIZE];
	Game* game;
};

#endif
