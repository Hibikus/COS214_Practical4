#ifndef READYSHOTITERATOR_H
#define READYSHOTITERATOR_H

#include <vector>
#include <cstddef>

#include "WorkUnitIterator.h"

class ReadyShotIterator: public WorkUnitIterator {
    private:
        std::vector<WorkUnit*> matches;
        std::size_t pos;

        bool isReady(WorkUnit* node); //is scheduled? helper
        void collect(WorkUnit* node); //recursive helper
    public:
        ReadyShotIterator(WorkUnit* root);
        void first() override;
        bool hasNext() override;
        WorkUnit* next() override;
};

#endif