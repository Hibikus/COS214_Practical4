#ifndef SCHEDULEDSTATE_H
#define SCHEDULEDSTATE_H

#include "ShotState.h"

class ScheduledState : public ShotState
{
public:
    virtual ~ScheduledState();

    virtual std::string getName();

    virtual void schedule(Shot* s);
    virtual void startFilming(Shot* s);
    virtual void submitForReview(Shot* s);
    virtual void approve(Shot* s);
    virtual void requestReshoot(Shot* s);
};

#endif