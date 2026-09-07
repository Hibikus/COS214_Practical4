#ifndef WORKUNIT_H
#define WORKUNIT_H

#include <string>

class WorkUnitIterator;
enum class IteratorType;

class WorkUnit
{
protected:
    std::string name;

public:
    WorkUnit(std::string name);
    virtual ~WorkUnit();

    virtual std::string getName() = 0;
    virtual int getEstimatedHours() = 0;
    virtual void process() = 0;
    virtual WorkUnitIterator* createIterator(IteratorType type) = 0;
};

#endif
