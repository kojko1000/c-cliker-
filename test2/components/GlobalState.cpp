#include "GlobalState.h"
#include <fstream>
#include <iostream>

// Инициализация статических переменных
float GlobalState::clickCost = 0.5;
int GlobalState::critChans = 0;
int GlobalState::scrapCritChans = 60;
int GlobalState::disassembledCount = 0;
int GlobalState::clickCount = 0;
int GlobalState::scrap = 0;

bool GlobalState::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return false;
    }

    file << toJsonString();
    file.close();

    std::cout << "Game saved to " << filename << std::endl;
    return true;
}

bool GlobalState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return false;
    }

    std::string jsonStr;
    std::string line;
    while (std::getline(file, line)) {
        jsonStr += line + "\n";
    }
    file.close();

    bool success = fromJsonString(jsonStr);
    if (success) {
        std::cout << "Game loaded from " << filename << std::endl;
    }
    else {
        std::cerr << "Error: Failed to parse save file" << std::endl;
    }

    return success;
}

std::string GlobalState::toJsonString() {
    // Простой JSON без внешних библиотек
    std::string json = "{\n";
    json += "  \"clickCost\": " + std::to_string(clickCost) + ",\n";
    json += "  \"critChans\": " + std::to_string(critChans) + ",\n";
    json += "  \"scrapCritChans\": " + std::to_string(scrapCritChans) + ",\n";
    json += "  \"disassembledCount\": " + std::to_string(disassembledCount) + ",\n";
    json += "  \"clickCount\": " + std::to_string(clickCount) + ",\n";
    json += "  \"scrap\": " + std::to_string(scrap) + "\n";
    json += "}";
    return json;
}

bool GlobalState::fromJsonString(const std::string& jsonStr) {
    try {
        // Простой парсинг JSON (для сложных случаев лучше использовать библиотеку)
        size_t pos;

        // Парсим clickCost
        pos = jsonStr.find("\"clickCost\":");
        if (pos != std::string::npos) {
            pos = jsonStr.find(":", pos) + 1;
            size_t end = jsonStr.find(",", pos);
            std::string value = jsonStr.substr(pos, end - pos);
            clickCost = std::stof(value);
        }

        pos = jsonStr.find("\"critChans\":");
        if (pos != std::string::npos) {
            pos = jsonStr.find(":", pos) + 1;
            size_t end = jsonStr.find(",", pos);
            std::string value = jsonStr.substr(pos, end - pos);
            critChans = std::stoi(value);
        }

        pos = jsonStr.find("\"scrapCritChans\":");
        if (pos != std::string::npos) {
            pos = jsonStr.find(":", pos) + 1;
            size_t end = jsonStr.find(",", pos);
            std::string value = jsonStr.substr(pos, end - pos);
            scrapCritChans = std::stoi(value);
        }

        // Парсим disassembledCount
        pos = jsonStr.find("\"disassembledCount\":");
        if (pos != std::string::npos) {
            pos = jsonStr.find(":", pos) + 1;
            size_t end = jsonStr.find(",", pos);
            std::string value = jsonStr.substr(pos, end - pos);
            disassembledCount = std::stoi(value);
        }

        // Парсим clickCount
        pos = jsonStr.find("\"clickCount\":");
        if (pos != std::string::npos) {
            pos = jsonStr.find(":", pos) + 1;
            size_t end = jsonStr.find(",", pos);
            std::string value = jsonStr.substr(pos, end - pos);
            clickCount = std::stoi(value);
        }

        // Парсим scrap
        pos = jsonStr.find("\"scrap\":");
        if (pos != std::string::npos) {
            pos = jsonStr.find(":", pos) + 1;
            size_t end = jsonStr.find("}", pos);
            std::string value = jsonStr.substr(pos, end - pos);
            scrap = std::stoi(value);
        }

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return false;
    }
}

void GlobalState::reset() {
    clickCost = 0.5;
    disassembledCount = 0;
    clickCount = 0;
    scrap = 0;
    critChans = 0;
    scrapCritChans = 0;
}