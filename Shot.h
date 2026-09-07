#ifndef SHOT_H
#define SHOT_H

#include "WorkUnit.h"
#include <string>

class ShotState;

class Shot : public WorkUnit
{
private:
    ShotState* currentState;
    int estimatedHours;

public:
    Shot(std::string name, int estimatedHours);
    virtual ~Shot();

    
    virtual std::string getName();
    virtual int getEstimatedHours();
    virtual void process();

    
    virtual WorkUnitIterator* createIterator(IteratorType type);

    
    void setState(ShotState* state);
    std::string getStateName();

    void schedule() override;
    void startFilming() override;
    void submitForReview() override;
    void approve() override;
    void requestReshoot() override;
};

#endif
