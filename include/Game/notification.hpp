#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <Game/turn.hpp>
#include <Global/kind.hpp>

class Notification {
public:
	virtual Turn getInput() const = 0;
	virtual void notify(Vector, Kind) const = 0;
};

#endif
