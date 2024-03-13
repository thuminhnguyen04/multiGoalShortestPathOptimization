#pragma once
#include "InformedSearch.h"



class GBFS : public InformedSearch
{

public:
	GBFS(string fp);
	~GBFS();
	GBFS(SearchBase&, Coordinate);

	bool expand(priority_queue<Cell, vector<Cell>, compareCost>& openList, Coordinate myGoal, vector<Coordinate>& closeList);
	bool search();
	unsigned int computeHeuristicValue();

};
