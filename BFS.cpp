#include "BFS.h"


BFS::BFS(string fp) : UninformedSearch(fp){}

BFS::BFS(SearchBase& aSearchOther, Coordinate aCoordinate) : UninformedSearch(aSearchOther, aCoordinate){}


BFS::~BFS()
{}

bool BFS::search()
{
	if (!isValid()) {
		throw exception("Invalid input");
	}

	makeVisited();
	queue<Coordinate> myQueue;
	myQueue.push(this->robotCurrent);
	incrementCounter();
	while (myQueue.size() != 0)
	{
		if (expand(myQueue)) return true;
	}
	return false;
}

bool BFS::expand(queue<Coordinate>& myQueue)
{
	const Coordinate parent = myQueue.front();
	robotCurrent = parent;
	if (isDone()) return true;
	myQueue.pop();

	for (int i = 0; i < 4; i++)
	{
		if (makeAValidMove(((Direction)i), parent) && !isVisited()) // Try each direction
		{
			// the position has changed already at this point
			makeVisited(); //mark as visited for that position
			myQueue.push(this->robotCurrent); //push that position to queue
			incrementCounter();
			updatePath((Direction)i);
			path[robotCurrent.x][robotCurrent.y] = parent;
		}
	}
	return false;
}

bool BFS::search(bool aFlag)
{
	if (!isVisited())
	{
		fQueue.push(this->robotCurrent);
		incrementCounter();
	}

	while (fQueue.size() != 0)
	{
		const Coordinate parent = fQueue.front();
		fQueue.pop();
		robotCurrent = parent;
		makeVisited();
		for (int i = 0; i < 4; i++)
		{
			if (makeAValidMove(((Direction)i), parent) && !isVisited()) // Try each direction
			{
				fQueue.push(this->robotCurrent); 
				incrementCounter();
				path[robotCurrent.x][robotCurrent.y] = parent;
			}
		}
		robotCurrent = parent;
		if (isDone()) return true;

	}
	return false;
}


int BFS::getLen(Coordinate aC)
{
	resetGoal(aC);
	if (!isVisitedAt(aC.x, aC.y))
		if (!(*this).search(true))
			return -1;

	Coordinate tmp = aC;
	int c = 0;
	while (!(tmp == startGrid))
	{
		tmp = getPath(tmp);
		c++;
	}
	return c;
}
void BFS::displayPathTo(Coordinate aGoal, vector<Coordinate> goalArr, vector<bool>& visitedGoal)
{
	resetGoal(aGoal);
	(*this).search();
	displayResult(goalArr, visitedGoal);
	cout << endl;
}
Coordinate BFS::getIntersaction(UninformedSearch* aOtherSearch)
{
	for (size_t i = 0; i < col; i++)
	{
		for (size_t j = 0; j < row; j++)
		{
			if (aOtherSearch->isVisitedAt(i, j) == isVisitedAt(i, j) && isVisitedAt(i, j))
				return Coordinate(i, j);
		}
	}
	return Coordinate(-1, -1);
}