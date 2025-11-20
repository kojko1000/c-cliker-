#include <SFML/Graphics.hpp>
#include "components/Button.h"
#include "components/SimpleButton.h"
#include "components/Lable.h"
#include "components/GlobalState.h"
#include <filesystem>
std::string ProgressConvert(float state);

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "It's WIN!");
    GlobalState::loadFromFile("save.json");

    //---- ШЕЙДЕР ДЛЯ ВСЕГО ОКНА ----
    sf::Shader windowShader;
    sf::Clock shaderClock;
    bool shaderEnabled = true; // Включить/выключить шейдер

    if (!windowShader.loadFromFile("assets/shaders/wave.frag", sf::Shader::Fragment)) {
        std::cout << "NONONONO afectov ne budet" << std::endl;
        shaderEnabled = false;
    }
    //---- ТЕКСТУРА ДЛЯ РЕНДЕРА ----
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(window.getSize().x, window.getSize().y)) {
        std::cout << "Не удалось создать текстуру рендера!" << std::endl;
        return -1;
    }
    sf::Sprite renderSprite(renderTexture.getTexture());

    //----MAIN_BUTTON----
    Button buttonRadio;

    float spriteSize = 7;
    std::vector<std::string> texturesPath = {
        "assets/Radio1.png",
        "assets/Radio2.png",
        "assets/Radio3.png",
        "assets/Radio4.png",
        "assets/TV1.png",
        "assets/TV2.png",
        "assets/TV3.png",
        "assets/TV4.png"
    };
    
    if (!buttonRadio.loadTextures(texturesPath)) return -1;
    buttonRadio.setPosition((window.getSize().x/2) - (32 * spriteSize) / 2, (window.getSize().y / 2) - (32 * spriteSize) / 2);
    buttonRadio.setScale(spriteSize);
    //-----UP_BUTTON_____
    bool showUpgrades = false;
    SimpleButton upgradeButton;

    if (!upgradeButton.loadTextures(
        "assets/ButtonApp/пасивно.png",    // Нормальное состояние
        "assets/ButtonApp/выделено.png",   // При наведении
        "assets/ButtonApp/нажато.png"      // При клике
    )) {return -1;}

    upgradeButton.setPosition(515, 10); // Позиция в правом верхнем углу
    upgradeButton.setScale(5);


    //-----TEXT_COUNTER----
    Label text1;
    if (!text1.loadFont("fonts/USSR STENCIL WEBFONT.ttf")) return -1;
    text1.setColor(sf::Color::Green);
    text1.setString("TC:" + std::to_string(GlobalState::clickCount));
    text1.setPosition(0, 0);
    text1.startBlinking();

    Label text2;
    if (!text2.loadFont("fonts/USSR STENCIL WEBFONT.ttf")) return -1;
    text2.setColor(sf::Color::Green);
    text2.setString("DB:" + std::to_string(GlobalState::disassembledCount));
    text2.setPosition(0, 50);
    text2.startBlinking();

    Label progressBar;
    if (!progressBar.loadFont("fonts/USSR STENCIL WEBFONT.ttf")) return -1;
    progressBar.setColor(sf::Color::Green);
    progressBar.setString(ProgressConvert(buttonRadio.getState()));
    progressBar.setPosition(0, 400);
    progressBar.centrHorizontal(600);
    progressBar.startBlinking();

    Label scrapCounter;
    if (!scrapCounter.loadFont("fonts/USSR STENCIL WEBFONT.ttf")) return -1;
    scrapCounter.setColor(sf::Color::Green);
    scrapCounter.setString("$:" + std::to_string(GlobalState::disassembledCount));
    scrapCounter.setPosition(0,0);
    scrapCounter.centrHorizontal(600);
    scrapCounter.startBlinking();
    //-------
 
    //----shit---
    sf::CircleShape sph1 = sf::CircleShape(300.f);
    sph1.setFillColor(sf::Color::Green);
    //----------

    //--------GAME_CUCLE---------
    while (window.isOpen())
    {
        sf::Event event;
        float currentTime = shaderClock.getElapsedTime().asSeconds();
        //--------------------------------------
        while (window.pollEvent(event)) 
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

            if (event.type == sf::Event::Closed) //ЗАКРЫВАЕМСЯ
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && !showUpgrades) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (buttonRadio.contains(mousePos)) {
                        buttonRadio.onClick();
                        text1.setString("TC:" + std::to_string(GlobalState::clickCount));//!!!!
                        text2.setString("DB:" + std::to_string(GlobalState::disassembledCount));//!!!!
                        progressBar.setString(ProgressConvert(buttonRadio.getState()));
                        progressBar.centrHorizontal(600);
                        scrapCounter.setString("$:" + std::to_string(GlobalState::scrap));
                        scrapCounter.centrHorizontal(600);
                        GlobalState::saveToFile("save.json");
                    }
                    
                }
                
            }
            //--------------------------------АПГРЭЙДЫ
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    upgradeButton.handleMousePress(mousePos);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                        sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                        
                    upgradeButton.handleMouseRelease(mousePos, [&showUpgrades]() {
                        showUpgrades = !showUpgrades;
                        std::cout << "Меню улучшений: " << (showUpgrades ? "OPEN" : "CLOSE") << std::endl;

                        
                       });
                }
            }



        }
        //--------------------------------------
        upgradeButton.updateShake();
        
        if (shaderEnabled && windowShader.isAvailable()) {
            // Устанавливаем параметры шейдера
            windowShader.setUniform("texture", sf::Shader::CurrentTexture);
            windowShader.setUniform("time", currentTime);
            windowShader.setUniform("resolution", sf::Vector2f(window.getSize()));

            // Рисуем текстуру с шейдером
            window.draw(renderSprite, &windowShader);
        }
        else {
            // Рисуем текстуру без шейдера
            window.draw(renderSprite);
        }
        renderTexture.clear(sf::Color(30, 30, 30));

        //------DRAWS-------
        if (!showUpgrades) {
            buttonRadio.updateShake();
            text1.update();
            text2.update();
            progressBar.update();
            scrapCounter.update();
            //window.clear(sf::Color(30, 30, 30));
           
            // window.draw(sph1);
            text1.draw(window);
            text2.draw(window);
            progressBar.draw(window);
            scrapCounter.draw(window);
            buttonRadio.draw(window);
        }
        else {
            sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
            overlay.setFillColor(sf::Color(30, 30, 30)); 
            window.draw(overlay);
        }
        //------------------
        upgradeButton.draw(window);
        

       



        window.display();
    }
    //-------------------------------------
    return 0;
}

std::string ProgressConvert(float state) {
    char a[32] = "-------------------------------";
    std::string bar = "[";
    int segments = state / 0.125;
    for (int i = 0;i < 32;i++){
        if (segments > (i + 1)) bar += 'I';
        else bar += "!";
    }
    
    int pr = (state * 10) *2.5;
    bar += ']';bar+= '\n';
    bar += std::to_string(pr) + '%';
    //std::cout << bar << std::endl;
    return bar ;
}