#ifndef WORKUNITITERATOR_H
#define WORKUNITITERATOR_H

class WorkUnit;

class WorkUnitIterator {
    public:
        virtual ~WorkUnitIterator() = default;
        virtual void first() = 0;
        virtual bool hasNext() = 0;
        virtual WorkUnit* next() = 0;
};

#endif