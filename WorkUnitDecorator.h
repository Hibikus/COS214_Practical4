#ifndef WORKUNITDECORATOR_H
#define WORKUNITDECORATOR_H

#include "WorkUnit.h"

class WorkUnitDecorator : public WorkUnit {
protected:
    WorkUnit* wrapped;

public:
    explicit WorkUnitDecorator(WorkUnit* wrapped) : wrapped(wrapped) {}

    virtual ~WorkUnitDecorator() {
        delete wrapped;
    }

    std::string getName() const override {
        return wrapped->getName();
    }

    int getEstimatedHours() const override {
        return wrapped->getEstimatedHours();
    }

    void process() override {
        wrapped->process();
    }
};

#endif
