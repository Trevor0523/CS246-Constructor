#ifndef __TEXT_DISPLAY_H__
#define __TEXT_DISPLAY_H__
#include <vector>
#include <string>
#include <iostream>

class Board;

class TextDisplay {
    //Board* board;
    std::vector<std::string> vertices;
    std::vector<std::string> edges;
    std::vector<std::string> tileType;
    std::vector<std::string> tileValue;
    std::vector<std::string> tileGeese;
    std::vector<std::string> tilePos;
    void printline1(int Ver, int Edg, int tilePos, int num = 6);
    void printline2(int tilePos);
    void printline3(int Edg, int tilePos, int num = 6);
    void printline4(int tilePos);
    void printline5(int Ver, int Edg, int tilePos);
    void printline6(int tilePos);
    void printline7(int Edg, int tilePos, int num = 6);
    void printline8(int tilePos);
    public:
    TextDisplay();
    void notifyVer(int pos, std::string info);
    void notifyEdg(int pos, std::string info);
    void notifyTile(int pos, std::string type, int value, bool is_geese = false);
    void notifyGeese(int pos, bool is_geese);
    
    void printBoard() noexcept;
};

#endif
