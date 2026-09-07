#ifndef WORKUNIT_H
#define WORKUNIT_H

#include <string>
#include <vector>

class WorkUnitIterator;
enum class IteratorType{
    DepthFirst,
    Ready
};

class WorkUnit
{
protected:
    std::string name;

    virtual std::vector<WorkUnit*> getChildren() const { return {}; } //only seen by concrete iterators
    friend class DepthFirstIterator;
    friend class ReadyShotIterator;
    friend class WorkUnitDecorator;
public:
    WorkUnit(std::string name);
    virtual ~WorkUnit();

    virtual std::string getName() = 0;
    virtual int getEstimatedHours() = 0;
    virtual void process() = 0;
    virtual WorkUnitIterator* createIterator(IteratorType type) = 0;

    virtual std::string getStateName() { return ""; }
    virtual bool isGroup() const { return false; }

    virtual void schedule() {}
    virtual void startFilming() {}
    virtual void submitForReview() {}
    virtual void approve() {}
    virtual void requestReshoot() {}
};

#endif
