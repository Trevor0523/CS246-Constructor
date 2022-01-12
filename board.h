#ifndef __BOARD_H__
#define __BOARD_H__
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept> // Enable exception
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include "textdisplay.h"
#include "builder.h"
#include "dice.h"

class Builder;
class Dice;
class TextDisplay;
class Tile;
class Edge;
class Vertex;

class Board {
    //public:
    int turn;
    std::vector<std::unique_ptr<Builder>> builders; // Records 4 players.
    std::unique_ptr<Dice> dice;
    std::string diceStrategy;
    std::unique_ptr<TextDisplay> td;               // Setup at initialization.
    std::vector<std::unique_ptr<Tile>> tiles;      // Stores all the tiles.
    std::vector<std::unique_ptr<Edge>> edges;      // Stores all the edges.
    std::vector<std::unique_ptr<Vertex>> vertices; // Stroes all the vertices.
    std::set<int> beginGameRes;
    int GeesePos; // Stores the tile where geese stays, nullptr at first.
    // Private Methods
    std::string getBeginRes();
    void randomBoard();
    void load(std::string fileName);
    void board(std::string line);
    void seed(int seed);
    void save(std::string file = "backup.sv"); // save the game if the game is not ended (no player have point over 10 [Please double check the game RULE!])
    public:
    Board(); // create the instance and the text display.
    //void readInput(const std::string cmd); // Act as the controller.
    void init(int argNum, const std::string firstArg, const std::string secondArg = "");
    void readBegin(std::string cmd);
    void readDuring(const std::string cmd);
};

#endif
