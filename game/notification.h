#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "turn.h"
#include "../globals/kind.h"

class Notification {
public:
	virtual Turn getInput() const = 0;
	virtual void notify(Vector, Kind) const = 0;
};

#endif
