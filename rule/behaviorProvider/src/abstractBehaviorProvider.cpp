#include "abstractBehaviorProvider.h"
#include "chariotBehaviorProvider.h"
#include "cannonBehaviorProvider.h"
#include "soldierBehaviorProvider.h"
#include "defaultBehaviorProvider.h"
#include "advisorBehaviorProvider.h"
#include "elephantBehaviorProvider.h"
#include "generalBehaviorProvider.h"
#include "horseBehaviorProvider.h"
#include <iostream>
#include "log.h"

void AbstractBehaviorProvider::handleDirection(Rule &rule){
    // std::cout << "Handle Direction===================" << std::endl;
    
    vector <direction_code> listDir = getListDir(rule);

    DirectionInterator *dirInterator = nullptr;
    handleBefore(rule);
    for (direction_code dir : listDir)
    {
        if ( dirInterator == nullptr)
            dirInterator = new DirectionInterator(rule.getTarget(), dir);
        else {
            dirInterator->changeDir(dir);
            // std::cout << "Change to a different direction " << dir << std::endl;
        }

        while (dirInterator->hasNext())
        {
            Point *point = dirInterator->getNext();
            // std::cout << "Handle the point (" << *point;
            if (predicate(point, rule))
            {
                // std::cout << "[True]" << std::endl;
                handleTrue(point, rule);
            }
            else
            {
                // std::cout << "[False]" << std::endl;
                handleFalse(point, rule);
                break;
            }
        }
        // std::cout << "There is no more point" << std::endl;
    }
    handleAfter(rule);
    delete dirInterator;

}

AbstractBehaviorProvider* AbstractBehaviorProvider::newInstance(chessman_code code) {
    switch (code){
        case CHARIOT:
            return new ChariotBehaviorProvider();
        case SOLDIER:
            return new SoldierBehaviorProvider();
        case CANNON:
            return new CannonBehaviorProvider();
        case ADVISOR:
            return new AdvisorBehaviorProvider();
        case ELEPHANT:
            return new ElephantBehaviorProvider();
        case GENERAL:
            return new GeneralBehaviorProvider();
        case HORSE:
            return new HorseBehaviorProvider();
        default:
            return new DefaultBehaviorProvider();       
    }
}