#include "ReadyShotIterator.h"
#include "WorkUnit.h"
#include "Shot.h"

ReadyShotIterator::ReadyShotIterator(WorkUnit* root) : pos(0){
    collect(root);
}

bool ReadyShotIterator::isReady(WorkUnit* node) {
    if (Shot* shot = dynamic_cast<Shot*>(node)) {
        return shot->getStateName() == "Scheduled";
    }
    return false;
}

void ReadyShotIterator::collect(WorkUnit* node) {
    if (!node) {
        return;
    }
    if (isReady(node)) {
        matches.push_back(node);
    }
    for (WorkUnit* child : node->getChildren()) {
        collect(child);
    }
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