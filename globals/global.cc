#include "global.h"

double Global::drand(double lower, double upper) {
	double d = (double)rand()/ RAND_MAX;
	return lower + d * (upper - lower);
}

int Global::irand(int lower, int upper) {
	double i = rand() % (upper + 1 - lower);
	return lower + i;
}

bool Global::hitChance(double c) {
	return drand(0, 1) <= c;
}
