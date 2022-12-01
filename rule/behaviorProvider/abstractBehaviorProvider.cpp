#include "rule/behaviorProvider/abstractBehaviorProvider.h"

void AbstractBehaviorProvider::handleDirection(Rule &rule){
    
    vector <direction_code> listDir = getListDir();

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