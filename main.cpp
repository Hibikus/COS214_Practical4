#include <iostream>
#include "ProductionManager.h"
#include "WorkGroup.h"
#include "WorkUnitIterator.h"
#include "Shot.h"

//  This walks through one coherent scenario rather than a menu of isolated pattern demos:
//   1. Build the production hierarchy (Composite).
//   2. Move shots through their lifecycle (State).
//   3. Pull two different views of the same structure (Iterator).
//   4. Show a decorated shot participating in normal behaviour (Decorator).
//   5. Make a runtime structural change and show its effect.

static void printDivider(const std::string& title) {
    std::cout << "\n========== " << title << " ==========\n";
}

int main() {
    ProductionManager pm;

    printDivider("1. Building the production");
    pm.buildProduction();
    
    // Main Production -> Sequence 1 -> Scene 1 -> { Shot 1A [VFX][Sound], Shot 1B }
    std::cout << "Production built: Main Production / Sequence 1 / Scene 1 "
                 "/ Shot 1A (VFX+Sound), Shot 1B\n";

    WorkGroup* root = pm.getRoot();

    // Locate the groups/shots we need for this scripted walkthrough by walking the structure once 
    WorkGroup* seq1 = nullptr;
    WorkGroup* scene1 = nullptr;
    Shot* shot1B = nullptr;
    WorkUnit* shot1AUnit = nullptr; // may be wrapped in decorators

    WorkUnitIterator* finder = root->createIterator(IteratorType::DepthFirst);
    for (finder->first(); finder->hasNext();) {
        WorkUnit* unit = finder->next();
        if (unit->getName() == "Sequence 1") {
            seq1 = dynamic_cast<WorkGroup*>(unit);
        } else if (unit->getName() == "Scene 1") {
            scene1 = dynamic_cast<WorkGroup*>(unit);
        } else if (unit->getName() == "Shot 1B") {
            shot1B = dynamic_cast<Shot*>(unit);
        } else if (unit->getName().rfind("Shot 1A", 0) == 0) {
            shot1AUnit = unit;
        }
    }
    delete finder;

    printDivider("2. Lifecycle (State)");
    std::cout << "-- Shot 1B starts as: " << shot1B->getStateName() << "\n";
    shot1B->schedule();
    std::cout << "-- After schedule(): " << shot1B->getStateName() << "\n";
    shot1B->startFilming();
    std::cout << "-- After startFilming(): " << shot1B->getStateName() << "\n";

    // Deliberately invalid transition: can't approve a shot that's still filming.
    std::cout << "-- Attempting an invalid transition (approve while filming):\n";
    shot1B->approve();
    std::cout << "-- Shot 1B state is still: " << shot1B->getStateName() << "\n";

    shot1B->submitForReview();
    shot1B->approve();
    std::cout << "-- Final Shot 1B state: " << shot1B->getStateName() << "\n";

    // Shot 1A only needs to be scheduled for this scenario, to show up on the call sheet below - even though it's wrapped in decorators,
    // getStateName() delegates through to the real Shot underneath.
    shot1AUnit->schedule();
    std::cout << "-- " << shot1AUnit->getName() << " scheduled -> state: "
              << shot1AUnit->getStateName() << "\n";

    printDivider("3. Two independent traversals (Iterator)");
    std::cout << "-- Full breakdown (DepthFirstIterator):\n";
    pm.runFullBreakdown();

    std::cout << "\n-- Daily call sheet (ReadyShotIterator) - only scheduled shots:\n";
    pm.runDailyCallSheet();

    printDivider("4. Decorated shot in normal behaviour");
    std::cout << "-- Processing " << shot1AUnit->getName()
              << " (" << shot1AUnit->getEstimatedHours() << "h total):\n";
    shot1AUnit->process();

    printDivider("5. Runtime change: moving a shot between groups");
    WorkGroup* newScene = new WorkGroup("Scene 2 (reshoot pickup)");
    seq1->add(newScene);

    std::cout << "-- Moving Shot 1B from Scene 1 into new Scene 2\n";
    pm.moveShot(shot1B, scene1, newScene);

    std::cout << "\n-- Full breakdown after the move:\n";
    pm.runFullBreakdown();

    printDivider("Done");
    return 0;
}
