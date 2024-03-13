#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <chrono>
#include <stdexcept>
#include <sstream>
#include <queue>

using namespace std;
struct Coordinate {
	int x, y;

	bool operator==(const Coordinate other)
	{
		if (x == other.x && y == other.y)
			return true;
		return false;
	}
	Coordinate()
	{
		x = -1;
		y = -1;
	}
	Coordinate(int aX, int aY)
	{
		x = aX;
		y = aY;
	}
};


struct Wall {
	Coordinate minCoor;
	unsigned int row, col;

	Wall()
	{
		minCoor = Coordinate(-1, -1);
		row = 0;
		col = 0;
	}
	Wall(int x, int y)
	{
		row = 1;
		col = 1;
		minCoor = Coordinate(x, y);
	}
};
enum Direction {
	up, left, down, right, invalid
};


struct Cell:Coordinate {
	unsigned int fcost = 0;
	unsigned int gcost = 0;
	vector<bool> unvistedGoals;

	void settrue(int i)
	{
		unvistedGoals[i] = true;
	}
	Cell()
	{};
	Cell(Coordinate aX, Coordinate aY)
	{
		x = aX.x;
		y = aX.y;

		fcost = abs(aY.x - aX.x) + abs(aY.y - aX.y);

		//fcost = calculateManhanttanDist(aX,aY);
	}
	Cell(Coordinate aX, Coordinate aY, int aCost) :Cell(aX, aY)
	{
		gcost = aCost;
		fcost += gcost;
	}
	Cell(Coordinate aX, int aCost, int hCost)
	{
		x = aX.x;
		y = aX.y;
		gcost = aCost;
		fcost = gcost + hCost;
	}
	Cell(Coordinate aX, int hCost)
	{
		x = aX.x;
		y = aX.y;
		fcost = hCost;
	}
};

struct compareCost {
	bool operator()(Cell const& p1, Cell const& p2)
	{
		// return "true" if "p1" is ordered
		// before "p2", for example:
		if (p1.fcost != p2.fcost)
			return (p1.fcost > p2.fcost);
		return (p1.fcost - p1.gcost > p2.fcost - p2.gcost); // return p1.hcost > p2.hcost
		
	}
	
};
/*namespace std {
	/*implement hash function so we can put GridLocation into an unordered_set 
	template <> struct hash<Cell> {
		std::size_t operator()(const Cell& cell) const noexcept {
			// NOTE: better to use something like boost hash_combine
			return std::hash<int>()(cell.cellPos.y * gRow + cell.cellPos.x);
		}
	};
}


struct NodeHash {
	size_t operator()(const Cell& node) const {
		return std::hash<int>()(node.id);
	}
};*/

