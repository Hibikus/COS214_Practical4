#ifndef WORKUNITDECORATOR_H
#define WORKUNITDECORATOR_H

#include "WorkUnit.h"

class WorkUnitDecorator : public WorkUnit {
protected:
    WorkUnit* wrapped;

    // WorkUnit has no default constructor, so the decorator must give it
    // a name explicitly; the wrapped unit's own name is the sensible default.
    std::vector<WorkUnit*> getChildren() const override {
        return wrapped->getChildren();
    }

public:
    explicit WorkUnitDecorator(WorkUnit* wrapped)
        : WorkUnit(wrapped->getName()), wrapped(wrapped) {}

    virtual ~WorkUnitDecorator() {
        delete wrapped;
    }

    std::string getName() override {
        return wrapped->getName();
    }

    int getEstimatedHours() override {
        return wrapped->getEstimatedHours();
    }

    void process() override {
        wrapped->process();
    }

    WorkUnitIterator* createIterator(IteratorType type) override {
        return wrapped->createIterator(type);
    }

    std::string getStateName() override {
        return wrapped->getStateName();
    }

    bool isGroup() const override {
        return wrapped->isGroup();
    }

    void schedule() override { wrapped->schedule(); }
    void startFilming() override { wrapped->startFilming(); }
    void submitForReview() override { wrapped->submitForReview(); }
    void approve() override { wrapped->approve(); }
    void requestReshoot() override { wrapped->requestReshoot(); }
};

#endif
