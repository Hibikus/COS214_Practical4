#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

#include "ProductionManager.h"
#include "WorkGroup.h"
#include "WorkUnitIterator.h"
#include "Shot.h"
#include "VFXDecorator.h"
#include "ColorGradeDecorator.h"
#include "SoundMixDecorator.h"

struct Entry {
    WorkUnit* unit;
    WorkGroup* group;   // set only if unit->isGroup()
};

static std::vector<Entry> listAll(WorkGroup* root) {
    std::vector<Entry> entries;
    WorkUnitIterator* it = root->createIterator(IteratorType::DepthFirst);
    for (it->first(); it->hasNext();) {
        WorkUnit* unit = it->next();
        Entry e;
        e.unit = unit;
        e.group = unit->isGroup() ? dynamic_cast<WorkGroup*>(unit) : nullptr;
        entries.push_back(e);
    }
    delete it;
    return entries;
}

static void printAll(const std::vector<Entry>& entries) {
    for (std::size_t i = 0; i < entries.size(); ++i) {
        const Entry& e = entries[i];
        std::cout << "  [" << i << "] "
                  << (e.group ? "(group) " : "(shot)  ")
                  << e.unit->getName();
        if (!e.group) {
            std::cout << " - state: " << e.unit->getStateName();
        }
        std::cout << " - " << e.unit->getEstimatedHours() << "h\n";
    }
}

static int readInt(const std::string& prompt, int min, int max) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        int value;
        if (iss >> value && value >= min && value <= max) {
            return value;
        }
        std::cout << "Please enter a number between " << min << " and " << max << ".\n";
    }
}

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

static void doFullBreakdown(ProductionManager& pm) {
    pm.runFullBreakdown();
}

static void doCallSheet(ProductionManager& pm) {
    pm.runDailyCallSheet();
}

static void doListAll(WorkGroup* root) {
    std::vector<Entry> entries = listAll(root);
    std::cout << "\nAll units in the hierarchy:\n";
    printAll(entries);
}

static void doAddShot(WorkGroup* root) {
    std::vector<Entry> entries = listAll(root);
    std::vector<Entry> groups;
    for (const Entry& e : entries) {
        if (e.group) groups.push_back(e);
    }
    if (groups.empty()) {
        std::cout << "No groups available.\n";
        return;
    }
    std::cout << "\nChoose a group to add the shot to:\n";
    printAll(groups);
    int idx = readInt("Group #: ", 0, (int)groups.size() - 1);

    std::string name = readLine("New shot name: ");
    int hours = readInt("Estimated hours: ", 0, 100000);

    groups[idx].group->add(new Shot(name, hours));
    std::cout << "Added '" << name << "' to '" << groups[idx].unit->getName() << "'.\n";
}

static void doAddGroup(WorkGroup* root) {
    std::vector<Entry> entries = listAll(root);
    std::vector<Entry> groups;
    for (const Entry& e : entries) {
        if (e.group) groups.push_back(e);
    }
    std::cout << "\nChoose a parent group:\n";
    printAll(groups);
    int idx = readInt("Group #: ", 0, (int)groups.size() - 1);
    std::string name = readLine("New group name: ");
    groups[idx].group->add(new WorkGroup(name));
    std::cout << "Added group '" << name << "' under '" << groups[idx].unit->getName() << "'.\n";
}

static void doMoveShot(WorkGroup* root) {
    std::vector<Entry> entries = listAll(root);
    std::vector<Entry> shots, groups;
    for (const Entry& e : entries) {
        if (e.group) groups.push_back(e); else shots.push_back(e);
    }
    if (shots.empty() || groups.size() < 2) {
        std::cout << "Need at least one shot and two groups to move between.\n";
        return;
    }

    std::cout << "\nWhich unit to move?\n";
    printAll(shots);
    int unitIdx = readInt("Unit #: ", 0, (int)shots.size() - 1);
    WorkUnit* toMove = shots[unitIdx].unit;

    std::cout << "\nWhich group is it currently in?\n";
    printAll(groups);
    int fromIdx = readInt("From group #: ", 0, (int)groups.size() - 1);

    std::cout << "\nWhich group should it move to?\n";
    printAll(groups);
    int toIdx = readInt("To group #: ", 0, (int)groups.size() - 1);

    groups[fromIdx].group->remove(toMove);
    groups[toIdx].group->add(toMove);
    std::cout << "Moved '" << toMove->getName() << "' from '"
              << groups[fromIdx].unit->getName() << "' to '"
              << groups[toIdx].unit->getName() << "'.\n";
}

static void doTransition(WorkGroup* root) {
    std::vector<Entry> entries = listAll(root);
    std::vector<Entry> shots;
    for (const Entry& e : entries) {
        if (!e.group) shots.push_back(e);
    }
    if (shots.empty()) {
        std::cout << "No shots available.\n";
        return;
    }
    std::cout << "\nWhich shot?\n";
    printAll(shots);
    int idx = readInt("Shot #: ", 0, (int)shots.size() - 1);
    WorkUnit* shot = shots[idx].unit;

    std::cout << "Current state: " << shot->getStateName() << "\n";
    std::cout << "  [0] schedule\n  [1] startFilming\n  [2] submitForReview\n"
                 "  [3] approve\n  [4] requestReshoot\n";
    int action = readInt("Action #: ", 0, 4);
    switch (action) {
        case 0: shot->schedule(); break;
        case 1: shot->startFilming(); break;
        case 2: shot->submitForReview(); break;
        case 3: shot->approve(); break;
        case 4: shot->requestReshoot(); break;
    }
    std::cout << "New state: " << shot->getStateName() << "\n";
}

static void doDecorate(WorkGroup* root) {
    std::vector<Entry> entries = listAll(root);
    std::vector<Entry> shots;
    for (const Entry& e : entries) {
        if (!e.group) shots.push_back(e);
    }
    if (shots.empty()) {
        std::cout << "No shots available.\n";
        return;
    }
    std::cout << "\nWhich shot to decorate?\n";
    printAll(shots);
    int idx = readInt("Shot #: ", 0, (int)shots.size() - 1);
    WorkUnit* target = shots[idx].unit;

    // We need the shot's current parent group to swap the raw pointer
    // for the decorated one, so ask the user (same reasoning as move).
    std::vector<Entry> groups;
    for (const Entry& e : entries) {
        if (e.group) groups.push_back(e);
    }
    std::cout << "\nWhich group currently holds it?\n";
    printAll(groups);
    int gIdx = readInt("Group #: ", 0, (int)groups.size() - 1);

    std::cout << "  [0] VFX\n  [1] Colour grade\n  [2] Sound mix\n";
    int choice = readInt("Decorator #: ", 0, 2);

    WorkUnit* decorated = nullptr;
    if (choice == 0) {
        int h = readInt("VFX hours: ", 0, 100000);
        decorated = new VFXDecorator(target, h);
    } else if (choice == 1) {
        int h = readInt("Grade hours: ", 0, 100000);
        std::string look = readLine("Look/LUT name: ");
        decorated = new ColorGradeDecorator(target, h, look);
    } else {
        int h = readInt("Mix hours: ", 0, 100000);
        int stems = readInt("Stem count: ", 0, 1000);
        decorated = new SoundMixDecorator(target, h, stems);
    }

    groups[gIdx].group->remove(target);
    groups[gIdx].group->add(decorated);
    std::cout << "'" << decorated->getName() << "' now in the hierarchy "
              << "(" << decorated->getEstimatedHours() << "h total).\n";
}

static void printMenu() {
    std::cout << "\n===================== TaskForge =====================\n"
                 " 1) Full breakdown (DepthFirstIterator)\n"
                 " 2) Daily call sheet (ReadyShotIterator)\n"
                 " 3) List all units\n"
                 " 4) Add a shot to a group\n"
                 " 5) Add a group\n"
                 " 6) Move a shot between groups\n"
                 " 7) Change a shot's lifecycle state\n"
                 " 8) Decorate a shot (stackable)\n"
                 " 9) Rebuild production from scratch\n"
                 " 0) Exit\n"
                 "======================================================\n";
}

int main() {
    ProductionManager pm;
    pm.buildProduction();
    std::cout << "TaskForge interactive console. Starting production built.\n";

    bool running = true;
    while (running) {
        printMenu();
        int choice = readInt("Choose an option: ", 0, 9);
        WorkGroup* root = pm.getRoot();

        switch (choice) {
            case 1: doFullBreakdown(pm); break;
            case 2: doCallSheet(pm); break;
            case 3: doListAll(root); break;
            case 4: doAddShot(root); break;
            case 5: doAddGroup(root); break;
            case 6: doMoveShot(root); break;
            case 7: doTransition(root); break;
            case 8: doDecorate(root); break;
            case 9:
                pm.buildProduction();
                std::cout << "Production rebuilt.\n";
                break;
            case 0: running = false; break;
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}
