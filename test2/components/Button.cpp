#include "Button.h"
#include "GlobalState.h"
#include <random>
 
	//________________INIT_______________
	//загрузка текстур
	bool Button::loadTextures(const std::vector<std::string>& paths) { 
	for (const std::string path : paths) {
		sf::Texture texture;
		if (!texture.loadFromFile(path)) {
			std::cout << "ne" << path << std::endl;
			return false;
		}
		textures.push_back(texture);
	}
	if (!textures.empty())
		sprite.setTexture(textures[0]);
	return true;
	}
	//
	void Button::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	//
	void Button::onClick() {
		if (textures.empty()) return;
		startShake();
		static std::mt19937 gen(std::random_device{}());
		std::uniform_real_distribution<float> dis(0, 100);
		float critChance = dis(gen);

		

		// Увеличиваем scrap при изменении целой части состояния
		
		if ((int)state != (int)(state + GlobalState::clickCost)) {
			GlobalState::scrap++;

		
			float scrapChance = dis(gen);
			
			if ((float)GlobalState::scrapCritChans >= scrapChance) 
			{
				GlobalState::scrap++;
				startScrapBonus();
			}
		}
		state = state + GlobalState::clickCost;
		if ((float)GlobalState::critChans >= critChance)
		{
			startCritBonus();
			shakeIntensity = shakeIntensity * 2;

			if ((int)state != (int)(state + GlobalState::clickCost)) {
				GlobalState::scrap++;


				float scrapChance = dis(gen);

				if ((float)GlobalState::scrapCritChans >= scrapChance)
				{
					GlobalState::scrap++;
					startScrapBonus();
				}
			}

			state = state + GlobalState::clickCost;
		}

		// Проверяем, достигли ли мы конца текущего набора текстур
		if (state >= 4) {
			// Переходим к следующему набору текстур
			texturePack++;
			state = 0;
			GlobalState::disassembledCount++;
			// Если прошли все наборы текстур, увеличиваем счетчик разобранных деталей
			if (texturePack >= textures.size() / 4) { // предполагая, что каждый набор имеет 4 текстуры
				
				texturePack = 0; // сбрасываем к первому набору
			}
		}

		// Вычисляем индекс текстуры: текущее состояние + смещение текущего набора
		int textureIndex = (int)state + (texturePack * 4);

		// Защита от выхода за границы массива
		if (textureIndex < textures.size()) {
			sprite.setTexture(textures[textureIndex]);
		}
		else {
			// Если индекс вне границ, сбрасываем к началу
			textureIndex = 0;
			texturePack = 0;
			state = 0;
			sprite.setTexture(textures[0]);
		}

		std::cout << textureIndex << std::endl;
		GlobalState::clickCount++;
	}

	
	//_____________GETS__________________
	sf::FloatRect Button::getBounds()			{return sprite.getGlobalBounds();}

	bool Button::contains(sf::Vector2f point)	{return sprite.getGlobalBounds().contains(point);}

	sf::Vector2f Button::getPosition()			{return sprite.getPosition();}

	float Button::getState()					{ return state; }

	//_____________SETS__________________
	void Button::setScale(float scale)			{Button::sprite.setScale(scale, scale);}

	void Button::setPosition(float x, float y)	{sprite.setPosition(x, y);}
	//________причины_ТРЯСКИ!___________
	void Button::startShake() {
		if (!isShaking) {
			isShaking = true;
			originalPos = sprite.getPosition();
			shakeTimer.restart();
		}
	}

	void Button::updateShake() {
		if (isShaking) {
			float elapsed = shakeTimer.getElapsedTime().asSeconds();
			if (elapsed < shakeDuration)
			{
				//rand
				static std::mt19937 gen(std::random_device{}());
				std::uniform_real_distribution<float> dis(-shakeIntensity, shakeIntensity);

				float offsetX = dis(gen);
				float offsetY = dis(gen);
				sprite.setPosition(originalPos.x + offsetX, originalPos.y + offsetY);
			}
			else
			{
				isShaking = false;
				sprite.setPosition(originalPos);
			}
		}
	}
	//Бонусы
	bool Button::getIsScrapBonus() { return isScrapBonus;}

	void Button::startScrapBonus() {
		if (!isScrapBonus) {
			isScrapBonus = true;
			scrapBonusTimer.restart();
		}
	}

	void Button::updateScrapBonus(){
		if (isScrapBonus) {
			float elapsed = scrapBonusTimer.getElapsedTime().asSeconds();
			if (elapsed > bonusDuration)
				isScrapBonus = false;
			
		}
	}
	//Бонусы
	bool Button::getIsCritBonus() { return isCritBonus; }

	void Button::startCritBonus() {
		if (!isCritBonus) {
			isCritBonus = true;
			critBonusTimer.restart();
		}
	}

	void Button::updateCritBonus() {
		if (isCritBonus) {
			float elapsed = critBonusTimer.getElapsedTime().asSeconds();
			if (elapsed > bonusDuration) {
				isCritBonus = false;
				shakeIntensity = shakeIntensity / 2;
			}
		}
	}