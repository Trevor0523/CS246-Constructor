#ifndef __DICE_STRATEGY_H__
#define __DICE_STRATEGY_H__

class Strategy {
    public:
    virtual ~Strategy();
    virtual void doAlgorithm(int& point) noexcept = 0;
};

class LoadedStrategy : public Strategy {
    public:
    void doAlgorithm(int& point) noexcept override;
};

class FairStrategy : public Strategy {
    public:
    void doAlgorithm(int& point) noexcept override;
};

#endif
