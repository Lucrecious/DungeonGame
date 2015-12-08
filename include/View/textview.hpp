#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <View/view.hpp>
#include <string>
#include <Global/kind.hpp>
#include <iostream>
#include <sstream>


class TextView : public View {
public:
	TextView(int, int);
	~TextView();
	const int width;
	const int height;
	char** floor;
	void display() const;
	void notify(Vector, Kind);
	void setInformationText(
			int atk, int def, int hp, int hpmax, int gold, std::string race, int level);
	void setFlavorText(std::string);
private:
	std::ostringstream informationText;
	std::ostringstream flavorText;
	char getCharFromKind(Kind);
};

#endif
