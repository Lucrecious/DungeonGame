#ifndef HUMAN_H
#define HUMAN_H

#include <Game/enemy.hpp>

class Human : public Enemy {
public:
	Human();
	void drop();
};

#endif
