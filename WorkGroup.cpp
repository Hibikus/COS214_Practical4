#include "WorkGroup.h"
#include <algorithm>

WorkGroup::WorkGroup(std::string name)
    : WorkUnit(name)
{
}

std::vector<WorkUnit*> WorkGroup::getChildren() const {
    return children;
}

WorkGroup::~WorkGroup()
{
}

void WorkGroup::add(WorkUnit* unit)
{
    if (unit != nullptr)
    {
        children.push_back(unit);
    }
}

void WorkGroup::remove(WorkUnit* unit)
{
    children.erase(
        std::remove(children.begin(), children.end(), unit),
        children.end());
}

std::string WorkGroup::getName()
{
    return name;
}

int WorkGroup::getEstimatedHours()
{
    int totalHours = 0;

    for (WorkUnit* child : children)
    {
        totalHours += child->getEstimatedHours();
    }

    return totalHours;
}

void WorkGroup::process()
{
    for (WorkUnit* child : children)
    {
        child->process();
    }
}

WorkUnitIterator* WorkGroup::createIterator(IteratorType type)
{
    (void)type;
    return nullptr; //currently just returns nullptr temporarily
}