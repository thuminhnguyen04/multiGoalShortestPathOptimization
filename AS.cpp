#include "AS.h"


AS::AS(string fp) : InformedSearch(fp) {}

AS::AS(SearchBase& aSearchOther, Coordinate aCoordinate) : InformedSearch(aSearchOther, aCoordinate) {}

AS::~AS()
{}

bool AS::search()
{
    // If the source is out of range
    if (!isValid()) {
        throw exception("Invalid input");
    }

    // If the destination cell is the same as source cell
    if (isDone())
    {
        cout << "Start cell is also the goal cell" << endl;
        return true;
    }

    vector <vector<int>> fCost;
    for (size_t i = 0; i < col; i++)
    {
        fCost.push_back({});
        for (size_t j = 0; j < row; j++)
        {
            fCost[i].push_back(-1);
        }
    }
    priority_queue<Cell, vector<Cell>, compareCost> openList;

    openList.push(Cell(robotCurrent, 0, computeHeuristicValue()));
    fCost[robotCurrent.x][robotCurrent.y] = openList.top().fcost;

    incrementCounter();

    while (!openList.empty()) {
        const Cell parent = openList.top();
        openList.pop();

        robotCurrent = parent;

        if (isDone())
        {
            return true;
        }
        
        for (int i = 0; i < 4; i++)// Try each direction
        {
            if (makeAValidMove(((Direction)i), parent)) //MISSING VISITED CHECK FOR CLOSE LIST
            {

                //if (isVisited()) // check close list
                  //  continue;

                Cell currCell(robotCurrent, parent.gcost + 1, computeHeuristicValue());

                if (fCost[robotCurrent.x][robotCurrent.y] == -1 // not in open list
                    || currCell.fcost < fCost[robotCurrent.x][robotCurrent.y])
                {
                    fCost[robotCurrent.x][robotCurrent.y] = currCell.fcost;
                    openList.push(currCell);//better remove the old one from this list
                    incrementCounter();
                    updatePath((Direction)i);
                    path[robotCurrent.x][robotCurrent.y] = parent;
                }

                
            }
        }
    }
    return false;

}

unsigned int AS::computeHeuristicValue()
{
    if (goalArr.size() == 0)
        throw exception("Error for goal input in AS");
    unsigned int lResult = calculateManhanttanDist(robotCurrent, goalArr[0]);
    for (size_t i = 1; i < goalArr.size(); i++)
    {
        lResult = min(lResult, calculateManhanttanDist(robotCurrent, goalArr[i]));
    }
    return lResult;
}
