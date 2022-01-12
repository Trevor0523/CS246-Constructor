#include "textdisplay.h"


TextDisplay::TextDisplay() {
    for (int i = 0; i <= 53; i++) { // Emplace the vertices.
        std::string msg;
        if (i < 10) {
            msg = "| " + std::to_string(i) + "|";
        } else {
            msg = "|" + std::to_string(i) + "|";
        }
        this->vertices.emplace_back(msg);
    }

    for (int i = 0; i <= 71; i++) { // Emplace the edges.
        std::string msg;
        if (i < 10) {
            msg = " " + std::to_string(i);
        } else {
            msg = std::to_string(i);
        }
        this->edges.emplace_back(msg);
    }

    for (int i = 0; i < 19; i++) {
        std::string msgType = "1234567";
        this->tileType.emplace_back(msgType);

        std::string msgValue = "123456";
        this->tileValue.emplace_back(msgValue);

        std::string msgGeese = "       "; // " GEESE "
        this->tileGeese.emplace_back(msgGeese);

        int pos = i;
        std::string poss;
        if (pos < 10) {
            poss = "    " + std::to_string(pos) + "   ";
        } else {
            poss = "   " + std::to_string(pos) + "   ";
        }
        //std::cout << poss << std::endl;
        this->tilePos.emplace_back(poss);
    }

}

void TextDisplay::notifyVer(int pos, std::string info) {
    this->vertices[pos] = info;
}

void TextDisplay::notifyEdg(int pos, std::string info) {
    this->edges[pos] = info;
}

void TextDisplay::notifyTile(int pos, std::string type, int value, bool is_geese) {
    std::string msgType;
    if (type != "ENERGY") {
        msgType = " " + type;
        msgType.resize(7, ' ');
    } else {
        msgType = "ENERGY ";
    }
    this->tileType[pos] = msgType;

    std::string msgValue;
    //if (value == 0) std::cout << "Being notified by 0 !";
    if (value < 10 && value != 7) {
        msgValue = "   " + std::to_string(value) + "  ";
    } else if (value == 7) {
        msgValue = "      ";
    } else {
        msgValue = "  " + std::to_string(value) + "  ";
    }
    this->tileValue[pos] = msgValue;

    if (is_geese) {
        this->tileGeese[pos] = " GEESE ";
    } else {
        this->tileGeese[pos] = "       ";
    }
}

void TextDisplay::notifyGeese(int pos, bool is_geese) {
    if (is_geese) {
        this->tileGeese[pos] = " GEESE ";
    } else {
        this->tileGeese[pos] = "       ";
    }
}

void printspace(int num) {
    for (int i = 0; i < num; i++) {
        std::cout << " ";
    }
}

void printblank() {
    std::cout << " |         | ";
}

void TextDisplay::printline1(int Ver, int Edg, int tilePos, int num) {
    printspace(6);
    int j = 0;
    int k = 0;
    for (int i = 0; i < num; i++) {
        std::cout << this->vertices[Ver + i];
        if (i == 0 || i == 2 || i == 4) {
            std::cout << "--" << this->edges[Edg + j] << "--";
            j += 1;
        } else {
            if (i != num - 1) {
                std::cout << this->tileValue[tilePos + k];
                k += 1;
            }
        }
    }
}

void TextDisplay::printline2(int tilePos) {
    printspace(6);
    std::cout << " ";
    for (int i = 0; i < 2; i++) {
        printblank();
        std::cout << this->tileGeese[tilePos + i];
    }
    std::cout << " |         |";
}

void TextDisplay::printline3(int Edg, int tilePos, int num) {
    printspace(6);
    std::cout << " ";
    int k = 0;
    for (int i = 0; i < num; i++) {
        std::cout << this->edges[Edg + i];
        if (i == 0 || i == 2 || i == 4) {
            std::cout << this->tilePos[tilePos + k];
            k += 1;
        } else {
            if (i != num - 1) { printspace(8); }
        }
    }
    //std::cout << " ";
}

void TextDisplay::printline4(int tilePos) {
    printspace(6);
    std::cout << "  | ";
    for (int i = 0; i < 3; i++) {
        std::cout << this->tileType[tilePos + i];
        if (i != 2) {
            printblank();
        }
    }
    std::cout << " |";
    //std::cout << " ";
}

void TextDisplay::printline5(int Ver, int Edg, int tilePos) {
    printspace(6);
    int j = 0;
    int k = 0;
    for (int i = 0; i < 6; i++) {
        std::cout << this->vertices[Ver + i];
        if (i == 0 || i == 2 || i == 4) {
            std::cout << this->tileValue[tilePos + j];
            j += 1;
        } else {
            if (i != 5) {
                std::cout << "--" << this->edges[Edg + k] << "--";
                k += 1;
            }
        }
    }
}

void TextDisplay::printline6(int tilePos) {
    printspace(6);
    std::cout << "  | ";
    for (int i = 0; i < 3; i++) {
        std::cout << this->tileGeese[tilePos + i];
        if (i != 2) {
            printblank();
        }
    }
    std::cout << " |";
    //std::cout << " ";
}

void TextDisplay::printline7(int Edg, int tilePos, int num) {
    printspace(6);
    std::cout << " ";
    int k = 0;
    for (int i = 0; i < num; i++) {
        std::cout << this->edges[Edg + i];
        if ((i == 1 || i == 3) && num != 2 && tilePos + k <= 18 ) {
            std::cout << this->tilePos[tilePos + k];
            k += 1;
        } else {
            if (i != num - 1) { printspace(8); }
        }
    }
    //std::cout << " ";
}

void TextDisplay::printline8(int tilePos) {
    printspace(6);
    std::cout << " ";
    for (int i = 0; i < 2; i++) {
        printblank();
        std::cout << this->tileType[tilePos + i];
    }
    std::cout << " |         |";
}

void TextDisplay::printBoard() noexcept {
    printspace(20);
    printline1(0, 0, 0, 2);
    //printspace(20);
    std::cout << std::endl;
    printspace(22 + 6);
    std::cout << "|         |";
    //printspace(21);
    std::cout << std::endl;
    printspace(20);
    printline3(1, 0, 2);
    //printspace(20);
    std::cout << std::endl;
    printspace(22 + 6);
    std::cout << "| " << this->tileType[0] << " |";
    //printspace(21);
    std::cout << std::endl;
    printspace(10);
    printline1(2, 3, 0, 4);
    //printspace(10);
    std::cout << std::endl;
    printspace(11 + 6);
    printblank();
    std::cout << this->tileGeese[0];
    std::cout << " |         |";
    //printblank();
    //printspace(10);
    std::cout << std::endl;
    printspace(10);
    printline3(5, 1, 4);
    //printspace(10);
    std::cout << std::endl;
    printspace(12 + 6);
    std::cout << "| " << this->tileType[1];
    printblank();
    std::cout << this->tileType[2] << " |";
    //printspace(11);
    std::cout << std::endl;
    int j = 0;
    int k = 0;
    for (int i = 6; i <= 30; i += 12) {
        printline1(i, 9 + j, 1 + k);
        std::cout << std::endl;
        printline2(1 + k);
        std::cout << std::endl;
        printline3(12 + j, 3 + k);
        std::cout << std::endl;
        printline4(3 + k);
        std::cout << std::endl;
        printline5(i + 6, 18 + j, 3 + k);
        std::cout << std::endl;
        printline6(3 + k);
        std::cout << std::endl;
        printline7(20 + j, 6 + k);
        std::cout << std::endl;
        printline8(6 + k);
        std::cout << std::endl;
        j += 17;
        k += 5;
    }
    printline1(42, 60, 16);
    std::cout << std::endl;
    printspace(12 + 6);
    std::cout << "| " << this->tileGeese[16];
    printblank();
    std::cout << this->tileGeese[17];
    std::cout << " |";
    //printspace(11);
    std::cout << std::endl;
    printspace(10);
    printline7(63, 18, 4);
    //printspace(10);
    std::cout << std::endl;
    printspace(11 + 6);
    printblank();
    std::cout << this->tileType[18];
    std::cout << " |         |";
    //printspace(10);
    std::cout << std::endl;
    printspace(10);
    printline1(48, 67, 18, 4);
    //printspace(10);
    std::cout << std::endl;
    printspace(22 + 6);
    std::cout << "| " << this->tileGeese[18] << " |";
    //printspace(20);
    std::cout << std::endl;
    printspace(20);
    printline7(69, 18, 2);
    //printspace(20);
    std::cout << std::endl;
    printspace(21 + 6);
    std::cout << " |         |";
    //printspace(20);
    std::cout << std::endl;
    printspace(20);
    printline1(52,71,18,2);
    //printspace(20);
    std::cout << std::endl;
}
