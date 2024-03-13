#include "CUS1.h"


CUS1::CUS1(string fp) : BFS(fp) {
	fFlag = false;
}


CUS1::~CUS1()
{}
bool CUS1::search()
{
	if (!isValid()) {
		throw exception("Invalid input");
	}

	priority_queue<Cell, vector<Cell>, compareCost> myGoals;

	for (size_t i = 0; i < goalArr.size(); i++)
	{
		myGoals.push(Cell(this->goalArr[i], this->robotCurrent));
	}

	cNode = 0;
	queue<Coordinate> myQueueFromStart;
	BFS* BFSFromStart = (new BFS(*this, startGrid));

	robotCurrent = startGrid;

	BFSFromStart->makeVisited();


	for (size_t i = 0; i < goalArr.size(); i++)
	{

		Coordinate myGoal = myGoals.top();
		myGoals.pop();

		BFS* BFSFromGoal = (new BFS(*this, myGoal));

		BFSFromGoal->makeVisited();
		
		queue<Coordinate> myQueueFromDestination;

		myQueueFromDestination.push(BFSFromGoal->getRobot());	
			
		Coordinate intersaction(-1,-1);
		Coordinate invalidCrdn(-1, -1);
		static_cast<BFS*>(BFSFromStart)->resetGoal(myGoal);
		static_cast<BFS*>(BFSFromGoal)->resetGoal(startGrid);

		while (myQueueFromStart.size() != 0 || myQueueFromDestination.size() != 0)
		{
			if (myQueueFromStart.size() != 0)
				static_cast<BFS*>(BFSFromStart)->expand(myQueueFromStart);
			if (myQueueFromDestination.size() != 0)
				static_cast<BFS*>(BFSFromGoal)->expand(myQueueFromDestination);

			intersaction = static_cast<BFS*>(BFSFromStart)->getIntersaction(BFSFromGoal);
			if (!(intersaction == invalidCrdn))
				break;
		}
		if (intersaction == invalidCrdn)
			continue;
		
		cNode += BFSFromGoal->getNumberOfNodes() + BFSFromStart->getNumberOfNodes() + 2;

		BFSFromStart->setRobot(intersaction);
		BFSFromStart->setNode(cNode);
		BFSFromStart->displayResult();
		
		while (!(intersaction == myGoal))
		{
			Direction x = BFSFromGoal->getDirection(intersaction);
			switch (x)
			{
			case 2:
				cout << "UP" << " ";
				break;
			case 0:
				cout << "DOWN" << " ";
				break;
			case 3:
				cout << "LEFT" << " ";
				break;
			case 1:
				cout << "RIGHT" << " ";
				break;
			default:
				cout << "INVALID" << " ";
				break;
			}
			intersaction = BFSFromGoal->getPath(intersaction);
		}
		return true;
	}
	return false;
}


