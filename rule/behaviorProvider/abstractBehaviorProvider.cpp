#include "rule/behaviorProvider/abstractBehaviorProvider.h"
#include <iostream>

void AbstractBehaviorProvider::handleDirection(Rule &rule){
    std::cout << "Handle Direction===================" << std::endl;
    
    vector <direction_code> listDir = getListDir(rule);

    DirectionInterator *dirInterator = nullptr;
    for (direction_code dir : listDir)
    {
        if ( dirInterator == nullptr)
            dirInterator = new DirectionInterator(rule.getTarget(), dir);
        else {
            dirInterator->changeDir(dir);
            std::cout << "Change to a different direction " << dir << std::endl;
        }

        while (dirInterator->hasNext())
        {
            Point *point = dirInterator->getNext();
            std::cout << "Handle the point (" << *point;
            if (predicate(point, rule))
            {
                std::cout << "[True]" << std::endl;
                handleTrue(point, rule);
            }
            else
            {
                std::cout << "[False]" << std::endl;
                handleFalse(point, rule);
                break;
            }
        }
        std::cout << "There is no more point" << std::endl;
    }
    delete dirInterator;

}