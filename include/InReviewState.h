#ifndef INREVIEWSTATE_H
#define INREVIEWSTATE_H

#include "ShotState.h"

class InReviewState : public ShotState
{
public:
    virtual ~InReviewState();

    virtual std::string getName();

    virtual void schedule(Shot* s);
    virtual void startFilming(Shot* s);
    virtual void submitForReview(Shot* s);
    virtual void approve(Shot* s);
    virtual void requestReshoot(Shot* s);
};

#endif