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

void AbstractBehaviorProvider::handleDirection(){
    // std::cout << "Handle Direction===================" << std::endl;
    
    vector <direction_code> listDir = getListDir();

    DirectionInterator *dirInterator = nullptr;
    handleBefore();
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
            if (predicate(point))
            {
                // std::cout << "[True]" << std::endl;
                handleTrue(point);
            }
            else
            {
                // std::cout << "[False]" << std::endl;
                handleFalse(point);
                break;
            }
        }
        // std::cout << "There is no more point" << std::endl;
    }
    handleAfter();
    delete dirInterator;

}

AbstractBehaviorProvider* AbstractBehaviorProvider::newInstance(Rule& rule, chessman_code code) {
    switch (code){
        case CHARIOT:
            return new ChariotBehaviorProvider(rule);
        case SOLDIER:
            return new SoldierBehaviorProvider(rule);
        case CANNON:
            return new CannonBehaviorProvider(rule);
        case ADVISOR:
            return new AdvisorBehaviorProvider(rule);
        case ELEPHANT:
            return new ElephantBehaviorProvider(rule);
        case GENERAL:
            return new GeneralBehaviorProvider(rule);
        case HORSE:
            return new HorseBehaviorProvider(rule);
        default:
            return new DefaultBehaviorProvider(rule);       
    }
}