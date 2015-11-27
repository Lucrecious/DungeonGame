#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "notification.h"

class Controller : public Notification {
public:
	Controller(std::istream&);
	Turn getInput() const;
private:
	std::istream& in;
	Vector getDirection(std::string) const;
};

#endif
