#ifndef TURN_H
#define TURN_H


#include "vector.h"
#include "turnkind.h"

class Turn {
public:
	const TurnKind kind;

	Turn(TurnKind, Vector);

	// Target vector for the potion, attack and move
	Vector target;
};


#endif
