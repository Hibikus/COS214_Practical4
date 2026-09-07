#ifndef SCRIPTEDSTATE_H
#define SCRIPTEDSTATE_H

#include "ShotState.h"

class ScriptedState : public ShotState
{
public:
    virtual ~ScriptedState();

    virtual std::string getName();

    virtual void schedule(Shot* s);
    virtual void startFilming(Shot* s);
    virtual void submitForReview(Shot* s);
    virtual void approve(Shot* s);
    virtual void requestReshoot(Shot* s);
};

#endif