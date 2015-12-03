#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "../player.h"

class Vampire : public Player {
public:
	Vampire();
	void turnSucceeded(Turn, bool, GameObject*);
	void setHP(int);

};

#endif
