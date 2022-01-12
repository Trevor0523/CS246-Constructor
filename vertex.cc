#include "vertex.h"
#include <algorithm>

// For Testing
#include "builder.h"
#include <algorithm>
#include <iostream>

Vertex::Vertex(int pos) : Subject("Vertex"), pos{pos}, neverAllow{false}, resInfo{Info::None} { }

bool Vertex::checkIfAllow(Builder* player) noexcept {
    if (this->neverAllow) return false;
    if (this->is_built && this->owner != player) return false;
    if (this->owner == player && this->resInfo != Info::Tower) return true;
    std::set<Builder*>::iterator it;
    it = std::find(this->allowedBuilder.begin(), this->allowedBuilder.end(),
                   player);
    if (it != this->allowedBuilder.end()) return true;
    return false;
}

void Vertex::notify(Subject* whoNotified) noexcept {
    if (this->neverAllow) return;
    if (this->is_built) return;
    if (whoNotified->getType() == "Vertex") {
        this->neverAllow = true;
        this->allowedBuilder.clear(); // Clean allowed Builder.
    } else { // Edge
        this->allowedBuilder.emplace(whoNotified->getOwner());
    }
}

void Vertex::levelUp() {
    if (this->resInfo == Info::None) {
        this->resInfo = Info::Basement;
    } else if (this->resInfo == Info::Basement) {
        this->resInfo = Info::House;
    } else if (this->resInfo == Info::House) {
        this->resInfo = Info::Tower;
        this->neverAllow = true;
    }
}

char Vertex::getLevel() noexcept {
    if (this->resInfo == Info::None) return 'N';
    if (this->resInfo == Info::Basement) return 'B';
    if (this->resInfo == Info::House) return 'H';
    if (this->resInfo == Info::Tower) return 'T';
    std::cout << "Eric: NOOOOO! vertex.cc at line 49" << std::endl;
    return 'N';
}

int Vertex::getIntLevel() noexcept {
    if (this->resInfo == Info::None) return 0;
    if (this->resInfo == Info::Basement) return 1;
    if (this->resInfo == Info::House) return 2;
    if (this->resInfo == Info::Tower) return 3;
    std::cout << "Eric: NOOOOO! vertex.cc at line 58" << std::endl;
    return -1;
}

void Vertex::build(Builder* player) noexcept {
    this->is_built = true;
    this->allowedBuilder.clear();
    this->allowedBuilder.emplace(player);
    this->owner = player;
    this->levelUp();
    this->notifyObservers();
    //return this->getIntLevel();
}

//std::string Vertex::getType() noexcept { return this->type; }

int Vertex::getPos() noexcept {
    return this->pos;
}

bool Vertex::getNeverAllow() {
    return this->neverAllow;
}

// for testing
void Vertex::show_info() {
    std::cout << "> [VERTEX] < ====================== " << std::endl;
    std::cout << "> [VERTEX] < This vertex is at [" << this->pos << "] and is build? [" << this->isBuilt() << "] and can build? [" << !(this->neverAllow) << "]  with building [" << this->getLevel() << "]" << std::endl;
    if (this->getOwner() != nullptr) std::cout << "> [VERTEX] < Owner : " << this->getOwner()->getName() << std::endl;
    std::cout << "> [VERTEX] < Who can built:";
    for (auto player : this->allowedBuilder) {
        std::cout << "  " << player->getName();
    }
    std::cout << std::endl;
    this->show_edgeObserver();
    this->show_vertexObserver();
}

void Vertex::show_edgeObserver() {
    std::cout << "> [VERTEX] < This vertex have edge observers : ";
    for_each(this->edgeObservers.begin(), this->edgeObservers.end(), 
            [](Subject* sub) {
                std::cout << sub->getType() << " at [" << sub->getPos() << "] | ";
            });
    std::cout << std::endl;
 }

void Vertex::show_vertexObserver() { 
    std::cout << "> [VERTEX] < This vertex have vertex observers : ";
    for_each(this->vertexObservers.begin(), this->vertexObservers.end(), 
            [](Subject* su) {
                Vertex* sub = dynamic_cast<Vertex*>(su);
                if (sub != nullptr) {
                    std::cout << sub->getType() << " at [" << sub->getPos() << "] with building [" << sub->getLevel() << "] | ";
                    if (sub->getOwner() != nullptr) std::cout << "Owner : " << sub->getOwner()->getName() << " | ";
                }
                if (sub == nullptr) std::cout << " [CODE ERROR!!! vertex.cc line 88 called ]  :( /n";
            });
    std::cout << std::endl;
}

