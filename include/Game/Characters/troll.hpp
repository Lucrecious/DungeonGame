#ifndef TROLL_H
#define TROLL_H

#include <Game/player.hpp>
#include <iostream>

class Troll : public Player {
public:
	Troll();
	void turnSucceeded(Turn, bool, GameObject*, std::ostream&);
};

#endif
