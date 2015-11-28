#ifndef VIEW_H
#define VIEW_H

#include "../game/kind.h"
#include "../game/vector.h"

class View {
public:
	virtual void display() const = 0;
	virtual void notify(Vector, Kind) = 0;
};

#endif
