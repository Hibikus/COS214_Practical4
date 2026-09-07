#ifndef FILMINGSTATE_H
#define FILMINGSTATE_H

#include "ShotState.h"

class FilmingState : public ShotState
{
public:
    virtual ~FilmingState();

    virtual std::string getName();

    virtual void schedule(Shot* s);
    virtual void startFilming(Shot* s);
    virtual void submitForReview(Shot* s);
    virtual void approve(Shot* s);
    virtual void requestReshoot(Shot* s);
};

#endif