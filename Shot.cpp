#include "Shot.h"
#include "ShotState.h"
#include "ScriptedState.h"
#include "DepthFirstIterator.h"
#include "ReadyShotIterator.h"

#include <iostream>

Shot::Shot(std::string name, int estimatedHours)
    : WorkUnit(name), estimatedHours(estimatedHours)
{
    static ScriptedState scriptedState;
    currentState = &scriptedState;
}

Shot::~Shot()
{
}

std::string Shot::getName()
{
    return name;
}

int Shot::getEstimatedHours()
{
    return estimatedHours;
}

void Shot::process()
{
    std::cout << "Processing shot: " << name<< " [" << currentState->getName() << "]" << std::endl;
}

WorkUnitIterator* Shot::createIterator(IteratorType type)
{
    // A Shot is a leaf, so either iterator just yields this single item
    // (or nothing, for ReadyShotIterator, if this shot isn't ready).
    switch (type)
    {
        case IteratorType::DepthFirst:
            return new DepthFirstIterator(this);
        case IteratorType::Ready:
            return new ReadyShotIterator(this);
    }
    return nullptr;
}

void Shot::setState(ShotState* state)
{
    if (state != nullptr)
    {
        currentState = state;
    }
}

std::string Shot::getStateName()
{
    return currentState->getName();
}

void Shot::schedule()
{
    currentState->schedule(this);
}

void Shot::startFilming()
{
    currentState->startFilming(this);
}

void Shot::submitForReview()
{
    currentState->submitForReview(this);
}

void Shot::approve()
{
    currentState->approve(this);
}

void Shot::requestReshoot()
{
    currentState->requestReshoot(this);
}