#include "CompletedState.h"
#include <iostream>

CompletedState::~CompletedState()
{
}

std::string CompletedState::getName()
{
    return "Completed";
}

void CompletedState::schedule(Shot* s)
{
    (void)s;
    std::cout << "Cannot schedule a completed shot." << std::endl;
}

void CompletedState::startFilming(Shot* s)
{
    (void)s;
    std::cout << "Cannot start filming a completed shot." << std::endl;
}

void CompletedState::submitForReview(Shot* s)
{
    (void)s;
    std::cout << "Cannot submit a completed shot for review." << std::endl;
}

void CompletedState::approve(Shot* s)
{
    (void)s;
    std::cout << "The shot is already completed." << std::endl;
}

void CompletedState::requestReshoot(Shot* s)
{
    (void)s;
    std::cout << "Cannot request a reshoot for a completed shot." << std::endl;
}