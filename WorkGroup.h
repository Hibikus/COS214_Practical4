#ifndef WORKGROUP_H
#define WORKGROUP_H

#include "WorkUnit.h"
#include <vector>
#include <string>

class WorkGroup : public WorkUnit
{
private:
    std::vector<WorkUnit*> children;
    std::vector<WorkUnit*> getChildren() const override;

public:
    WorkGroup(std::string name);
    virtual ~WorkGroup();

    void add(WorkUnit* unit);
    void remove(WorkUnit* unit);

    virtual std::string getName();
    virtual int getEstimatedHours();
    virtual void process();
    virtual WorkUnitIterator* createIterator(IteratorType type);
};

#endif