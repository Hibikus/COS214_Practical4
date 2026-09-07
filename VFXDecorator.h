#ifndef VFXDECORATOR_H
#define VFXDECORATOR_H

#include <iostream>
#include "WorkUnitDecorator.h"

class VFXDecorator : public WorkUnitDecorator {
private:
    int vfxHours;

public:
    VFXDecorator(WorkUnit* wrapped, int vfxHours)
        : WorkUnitDecorator(wrapped), vfxHours(vfxHours) {}

    std::string getName() const override {
        return wrapped->getName() + " [VFX]";
    }

    int getEstimatedHours() const override {
        return wrapped->getEstimatedHours() + vfxHours;
    }

    void process() override {
        wrapped->process();
        std::cout << "  -> Applying VFX pass (" << vfxHours << "h render/comp)\n";
    }
};

#endif
