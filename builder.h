#ifndef __BUILDER_H__
#define __BUILDER_H__
#include <string>
#include <vector>
#include <map>

class Vertex;
class Edge;

class Builder {
    std::string name;
    int point;
    int numBrick;
    int numEnergy;
    int numGlass;
    int numHeat;
    int numWifi;
    std::vector<int> road;
    std::map<int, char> res;
    public:
    Builder(std::string name, int point = 0, int numBrick = 0, 
            int numEnergy = 0, int numGlass = 0, int numHeat = 0, 
            int numWifi = 0);

    // General use to build a road, if the road cannot be build,
    //   an exception is throwed. The return type indicated whether the
    //   building process is successful or not.
    //   ONLY called when: 1. Geese is not at the Tile
    bool buildRes(Vertex* ver, char level = 'B', bool ifStart = false); 

    // Similiar as buildRes().
    bool buildRoad(Edge* edg, bool ifStart = false);

    //void improve(Vertex*);

    // trade() is called after the, target player has accepted the 
    void trade(Builder*);
    void printStatus() noexcept;
    //void printRoads() noexcept;
    void printRes() noexcept; // print the residence.
    bool lostRes(std::string type, int amount = 1); // lost resources
    bool addRes(std::string type, int amount = 1);  // add resources
    bool geeseAttack(); // return true if the geese succeaafully stole the resources.
    void beingStole(Builder* stealer);
    std::string randomLost(); // random lost one resources.
    int getPoint();
    std::string builderInfo();
    std::string getName();
    int getIntName();
    bool market();

    bool checkEnough(int brick = 0, int energy = 0, int glass = 0, int heat = 0, int wifi = 0);
    void changeMany(int brick, int energy, int glass, int heat, int wifi); // Might move to private.
};

#endif
