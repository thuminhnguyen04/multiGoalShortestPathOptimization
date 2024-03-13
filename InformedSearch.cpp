#include "InformedSearch.h"

unsigned int InformedSearch::calculateManhanttanDist(Coordinate aX, Coordinate aY)
{
	return abs(aY.x - aX.x) + abs(aY.y - aX.y);
}

InformedSearch::InformedSearch(string fp) : SearchBase(fp) {
}

InformedSearch::InformedSearch(SearchBase& aSearchOther, Coordinate aCoordinate) : SearchBase(aSearchOther, aCoordinate) {
}

bool InformedSearch::isGoal(Coordinate currGoal)
{
	return (currGoal == this->robotCurrent);
}
