#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <View/view.hpp>
#include <string>
#include <Global/kind.hpp>
#include <iostream>
#include <sstream>
#include <map>
#include <Global/information.hpp>


class TextView : public View {
public:
	TextView(int, int);
	~TextView();
	const int width;
	const int height;
	char** floor;
	void display() const;
	void notify(Vector, Kind);
	void setInformationText(Information);
	void setFlavorText(std::string);
	
	static std::map<Kind,char> kindChar;

private:
	std::ostringstream informationText;
	std::ostringstream flavorText;
	char getCharFromKind(Kind);

	const static int maxFlavorLines = 5;
};

#endif
