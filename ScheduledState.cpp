#include "ScheduledState.h"
#include "Shot.h"
#include "FilmingState.h"
#include <iostream>

ScheduledState::~ScheduledState()
{
}

std::string ScheduledState::getName()
{
    return "Scheduled";
}

void ScheduledState::schedule(Shot* s)
{
    (void)s;
    std::cout << "The shot is already scheduled." << std::endl;
}

void ScheduledState::startFilming(Shot* s)
{
    static FilmingState filmingState;
    s->setState(&filmingState);
}

void ScheduledState::submitForReview(Shot* s)
{
    (void)s;
    std::cout << "Cannot submit a scheduled shot for review." << std::endl;
}

void ScheduledState::approve(Shot* s)
{
    (void)s;
    std::cout << "Cannot approve a scheduled shot." << std::endl;
}

void ScheduledState::requestReshoot(Shot* s)
{
    (void)s;
    std::cout << "Cannot request a reshoot for a scheduled shot." << std::endl;
}