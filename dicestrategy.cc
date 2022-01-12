#include "dicestrategy.h"
#include <random>
#include <chrono>

Strategy::~Strategy() {}

void LoadedStrategy::doAlgorithm(int& point) noexcept {}

void FairStrategy::doAlgorithm(int& point) noexcept {
    //std::random_device rd;
    //std::default_random_engine generator{rd()};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{seed};
    std::uniform_int_distribution<int> distribution(2,12);
    point = distribution(generator);
}
