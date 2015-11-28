#include "textview.h"
#include <iostream>
using namespace std;

TextView::TextView(int w, int h) : width(w), height(h) {
	this->floor = new char*[h];
	for (int i = 0; i < h; i++) {
		this->floor[i] = new char[w];
		for (int j = 0; j < w; j++) {
			this->floor[i][j] = ' ';
		}
	}
}

TextView::~TextView() {
	for (int i = 0; i < this->height; i++) {
		delete[] this->floor[i];
	}

	delete[] this->floor;
}


void TextView::display() const {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			cout << this->floor[i][j];
		}
		cout << endl;
	}
}

void TextView::notify(Vector v, Kind k) {
	this->floor[v.y][v.x] = this->getCharFromKind(k);
}

char TextView::getCharFromKind(Kind kind) {
	switch(kind) {
		case FloorKind:
			return '.';
		case VWallKind:
			return '|';
		case HWallKind:
			return '-';
		default:
			return '?';
	}
}




