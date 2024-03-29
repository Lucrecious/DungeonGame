#ifndef VECTOR_H
#define VECTOR_H

struct Vector {
	int x;
	int y;
	Vector operator+(Vector v) {
		Vector sum;
		sum.x = x + v.x;
		sum.y = y + v.y;

		return sum;
	}

	Vector operator-(Vector v) {
		Vector diff;
		diff.x = x - v.x;
		diff.y = y - v.y;

		return diff;
	}
};


#endif
