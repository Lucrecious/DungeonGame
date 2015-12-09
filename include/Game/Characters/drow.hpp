#ifndef DROW_H
#define DROW_H

#include <Game/player.hpp>
#include <Game/Statics/potion.hpp>

class Drow : public Player {
public:
	Drow();
	int getAtkStat() const;
	int getDefStat() const;

	void drink(Potion*);

private:
	const static double scale = 2;
	const static int heal = 25;
};

#endif
