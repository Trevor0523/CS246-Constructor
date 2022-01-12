#include "builder.h"
#include <iostream>
#include <string>
#include <locale> // std::toupper
#include <algorithm> // std::transform
#include <random>
#include <chrono>
#include "subject.h"
#include "vertex.h"
#include "edge.h"

Builder::Builder(std::string name, int point, int numBrick, int numEnergy, 
                 int numGlass, int numHeat, int numWifi) :
                 point{point}, numBrick{numBrick}, numEnergy{numEnergy}, 
                 numGlass{numGlass}, numHeat{numHeat}, numWifi{numWifi} {
                    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                    name[0] = std::toupper(name[0]);
                    this->name = name;
                 }

// void Builder::recordRoad(int oneRoad) {
//     // Assume the operation is valid
//     this->road.emplace_back(oneRoad);
// }

// void Builder::recordRes(int oneRes, char type) {
//     // Assume the operation is valid
//     this->res.emplace(oneRes, type);
//     if (type == 'B') this->point += 1;
//     if (type == 'H') this->point += 2;
//     if (type == 'T') this->point += 3;
// }

bool Builder::buildRes(Vertex* ver, char l, bool ifStart) {
    // Check whether the Builder can build Res here.
    int lpoint = 0;
    if (l == 'B') lpoint = 1;
    if (l == 'H') lpoint = 2;
    if (l == 'T') lpoint = 3;
    if (ifStart) {
        if (ver->getNeverAllow() || ver->isBuilt()) {
            // std::cout << "You cannot build here" << std::endl;
            return false;
        } else {
            for (int i = 0; i < lpoint; i++) {
                ver->build(this);
            }
            char level = ver->getLevel();
            int levelpoint = ver->getIntLevel();
            this->point += levelpoint;
            int pos = ver->getPos();
            this->res[pos] = level;
            return true;
        }
    }
    int buildLevel = ver->getIntLevel();
    bool allow = ver->checkIfAllow(this);
    if (!allow) {
        std::cout << "You cannot build here." << std::endl;
        return false;
    }
    std::string errMsg1 =  "You do not have enough resources.";
    if (buildLevel == 0) {
        if (!(this->checkEnough(1,1,1,0,1))) {
            std::cout << errMsg1 <<std::endl;
            std::cout << "The cost of a Basement is one BRICK, one ENERGY, one GLASS, and one WIFI resources." << std::endl;
            return false;
        }
        ver->build(this);
        this->point += 1;
        int pos = ver->getPos();
        char level = ver->getLevel();
        this->res.emplace(pos, level);
        this->changeMany(-1,-1,-1,0,-1);
        std::cout << "Builder " << this->name << " successfully built a Basement at " << ver->getPos() << "." << std::endl;
        return true;
    } else if (buildLevel == 1) {
        if (!(this->checkEnough(0,0,2,3,0))) {
            std::cout << errMsg1 <<std::endl;
            std::cout << "The cost of a House are two GLASS, and three HEAT resources." << std::endl;
            return false;
        }
        ver->build(this);
        this->point += 1;
        int pos = ver->getPos();
        char level = ver->getLevel();
        this->res[pos] = level;
        this->changeMany(0,0,-2,-3,0);
        std::cout << "Builder " << this->name << " successfully built a House at " << ver->getPos() << "." << std::endl;
        return true;
    } else if (buildLevel == 2) {
        if (!(this->checkEnough(3,2,2,2,1))) {
            std::cout << errMsg1 << std::endl;
            std::cout << "The cost of a Tower are three BRICK, two ENERGY, two GLASS,"<< std::endl << "one WIFI, and two HEAT resources." << std::endl;
            return false;
        }
        ver->build(this);
        this->point += 1;
        int pos = ver->getPos();
        char level = ver->getLevel();
        this->res[pos] = level;
        this->changeMany(-3,-2,-2,-2,-1);
        std::cout << "Builder " << this->name << " successfully built a Tower at " << ver->getPos() << "." << std::endl;
        return true;
    }
    return false;
}

bool Builder::buildRoad(Edge* e, bool ifStart) {
    // Check whether the Builder can build Road here.
    std::string errMsg1 = "You do not have enough resources.";
    if (ifStart) {
        if (e->isBuilt()) {
            return false;
        }
        e->build(this);
        int pos = e->getPos();
        this->road.emplace_back(pos);
        return true;
    }
    bool allow = e->checkIfAllow(this);
    if (!allow) {
        std::cout << "You cannot build here." << std::endl;
        return false;
    }
    if (this->checkEnough(0,0,0,1,1)) { // Allowed to build and No geese
        e->build(this);
        int pos = e->getPos();
        this->road.emplace_back(pos);
        this->changeMany(0,0,0,-1,-1);
        std::cout << "Builder " << this->name << " successfully built a road at " << e->getPos() << "." << std::endl;
        return true;
    } else {
        std::cout << errMsg1 <<std::endl;
        std::cout << "The cost of a Road is one HEAT and one WIFI resource." << std::endl;
        return false;
    }
}

void Builder::trade(Builder* target) {
    // trade was called.
    // Don't Trade with YOURSELF!
    if (this->name == target->name) {
        std::cout << "> > Can't trade with yourself." << std::endl;
    }
    // 1. Read in the giveR
    bool thisEnoughR = false; // indicate whether this builder have enough to give
    bool giveReadSuccess = false;
    std::string giveR;
    while (std::cin >> giveR) {
        std::transform(giveR.begin(), giveR.end(), giveR.begin(), ::toupper); // TO UPPER
        if (giveR == "BRICK") {
            thisEnoughR = this->numBrick > 0 ? true : false;
            giveReadSuccess = true;
            break;
        } else if (giveR == "ENERGY") {
            thisEnoughR = this->numEnergy > 0 ? true : false;
            giveReadSuccess = true;
            break;
        } else if (giveR == "GLASS") {
            thisEnoughR = this->numGlass > 0 ? true : false;
            giveReadSuccess = true;
            break;
        } else if (giveR == "HEAT") {
            thisEnoughR = this->numHeat > 0 ? true : false;
            giveReadSuccess = true;
            break;
        } else if (giveR == "WIFI") {
            thisEnoughR = this->numWifi > 0 ? true : false;
            giveReadSuccess = true;
            break;
        } else { // invalid give resources
            std::cout << "Invalid item." << std::endl;
            // print message "INVALID"
        }
    }

    // 2. Read in the getR. 
    bool thatEnoughR = false;
    bool getReadSuccess = false;
    std::string getR;
    while (std::cin >> getR) {
        std::transform(getR.begin(), getR.end(), getR.begin(), ::toupper); // TO UPPER
        if (getR == "BRICK") {
            thatEnoughR = target->numBrick > 0 ? true : false;
            getReadSuccess = true;
            break;
        } else if (getR == "ENERGY") {
            thatEnoughR = target->numEnergy > 0 ? true : false;
            getReadSuccess = true;
            break;
        } else if (getR == "GLASS") {
            thatEnoughR = target->numGlass > 0 ? true : false;
            getReadSuccess = true;
            break;
        } else if (getR == "HEAT") {
            thatEnoughR = target->numHeat > 0 ? true : false;
            getReadSuccess = true;
            break;
        } else if (getR == "WIFI") {
            thatEnoughR = target->numWifi > 0 ? true : false;
            getReadSuccess = true;
            break;
        } else { // invalid give resources
            std::cout << "Invalid item." << std::endl;
            // print message "INVALID"
        }
    }

    // 3. Check if read success.
    if (!giveReadSuccess || !getReadSuccess) return;

    // 4. Trade same resources.
    if (getR == giveR) {
        std::cout << "> > Why are you trading for the same resource..." << std::endl;
        return;
    }

    // 5. Check if this player has enough resources to trade.
    if (!thisEnoughR) {
        // print message "NOT ENOUGH SOURCES"
        std::cout << "You don't have enough " << giveR << "." << std::endl;
        return;
    }

    // 6. Check if target player has enough resources to trade.
    if (!thatEnoughR) {
        // print message "NOT ENOUGH SOURCES"
        std::cout << target->name << " doesn't have enough " << getR << "." << std::endl;
        return;
    }


    // No modification is made till now, just checking.

    

    // 7. Check if target player accept the request.
    bool accepted = false;
    std::cout << "> > " << this->name << " offers " << target->name << " one " << giveR << " for one " << getR << "." << std::endl;
    std::string ans;
    while (true) {
        std::cout << "Does " << target->name << " accept this offer?" << std::endl;
        std::cin >> ans;
        std::transform(ans.begin(), ans.end(), ans.begin(), ::toupper); // TO UPPER
        if (ans == "Y" || ans == "YES") { // Can do the trade
            this->lostRes(giveR);
            this->addRes(getR);
            target->lostRes(getR);
            target->addRes(giveR);
            accepted = true;
            break;
        } else if (ans == "N" || ans == "NO") {
            std::cout << target->name << " declined the trade." << std::endl;
            break;
        } else {
            std::cout << "Invalid command." << std::endl;
            std::cout << std::endl;
        }
    }
    
    // 8. Print the final message.
    if (accepted) {
        std::cout << this->name << " gains one " << getR << " and loses one " << giveR << "," << std::endl;
        std::cout << target->name << " gains one " << giveR << " and loses one " << getR << "." << std::endl;
    }
}

void Builder::printStatus() noexcept {
    std::string name = this->name;
    name.resize(8, ' ');
    std::cout << "Builder " << name;
    std::cout << " has " << this->point << " building points, ";
    std::cout << this->numBrick << " BRICK, " << this->numEnergy << " ENERGY, "
              << this->numGlass << " GLASS, " << this->numHeat << " HEAT, "
              << this->numWifi << " WIFI." << std::endl;
}

void Builder::printRes() noexcept {
    std::cout << this->name << " has built:" << std::endl;
    for (auto& pair : this->res) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}

bool Builder::lostRes(std::string type, int amount){
    if (amount < 0){
        //exception
        std::cerr << "Eric: impossible at line 289 builder.cc | amount = " << amount << std::endl;
    }
    std::transform(type.begin(), type.end(), type.begin(), ::toupper); // TO UPPER
    bool success = false;
    if (type == "BRICK" && amount <= this->numBrick) {
        this->numBrick -= amount;
        success = true;
    } else if (type == "ENERGY" && amount <= this->numEnergy) {
        this->numEnergy -= amount;
        success = true;
    } else if (type == "GLASS" && amount <= this->numGlass) {
        this->numGlass -= amount;
        success = true;
    } else if (type == "HEAT" && amount <= this->numHeat) {
        this->numHeat -= amount;
        success = true;
    } else if (type == "WIFI" && amount <= this->numWifi) {
        this->numWifi -= amount;
        success = true;
    } else {
        std::cout << "You do not have enough resources." << std::endl;
        //std::cout << "Builder " << this->name << " cannot lost type : " << type << " amount = " << amount << std::endl;
    }
    return success;
}

bool Builder::addRes(std::string type, int amount){
    if (amount < 0){
        //exception
        std::cerr << "Eric: impossible at line 318 builder.cc | amount = " << amount << std::endl;
    }
    std::transform(type.begin(), type.end(), type.begin(), ::toupper); // TO UPPER
    bool success = false;
    if (type == "BRICK") {
        this->numBrick += amount;
        success = true;
    } else if (type == "ENERGY") {
        this->numEnergy += amount;
        success = true;
    } else if (type == "GLASS") {
        this->numGlass += amount;
        success = true;
    } else if (type == "HEAT") {
        this->numHeat += amount;
        success = true;
    } else if (type == "WIFI") {
        this->numWifi += amount;
        success = true;
    } else {
        // NOT POSSIBLE TO REACH HERE!!
        std::cout << "Eric: WTF?? NOT POSSIBLE TO REACH HERE! At builder.cc line 297 with " << type << std::endl;
    }
    return success;
}

std::string Builder::randomLost() {
    std::string lostType = "NONE";
    int sum = this->numBrick + this->numEnergy + this->numGlass + this->numHeat
              + this->numWifi;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(1, sum);
    int num = distribution(generator);
    int tempSum = this->numBrick;
    if (1 <= num && num <= tempSum) {
        this->lostRes("BRICK");
        lostType = "BRICK";
    } else if (tempSum < num && num <= (tempSum += this->numEnergy)) {
        this->lostRes("ENERGY");
        lostType = "ENERGY";
    } else if (tempSum < num && num <= (tempSum += this->numGlass)) {
        this->lostRes("GLASS");
        lostType = "GLASS";
    } else if (tempSum < num && num <= (tempSum += this->numHeat)) {
        this->lostRes("HEAT");
        lostType = "HEAT";
    } else {// (this->numHeat <= num && num < this->numWifi) 
        this->lostRes("WIFI");
        lostType = "WIFI";
    }
    return lostType;
}

bool Builder::geeseAttack() {
    // Calculate the sum.
    bool attackSuccess = false;
    int sum = this->numBrick + this->numEnergy + this->numGlass + this->numHeat
              + this->numWifi;
    if (sum >= 10) { // Check if 10 or more resources.
        // 10+ resources.
        int half = sum / 2; // take half of the total resources.
        //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        //std::default_random_engine generator (seed);
        int brickLost = 0;
        int energyLost = 0;
        int glassLost = 0;
        int heatLost = 0;
        int wifiLost = 0;
        //int tempSum = this->numBrick;
        std::string lostType = "NONE";
        for (int i = 0; i < half; i++) { // lost half amount of the Resources.
            //std::uniform_int_distribution<int> distribution(1,sum);
            //int num = distribution(generator);
            lostType = this->randomLost();
            if (lostType == "BRICK") {
                brickLost += 1;
            } else if (lostType == "ENERGY") {
                energyLost += 1;
            } else if (lostType == "GLASS") {
                glassLost += 1;
            } else if (lostType == "HEAT") {
                heatLost += 1;
            } else {// (lostType == "WIFI") 
                wifiLost += 1;
            }
        }
        // Printing the message;
        std::cout << "Builder " << this->name << " loses " << half << " resources to the geese. They lose :" << std::endl;
        std::cout << brickLost << " BRICK" << std::endl;
        std::cout << energyLost << " ENERGY" << std::endl;
        std::cout << glassLost << " GLASS" << std::endl;
        std::cout << heatLost << " HEAT" << std::endl;
        std::cout << wifiLost << " WIFI" << std::endl;
        attackSuccess = true;
    }
    return attackSuccess;
}

void Builder::beingStole(Builder* stealer) {
    std::string lostType = this->randomLost();
    stealer->addRes(lostType);
    std::cout << "Builer " << stealer->name << " steals " << lostType << " from builder " << this->name << "." << std::endl;
}

int Builder::getPoint() {
    return this->point;
}

std::string Builder::getName() {
    return this->name;
}

int Builder::getIntName() {
    std::string name = this->name;
    std::transform(name.begin(), name.end(), name.begin(), ::toupper); // TO UPPER
    if (name == "BLUE") return 0;
    if (name == "RED") return 1;
    if (name == "ORANGE") return 2;
    if (name == "YELLOW") return 3;
    std::cerr << "Builder::getIntName() ERROR!!!!" << std::endl;
    return -1;
}

std::string Builder::builderInfo() {
    std::string data;
    data = std::to_string(this->numBrick) + " " + std::to_string(this->numEnergy) +
           " " + std::to_string(this->numGlass) + " " + std::to_string(this->numHeat) +
           " " + std::to_string(this->numWifi) + " r ";
    for_each(this->road.begin(), this->road.end(), 
             [&data] (int road){
                 data += std::to_string(road) + " ";
             }); 
    data = data + "h";
    for_each(this->res.begin(), this->res.end(),
             [&data] (std::pair<int, char> pair) {
                 data = data + " " + std::to_string(pair.first) + " " + pair.second;
             });
    return data;
}

bool Builder::market() {
    std::cout << "Welcome to the Market! : )" << std::endl;
    std::cout << "Which resources do you want to sell ?" << std::endl << "> ";
    std::string resourcesIn;
    while (std::cin >> resourcesIn) {
        std::transform(resourcesIn.begin(), resourcesIn.end(), resourcesIn.begin(), ::toupper); // TO UPPER
        if (resourcesIn == "BRICK" || resourcesIn == "ENERGY" ||
            resourcesIn == "GLASS" || resourcesIn == "HEAT" || 
            resourcesIn == "WIFI") {
            break;
        } else if (resourcesIn == "Q"){
            std::cout << "Market Closed. Bye~" << std::endl;
            return false;
        } else {
            std::cout << "This is not a valid Resources." << std::endl 
                      << "Enter one of the resources: BRICK, ENERGY, GLASS, HEAT, WIFI. Or type Q to quit the market." << std::endl << "> ";
        }
    
    }
    if (std::cin.eof() || std::cin.fail()) {
        std::cout << "Market closed." << std::endl;
        return false;
    }
    if (!(this->lostRes(resourcesIn, 4))) {
        std::cout << "You need to sell 4 " << resourcesIn << " at one time." << std::endl;
        std::cout << "Market closed. Bye~" << std::endl;
        return false;
    }
    std::string resourcesOut;
    std::cout << "Which resources would you like?" << std::endl << "> ";
    while (std::cin >> resourcesOut) {
        std::transform(resourcesOut.begin(), resourcesOut.end(), resourcesOut.begin(), ::toupper); // TO UPPER
        if (resourcesOut == "BRICK" || resourcesOut == "ENERGY" ||
            resourcesOut == "GLASS" || resourcesOut == "HEAT" || 
            resourcesOut == "WIFI") {
            this->addRes(resourcesOut);
            std::cout << "You got one [" << resourcesOut << "] and sold four [" << resourcesIn << "] !" << std::endl;
            std::cout << "Thanks for visiting market, Bye~" << std::endl;
            return true;
        } else {
            std::cout << "This is not a valid Resources." << std::endl 
                      << "Enter one of the resources: BRICK, ENERGY, GLASS, HEAT, WIFI" << std::endl << "> ";
        }
    }
    this->addRes(resourcesIn, 4);
    std::cout << "Market closed. Bye~" << std::endl;
    return false;
}



bool Builder::checkEnough(int brick, int energy, int glass, int heat, int wifi) {
    bool enough = this->numBrick >= brick && this->numEnergy >= energy && this->numGlass >= glass && this->numHeat >= heat && this->numWifi >= wifi;
    // if (!enough) std::cerr << "[[ ERIC ]] NOT ENOUGH RESOURCES!";
    return enough;
}

void Builder::changeMany(int brick, int energy, int glass, int heat, int wifi) {
    // DANGER !!! WEEK GURANTEE !!!
    if (brick > 0) {
        this->addRes("BRICK", brick);
    } else {
        this->lostRes("BRICK", brick * (-1));
    }
    if (energy > 0) {
        this->addRes("ENERGY", energy);
    } else {
        this->lostRes("ENERGY", energy * (-1));
    }
    if (glass > 0 && glass != 0) {
        this->addRes("GLASS", glass);
    } else {
        this->lostRes("GLASS", glass * (-1));
    }
    if (heat > 0 && heat != 0) {
        this->addRes("HEAT", heat);
    } else {
        this->lostRes("HEAT", heat * (-1));
    }
    if (wifi > 0 && wifi != 0) {
        this->addRes("WIFI", wifi);
    } else {
        this->lostRes("WIFI", wifi * (-1));
    }

}
