#ifndef DROW_H
#define DROW_H

#include "../player.h"
#include "../statics/potion.h"

class Drow : public Player {
public:
	Drow();
	int getAtkStat() const;
	int getDefStat() const;
};

#endif
