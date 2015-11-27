#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "turn.h"

class Notification {
public:
	virtual Turn getInput() const = 0;
};

#endif
