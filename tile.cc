#include "tile.h"
#include "subject.h"
#include "vertex.h"
#include "builder.h"
#include <string>
#include <set>

// For Testing
#include <algorithm>
#include <iostream>

Tile::Tile() noexcept : is_geese{false}, type{"NONE"}, value{-1} { }

std::vector<int> Tile::addResources() noexcept {
    std::vector<int> record;
    for (int i = 0; i < 4; i++) {
        record.emplace_back(0);
    }
    if (is_geese) return record;
    // std::map<str::string, int>
    for (auto ver : this->neighbourV) {
        if (ver->isBuilt()) { // Check the is_built field using method isbuilt();
            // Use field owner in Subject to find the builder, getlevel() to find the building level in resInfo, 
            //      and call the builder method addResources(std::string xxx, int amount = 0);
            record[ver->getOwner()->getIntName()] += ver->getIntLevel();
            ver->getOwner()->addRes(this->type, ver->getIntLevel());
            //std::cout << "> Builder " << ver->getOwner()->getName() << " gained:" << std::endl;
            //std::cout << std::to_string(ver->getIntLevel()) << " " << this->type << std::endl;
            /// ADDDD SOME INFORMATION Builder Orange gained: /n 1 ENERGY;
        }
    }
    //////////////
    // for (int i = 0; i < 4; i++) {
    //     std::cout << record[i];
    // }
    return record;
}

void Tile::addVertex(Vertex* v) noexcept {
    this->neighbourV.emplace_back(v);
}

/*
void Tile::addEdge(Edge* e) noexcept {
    this->neighbourE.emplace_back(e);
}
*/

bool Tile::isGeese() noexcept {
    return this->is_geese;
}

bool Tile::setGeese(bool is_geese) noexcept {
    this->is_geese = is_geese;
    return this->is_geese;
}

void Tile::setValue(int value) noexcept {
    this->value = value;
}

void Tile::setType(std::string type) noexcept {
    this->type = type;
}

std::string Tile::getType() {
    return this->type;
}

std::string Tile::tileInfo() {
    int typeInt = -1;
    if (this->type == "BRICK") {
        typeInt = 0;
    } else if (this->type == "ENERGY") {
        typeInt = 1;
    } else if (this->type == "GLASS") {
        typeInt = 2;
    } else if (this->type == "HEAT") {
        typeInt = 3;
    } else if (this->type == "WIFI") { 
        typeInt = 4;
    } else { // (this->type == "PARK")
        typeInt = 5;
    }
    return std::to_string(typeInt) + " " + std::to_string(this->value);
}

std::vector<Builder*> Tile::stoleFrom(Builder* player) {
    std::set<Builder*> allowed;
    for (auto verptr : this->neighbourV) {
        if (verptr->isBuilt() && verptr->getOwner() != player) {
            allowed.emplace(verptr->getOwner());
        }
    }
    std::vector<Builder*> finalResult;
    for (auto allow : allowed) {
        finalResult.emplace_back(allow);
    }
    return finalResult;
}

int Tile::getValue() {
    return this->value;
}

// FOR TESTING

void Tile::show_neighbourV() {
    std::cout << "> [DEBUG] < This Tile object's neighbourV contain: ";
    for_each(this->neighbourV.begin(), this->neighbourV.end(), 
            [](Vertex* ver) {
                std::cout << "| Pos: " << ver->getPos() << " Res: " << ver->getLevel() << " ";
            });
    std::cout << std::endl;
}

void Tile::show_info() {
    std::cout << "> [DEBUG] < ====================== " << std::endl;
    std::cout << "> [DEBUG] < This Tile is type: " << this->type << " with value: " << this->value << std::endl;
    this->show_neighbourV();
}




