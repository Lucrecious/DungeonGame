#include "global.h"

double Global::drand(double lower, double upper) {
	double d = (double)rand()/ RAND_MAX;
	return lower + d * (upper - lower);
}

bool Global::hitChance(double c) {
	return drand(0, 1) <= c;
}
