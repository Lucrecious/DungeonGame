#ifndef LEVEL_H
#define LEVEL_H

#include "../utils/stack.h"

const int LEVELSIZE = 4;
class Level {
public:
	Level();
	~Level();
	Stack* tiles[LEVELSIZE][LEVELSIZE];
};

#endif
