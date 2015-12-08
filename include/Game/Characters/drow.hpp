#ifndef DROW_H
#define DROW_H

#include <Game/player.hpp>
#include <Game/Statics/potion.hpp>

class Drow : public Player {
public:
	Drow();
	int getAtkStat() const;
	int getDefStat() const;
};

#endif
