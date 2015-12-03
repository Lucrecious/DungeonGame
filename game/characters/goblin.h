#ifndef GOBLIN_H
#define GOBLIN_H

#include "../player.h"

class Goblin : public Player {
public:
	Goblin();
	void turnSucceeded(Turn, bool, GameObject*);

};

#endif
