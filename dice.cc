#include "dice.h"
#include <iostream>
#include <random>
#include <chrono>

Dice::Dice(std::shared_ptr<Strategy> strategy) noexcept: option{strategy} {}

void Dice::setStrategy(std::shared_ptr<Strategy> strategy) noexcept {
        this->option = strategy;
}

int Dice::roll(int& point) noexcept {
    option->doAlgorithm(point);
    return point;
}

/*
int main() {
    auto dice = std::make_shared<Dice> (std::make_shared<FairStrategy>());
    int a = -1;
    int pnt = dice.get()->roll(a);
    std::cout << pnt << std::endl;
    dice.get()->setStrategy (std::make_shared<LoadedStrategy>());
    std::cout << dice.get()->roll(pnt) << std::endl;
}
*/
