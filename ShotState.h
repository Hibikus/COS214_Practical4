#ifndef SHOTSTATE_H
#define SHOTSTATE_H

#include <string>

class Shot;

class ShotState
{
public:
    virtual ~ShotState();

    virtual std::string getName() = 0;

    virtual void schedule(Shot* s) = 0;
    virtual void startFilming(Shot* s) = 0;
    virtual void submitForReview(Shot* s) = 0;
    virtual void approve(Shot* s) = 0;
    virtual void requestReshoot(Shot* s) = 0;
};

#endif