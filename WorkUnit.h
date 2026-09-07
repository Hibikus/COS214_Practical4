#ifndef WORKUNIT_H
#define WORKUNIT_H

#include <string>

class WorkUnit {
public:
    virtual ~WorkUnit() {}

    virtual std::string getName() const = 0;
    virtual int getEstimatedHours() const = 0;
    virtual void process() = 0;
};

#endif
