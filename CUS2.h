#pragma once
#include "InformedSearch.h"

#define  MAX_INT 1e9
class CUS2 : public InformedSearch
{
private:
	
public:
	//Coordinate currentGoal;
	CUS2(string fp);
	~CUS2();

	int DFS(Coordinate, int, int, vector<Direction>&, vector<Coordinate>&);
	bool search();
	unsigned int computeHeuristicValue();

};

