#ifndef COLORGRADEDECORATOR_H
#define COLORGRADEDECORATOR_H

#include <iostream>
#include "WorkUnitDecorator.h"

class ColorGradeDecorator : public WorkUnitDecorator {
private:
    int gradeHours;
    std::string look;

public:
    ColorGradeDecorator(WorkUnit* wrapped, int gradeHours, const std::string& look)
        : WorkUnitDecorator(wrapped), gradeHours(gradeHours), look(look) {}

    std::string getName() override {
        return wrapped->getName() + " [Grade]";
    }

    int getEstimatedHours() override {
        return wrapped->getEstimatedHours() + gradeHours;
    }

    void process() override {
        wrapped->process();
        std::cout << "  -> Colour grading with look '" << look
                  << "' (" << gradeHours << "h)\n";
    }
};

#endif
