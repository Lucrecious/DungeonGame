#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "../player.h"
#include <iostream>

class Vampire : public Player {
public:
	Vampire();
	void turnSucceeded(Turn, bool, GameObject*, std::ostream&);
	void setHP(int);

};

#endif
