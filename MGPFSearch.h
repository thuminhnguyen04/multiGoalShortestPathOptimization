#pragma once
#include "AS.h"
#include <utility>

class MGPFSearch : public SearchBase
{
private:
	//vector<Coordinate> unvistedGoals;
	vector<bool> visitedGoals;
	vector<int> gCostFromStart;

	vector<vector<int>> fGraph;
	int lResult = 0;
	int gcost_so_far = 0;
	bool isUpToDateDistance = false;
	//Coordinate tmpStart;
	pair <int, int> fCurrentMax;

	int** memo;
	//int n = 14;
	//int memo[14 + 1][1 << (14 + 1)];


public:
	MGPFSearch(string fp);

	//void displayResult();

	~MGPFSearch();
	MGPFSearch(SearchBase&, Coordinate);

	//bool isGoal(Cell&);
	bool isGoal();
	int fun(int,int);
	
	int computeHeuristicValue(int);
	pair<int,int> computeMapDistance(int);
	bool search();

	void setUpPermutation();
	bool executePermutation();
};