#ifndef SHOT_H
#define SHOT_H

#include <iostream>
#include "WorkUnit.h"

class Shot : public WorkUnit {
private:
    std::string name;
    int baseHours;

public:
    Shot(const std::string& name, int baseHours)
        : name(name), baseHours(baseHours) {}

    ~Shot() {}

    std::string getName() const override {
        return name;
    }

    int getEstimatedHours() const override {
        return baseHours;
    }

    void process() override {
        std::cout << "Filming shot: " << name << " (" << baseHours << "h)\n";
    }
};

#endif
