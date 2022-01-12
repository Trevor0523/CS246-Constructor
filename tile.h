#ifndef __TILE_H__
#define __TILE_H__
#include <vector>
#include <string>

class Vertex;
class Edge;
class Builder;

class Tile {
    bool is_geese;
    std::vector<Vertex*> neighbourV;
    //std::vector<Edge*> neighbourE;
    std::string type; // the resource type of the tile
    int value; // the value of dice point that trigger tile.
    public:
    Tile() noexcept; // Must be initialized after Vertex and Edge already exist.
    std::vector<int> addResources() noexcept; // Called when dice points match the tile value.
    void addVertex(Vertex* v) noexcept; // Add tile's vertex neighbour
    // void addEdge(Edge* e) noexcept; // Add tile's edge neighbour
    bool isGeese() noexcept; 
    bool setGeese(bool is_geese) noexcept; // return the changed geese.
    void setValue(int value) noexcept;
    void setType(std::string type) noexcept;
    std::string tileInfo();
    int getValue();
    std::vector<Builder*> stoleFrom(Builder* player);
    std::string getType();

    // for testing
    void show_neighbourV();
    void show_info();
};

#endif
