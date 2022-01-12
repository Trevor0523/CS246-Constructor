#ifndef __EDGE_H__
#define __DEGE_H__
#include "subject.h"
//#include "observer.h"

class Edge : public Subject /*, public Observer*/ {
    int pos;
    public:
    Edge(int pos);
    bool checkIfAllow(Builder*) override;
    //std::string getType() override;
    void notify(Subject*) override;
    // Never call this if you did not check if you can build here by calling checkIfAllow() before!!
    void build(Builder* player) override;
    int getPos() override; // returns the current position.

    // for testing
    void show_info();
    void show_edgeObserver();
    void show_vertexObserver();
};

#endif
