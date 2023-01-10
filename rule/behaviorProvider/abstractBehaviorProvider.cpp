#include "rule/behaviorProvider/abstractBehaviorProvider.h"
#include <iostream>
void AbstractBehaviorProvider::handleDirection(Rule &rule){
    vector <direction_code> listDir = getListDir(rule);
    std::cout << "Start handleDirection " << std::endl;

    DirectionInterator *dirInterator = nullptr;
    for (direction_code dir : listDir)
    {
        if ( dirInterator == nullptr)
            dirInterator = new DirectionInterator(rule.getTarget(), dir);
        else
            dirInterator->changeDir(dir);
        
        while (dirInterator->hasNext())
        {
            Point *point = dirInterator->getNext();
            
            if (predicate(point, rule))
            {
                handleTrue(point, rule);
            }
            else
            {
                handleFalse(point, rule);
                break;
            }
        }
    }
    delete dirInterator;

}