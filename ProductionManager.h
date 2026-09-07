#ifndef PRODUCTIONMANAGER_H
#define PRODUCTIONMANAGER_H

#include <iostream>

class WorkGroup;
class WorkUnit;

class ProductionManager {
    private:
        WorkGroup* root;
    public:
        ProductionManager();
        ~ProductionManager();
        void buildProduction();
        void runDailyCallSheet();
        void runFullBreakdown();
        void moveShot(WorkUnit* shot, WorkGroup* from, WorkGroup* to);
};

#endif