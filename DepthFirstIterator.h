#ifndef DEPTHFIRSTITERATOR_H
#define DEPTHFIRSTITERATOR_H

#include <vector>
#include <cstddef>

#include "WorkUnitIterator.h"

class DepthFirstIterator : public WorkUnitIterator {
    private:
        std::vector<WorkUnit*> snapshot;
        std::size_t pos;

        void collect(WorkUnit* node); //recursive helper
    public:
        DepthFirstIterator(WorkUnit*root);
        void first() override;
        bool hasNext() override;
        WorkUnit* next() override;
};

#endif