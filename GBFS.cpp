#include "GBFS.h"


GBFS::GBFS(string fp) : InformedSearch(fp) {
}
GBFS::GBFS(SearchBase& aSearchOther, Coordinate aCoordinate) : InformedSearch(aSearchOther, aCoordinate) {
}


GBFS::~GBFS()
{}

unsigned int GBFS::computeHeuristicValue()
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

bool GBFS::search()
{
	if (!isValid()) {
		throw exception("Invalid input");
	}



	priority_queue<Cell, vector<Cell>, compareCost> openList;

	openList.push(Cell(startGrid, computeHeuristicValue()));

	incrementCounter(); //count  the expanded nodes

	robotCurrent = startGrid; //in case there is a goal that is impossible to make a visit --> for reset purpose

	// Add this vertex to the closed list
	makeVisited();

	while (!openList.empty()) {
		const Cell parent = openList.top();
		openList.pop();

		robotCurrent = parent;


		if (isDone()) //check is goal
			return true;
		for (int i = 0; i < 4; i++)// Try each direction
		{
			if (makeAValidMove(((Direction)i), parent)) //MISSING VISITED CHECK FOR CLOSE LIST
			{

				if (isVisited()) // check close list
					continue;

				makeVisited(); // put it in close list

				Cell currCell(robotCurrent, computeHeuristicValue());
				openList.push(currCell);//better remove the old one from this list

				incrementCounter(); //count number of expanded node

				updatePath((Direction)i);//save for backtracking
				path[robotCurrent.x][robotCurrent.y] = parent; //for backtracking

				
			}
		}

	}
	return false;
}
