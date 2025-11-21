#include <SFML/Graphics.hpp>
#include "components/Button.h"
#include "components/SimpleButton.h"
#include "components/Lable.h"
#include "components/GlobalState.h"
#include <filesystem>
#include "components/UpgraidButton.h"
#include <sstream>
#include <iomanip>
std::string ProgressConvert(float state);
void CastilProstoSamiyTypoiCastilNoMneTakLenStrukturyProektaPeredelvatChtoDaYetoSmiyHoroshiyVariant(UpButton button, std::string text);
std::string formatFloat(float number);

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
    //улушеня ёу

      // СОЗДАЕМ КНОПКИ ВЕЛИКОГО КИТАЯ
    UpButton chinaButton1;
    UpButton chinaButton2;
    UpButton chinaButton3;
    UpButton chinaButton4;

    chinaButton1.create(150, 50, 300, 100, "quality");
    chinaButton2.create(150, 200, 300, 100, "critical\n click");
    chinaButton3.create(150, 350, 300, 100, "scrap\nbonus");
    chinaButton4.create(540, 540, 50, 50, "RT");

    
    chinaButton1.setOnClick([]() {
        int cost = (int)(GlobalState::clickCost * 100);
        if (GlobalState::clickCost < 0.5 && GlobalState::scrap >= cost) {
            GlobalState::scrap = GlobalState::scrap - cost;
            GlobalState::clickCost += 0.02;
        }
        });

    chinaButton2.setOnClick([]() {
        
        int cost = (int)((GlobalState::critChans +1) * 2);
        if (GlobalState::critChans < 100&& GlobalState::scrap >= cost) {
            GlobalState::scrap = GlobalState::scrap - cost;
            GlobalState::critChans += 4;
        }
        });

    chinaButton3.setOnClick([]() {
        int cost = (int)((GlobalState::scrapCritChans + 1) * 3);
         if (GlobalState::scrapCritChans < 100 && GlobalState::scrap >= cost) {
             GlobalState::scrap = GlobalState::scrap - cost;
             GlobalState::scrapCritChans += 4;
        }
        });
    chinaButton4.setOnClick([]() {
        GlobalState::reset();
        });

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

    Label scrapBonus;
    if (!scrapBonus.loadFont("fonts/USSR STENCIL WEBFONT.ttf")) return -1;
    scrapBonus.setColor(sf::Color::Green);
    scrapBonus.setPosition(0, 200);
    scrapBonus.centrHorizontal(600);
    scrapBonus.startBlinking();

    Label critBonus;
    if (!critBonus.loadFont("fonts/USSR STENCIL WEBFONT.ttf")) return -1;
    critBonus.setColor(sf::Color::Green);
    critBonus.setPosition(300, 175);
    critBonus.startBlinking();
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
            if (showUpgrades) 
            {
                chinaButton1.handleEvent(event, mousePos);
                chinaButton2.handleEvent(event, mousePos);
                chinaButton3.handleEvent(event, mousePos);
                chinaButton4.handleEvent(event, mousePos);
                text1.setString("TC:" + std::to_string(GlobalState::clickCount));//!!!!
                text2.setString("DB:" + std::to_string(GlobalState::disassembledCount));//!!!!
                progressBar.setString(ProgressConvert(buttonRadio.getState()));
                progressBar.centrHorizontal(600);
                scrapCounter.setString("$:" + std::to_string(GlobalState::scrap));
                scrapCounter.centrHorizontal(600);
                
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
            buttonRadio.updateScrapBonus();
            buttonRadio.updateCritBonus();
            scrapBonus.update();
            critBonus.update();
            text1.update();
            text2.update();
            progressBar.update();
            scrapCounter.update();
            //window.clear(sf::Color(30, 30, 30));
           
            // window.draw(sph1);
            if (buttonRadio.getIsScrapBonus()) {
                scrapBonus.setString("Double scrap!!!");
                scrapBonus.draw(window);
            }
            else
                scrapBonus.setString("");
            if (buttonRadio.getIsCritBonus()) {
                critBonus.setString("Click click!!!");
                critBonus.draw(window);
            }
            else
                critBonus.setString("");

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
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            chinaButton1.update(mousePos);
            chinaButton2.update(mousePos);
            chinaButton3.update(mousePos);
            chinaButton4.update(mousePos);
            //-----1
            std::string clickCost = "click: ";
            if (GlobalState::clickCost < 0.5)  
                clickCost += formatFloat(GlobalState::clickCost) + "\n"+ formatFloat(GlobalState::clickCost+0.02) +" = " + std::to_string( (int)(GlobalState::clickCost*100))+"-$";
            else
                clickCost += formatFloat(GlobalState::clickCost) + "\nMAX";
            chinaButton1.setButtonText(clickCost);
            chinaButton1.centerText();
            //------1
            //------2
            std::string dclc = "DBclick: ";
            if (GlobalState::critChans < 100)
                dclc += formatFloat(GlobalState::critChans)+"%" + "\n" + formatFloat(GlobalState::critChans + 4) + "% = " + std::to_string((int)((GlobalState::critChans + 1) * 2)) + "-$";
            else
                dclc += formatFloat(GlobalState::critChans) + "\nMAX";
            chinaButton2.setButtonText(dclc);
            chinaButton2.centerText();
            //------2
            //------3
            std::string dscc = "DBScrap$: ";
            if (GlobalState::scrapCritChans < 100)
                dscc += formatFloat(GlobalState::scrapCritChans) + "%" + "\n" + formatFloat(GlobalState::scrapCritChans + 4) + "% = " + std::to_string((int)((GlobalState::scrapCritChans + 1) * 3)) + "-$";
            else
                dscc += formatFloat(GlobalState::scrapCritChans) + "\nMAX";
            chinaButton3.setButtonText(dscc);
            chinaButton3.centerText();
            //------3
            scrapCounter.update();

            chinaButton1.draw(window);
            chinaButton2.draw(window);
            chinaButton3.draw(window);
            chinaButton4.draw(window);
            scrapCounter.draw(window);
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
void CastilProstoSamiyTypoiCastilNoMneTakLenStrukturyProektaPeredelvatChtoDaYetoSmiyHoroshiyVariant(UpButton button,std::string text) {
    button.setButtonText(text);
}
std::string formatFloat(float number ) {
    int precision = 2;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << number;
    std::string result = stream.str();

    // Убираем лишние нули после запятой
    size_t dotPos = result.find('.');
    if (dotPos != std::string::npos) {
        // Удаляем нули с конца
        result = result.substr(0, result.find_last_not_of('0') + 1);
        // Если после запятой ничего не осталось, удаляем и запятую
        if (result.back() == '.') {
            result.pop_back();
        }
    }

    return result;
}