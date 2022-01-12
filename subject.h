#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <string>
#include <vector>
#include <set>

class Builder;
//class Observer;
//class Vertex;
//class Edge;

class Subject {
  protected: // Can be accessed by the derived classes
    std::string type; // Edge or Vertex.
    std::set<Builder*> allowedBuilder;
    Builder* owner;
    bool is_built;
    void notifyObservers() noexcept;
  public:
    std::vector<Subject*> vertexObservers; // All vertex; CHANGED from Observer* 
    std::vector<Subject*> edgeObservers; // All edge; CHANGED from Observer*
    Subject(std::string type);
    bool isBuilt() noexcept;
    Builder* getOwner() noexcept;
    void attach(Subject*) noexcept; // CHANGED from Object* to Subject*
    std::string getType() noexcept;
    // Only returns if the builder can or cannot, does not include checker for cases before the game.
    virtual bool checkIfAllow(Builder*) = 0;
    virtual void build(Builder* player) = 0; // Make sure it can be built before calling this function! 
    
    // adjust version
    virtual int getPos() = 0;
    virtual void notify(Subject* whoNotified) = 0;
};

#endif
