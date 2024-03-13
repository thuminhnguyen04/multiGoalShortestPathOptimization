#pragma once
#include "SearchBase.h"
#include "BFS.h"

class InformedSearch : public SearchBase
{

public:

	InformedSearch(string fp);
	InformedSearch(SearchBase&, Coordinate);

	virtual bool search() = 0;
	bool isGoal(Coordinate currGoal);

	unsigned int calculateManhanttanDist(Coordinate aX, Coordinate aY);
	virtual unsigned int computeHeuristicValue() = 0;


};
