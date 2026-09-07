#include "ReadyShotIterator.h"
#include "WorkUnit.h"

ReadyShotIterator::ReadyShotIterator(WorkUnit* root) : pos(0){
    collect(root);
}

bool ReadyShotIterator::isReady(WorkUnit* node) {
    // getStateName() is "" for anything that isn't a Shot (or a decorated
    // Shot), so this naturally excludes groups without needing a cast.
    return node->getStateName() == "Scheduled";
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