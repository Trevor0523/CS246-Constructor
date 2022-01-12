#include "board.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <locale> // std::toupper
#include <algorithm> // std::transform
#include <iostream>

Board::Board(): turn{0}, dice{std::make_unique<Dice> (std::make_shared<LoadedStrategy>())},
    diceStrategy{"load"}, td{std::make_unique<TextDisplay>()}, GeesePos{-1} {
        this->builders.emplace_back (std::make_unique<Builder>("Blue"));
        this->builders.emplace_back (std::make_unique<Builder>("Red"));
        this->builders.emplace_back (std::make_unique<Builder>("Orange"));
        this->builders.emplace_back (std::make_unique<Builder>("Yellow"));
        int sumVertex = 54;
        int sumEdge = 72;
        int sumTile = 19;
        for (int i = 0; i < sumEdge; i++) {
            this->edges.emplace_back (std::make_unique<Edge>(i));
        } //add all edges
        for (int i = 0; i < sumVertex; i++) {
            this->vertices.emplace_back (std::make_unique<Vertex>(i));
        } //add all vertices
        for (int i = 0; i <sumTile; i++) {
            this->tiles.emplace_back (std::make_unique<Tile>());
        }
        // add vertices in tile
        for (int i = 0; i <= 0; i++) {
            int diff = 1;
            for (int j = 0; j < 9; j++) {
                this->tiles[i]->addVertex(this->vertices[j].get());
                this->tiles[i]->addVertex(this->vertices[j + 1].get());
                this->tiles[sumTile - 1 - i]->addVertex(this->vertices[sumVertex - j - 1].get());
                this->tiles[sumTile - 1 - i]->addVertex(this->vertices[sumVertex - j - 2].get());
                diff *= 2;
                j += diff;
            }
        }
        for (int i = 1; i <= 2; i++) {
            int diff = 4;
            for (int j = 2; j < 14; j++) {
                int posn = j + (i - 1) * 2;
                this->tiles[i]->addVertex(this->vertices[posn].get());
                this->tiles[i]->addVertex(this->vertices[posn + 1].get());
                this->tiles[sumTile - 1 - i]->addVertex(this->vertices[sumVertex - posn - 1].get());
                this->tiles[sumTile - 1 - i]->addVertex(this->vertices[sumVertex - posn - 2].get());
                j += diff;
                diff += 1;
            }
        }
        int diff = 3;
        for (int i = 3; i <= 15; i++) {
            if (diff == 6 || diff == 9 || diff == 13 || diff == 16) {
                diff += 1;
            }
            for (int j = 0; j <= 12; j += 6) {
                int posn = i + diff + j;
                this->tiles[i]->addVertex(this->vertices[posn].get());
                this->tiles[i]->addVertex(this->vertices[posn + 1].get());
            }
            diff += 1;
        }
        // vertex attach vertex
        for (int i = 0; i <= 1; i++) {
            this->vertices[i]->attach(this->vertices[i + 3].get());
            this->vertices[i + 3]->attach(this->vertices[i].get());
            this->vertices[sumVertex - i - 1]->attach(this->vertices[sumVertex - i - 4].get());
            this->vertices[sumVertex - i - 4]->attach(this->vertices[sumVertex - i - 1].get());
        }
        for (int i = 2; i <= 5; i++) {
            this->vertices[i]->attach(this->vertices[i + 5].get());
            this->vertices[i + 5]->attach(this->vertices[i].get());
            this->vertices[sumVertex - i - 1]->attach(this->vertices[sumVertex - i - 6].get());
            this->vertices[sumVertex - i - 6]->attach(this->vertices[sumVertex - i - 1].get());
        }
        for (int i = 6; i <= 41; i++) {
            this->vertices[i]->attach(this->vertices[i + 6].get());
            this->vertices[i + 6]->attach(this->vertices[i].get());
        }
        for (int i = 0; i <= 22; i += 2) {
            if(i == 12) { i = 18; }
            this->vertices[i]->attach(this->vertices[i + 1].get());
            this->vertices[i + 1]->attach(this->vertices[i].get());
            this->vertices[sumVertex - i - 1]->attach(this->vertices[sumVertex - i - 2].get());
            this->vertices[sumVertex - i - 2]->attach(this->vertices[sumVertex - i - 1].get());
        }
        for (int i = 13; i <= 25; i += 2) {
            if(i == 17) { i = 25; }
            this->vertices[i]->attach(this->vertices[i + 1].get());
            this->vertices[i + 1]->attach(this->vertices[i].get());
            this->vertices[sumVertex - i - 1]->attach(this->vertices[sumVertex - i - 2].get());
            this->vertices[sumVertex - i - 2]->attach(this->vertices[sumVertex - i - 1].get());
        }
        // edge attach edge
        for (int i = 1; i <= 2; i++) {
            this->edges[i]->attach(this->edges[i + 5].get());
            this->edges[i + 5]->attach(this->edges[i].get());
            this->edges[sumEdge - i - 1]->attach(this->edges[sumEdge - i - 6].get());
            this->edges[sumEdge - i - 6]->attach(this->edges[sumEdge - i - 1].get());
        }
        for (int i = 5; i <= 34; i++) {
            this->edges[i]->attach(this->edges[i + 8].get());
            this->edges[i + 8]->attach(this->edges[i].get());
            if (i < 29) {
                this->edges[sumEdge - i - 1]->attach(this->edges[sumEdge - i - 9].get());
                this->edges[sumEdge - i - 9]->attach(this->edges[sumEdge - i - 1].get());
            }
            if (i == 8) { i = 11; }
            if (i == 17) { i = 28; }
        }
        for (int i = 20; i <= 25; i++) {
            this->edges[i]->attach(this->edges[i + 9].get());
            this->edges[i + 9]->attach(this->edges[i].get());
            this->edges[sumEdge - i - 1]->attach(this->edges[sumEdge - i - 10].get());
            this->edges[sumEdge - i - 10]->attach(this->edges[sumEdge - i - 1].get());
        }
        for (int i = 0; i <= 0; i++) {
            this->edges[i]->attach(this->edges[i + 1].get());
            this->edges[i]->attach(this->edges[i + 2].get());
            this->edges[i + 1]->attach(this->edges[i].get());
            this->edges[i + 2]->attach(this->edges[i].get());
            this->edges[sumEdge - i - 1]->attach(this->edges[sumEdge - i - 2].get());
            this->edges[sumEdge - i - 1]->attach(this->edges[sumEdge - i - 3].get());
            this->edges[sumEdge - i - 2]->attach(this->edges[sumEdge - i - 1].get());
            this->edges[sumEdge - i - 3]->attach(this->edges[sumEdge - i - 1].get());
        }
        int j = 0;
        for (int i = 3; i <= 4; i++) {
            this->edges[i]->attach(this->edges[i - 2].get());
            this->edges[i]->attach(this->edges[i + 2 + j].get());
            this->edges[i]->attach(this->edges[i + 3 + j].get());
            this->edges[i - 2]->attach(this->edges[i].get());
            this->edges[i + 2 + j]->attach(this->edges[i].get());
            this->edges[i + 3 + j]->attach(this->edges[i].get());
            this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i - 2)].get());
            this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i + 2 + j)].get());
            this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i + 3 + j)].get());
            this->edges[sumEdge - 1 - (i - 2)]->attach(this->edges[sumEdge - 1 - i].get());
            this->edges[sumEdge - 1 - (i + 2 + j)]->attach(this->edges[sumEdge - 1 - i].get());
            this->edges[sumEdge - 1 - (i + 3 + j)]->attach(this->edges[sumEdge - 1 - i].get());
            j += 1;
        }
        j = 0;
        for (int i = 9; i <= 11; i++) {
            int k = 0;
            if (i == 11) {
                k = 1;
            }
            this->edges[i]->attach(this->edges[i - 4 + k].get());
            this->edges[i]->attach(this->edges[i + 3 + j].get());
            this->edges[i]->attach(this->edges[i + 4 + j].get());
            this->edges[i - 4 + k]->attach(this->edges[i].get());
            this->edges[i + 3 + j]->attach(this->edges[i].get());
            this->edges[i + 4 + j]->attach(this->edges[i].get());
            this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i - 4 + k)].get());
            this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i + 3 + j)].get());
            this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i + 4 + j)].get());
            this->edges[sumEdge - 1 - (i - 4 + k)]->attach(this->edges[sumEdge - 1 - i].get());
            this->edges[sumEdge - 1 - (i + 3 + j)]->attach(this->edges[sumEdge - 1 - i].get());
            this->edges[sumEdge - 1 - (i + 4 + j)]->attach(this->edges[sumEdge - 1 - i].get());
            if (i == 10) {
                this->edges[i]->attach(this->edges[i - 4 + j].get());
                this->edges[i - 4 + j]->attach(this->edges[i].get());
                this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i - 4 + j)].get());
                this->edges[sumEdge - 1 - (i - 4 + j)]->attach(this->edges[sumEdge - 1 - i].get());
            }
            j += 1;
        }
        j = 0;
        int x = 5;
        for (int i = 18; i <= 35; i++) {
            if (i == 20) { i = 26; }
            if (i == 29) { i = 35; }
            if (i == 26) { x = 6; }
            if (i == 35) { x = 5; }
            this->edges[i]->attach(this->edges[i - x].get());
            this->edges[i]->attach(this->edges[i - x + 1].get());
            this->edges[i]->attach(this->edges[i + 3 + j].get());
            this->edges[i]->attach(this->edges[i + 4 + j].get());
            this->edges[i - x]->attach(this->edges[i].get());
            this->edges[i - x + 1]->attach(this->edges[i].get());
            this->edges[i + 3 + j]->attach(this->edges[i].get());
            this->edges[i + 4 + j]->attach(this->edges[i].get());
            this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i - x)].get());
            this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i - x + 1)].get());
            this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i + 3 + j)].get());
            this->edges[sumEdge - 1 - i]->attach(this->edges[sumEdge - 1 - (i + 4 + j)].get());
            this->edges[sumEdge - 1 - (i - x)]->attach(this->edges[sumEdge - 1 - i].get());
            this->edges[sumEdge - 1 - (i - x + 1)]->attach(this->edges[sumEdge - 1 - i].get());
            this->edges[sumEdge - 1 - (i + 3 + j)]->attach(this->edges[sumEdge - 1 - i].get());
            this->edges[sumEdge - 1 - (i + 4 + j)]->attach(this->edges[sumEdge - 1 - i].get());
            j += 1;
            x -= 1;
            if (i == 19 || i == 28) {
                j = 0;
            }
        }
        // vertex attach edge
        int a = 3; // difference between upper vertex and lower vertex
        int b = 1; // difference between edge and upper vertex
        for (int i = 1; i <= 34; i++) {
            if (i == 3) {
                i = 5;
                a = 5;
                b = 3;
            }
            if (i == 9) {
                i = 12;
                a = 6;
                b = 6;
            }
            if (i == 18) {
                i = 20;
                b = 8;
            }
            if (i == 26) {
                i = 29;
                b = 11;
            }
            this->edges[i]->attach(this->vertices[i - b].get());
            this->edges[i]->attach(this->vertices[i - b + a].get());
            this->vertices[i - b]->attach(this->edges[i].get());
            this->vertices[i - b + a]->attach(this->edges[i].get());
            this->edges[sumEdge - 1 - i]->attach(this->vertices[sumVertex - 1 - (i - b)].get());
            this->edges[sumEdge - 1 - i]->attach(this->vertices[sumVertex - 1 - (i - b + a)].get());
            this->vertices[sumVertex - 1 - (i - b)]->attach(this->edges[sumEdge - 1 - i].get());
            this->vertices[sumVertex - 1 - (i - b + a)]->attach(this->edges[sumEdge - 1 - i].get());
        }
        int c = 0; // difference between edge and left vertex
        for (int i = 0; i <= 35; i++) {
            if (i == 1) {
                i = 3;
                c = 1;
            }
            if (i == 5) {
                i = 9;
                c = 3;
            }
            if (i == 12) {
                i = 18;
                c = 5;
            }
            if (i == 20) {
                i = 26;
                c = 8;
            }
            if (i == 29) {
                i = 35;
                c = 10;
            }
            this->edges[i]->attach(this->vertices[i - c].get());
            this->edges[i]->attach(this->vertices[i - c + 1].get());
            this->vertices[i - c]->attach(this->edges[i].get());
            this->vertices[i - c + 1]->attach(this->edges[i].get());
            this->edges[sumEdge - 1 - i]->attach(this->vertices[sumVertex - 1 - (i - c)].get());
            this->edges[sumEdge - 1 - i]->attach(this->vertices[sumVertex- 1 - (i - c + 1)].get());
            this->vertices[sumVertex - 1 - (i - c)]->attach(this->edges[sumEdge - 1 - i].get());
            this->vertices[sumVertex - 1 - (i - c + 1)]->attach(this->edges[sumEdge - 1 - i].get());
            c -= 1;
        }
}

std::string Board::getBeginRes() {
    std::string msg;
    for (auto one : this->beginGameRes) {
        msg += std::to_string(one) + " ";
    }
    return msg;
}

void Board::randomBoard() {
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->seed(seed);
}

void Board::load(std::string fileName) {
    std::ifstream infile{fileName};
        if (! infile.is_open()) {
            throw std::invalid_argument{"ERROR: Unable to open file " + fileName + " for board layout."};
        }
    std::string line;
    int turn;
    int numBricks;
    int numEnergies;
    int numGlass;
    int numHeat;
    int numWifi;
    std::string type;
    char level;
    std::string posn;
    int posnint;
    int tilePosn;
    int i = 0;
    while (std::getline(infile, line)) {
        //std::cerr << line << std::endl;
        //std::cerr << "i: " << i << std::endl;
        std::istringstream iss{line};
        if (i == 0) {
            if (!(iss >> turn)) {
                throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
            }
            this->turn = turn;
            i += 1;
        } else if (i == 5) {
            //try {
                //std::cerr << line << std::endl;
                this->board(line);
            // } catch (std::invalid_argument & e) {
            //     std::string errorMsg = e.what();
            //     if (errorMsg == "Something went wrong when loading.") {
            //         throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
            //     }
            // }
            i += 1;
        } else if (i == 6) {
            iss >> tilePosn;
            if (tilePosn < 2 || tilePosn > 18) {
                throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
            } else {
                this->GeesePos = tilePosn;
                this->tiles[tilePosn]->setGeese(true);
                this->td->notifyGeese(tilePosn, true);
            }
        } else {
            if (!(iss >> numBricks >> numEnergies >> numGlass >> numHeat >> numWifi)) {
                throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
            }
            this->builders[i - 1]->addRes("BRICK", numBricks);
            this->builders[i - 1]->addRes("ENERGY", numEnergies);
            this->builders[i - 1]->addRes("GLASS", numGlass);
            this->builders[i - 1]->addRes("HEAT", numHeat);
            this->builders[i - 1]->addRes("WIFI", numWifi);
            //std::cerr << numBricks << " " << numEnergies << " " << numGlass << " " << numHeat << " " << numWifi << std::endl;
            iss >> type;
            if (type != "r") {
                throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
            }
            while (iss >> posn) {
                std::istringstream os{posn};
                if (os >> posnint) {
                    //this->builders[i - 1]->recordRoad(posnint);
                    if (posnint >= 0 && posnint <= 71) {
                        this->builders[i - 1]->buildRoad(this->edges[posnint].get(), true);
                        std::string edgMsg = (this->builders[i - 1]->getName()).substr(0,1) + "R";
                        //std::cout << edgMsg << std::endl;
                        this->td->notifyEdg(posnint, edgMsg);
                    } else {
                        throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
                    }
                } else {
                    if (posn != "h") {
                        throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
                    } else {
                        break;
                    }
                }
            }
            while (iss >> posnint) {
                if (posnint < 0 || posnint > 53) {
                    throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
                }
                if (iss >> level) {
                    if (!(level == 'B' || level == 'H' || level == 'T')) {
                        throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
                    }
                    //this->builders[i - 1]->recordRes(posnint, level);
                    this->builders[i - 1]->buildRes(this->vertices[posnint].get(), level, true);
                    std::string resMsg = "|" + (this->builders[i - 1]->getName()).substr(0,1);
                    resMsg = resMsg + level;
                    resMsg += "|";
                    //std::cout << resMsg << std::endl;
                    this->td->notifyVer(posnint, resMsg);
                } else {
                    throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
                }
            }
            i += 1;
            //std::cerr << "REACHED: " << i << " times" << std::endl;
        }
    }
    //std::cerr << "i: " << i << std::endl;
    if (i < 6) {
        throw std::invalid_argument{"ERROR: " + fileName + " has an invalid format."};
    }
}

void Board::board(std::string line) {
    int source;
    int value;
    int tileNum = 0;
    int time = 0;
    //bool park = false;
    std::istringstream iss{line};
    while(iss >> source) {
        time += 1;
        if(!(iss >> value)) {
            throw std::invalid_argument{"Something went wrong when loading."};
        }
        if (value < 2 || value > 12) {
            throw std::invalid_argument{"Something went wrong when loading."};
        }
        this->tiles[tileNum]->setValue(value);
        if(source == 0) {
            this->tiles[tileNum]->setType("BRICK");
            this->td->notifyTile(tileNum, "BRICK", value);
        } else if(source == 1) {
            this->tiles[tileNum]->setType("ENERGY");
            this->td->notifyTile(tileNum, "ENERGY", value);
        } else if(source == 2) {
            this->tiles[tileNum]->setType("GLASS");
            this->td->notifyTile(tileNum, "GLASS", value);
        } else if(source == 3) {
            this->tiles[tileNum]->setType("HEAT");
            this->td->notifyTile(tileNum, "HEAT", value);
        } else if(source == 4) {
            this->tiles[tileNum]->setType("WIFI");
            this->td->notifyTile(tileNum, "WIFI", value);
        } else if(source == 5) {
            if(value != 7) {
                throw std::invalid_argument{"Something went wrong when loading."};
            }
            //park = true;
            this->tiles[tileNum]->setType("PARK");
            this->td->notifyTile(tileNum, "PARK", value);
        } else {
            throw std::invalid_argument{"Something went wrong when loading."};
        }
        tileNum += 1;
    }
    if (time != 19) {
        throw std::invalid_argument{"Something went wrong when loading."};
    }
}

void Board::seed(int seed) {
    std::vector<std::string> source;
    int num = 3;
    for (int i = 0; i < num; i++) {
        source.emplace_back("WIFI");
        source.emplace_back("HEAT");
    }
    num = 4;
    for (int i = 0; i < num; i++) {
        source.emplace_back("BRICK");
        source.emplace_back("ENERGY");
        source.emplace_back("GLASS");
    }
    source.emplace_back("PARK");
    std::vector<int> value;
    value.emplace_back(2);
    for (int i = 3; i <= 11; i++) {
        if (i == 7) { i += 1; }
        value.emplace_back(i);
        value.emplace_back(i);
    }
    value.emplace_back(12);
    std::default_random_engine rng{seed};
    std::shuffle( source.begin(), source.end(), rng );
    std::shuffle( value.begin(), value.end(), rng );
    int parkShowed = 0;
    for (int i = 0; i <= 18; i++) {
        // if (source[i] == "PARK") {
        //     value.emplace_back(value[i]);
        //     value[i] = 7;
        // }
        if (source[i] == "PARK") {
            this->tiles[i]->setType(source[i]);
            this->tiles[i]->setValue(7);
            this->td->notifyTile(i, source[i], 7);
            parkShowed = 1;
            continue;
        }
        this->tiles[i]->setType(source[i]);
        this->tiles[i]->setValue(value[i - parkShowed]);
        // std::cout << source[i] << " with value " << value[i - parkShowed] << std::endl;
        this->td->notifyTile(i, source[i], value[i - parkShowed]);
    }
}

void Board::save(std::string file) {
    std::ofstream ofs (file, std::ofstream::out);
    ofs << this->turn << std::endl;
    for (int i = 0; i < 4; i++) {
        ofs << this->builders[i]->builderInfo() << std::endl;
    }
    for (int i = 0; i <= 18; i++) {
        ofs << this->tiles[i]->tileInfo() << " ";
    }
    ofs << std::endl;
    if (this->GeesePos != -1) {
        ofs << this->GeesePos << std::endl;
    }
    ofs.close();
}

void Board::init(int argNum, const std::string firstArg, const std::string secondArg) {
    if (argNum == 1) {
        std::ifstream file{secondArg};
        std::string line;
        std::getline(file, line);
        this->board(line);
    } else if (firstArg == "-seed") {
        std::istringstream iss{secondArg};
        int seed;
        iss >> seed;
        this->seed(seed);
    } else if (firstArg == "-load") {
        this->load(secondArg);
    } else if (firstArg == "-board") {
        std::ifstream file{secondArg};
        if (!file.is_open()) {
            throw std::invalid_argument{"ERROR: Unable to open file " + secondArg + " for board layout."};
        }
        std::string line;
        std::getline(file, line);
        this->board(line);
    } else if (firstArg == "-random-board") {
        this->randomBoard();
    } else if (argNum == 0 && firstArg == "choose") {
        this->td->printBoard();
        for (int i = 0; i <= 3; i++) {
            int posn;
            std::string mid;
            std::string msg;
            msg =  "Builder " + this->builders[i]->getName() + " where do you want to build a basement?";
            while (!std::cin.eof()) {
                std::cout << msg << std::endl << "> ";
                std::cin >> mid;
                if (std::cin.eof()) {
                    throw std::invalid_argument{"End of file reached."};
                }
                bool successRead = true;
                try {
                    posn = std::stoi(mid);
                } catch (std::invalid_argument& e) {
                    successRead = false;
                } catch (std::out_of_range& e) {
                    successRead = false;
                }
                if (!successRead) {
                    std::cout << "ERROR: " << mid << " isn't a valid integer." << std::endl;
                } else if (!(0 <= posn && posn <= 53)) {
                    std::cout << "You cannot build here." << std::endl;
                    std::cout << "Basements already exist at locations: " << this->getBeginRes() << std::endl;
                } else if (!(this->builders[i]->buildRes(this->vertices[posn].get(), 'B', true))) {
                    std::cout << "You cannot build here." << std::endl;
                    std::cout << "Basements already exist at locations: " << this->getBeginRes() << std::endl;
                } else {
                    std::string buildMsg = "|" +this->builders[i]->getName().substr(0,1) + this->vertices[posn]->getLevel() + "|";
                    this->td->notifyVer(posn, buildMsg);
                    this->beginGameRes.emplace(posn);
                    break;
                }
            }
        }
        for (int i = 3; i >= 0; i--) {
            int posn;
            std::string mid;
            std::string msg;
            msg =  "Builder " + this->builders[i]->getName() + " where do you want to build a basement?";
            while (!std::cin.eof()) {
                std::cout << msg << std::endl << "> ";
                std::cin >> mid;
                if (std::cin.eof()) {
                    throw std::invalid_argument{"End of file reached."};
                }
                bool successRead = true;
                try {
                    posn = std::stoi(mid);
                } catch (std::invalid_argument& e) {
                    successRead = false;
                } catch (std::out_of_range& e) {
                    successRead = false;
                }
                if (!successRead) {
                    std::cout << "ERROR: " << mid << " isn't a valid integer." << std::endl;
                } else if (!(0 <= posn && posn <= 53)) {
                    std::cout << "You cannot build here." << std::endl;
                    std::cout << "Basements already exist at locations: " << this->getBeginRes() << std::endl;
                } else if (!(this->builders[i]->buildRes(this->vertices[posn].get(), 'B', true))) {
                    std::cout << "You cannot build here." << std::endl;
                    std::cout << "Basements already exist at locations: " << this->getBeginRes() << std::endl;
                } else {
                    std::string buildMsg = "|" +this->builders[i]->getName().substr(0,1) + this->vertices[posn]->getLevel() + "|";
                    this->td->notifyVer(posn, buildMsg);
                    this->beginGameRes.emplace(posn);
                    break;
                }
            }
        }
    }
}

void Board::readBegin(std::string cmd) {
    int pnt = -1;
    int diceNum = -1;
    std::string nextCmd;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower); // TO lower
    if (cmd == "start") {
        std::cout << "Builder " << this->builders[this->turn % 4]->getName() << "'s turn." << std::endl;
        std::cout << "> ";
    } else if (cmd == "load") {
        int i = this->turn % 4;
        std::cout << "Builder " << this->builders[i]->getName() << " now has loaded Dice." << std::endl;
        std::cout << "> ";
        this->dice->setStrategy(std::make_shared<LoadedStrategy>());
        this->diceStrategy = "load";
    } else if (cmd == "fair") {
        int i = this->turn % 4;
        std::cout << "Builder " << this->builders[i]->getName() << " now has fair Dice." << std::endl;
        std::cout << "> ";
        this->dice->setStrategy(std::make_shared<FairStrategy>());
        this->diceStrategy = "fair";
    } else if (cmd == "roll") {
        if (this->diceStrategy == "load") {
            std::cout << "Input a roll between 2 and 12:" << std::endl;
            std::cout << "> ";
            while (std::cin >> nextCmd) {
                std::istringstream iss(nextCmd);
                if (!(iss >> pnt)) {
                    std::cerr << "ERROR:  isn't a valid integer." << std::endl;
                    std::cout << "> ";
                } else if (pnt < 2 || pnt > 12) {
                    std::cerr << "Invalid roll " << pnt << "." << std::endl;
                    std::cout << "Input a roll between 2 and 12:" << std::endl;
                    std::cout << "> ";
                } else {
                    diceNum = this->dice->roll(pnt);
                    break;
                }
            }
        } else if (this->diceStrategy == "fair") {
            diceNum = this->dice->roll(pnt);
            std::cout << "The number you rolled is " << diceNum << std::endl;
        }
        if (diceNum != 7) {
            std::vector<int> allBrick {0, 0, 0, 0};
            std::vector<int> allEnergy {0, 0, 0, 0};
            std::vector<int> allGlass {0, 0, 0, 0};
            std::vector<int> allHeat {0, 0, 0, 0};
            std::vector<int> allWifi {0, 0, 0, 0};
            for (int i = 0; i <= 18; i++) {
                if(this->tiles[i]->getValue() == diceNum) {
                    if (this->GeesePos == i) {
                        continue;
                    }
                    std::vector<int> distribution = this->tiles[i]->addResources();
                    // for (int j = 0; j < 4; j++) {
                    //     std::cerr << distribution[j] << " ";
                    // }
                    if (this->tiles[i]->getType() == "BRICK") {
                        for (int j = 0; j < 4; j++) {
                            allBrick[j] += distribution[j];
                        }
                    } else if (this->tiles[i]->getType() == "ENERGY") {
                        for (int j = 0; j < 4; j++) {
                            allEnergy[j] += distribution[j];
                        }
                    } else if (this->tiles[i]->getType() == "GLASS") {
                        for (int j = 0; j < 4; j++) {
                            allGlass[j] += distribution[j];
                        }
                    } else if (this->tiles[i]->getType() == "HEAT") {
                        for (int j = 0; j < 4; j++) {
                            allHeat[j] += distribution[j];
                        }
                    } else if (this->tiles[i]->getType() == "WIFI") {
                        for (int j = 0; j < 4; j++) {
                            allWifi[j] += distribution[j];
                        }
                    }
                }
            }
            bool gained = false;
            for (int i = 0; i < 4; i++) {
                if (! (allBrick[i] == 0 && allEnergy[i] == 0 && allGlass[i] == 0 && allHeat[i] == 0 && allWifi[i] == 0)) {
                    std::cout << "Builder " << this->builders[i]->getName() << " gained:" << std::endl;
                    if (allBrick[i] != 0) {
                        std::cout << allBrick[i] << " " << "BRICK" << std::endl;
                    }
                    if (allEnergy[i] != 0) {
                        std::cout << allEnergy[i] << " " << "ENERGY" << std::endl;
                    }
                    if (allGlass[i] != 0) {
                        std::cout << allGlass[i] << " " << "GLASS" << std::endl;
                    }
                    if (allHeat[i] != 0) {
                        std::cout << allHeat[i] << " " << "HEAT" << std::endl;
                    }
                    if (allWifi[i] != 0) {
                        std::cout << allWifi[i] << " " << "WIFI" << std::endl;
                    }
                    gained = true;
                }
            }
            if (!gained) {
                std::cout << "> No builders gained resources." << std::endl;
            }
            std::cout << "Enter a command:" << std::endl << "> ";
        } else if (diceNum == 7) {
            std::cout << "> ";
            for (int i = 0; i < 4; i++) {
                this->builders[i]->geeseAttack();
            }
            std::cout << "Choose where to place the GEESE." << std::endl << "> ";
            int tilePosn = -1;
            std::string geeseCMD;
            // By Eric
            while (!(std::cin.eof())) {
                std::cin >> geeseCMD;
                if (std::cin.eof()) {
                    throw std::invalid_argument{"End of file reached."};
                }
                bool successRead = true;
                try {
                    tilePosn = std::stoi(geeseCMD);
                } catch (std::invalid_argument& e) {
                    successRead = false;
                } catch (std::out_of_range& e) {
                    successRead = false;
                }
                if (!successRead) {
                    std::cout << "ERROR: Choose where to place the GEESE. isn't a valid integer." << std::endl;
                    std::cout << "Choose where to place the GEESE." << std::endl << "> ";
                } else if (!(0 <= tilePosn && tilePosn <= 18)){
                    std::cout << "Geese can't move here." << std::endl;
                    std::cout << "Choose where to place the GEESE." << std::endl << "> ";
                } else if (tilePosn == this->GeesePos) {
                    std::cout << "Geese can't move here. Move to a new place." << std::endl << "> ";
                } else { // if (0 <= tilePosn <= 18) break;
                    break;
                }
            }
            if (std::cin.eof()) { 
                throw std::invalid_argument{"End of file reached."};
            } // Throw invalid_argument.
            if (this->GeesePos > 0) {
                this->td->notifyGeese(this->GeesePos, false);
                this->tiles[this->GeesePos]->setGeese(false);
            }
            this->GeesePos = tilePosn;
            this->td->notifyGeese(tilePosn, true);
            this->tiles[this->GeesePos]->setGeese(true);
            // ^^^ Eric
            std::vector<Builder*> buildersLst = this->tiles[tilePosn]->stoleFrom(this->builders[this->turn % 4].get());
            if (buildersLst.size() == 0) {
                std::cout << "Builder " << this->builders[this->turn % 4]->getName() << " has no builders to steal from." << std::endl;
                std::cout << "> ";
            } else {
                std::cout << "Builder " << this->builders[this->turn % 4]->getName() << " can choose to steal from " << std::endl;
                for (unsigned int i = 0; i < buildersLst.size(); i++) {
                    std::cout << buildersLst[i]->getName();
                    if (i != buildersLst.size() - 1) {
                        std::cout << ", ";
                    } else {
                        std::cout << "." << std::endl;
                    }
                }
                std::string victim;
                bool notFound = true;
                bool invalid = true;
                while (notFound) {
                    std::cout << "Choose a builder to steal from." << std::endl << "> ";
                    std::cin >> victim;
                    if (std::cin.eof()) {
                        throw std::invalid_argument{"End of file reached."};// EOF reached.
                    }
                    std::transform(victim.begin(), victim.end(), victim.begin(), ::tolower);
                    victim[0] = toupper(victim[0]);
                    for (unsigned int i = 0; i < buildersLst.size(); i++) {
                        if (victim == buildersLst[i]->getName() || victim == buildersLst[i]->getName().substr(0,1)) {
                            buildersLst[i]->beingStole(this->builders[this->turn % 4].get());
                            std::cout << "> ";
                            notFound = false;
                            break;
                        }
                    }
                    if (notFound) {
                        for (int i = 0; i < 4; i++) {
                            if (this->builders[i]->getName() == victim || victim == this->builders[i]->getName().substr(0,1)) {
                                invalid = false;
                            }
                        }
                        if (invalid) {
                            std::cerr << "Invalid colour." << std::endl;
                        } else {
                            std::cerr << "They can't be stolen from." << std::endl;
                        }
                    }
                }            
            }
        }
    } else if (cmd == "status") {
        std::cout << "> ";
        for (int i = 0; i < 4; i++) {
            this->builders[i]->printStatus();
            std::cout << "> ";
        }
    } else if (cmd == "help") {
        std::cout << "~ load : changes current builder's dice type to 'loaded'" << std::endl;
        std::cout << "~ fair : changes current builder's dice type to 'fair'" << std::endl;
        std::cout << "~ roll : rolls the dice and distributes resources." << std::endl;
        std::cout << "~ status : prints the current status of all builders in order from builder 0 to 3." << std::endl;
        std::cout << "~ help : prints out the list of commands." << std::endl;
        std::cout << "> ";
    } else {
        throw std::invalid_argument{"Invalid command."};
    }
}

void Board::readDuring(const std::string cmd) {
    if (cmd == "board") {
        this->td->printBoard();
        std::cout << "> ";
    } else if (cmd == "status") {
        for (int i = 0; i < 4; i++) {
            this->builders[i]->printStatus();
        }
    } else if (cmd == "residences") {
        this->builders[this->turn % 4]->printRes();
    } else if (cmd == "build-road") {
        int posn;
        if (!(std::cin >> posn)) {
            throw std::invalid_argument{"ERROR:  isn't a valid integer."};
        }

        if (this->builders[this->turn % 4]->buildRoad(this->edges[posn].get())) {
            std::string roadMsg = this->builders[this->turn % 4]->getName().substr(0,1) + "R";
            this->td->notifyEdg(posn, roadMsg);
        }

    } else if (cmd == "build-res") {
        int posn;
        if (!(std::cin >> posn)) {
            throw std::invalid_argument{"ERROR:  isn't a valid integer."};
        }
        if (this->vertices[posn]->getLevel() == 'N') {
            if (this->builders[this->turn % 4]->buildRes(this->vertices[posn].get())) {
                std::string verMsg = "|" + this->builders[this->turn % 4]->getName().substr(0,1) + "B|";
                this->td->notifyVer(posn, verMsg);
            }
        } else {
            std::cout << "You cannot build here." << std::endl << "> ";
        }
    } else if (cmd == "improve") {
        int posn;
        if (!(std::cin >> posn)) {
            throw std::invalid_argument{"ERROR:  isn't a valid integer."};
        }
        if (this->vertices[posn]->getLevel() != 'N') {
            if (this->builders[this->turn % 4]->buildRes(this->vertices[posn].get())) {
                std::string verMsg = "|" + this->builders[this->turn % 4]->getName().substr(0,1) + this->vertices[posn]->getLevel() + "|";
                this->td->notifyVer(posn, verMsg);
            }
        } else {
            std::cout << "You cannot build here." << std::endl << "> ";
        }
    } else if (cmd == "trade") {
        std::string colour;
        while (std::cin >> colour) {
            std::transform(colour.begin(), colour.end(), colour.begin(), ::tolower);
            int target = -1;
            if (colour == "0" || colour == "b" || colour == "blue") {
                target = 0;
            } else if (colour == "1" || colour == "r" || colour == "red") {
                target = 1;
            } else if (colour == "2" || colour == "o" || colour == "orange") {
                target = 2;
            } else if (colour == "3" || colour == "y" || colour == "yellow")  {
                target = 3;
            } else {
                std::cout << "> ";
                std::cerr << "Invalid colour" << std::endl;
                std::cout << "> ";
                continue;
            }
            this->builders[this->turn % 4]->trade(this->builders[target].get());
            break;
        }
    } else if (cmd == "market") {
        this->builders[this->turn % 4]->market();
    } else if (cmd == "next") {
        std::vector<std::string> players {"Blue", "Red", "Orange", "Yellow"};
        for (int i = 0; i < 4; i++) {
            if (this->builders[i]->getPoint() >= 10) {
                std::cout << "Congratulations!! " << players[i] << " wins!!" << std::endl;
                std::cout << "Would you like to play again?" << std::endl;
                std::cout << "> ";
                while (!std::cin.eof()) {
                    std::string again;
                    std::cin >> again;
                    std::transform(again.begin(), again.end(), again.begin(), ::tolower);
                    if (again == "y" || again == "yes") {
                        throw std::invalid_argument{"AGAIN"};
                    } else if (again == "n" || again == "no"){
                        throw std::invalid_argument{"END"};
                    } else {
                        std::cerr << "Invalid command." << std::endl;
                        std::cout << "Would you like to play again?" << std::endl;
                        std::cout << "> ";
                    }
                }
            }
        }
        this->turn += 1;
        throw std::invalid_argument{"next"};
        //this->td->printBoard();
        //std::cout << "Builder " << this->builders[this->turn % 4]->getName() << "'s turn." << std::endl;
        return;
    } else if (cmd == "save") {
        std::string fileName;
        if (std::cin.eof()) {
            this->save("backup.sv");
        } else {
            std::cin >> fileName;
            std::cout << "Saving to " << fileName << "..." << std::endl; 
            this->save(fileName);
        }
    } else if (cmd == "help") {
        std::cout << "~ board : prints the current board." << std::endl;
        std::cout << "~ status : prints the current status of all builders in order from builder 0 to 3." << std::endl;
        std::cout << "~ residences : prints the residences the current builder has currently completed." << std::endl;
        std::cout << "~ build - road <road#> : attempts to builds the road at <road#>." << std::endl;
        std::cout << "~ build - res <housing#> : attempts to builds a basement at <housing#>." << std::endl;
        std::cout << "~ improve <housing#> : attempts to improve the residence at <housing#>." << std::endl;
        std::cout << "~ trade <colour> <give> <take> : attempts to trade with builder <colour>, giving one resource of type <give> and receiving one resource of type <take>." << std::endl;
        std::cout << "~ market <sell> <buy> : attempts to sell resources on the market, giving four resource of type <sell> and receiving one resource of type <buy>." << std::endl;
        std::cout << "~ next : passes control onto the next builder in the game." << std::endl;
        std::cout << "~ save <file> : saves the current game state to <file>." << std::endl;
        std::cout << "~ help : prints out the list of commands." << std::endl;
        std::cout << "> ";
    } else {
        throw std::invalid_argument{"Invalid command."};
    }
}
