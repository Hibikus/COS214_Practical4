#include "InReviewState.h"
#include "Shot.h"
#include "CompletedState.h"
#include "ReshootNeededState.h"
#include <iostream>

InReviewState::~InReviewState()
{
}

std::string InReviewState::getName()
{
    return "In Review";
}

void InReviewState::schedule(Shot* s)
{
    (void)s;
    std::cout << "Cannot schedule a shot that is already in review." << std::endl;
}

void InReviewState::startFilming(Shot* s)
{
    (void)s;
    std::cout << "Cannot start filming while the shot is in review." << std::endl;
}

void InReviewState::submitForReview(Shot* s)
{
    (void)s;
    std::cout << "The shot is already in review." << std::endl;
}

void InReviewState::approve(Shot* s)
{
    static CompletedState completedState;
    s->setState(&completedState);
}

void InReviewState::requestReshoot(Shot* s)
{
    static ReshootNeededState reshootNeededState;
    s->setState(&reshootNeededState);
}