#ifndef SOUNDMIXDECORATOR_H
#define SOUNDMIXDECORATOR_H

#include <iostream>
#include "WorkUnitDecorator.h"

class SoundMixDecorator : public WorkUnitDecorator {
private:
    int mixHours;
    int stemCount;

public:
    SoundMixDecorator(WorkUnit* wrapped, int mixHours, int stemCount)
        : WorkUnitDecorator(wrapped), mixHours(mixHours), stemCount(stemCount) {}

    std::string getName() const override {
        return wrapped->getName() + " [Sound]";
    }

    int getEstimatedHours() const override {
        return wrapped->getEstimatedHours() + mixHours;
    }

    void process() override {
        wrapped->process();
        std::cout << "  -> Mixing sound, " << stemCount
                  << " stems (" << mixHours << "h)\n";
    }
};

#endif
