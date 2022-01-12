#include "edge.h"
#include <algorithm>

// for Testing
#include "builder.h"
#include <iostream>
#include "vertex.h"

Edge::Edge(int pos) : Subject("Edge"), pos{pos} { }

bool Edge::checkIfAllow(Builder* player) { // more if statement may be needed for exception (maybe?)
    if (!this->is_built) {
        std::set<Builder*>::iterator it;
        it = std::find(this->allowedBuilder.begin(), this->allowedBuilder.end(),
                       player);
        if (it != this->allowedBuilder.end()) return true;
    }
    return false;
}

void Edge::notify(Subject* whoNotified) {
    if (this->is_built) return;
    if (whoNotified->getType() == "Edge") {
        this->allowedBuilder.emplace(whoNotified->getOwner());
    } else {
        this->allowedBuilder.clear();
        for (auto vertexPtr : this->vertexObservers) { // for each current edge's (vertex)observer || current -> vertex observer
            if (!(vertexPtr->isBuilt())) {
                std::for_each(this->edgeObservers.begin(), this->edgeObservers.end(), // for each current edge's (edge)observer || current -> edge observer
                    [&, this](Subject* thisEdgeOb) { // check if the vertex observer have the same edge observer of current edge
                        for (auto callerEdge : vertexPtr->edgeObservers) { // current -> vertex observer -> edge observer
                            if (callerEdge == thisEdgeOb && callerEdge->isBuilt()) {
                                this->allowedBuilder.emplace(callerEdge->getOwner());
                                return;
                            }
                        }
                    });
            } else {
                this->allowedBuilder.emplace(vertexPtr->getOwner());
            }
        }
    }
}

void Edge::build(Builder* player) {
    this->is_built = true;
    this->allowedBuilder.clear();
    this->owner = player;
    this->notifyObservers();
    //return 1;
}

//std::string Edge::getType() noexcept { return this->type; }

int Edge::getPos() {
    return this->pos;
}



// for testing
void Edge::show_info() {
    std::cout << "> [EDGE] < ====================== " << std::endl;
    std::cout << "> [EDGE] < This edge is at [" << this->pos << "] and the road is build? [" << this->isBuilt() << "] " << std::endl;
    std::cout << "> [EDGE] < Who can built:";
    for (auto player : this->allowedBuilder) {
        std::cout << "  " << player->getName();
    }
    std::cout << std::endl;
    this->show_edgeObserver();
    this->show_vertexObserver();
}

void Edge::show_edgeObserver() {
    std::cout << "> [EDGE] < This edge have edge observers : ";
    for_each(this->edgeObservers.begin(), this->edgeObservers.end(), 
            [](Subject* sub) {
                std::cout << sub->getType() << " at [" << sub->getPos() << "] | ";
            });
    std::cout << std::endl;
 }

void Edge::show_vertexObserver() { 
    std::cout << "> [EDGE] < This edge have vertex observers : ";
    for_each(this->vertexObservers.begin(), this->vertexObservers.end(), 
            [](Subject* su) {
                Vertex* sub = dynamic_cast<Vertex*>(su);
                if (sub != nullptr) {
                    std::cout << sub->getType() << " at [" << sub->getPos() << "] with building [" << sub->getLevel() << "] | ";
                    if (sub->getOwner() != nullptr) std::cout << "Owner : " << sub->getOwner()->getName() << " | ";
                }
                if (sub == nullptr) std::cout << "/n [CODE ERROR!!! edge.cc line 102 called ]  :( /n";
            });
    std::cout << std::endl;
}
