#ifndef RESHOOTNEEDEDSTATE_H
#define RESHOOTNEEDEDSTATE_H

#include "ShotState.h"

class ReshootNeededState : public ShotState
{
public:
    virtual ~ReshootNeededState();

    virtual std::string getName();

    virtual void schedule(Shot* s);
    virtual void startFilming(Shot* s);
    virtual void submitForReview(Shot* s);
    virtual void approve(Shot* s);
    virtual void requestReshoot(Shot* s);
};

#endif