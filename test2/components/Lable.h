#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <random>

class Label {
private:
	//общие
	sf::Font font;
	sf::Text text;
	bool fontloaded = false;
	//мигание
	bool isBlinking = false;
	sf::Clock blinkLongestTimer;
	float blinkLong = 0.5;
		//движуха

	//___________INIT___________
public:
	bool loadFont(const std::string & fontPath) {
		if (!font.loadFromFile(fontPath))
			return false;

		fontloaded = true;
		text.setFont(font);
		return true;
	}

	void draw(sf::RenderWindow& window) {
		if (fontloaded)
			window.draw(text);
	}
	void centrHorizontal(float windowWidth)
	{
		sf::FloatRect bounds = text.getGlobalBounds();
		text.setPosition((windowWidth - bounds.width) / 2, text.getPosition().y);
	}
	//_____________SETS__________
	void setString(const std::string& str) {
		if (text.getString() != str){ text.setString(str);startBlinking();}
	}
	void setPosition(float x, float y) { text.setPosition(x, y); }
	void setColor(const sf::Color& color) { text.setFillColor(color); }
	void setSize(unsigned int size) { text.setCharacterSize(size); }
	void setOutline(float thickness, const sf::Color& color)
	{
		text.setOutlineThickness(thickness);
		text.setOutlineColor(color);
	}
	//_____________EFFECTS_______
	void startBlinking()
	{
			isBlinking = true;
			blinkLongestTimer.restart(); 
	}
	void update()
	{
		sf::Color currentColor = text.getFillColor();
		if (blinkLongestTimer.getElapsedTime().asSeconds() < blinkLong) {
			static std::mt19937 gen(std::random_device{}());
			std::uniform_real_distribution<float> dis(180, 255);
			if (isBlinking) {
				if (currentColor.a < 255) {
					currentColor.a = dis(gen);
				}
				else {
					currentColor.a = 128;
				}
				text.setFillColor(currentColor);
			}
		}
		else {
			isBlinking = false;
			currentColor.a = 255;
			text.setFillColor(currentColor);
		}
	}

	
};
