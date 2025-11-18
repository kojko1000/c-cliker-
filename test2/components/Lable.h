#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

class Label {
private:
	sf::Font font;
	sf::Text text;
	bool fontloaded = false;
public:
	bool loadFont(const std::string& fontPath) {
		if (!font.loadFromFile(fontPath))
			return false;

		fontloaded = true;
		text.setFont(font);
		return true;
	}


	void setString(const std::string& str) {
		text.setString(str);
	}
	void setPosition(float x, float y){
		text.setPosition(x, y);
	}
	void draw(sf::RenderWindow& window) {
		if(fontloaded)
			window.draw(text);
	}


};