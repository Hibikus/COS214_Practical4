#include "ScriptedState.h"
#include "Shot.h"
#include "ScheduledState.h"
#include <iostream>

ScriptedState::~ScriptedState()
{
}

std::string ScriptedState::getName()
{
    return "Scripted";
}

void ScriptedState::schedule(Shot* s)
{
    static ScheduledState scheduledState;
    s->setState(&scheduledState);
}

void ScriptedState::startFilming(Shot* s)
{
    (void)s;
    std::cout << "Cannot start filming while the shot is scripted." << std::endl;
}

void ScriptedState::submitForReview(Shot* s)
{
    (void)s;
    std::cout << "Cannot submit a scripted shot for review." << std::endl;
}

void ScriptedState::approve(Shot* s)
{
    (void)s;
    std::cout << "Cannot approve a scripted shot." << std::endl;
}

void ScriptedState::requestReshoot(Shot* s)
{
    (void)s;
    std::cout << "Cannot request a reshoot for a scripted shot." << std::endl;
}