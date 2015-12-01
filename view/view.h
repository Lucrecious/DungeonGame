#ifndef VIEW_H
#define VIEW_H

#include "../globals/kind.h"
#include "../utils/vector.h"

class View {
public:
	virtual ~View() { };
	virtual void display() const = 0;
	virtual void notify(Vector, Kind) = 0;
};

#endif
