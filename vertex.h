#ifndef __VERTEX_H__
#define __VERTEX_H__
//#include <memory>
#include "subject.h"
//#include "observer.h"
#include "res_info.h"

class Vertex : public Subject /*, public Observer */{
    int pos;
    bool neverAllow; // Used when checking whether the player can build.
    Info resInfo;
    public:
    Vertex(int pos); // create a Vertex with given position
    void levelUp(); // might throw exception, not decided yet
    char getLevel() noexcept;
    int getIntLevel() noexcept;
    bool checkIfAllow(Builder*) noexcept override;
    // Never call this if you did not check whether you can build here by calling checkIfAllow() before!!
    void build(Builder* player) noexcept override; 
    //std::string getType() noexcept override;
    void notify(Subject* whoNotified) noexcept override;
    int getPos() noexcept override; // returns the position.
    bool getNeverAllow();

    // for testing
    void show_info();
    void show_edgeObserver();
    void show_vertexObserver();

};

#endif
