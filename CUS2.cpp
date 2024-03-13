#include "CUS2.h"


CUS2::CUS2(string fp) : InformedSearch(fp) {
	fFlag = false;
}


CUS2::~CUS2()
{}
int CUS2::DFS(Coordinate parent, int b, int threshold, vector<Direction>& lDirection, vector<Coordinate>& lPath)
{
	if (this->isDone())
		return -1;

	int cost = b + computeHeuristicValue();
	if (cost > threshold)
		return cost;
	
	int min = MAX_INT;

	for (int i = 0; i < 4; i++)
	{
		if (makeAValidMove(((Direction)i), parent)) // Try each direction
		{
			if (find(lPath.begin(), lPath.end(), robotCurrent) != lPath.end())
				continue;
			lPath.push_back(robotCurrent);
			lDirection.push_back((Direction)i);
			// the position has changed already at this point
			
			incrementCounter();
			//cout << "Set parent of " << robotCurrent.x << ", " << robotCurrent.y << ": " << parent.x << "," << parent.y << endl;
			int tmp = DFS(robotCurrent, b + 1, threshold, lDirection, lPath);
			if (tmp == -1)
				return -1;
			min = std::min(min, tmp);

			lPath.pop_back();
			lDirection.pop_back();
		}
	}
	return min;

}
bool CUS2::search()
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

	vector <Direction> lDirection;
	vector <Coordinate> lPath;
	lPath.push_back(robotCurrent);
	int threshold = computeHeuristicValue();

	while (true)
	{
		threshold = this->DFS(startGrid, 0, threshold, lDirection, lPath);

		if (threshold == -1)
		{
			cout << cNode << endl;
			if (lDirection.size() < 1)
			{
				if (lDirection[0] == 0)
					lDirection[0] = Direction(2);
				else if (lDirection[0] == 2)
					lDirection[0] = Direction(0);
				else lDirection[0] = Direction(abs(int(lDirection[0]) - 4));
			}
			int i = 0;
			while (i< lDirection.size())
			{
				cout << getDirectionString(lDirection[i++]) << " ";
			}
			return true;
		}
			
		
		if (threshold >= MAX_INT)
			return false;
	}
	
	return false;

}
unsigned int CUS2::computeHeuristicValue()
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
