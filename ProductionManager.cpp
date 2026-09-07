#include "ProductionManager.h"
#include "WorkGroup.h"
#include "Shot.h"
#include "VFXDecorator.h"
#include "SoundMixDecorator.h"
#include "WorkUnitIterator.h"
#include "ReadyShotIterator.h"
#include "DepthFirstIterator.h"


ProductionManager::ProductionManager() : root(nullptr) {}

ProductionManager::~ProductionManager() {
    delete root; 
}

void ProductionManager::buildProduction() {
    if (root) {
        delete root; // guard against leaking a previous build
    }

    root = new WorkGroup("Main Production");

    WorkGroup* seq1 = new WorkGroup("Sequence 1");
    WorkGroup* scene1 = new WorkGroup("Scene 1");

    Shot* shotA = new Shot("Shot 1A", 8);
    Shot* shotB = new Shot("Shot 1B", 6);

    WorkUnit* decoratedShotA = new SoundMixDecorator(new VFXDecorator(shotA, 10), 5, 8);

    scene1->add(decoratedShotA);
    scene1->add(shotB);
    seq1->add(scene1);
    root->add(seq1);
}

WorkGroup* ProductionManager::getRoot() const {
    return root;
}

void ProductionManager::runDailyCallSheet() {
    if (!root){
        return;
    }

    std::cout << "Daily Call Sheet:" << std::endl;

    WorkUnitIterator* it = new ReadyShotIterator(root);

    for (it->first(); it->hasNext();) {
        WorkUnit* unit = it->next();
        if (unit) {
            std::cout << "Processing: " << unit->getName() << std::endl;
            unit->process();
        }
    }

    delete it;
}

void ProductionManager::runFullBreakdown() {
    if (!root) {
        return;
    }

    std::cout << "Full Production Breakdown" << std::endl;
  
    WorkUnitIterator* it = new DepthFirstIterator(root);

    for (it->first(); it->hasNext();) {
        WorkUnit* unit = it->next();
        if (unit) {
            std::cout << "Unit: " << unit->getName() << " | Total Hours: " << unit->getEstimatedHours() << std::endl;
        }
    }

    delete it; 
}

void ProductionManager::moveShot(WorkUnit* shot, WorkGroup* from, WorkGroup* to) {
    if (!shot || !from || !to){
        return;
    }

    from->remove(shot);
    to->add(shot);

    std::cout << "Successfully moved '" << shot->getName() << "' from '" << from->getName() << "' to '" << to->getName() << "'" << std::endl;
}