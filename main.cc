#include "board.h"
#include <iostream>

int main(int argNum, char* argVal[]) {
    while (true) {
        auto board = std::make_unique<Board> ();
        bool haveSeed = false;
        std::string seedNum;
        bool setSeed = false;
        bool setLoad = false;
        std::string loadFile;
        bool setBoard = false;
        std::string boardFile;
        bool random = false;
        try {
            if (argNum == 1) {
                board->init(argNum, "-board", "layout.txt");
            } else {
                for (int i = 1; i < argNum; i++) {
                    std::string argName{argVal[i]};
                    //std::cerr << argName << std::endl;
                    if (argName == "-seed") {
                        if (haveSeed) {
                            std::cerr << "ERROR: already specified -seed once before" << std::endl;
                            return 0;
                        }
                        if (argNum == i + 1) {
                            std::cerr << "ERROR: -seed missing seed argument" << std::endl;
                            return 0;
                        } else {
                            int seed;
                            seedNum = argVal[i + 1];
                            std::istringstream iss{seedNum};
                            if (iss >> seed) {
                                seedNum = argVal[i + 1];
                                i += 1;
                                if (random) {
                                    haveSeed = true;
                                    setSeed = true;
                                } else {
                                    haveSeed = true;
                                }
                            } else {
                                std::cerr << "ERROR: " << seedNum << " isn't an invalid seed." << std::endl;
                                return 0;
                            }
                        }
                    } else if (argName == "-load") {
                        if (setLoad) {
                            std::cerr << "ERROR: already specified -load once before" << std::endl;
                            return 0;
                        }
                        if (setBoard) {
                            std::cerr << "ERROR: already specified -board, can't also specify -load" << std::endl;
                            return 0;
                        }
                        if (random) {
                            std::cerr << "ERROR: previous -random-board being ignored in favour of -load" << std::endl;
                        }
                        if (argNum == i + 1) {
                            std::cerr << "ERROR: -load missing filename argument" << std::endl;
                            return 0;
                        } else {
                            loadFile = argVal[i + 1];
                            setLoad = true;
                            i += 1;
                        }
                    } else if (argName == "-board") {
                        if (setBoard) {
                            std::cerr << "ERROR: already specified -board once before" << std::endl;
                            return 0;
                        }
                        if (setLoad) {
                            std::cerr << "ERROR: already specified -load, can't also specify -board" << std::endl;
                            return 0;
                        }
                        if (random) {
                            std::cerr << "ERROR: previous -random-board being ignored in favour of -board" << std::endl;
                        }
                        if (argNum == i + 1) {
                            std::cerr << "ERROR: -board missing filename argument" << std::endl;
                            return 0;
                        } else {
                            boardFile = argVal[i + 1];
                            setBoard = true;
                            i += 1;
                        }
                    } else if (argName == "-random-board") {
                        if (haveSeed) {
                            setSeed = true;
                        }
                        if (setLoad) {
                            std::cerr << "ERROR: -random-board being ignored in favour of previous -load" << std::endl;
                        } else if (setBoard) {
                            std::cerr << "ERROR: -random-board being ignored in favour of previous -board" << std::endl;
                        }
                        random = true;
                    } else {
                        std::cerr << "ERROR: unrecognized argument " << argVal[i] << std::endl;
                        return 0;
                    }
                }
                if (setLoad) {
                    board->init(argNum, "-load", loadFile);
                } else if (setBoard) {
                    board->init(argNum, "-board", boardFile);
                } else if (setSeed) {
                    board->init(argNum, "-seed", seedNum);
                } else if (random) {
                    board->init(argNum, "-random-board");
                } else {
                    board->init(argNum, "-board", "layout.txt");
                }
            }
        } catch (std::invalid_argument & e) {
            std::cerr << e.what() << std::endl;
            return 0;
        }
        if (! setLoad) {
            std::string status = "choose";
            try {
                board->init(0, status);
            } catch (std::invalid_argument & e) {
                    std::cerr << e.what() << std::endl;
                    return 0;
            }
        }
        bool again = false;
        while (!std::cin.eof()) {
            board->readDuring("board");
            board->readBegin("start");
            std::string command;
            try {
                while (std::cin >> command && command != "roll") {
                    try {
                        board->readBegin(command);
                    } catch (std::invalid_argument & e) {
                        std::cerr << e.what() << std::endl;
                        std::cout << "Please enter 'help' for a list of valid commands." << std::endl;
                        std::cout << "> ";
                    }
                }
                board->readBegin(command);
                while (std::cin >> command) {
                    if (std::cin.eof()) break;
                    try {
                        board->readDuring(command);
                    } catch (std::invalid_argument & e) {
                        std::string errorMsg = e.what();
                        if (errorMsg == "Invalid command.") {
                            std::cerr << "Invalid command." << std::endl;
                            std::cout << "Please enter 'help' for a list of valid commands." << std::endl;
                            std::cout << "> ";
                        } else {
                            throw e;
                        }
                    }
                    if (command == "next") break;
                    std::cout << "Enter a command:" << std::endl << "> ";
                }
            } catch (std::invalid_argument & e) {
                std::string errorMsg = e.what();
                if (errorMsg == "END") {
                    return 0;
                } else if (errorMsg == "AGAIN") {
                    argNum = 1;
                    again = true;
                    break;
                } else if (errorMsg != "next") {
                    std::cerr << errorMsg << std::endl << "> ";
                }
            }
        }
        if (again) continue;
        std::cout << "End of file reached." << std::endl;
        std::cout << std::endl << "Saving to backup.sv..." <<std::endl;
        board->readDuring("save");
        return 0;
    }
}
