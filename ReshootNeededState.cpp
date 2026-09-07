#include "ReshootNeededState.h"
#include "Shot.h"
#include "ScheduledState.h"
#include <iostream>

ReshootNeededState::~ReshootNeededState()
{
}

std::string ReshootNeededState::getName()
{
    return "Reshoot Needed";
}

void ReshootNeededState::schedule(Shot* s)
{
    static ScheduledState scheduledState;
    s->setState(&scheduledState);
}

void ReshootNeededState::startFilming(Shot* s)
{
    (void)s;
    std::cout << "Cannot start filming until the reshoot has been scheduled." << std::endl;
}

void ReshootNeededState::submitForReview(Shot* s)
{
    (void)s;
    std::cout << "Cannot submit for review until the reshoot has been completed." << std::endl;
}

void ReshootNeededState::approve(Shot* s)
{
    (void)s;
    std::cout << "Cannot approve a shot that requires a reshoot." << std::endl;
}

void ReshootNeededState::requestReshoot(Shot* s)
{
    (void)s;
    std::cout << "A reshoot has already been requested." << std::endl;
}