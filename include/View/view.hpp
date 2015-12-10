#ifndef VIEW_H
#define VIEW_H

#include <Global/kind.hpp>
#include <Utils/vector.hpp>
#include <string>

struct Information;

class View {
public:
	virtual ~View() { };
	virtual void display() const = 0;
	virtual void setInformationText(Information) = 0;
	virtual void setFlavorText(std::string) = 0;
	virtual void notify(Vector, Kind) = 0;
};

#endif
