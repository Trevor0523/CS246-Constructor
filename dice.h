#ifndef __DICE_H__
#define __DICE_H__
#include <memory>
#include <string>
#include "dicestrategy.h"


class Dice {
    std::shared_ptr<Strategy> option;
    int point; // only valid for 2~12
    public:
    Dice(std::shared_ptr<Strategy> strategy) noexcept; // Set loaded strategy as default
    void setStrategy(std::shared_ptr<Strategy> strategy) noexcept; // Read in the option and set up the according strategy.
    int roll(int& point) noexcept; // roll the dice, using the strategy and return the result dice point.
};

#endif
