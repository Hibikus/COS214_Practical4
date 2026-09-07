#include "ReadyShotIterator.h"

ReadyShotIterator::ReadyShotIterator(WorkUnit* root) : pos(0){

}

void ReadyShotIterator::first(){
    pos = 0;
}

bool ReadyShotIterator::hasNext(){
    return pos < matches.size();
}

WorkUnit* ReadyShotIterator::next() {
    if (!hasNext()){
        return nullptr;
    }
    return matches[pos++];
}