#pragma once
#include "UninformedSearch.h"

class BFS : public UninformedSearch
{private:
	queue<Coordinate> fQueue;

public:
	BFS(string fp);
	BFS(SearchBase&, Coordinate);

	~BFS();
	Coordinate getIntersaction(UninformedSearch* aOtherSearch);

	bool search();
	bool search(bool);
	void displayPathTo(Coordinate aGoal, vector<Coordinate> goalArr, vector<bool>& visitedGoal);
	bool expand(queue<Coordinate> &myQueue);
	int getLen(Coordinate aC);
};
