#include "subject.h"
//#include "observer.h"
//#include "vertex.h"
//#include "edge.h"

Subject::Subject(std::string type) : type{type}, owner{nullptr}, is_built{false} { }

bool Subject::isBuilt() noexcept {return this->is_built;}

Builder* Subject:: getOwner() noexcept {return this->owner;}

void Subject::notifyObservers() noexcept {
    for (auto v : this->vertexObservers) {
        v->notify(this);
    }
    for (auto e : this->edgeObservers) {
        e->notify(this);
    }
}

void Subject::attach(Subject* observer) noexcept {
    if (observer->getType() == "Vertex") {
        this->vertexObservers.emplace_back(observer);
    } else { // Edge
        this->edgeObservers.emplace_back(observer);
    }
}

std::string Subject::getType() noexcept {
    return this->type;
}

