#ifndef COMPLETEDSTATE_H
#define COMPLETEDSTATE_H

#include "ShotState.h"

class CompletedState : public ShotState
{
public:
    virtual ~CompletedState();

    virtual std::string getName();

    virtual void schedule(Shot* s);
    virtual void startFilming(Shot* s);
    virtual void submitForReview(Shot* s);
    virtual void approve(Shot* s);
    virtual void requestReshoot(Shot* s);
};

#endif