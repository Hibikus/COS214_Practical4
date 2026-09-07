#include "DepthFirstIterator.h"
#include "WorkUnit.h"

DepthFirstIterator::DepthFirstIterator(WorkUnit* root) :pos(0){
    collect(root);
}

void DepthFirstIterator::collect(WorkUnit* node) {
    if (!node) {
        return;
    }
    snapshot.push_back(node);              
    for (WorkUnit* child : node->getChildren()) {
        collect(child);                   
    }
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