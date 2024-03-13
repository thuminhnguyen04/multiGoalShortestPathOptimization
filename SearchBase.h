#pragma once

#include "Header.h"

class SearchBase
{
protected:
	int cStep = 0;

	Coordinate robotCurrent; //current Coordinate
	unsigned int row = 0, col = 0, cNode = 0;
	Coordinate startGrid;
	vector<Wall> wallArr;
	vector<Coordinate> goalArr;

	vector <vector<Direction>> direction;
	vector <vector<Coordinate>> path;
	vector <vector<int>> visited;

	bool fFlag;
	//vector <vector<int>> visited;


public:
	~SearchBase();
	SearchBase(string fp);
	SearchBase(SearchBase&, Coordinate);

	virtual bool search() = 0;
	void goUp();
	void goDown();
	void goLeft();
	void goRight();
	bool isWall() noexcept;
	bool isWallAt(int x, int y) noexcept;

	//virtual bool isDone() = 0;
	void displayResult(bool aFlag = true);
	void displayResult(vector<Coordinate> goalArr, vector<bool>& visitedGoal);

	Coordinate getRobot();
	void incrementCounter();
	void makeAMove(Direction direction); // go in specified direction
	//void makeAReversedMove(Direction direction); // go in specified direction
	void updatePath(Direction d);
	void resetSearch();
	unsigned int getNumberOfNodes();
	int getStep();
	Direction getDirection(Coordinate);
	Coordinate getPath(Coordinate);
	void initialiseVector();
	bool isDone();
	bool isValid();
	bool isValidAt(int x, int y);

	void resetGoal(Coordinate);
	void makeVisited();
	bool isVisited();
	bool makeAValidMove(Direction direction, Coordinate parent);
	string getDirectionString(Direction);
	void setRobot(Coordinate aX);
	void setNode(int aX);
	bool isVisitedAt(int aX, int aY);

};
