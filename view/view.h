#ifndef VIEW_H
#define VIEW_H

#include "../globals/kind.h"
#include "../utils/vector.h"
#include <string>

class View {
public:
	virtual ~View() { };
	virtual void display() const = 0;
	virtual void setInformationText(int atk, int def, int hp, int maxhp, int gold, std::string race, int level) = 0;
	virtual void setFlavorText(std::string) = 0;
	virtual void notify(Vector, Kind) = 0;
};

#endif
