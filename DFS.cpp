#include "DFS.h"

DFS::DFS(string fp) : UninformedSearch(fp) {}

DFS::~DFS()
{}

bool DFS::search()
{
	if (!isValid()) {
		throw exception("Invalid input");
	}
	incrementCounter();
	return expand();
}
bool DFS::expand()
{
	makeVisited();
	const Coordinate parent = this->robotCurrent;
	for (int i = 0; i < 4; i++)
	{
		if (makeAValidMove(((Direction)i), parent) && !isVisited()) // Try each direction
		{
			// the position has changed already at this point
			updatePath((Direction)i);
			path[robotCurrent.x][robotCurrent.y] = parent;
			
			incrementCounter();

			if (isDone())
				return true;

			if (expand())
				return true;
		}
	
	}
	return false;
}

