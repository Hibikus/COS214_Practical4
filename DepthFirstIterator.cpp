#include "DepthFirstIterator.h"

DepthFirstIterator::DepthFirstIterator(WorkUnit* root) :pos(0){

}

void DepthFirstIterator::first() {
    pos = 0;
}

bool DepthFirstIterator::hasNext(){
    return pos<snapshot.size();
}

WorkUnit* DepthFirstIterator::next(){
    if (!hasNext()){
        return nullptr;
    }
    return snapshot[pos++];
}