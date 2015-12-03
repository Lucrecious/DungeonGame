#ifndef HUMAN_H
#define HUMAN_H

#include "../enemy.h"

class Human : public Enemy {
public:
	Human();
	void drop();
};

#endif
