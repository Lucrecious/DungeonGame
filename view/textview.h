#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "view.h"

class TextView : public View {
public:
	TextView(int, int);
	~TextView();
	const int width;
	const int height;
	char** floor;
	void display() const;
	void notify(Vector, Kind);
private:
	char getCharFromKind(Kind);
};

#endif
