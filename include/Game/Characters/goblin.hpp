#ifndef GOBLIN_H
#define GOBLIN_H

#include <Game/player.hpp>
#include <iostream>

class Goblin : public Player {
public:
	Goblin();
	void turnSucceeded(Turn, bool, GameObject*, std::ostream&);

};

#endif
