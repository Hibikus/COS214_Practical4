#ifndef SHOT_H
#define SHOT_H

#include "WorkUnit.h"
#include <string>

class ShotState;

class Shot : public WorkUnit
{
private:
    ShotState* currentState;

public:
    Shot(std::string name);
    virtual ~Shot();

    virtual std::string getName();
    virtual int getEstimatedHours();
    virtual void process();
    virtual WorkUnitIterator* createIterator(IteratorType type);

    void setState(ShotState* state);
    std::string getStateName();
};

#endif