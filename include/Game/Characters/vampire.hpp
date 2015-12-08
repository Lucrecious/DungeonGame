#ifndef VAMPIRE_H
#define VAMPIRE_H

#include <Game/player.hpp>
#include <iostream>

class Vampire : public Player {
public:
	Vampire();
	void turnSucceeded(Turn, bool, GameObject*, std::ostream&);
	void setHP(int);

};

#endif
