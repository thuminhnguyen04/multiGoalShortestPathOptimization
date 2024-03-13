#include "SearchBase.h"


SearchBase::SearchBase(string fp)
{
	fFlag = true;
	ifstream myFile;
	char buffer; // Junk text is funneled in here 

	myFile.open(fp);
	try
	{
		if (myFile.is_open())
		{
			// Get the number of lines to define the vector 

			myFile >> buffer >> row >> buffer >> col >> buffer; //number of rows and cols
			string text;
			getline(myFile, text);
			for (size_t i = 0; i < row; i++)
			{
				
				getline(myFile, text);

				for (size_t j = 0; j < col; j++)
				{
					buffer = text[j];
					if (buffer == 'P')
						startGrid = Coordinate(j, i);
					else if (buffer == '%')
						wallArr.push_back(Wall(j, i));
					else if (buffer == '.')
						goalArr.push_back(Coordinate(j, i));
				}
			}
			myFile.close();
			initialiseVector(); //initialising all vectors in search, inc. path, direction, visited
			robotCurrent = startGrid;

		}
		else {
			cout << "File could not be opened!" << endl;
		}
	}
	catch (...)
	{
		cout << "Invalid file input format!" << endl;
	}
}

SearchBase::SearchBase(SearchBase& aSearch, Coordinate aCoordinate)
{//copy constructure with a given start position
	fFlag = true;
	row = aSearch.row; 
	col = aSearch.col;
	startGrid = aCoordinate;
	wallArr = aSearch.wallArr;
	initialiseVector();
	goalArr.push_back(Coordinate(aSearch.robotCurrent));
	robotCurrent = startGrid;
}
/* DESTRUCTOR */
SearchBase::~SearchBase()
{
	wallArr.clear();
	goalArr.clear();
	direction.clear();
	//wallCount = 0;
}
bool SearchBase::isWallAt(int x, int y) noexcept
{
	for (int i = 0; i < wallArr.size(); i++)
	{
		Wall currentWall = wallArr[i];

		if (x < currentWall.minCoor.x) //if x is less than the left side of the wall
			continue;
		//swap
		if (x >= currentWall.minCoor.x + currentWall.row)//if x is greater than the right side of the wall
			continue;

		if (y < currentWall.minCoor.y)//if y is less than the top corner of the wall
			continue;

		if (y >= currentWall.minCoor.y + currentWall.col)//if y is greater than the bottom corner of the wall
			continue;

		return true;
	}
	return false;
}

bool SearchBase::isWall() noexcept
{
	return isWallAt(robotCurrent.x, robotCurrent.y);
}

void SearchBase::makeAMove(Direction direction)
{
	switch (direction) // moving order: up left down right
	{
	case 0: goUp();
		break;
	case 2: goDown();
		break;
	case 1: goLeft();
		break;
	case 3: goRight();
		break;
	}
}

void SearchBase::goUp()
{
	robotCurrent.y--;
}

void SearchBase::goDown()
{
	robotCurrent.y++;
}

void SearchBase::goLeft()
{
	robotCurrent.x--;
}

void SearchBase::goRight()
{
	robotCurrent.x++;
}

void SearchBase::incrementCounter()
{
	cNode++;
}

void SearchBase::updatePath(Direction d)
{
	direction[robotCurrent.x][robotCurrent.y] = d;
}
string SearchBase::getDirectionString(Direction x)
{
	switch (x)
	{
	case 0:
		return "UP";
	case 2:
		return "DOWN";
	case 1:
		return "LEFT";
	case 3:
		return "RIGHT";
	}
	throw exception("Error in processing data - invalid direction in [SearchBase] getDirectionString");
}

void SearchBase::displayResult(vector<Coordinate> goalArr, vector<bool>& visitedGoal)
{
	Coordinate tmp = robotCurrent;
	vector <string> myDirection;
	cout << "just been to ";

	while (!(tmp == startGrid))
	{
		for (int i = 0; i < goalArr.size(); i++)
		{
			if (visitedGoal[i])
				continue;
			if (tmp == goalArr[i])
			{
				visitedGoal[i] = true;
				cout << "(" << goalArr[i].x << ", " << goalArr[i].y << "), ";

				int dx[] = {-1, 0, 0, 1};
				int dy[] = { 0, -1, 1, 0 };

				for (size_t jj = 0; jj < 4; jj++)
				{
					if (isValidAt(goalArr[i].x + dx[jj], goalArr[i].y + dy[jj]))
					{
						auto neighborC = Coordinate(goalArr[i].x + dx[jj], goalArr[i].y + dy[jj]);

						if (neighborC == getPath(tmp))
							continue;

						for (int ii = 0; ii < goalArr.size(); ii++)// Try each direction
						{
							bool flagNeighbor = true;

							if (goalArr[ii] == neighborC)
							{
								if (!visitedGoal[ii])
								{
									for (size_t jjj = 0; jjj < 4; jjj++)
									{
										if (flagNeighbor && isValidAt(neighborC.x + dx[jjj], neighborC.y + dy[jjj]))
										{
											auto neighborCC = Coordinate(neighborC.x + dx[jjj], neighborC.y + dy[jjj]);

											for (int iii = 0; iii < goalArr.size(); iii++)// Try each direction
											{
												if (goalArr[iii] == neighborCC)
												{
													if (!visitedGoal[iii]) flagNeighbor= false;
													break;
												}
											}
										}
									}
									if (flagNeighbor)
									{
										for (size_t iiii = 0; iiii < goalArr.size(); iiii++)
										{
											if (goalArr[ii].x <= col / 2)
											{
												if (goalArr[iiii].x >= goalArr[ii].x)
													continue;
												//cout << abs(goalArr[iiii].y - goalArr[ii].y) << endl << row/4;
												if (abs(goalArr[iiii].y- goalArr[ii].y)>= max(1,int(row)/4-1))
													continue;
												if (visitedGoal[iiii])
													continue;
												else {
													flagNeighbor = false;
													break;
												}
											}
											else
											{
												if (goalArr[iiii].x < goalArr[ii].x)
													continue;
												if (visitedGoal[iiii])
													continue;
												else {
													flagNeighbor = false;
													break;
												}
											}
										}
										if (!flagNeighbor) continue;
										cout << "(" << goalArr[ii].x << ", " << goalArr[ii].y << "), " << endl;
										visitedGoal[ii] = true;
										if (jj == 0)
										{
											myDirection.push_back("RIGHT");
											myDirection.push_back("LEFT");

										}
										if (jj == 3)
										{
											myDirection.push_back("LEFT");
											myDirection.push_back("RIGHT");

										}
										if (jj == 2)
										{
											myDirection.push_back("UP");
											myDirection.push_back("DOWN");

										}
										if (jj == 1)
										{
											myDirection.push_back("DOWN");
											myDirection.push_back("UP");

										}
									}
								}
							}
						}
					}
				}


			}
		}
		Direction x = getDirection(tmp);
		myDirection.push_back(getDirectionString(x));
		tmp = getPath(tmp);
	}
	cout << "(" << robotCurrent.x << ", " << robotCurrent.y << ") by ";

	// print out input from back to front 
	while (myDirection.size() != 0)
	{
		cout << *(myDirection.cend() - 1) << " ";
		myDirection.pop_back();
		cStep+=1;
	}
	cout << endl << "Steps taken: " << cStep;
}
void SearchBase::displayResult(bool aFlag)
{
	if (!fFlag)
		return;
	if (aFlag)
		cout << cNode << endl; //number of expanded nodes

	Coordinate tmp = robotCurrent;
	vector <string> myDirection;
	while (!(tmp == startGrid))
	{
		Direction x = getDirection(tmp);		
		myDirection.push_back(getDirectionString(x));
		tmp = getPath(tmp);
	}

	// print out input from back to front 
	while (myDirection.size() != 0)
	{
		cout << *(myDirection.cend()-1) << " ";
		myDirection.pop_back();
	}
}

void SearchBase::resetSearch()
{
	Coordinate tmp(-1, -1);
	for (size_t i = 0; i < col; i++)
	{
		direction[i].clear();
		path[i].clear();
		visited[i].clear();
		for (size_t j = 0; j < row; j++)
		{
			direction[i].push_back(Direction(4));
			visited[i].push_back(0);
			path[i].push_back(tmp);
		}
	}
}

Coordinate SearchBase::getRobot()
{
	return robotCurrent;
}

void SearchBase::initialiseVector()
{
	direction.clear();
	path.clear();
	visited.clear();
	Coordinate tmp(-1,-1);

	for (size_t i = 0; i < col; i++)
	{
		direction.push_back({});
		path.push_back({});
		visited.push_back({});

		for (size_t j = 0; j < row; j++)
		{
			direction[i].push_back(Direction(4));
			path[i].push_back(tmp);
			visited[i].push_back(0);
		}
	}
	cNode = 0;
}
unsigned int SearchBase::getNumberOfNodes()
{
	return cNode;
}
int SearchBase::getStep()
{
	return cStep;
}
Direction SearchBase::getDirection(Coordinate aCoor)
{
	return direction[aCoor.x][aCoor.y];
}
Coordinate SearchBase::getPath(Coordinate aCoor)
{
	return path[aCoor.x][aCoor.y];
}
bool SearchBase::isDone()
{
	return (find(goalArr.begin(), goalArr.end(), robotCurrent) != goalArr.end());
}
bool SearchBase::isValid()
{
	return isValidAt(robotCurrent.x, robotCurrent.y);
}
bool SearchBase::isValidAt(int x, int y)
{
	return (x >= 0
		&& x < col
		&& y >= 0
		&& y < row
		&& !isWallAt(x,y));
}

void SearchBase::resetGoal(Coordinate aC)
{
	goalArr.clear();
	goalArr.push_back(aC);
}
void SearchBase::makeVisited()
{
	visited[robotCurrent.x][robotCurrent.y] = true;
}
bool SearchBase::isVisited()
{
	return visited[robotCurrent.x][robotCurrent.y];
}
bool SearchBase::isVisitedAt(int aX, int aY)
{
	return visited[aX][aY];
}
bool SearchBase::makeAValidMove(Direction direction, Coordinate parent)
{
	robotCurrent = parent;
	makeAMove(direction);

	return isValid();
}
void SearchBase::setRobot(Coordinate ax)
{
	robotCurrent = ax;
}
void SearchBase::setNode(int ax)
{
	cNode = ax;
}

/*
SearchBase::SearchBase(string fp)
{
	fFlag = true;
	ifstream myFile;
	char buffer; // Junk text is funneled in here

	myFile.open(fp);
	try
	{
		if (myFile.is_open())
		{
			// Get the number of lines to define the vector

			myFile >> buffer >> row >> buffer >> col >> buffer; //number of rows and cols
			myFile >> buffer >> startGrid.x >> buffer >> startGrid.y >> buffer; //the initial position of the robot
			robotCurrent = startGrid;
			do
			{
				Coordinate tmp; //goal read format: (7,0) | (10,3)
				myFile >> buffer >> tmp.x >> buffer >> tmp.y >> buffer;
				goalArr.push_back(tmp);
				myFile >> buffer; // a goal is read
			} while (buffer == '|');

			if (buffer != '(' && buffer != ')') // did not know in advance the number of goal nodes or number of walls --> this line of code is to handle them
				throw exception("Invalid input of goals");
			while (!myFile.eof())
			{
				if (buffer == ')')
					if (!(myFile >> buffer))
						break; // handle line with empty content
				Wall myWall; // wall read format: (2,0,2,2)
				myFile >> myWall.minCoor.x >> buffer >> myWall.minCoor.y >> buffer;
				myFile >> myWall.row >> buffer >> myWall.col >> buffer;
				wallArr.push_back(myWall);

			}
			myFile.close();
			initialiseVector(); //initialising all vectors in search, inc. path, direction, visited
		}
		else {
			cout << "File could not be opened!" << endl;
		}
	}
	catch (...)
	{
		cout << "Invalid file input format!" << endl;
	}
}*/
