#pragma once
#include <string>

class GlobalState {
public:
    static float clickCost;
    static int critChans;
    static int scrapCritChans;
    static int disassembledCount;
    static int clickCount;
    static int scrap;
  

    // Функции для работы с JSON
    static bool saveToFile(const std::string& filename = "save.json");
    static bool loadFromFile(const std::string& filename = "save.json");
    static void reset(); // Сброс к начальным значениям (опционально)

private:
    // Внутренние функции для сериализации/десериализации
    static std::string toJsonString();
    static bool fromJsonString(const std::string& jsonStr);
};