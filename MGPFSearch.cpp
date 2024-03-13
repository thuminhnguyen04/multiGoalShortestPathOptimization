#include "MGPFSearch.h"


MGPFSearch::MGPFSearch(string fp) : SearchBase(fp) {
    // unvistedGoals = goalArr;
    if (goalArr.size() == 0)
        throw exception("Invalid goal input");
    fFlag = false;

    for (int i = 0; i < goalArr.size(); i++)
    {
        fGraph.push_back({});
        visitedGoals.push_back(false);
    }
    fGraph.push_back({});

    BFS* lTmp = new BFS(*this, robotCurrent);
    for (int i = 0; i < goalArr.size(); i++)
    {
        BFS* tmp = new BFS(*this, goalArr[i]);
        fGraph[i].push_back(0);
        for (int j = i + 1; j < goalArr.size(); j++)
        {
            int tmpLen = tmp->getLen(goalArr[j]);
            if (tmpLen == -1)
            {
                cout << "Input invalid: There is a goal to which there is no path" << endl;
                throw exception("Invalid input");
            }
            fGraph[i].push_back(tmpLen);
            fGraph[j].push_back(tmpLen);
        }
        cNode += tmp->getNumberOfNodes();

        int tmpLen = lTmp->getLen(goalArr[i]);
        if (tmpLen == -1)
        {
            cout << "Input invalid: There is a goal to which there is no path" << endl;
            throw exception("Invalid input");
        }
        fGraph[goalArr.size()].push_back(tmpLen);
    }
    cNode += lTmp->getNumberOfNodes();

    //setUpPermutation();
    //executePermutation();
}

MGPFSearch::MGPFSearch(SearchBase& aSearchOther, Coordinate aCoordinate) : SearchBase(aSearchOther, aCoordinate) {}

MGPFSearch::~MGPFSearch()
{
    for (int i = 0; i < goalArr.size() + 2; i++)
        delete memo[i];
    delete memo;
}
bool MGPFSearch::search()
{
    // If the source is out of range
    if (!isValid()) {
        throw exception("Invalid input");
    }

    // If the destination cell is the same as source cell
    if (isDone())
    {
        cout << "Start cell is also the goal cell" << endl;
        return true;
    }

    int lIndex = goalArr.size();

    incrementCounter();

    int min_i = lIndex;

    while (true)
    {
        int min_f = 1e9;

        lIndex = min_i;

        if (lIndex != goalArr.size())
        {
            if (visitedGoals[lIndex])
                continue;

            visitedGoals[lIndex] = true;
            BFS* bfstmp = new BFS(*this, robotCurrent);
            bfstmp->displayPathTo(goalArr[lIndex], goalArr, visitedGoals);
            cStep += bfstmp->getStep();
            robotCurrent = goalArr[lIndex];
            if (visitedGoals[fCurrentMax.first] || visitedGoals[fCurrentMax.second])
                isUpToDateDistance = false;
        }

        if (isGoal())
        {
            cout << "Number of steps: " << cStep << endl;
            cout << "Number of nodes: " << cNode << endl;
            if (goalArr.size() > 25)
            {
                cout << endl << "Permutation to calculate the actual shortest path cost is unable to be done due to high input size." << endl;
                cout << "The number of goals must be less than 25." << endl;
            }
            else {
                setUpPermutation();
                cout << endl << "PLEASE NOTE THAT PERMUTATION IS RUNNING IN PROGRESS." << endl;
                cout << "The higher number of goals, the longer waiting time." << endl;
                cout << "Actual cost by permutation: ";
                executePermutation();
            }return true;
        }

        for (int i = 0; i < goalArr.size(); i++)// Try each direction
        {
            if (visitedGoals[i])
                continue;

            int fValue = computeHeuristicValue(i) + fGraph[lIndex][i];

            Coordinate parenttmp = (lIndex == goalArr.size()) ? startGrid : goalArr[lIndex];

            //if (goalArr[i] == Coordinate(11, 12) && robotCurrent == Coordinate(12, 13))
            {
                //min_f = fValue;
                //min_i = i;
                //break;
            }

            if (goalArr[i].x != parenttmp.x && goalArr[i].y != parenttmp.y)
            {
                fValue += 1;
            }
            else {
                if (abs(goalArr[i].x - parenttmp.x) + abs(goalArr[i].y - parenttmp.y) == 1
                    )//&& ((goalArr[i].x < parenttmp.x && parenttmp.x < col / 2)
                    //|| (goalArr[i].x > parenttmp.x && parenttmp.x >= col / 2)
                    //|| (goalArr[i].y < parenttmp.y && parenttmp.y < row / 2)
                    //|| (goalArr[i].y > parenttmp.y && parenttmp.y > row / 2 )))
                {
                    int cNeighbor = 0;
                    int dx[] = { -1, 0, 0, 1 };
                    int dy[] = { 0, -1, 1, 0 };

                    for (size_t jj = 0; jj < 4; jj++)
                    {
                        if (isValidAt(goalArr[i].x + dx[jj], goalArr[i].y + dy[jj]))
                        {
                            auto neighborC = Coordinate(goalArr[i].x + dx[jj], goalArr[i].y + dy[jj]);

                            for (int ii = 0; ii < goalArr.size(); ii++)// Try each direction
                            {
                                if (goalArr[ii] == neighborC)
                                {
                                    if (!visitedGoals[ii]) cNeighbor++;
                                    break;
                                }
                            }
                        }
                    }
                    if (cNeighbor <= 1)
                    {
                        fValue -= 1;
                    }

                }

            }

            if (min_f > fValue)
            {
                min_f = fValue;
                min_i = i;
            }
        }
    }
    return false;

}

bool MGPFSearch::isGoal()
{
    return (count(visitedGoals.begin(), visitedGoals.end(), false) == 0);
}

int MGPFSearch::computeHeuristicValue(int aIndex)
{
    /*--------Initialising + checking stuff ----------*/

    int numberOfUnvisted = count(visitedGoals.begin(), visitedGoals.end(), false);
    if (numberOfUnvisted == 0)  return 0;

    if (numberOfUnvisted == 1)
    {
        for (size_t i = 0; i < goalArr.size(); i++)
        {
            if (!visitedGoals[i])
                return fGraph[i][aIndex];
        }

    }
    /*--------When there is at least one goal remaining to be visited: ----------*/
    if (numberOfUnvisted > 1)
    {
        if (!isUpToDateDistance)
        {
            fCurrentMax = computeMapDistance(aIndex);
            lResult = fGraph[fCurrentMax.first][fCurrentMax.second];
            isUpToDateDistance = true;
        }
    }
    //return fGraph[aIndex][fCurrentMax.first] + fGraph[fCurrentMax.second][fCurrentMax.first];
    return lResult + min(fGraph[aIndex][fCurrentMax.first], fGraph[aIndex][fCurrentMax.second]);
}
pair<int, int> MGPFSearch::computeMapDistance(int aIndex)
{
    //if (!flag) //visit the same set of unvisited goal again - flag = false --> return directly
      //  return lResult;

    pair <int, int> tmp;

    int lcost = -1;
    
     /*----2. compute the cost among each pair of unvisited goals MANHANTTAN - set up*/
    for (size_t i = 0; i < goalArr.size(); i++)
    {
        if (visitedGoals[i])
            continue;

        for (size_t j = i + 1; j < goalArr.size(); j++)
        {
            if (visitedGoals[j])
                continue;

            if (lcost < fGraph[i][j])
            {
                lcost = fGraph[i][j];
                tmp = make_pair(i, j);
            }
        }
    }
    return tmp;
}

void MGPFSearch::setUpPermutation()
{
    //int memo[n][1 << (n + 1)];
    int n = goalArr.size();
    memo = new int* [n + 2];
    memo[0] = new int[1 << (n + 2)];
    memset(memo[0], 0, (1 << (n + 2)) * sizeof(int));

    memo[n + 1] = new int[1 << (n + 2)];
    memset(memo[n + 1], 0, (1 << (n + 2)) * sizeof(int));


    fGraph.insert(fGraph.begin(), vector<int>(n + 2, 0)); //insert mask at first position
    vector <int> lTmp = fGraph[n + 1]; //copy graph of starting node
    // mask - goal 0 - goal 1 - .... - starting node
    for (int i = n; i >= 1; i--)
    {
        memo[i] = new int[1 << (n + 2)];
        memset(memo[i], 0, (1 << (n + 2)) * sizeof(int));

        fGraph[i].insert(fGraph[i].begin(), 2, 0);
        fGraph[i + 1] = fGraph[i];
    }
    fGraph[1] = lTmp;
    fGraph[1].insert(fGraph[1].begin(), 2, 0);

    //executePermutation();
}


bool MGPFSearch::executePermutation()
{
    // If the source is out of range
    int n = goalArr.size() + 1;
    int ans = 1e9;

    for (int i = 1; i <= n; i++)

        // try to go from node 1 visiting all nodes in

        // between to i then return from i taking the

        // shortest route to 1
    {
        ans = std::min(ans, fun(i, (1 << (n + 1)) - 1) + fGraph[i][1]);
    }
    cout << "Shortest path: " << ans << endl;
    return 0;

}
int MGPFSearch::fun(int i, int mask)
{

    // base case

    // if only ith bit and 1st bit is set in our mask,

    // it implies we have visited all other nodes already
    int n = goalArr.size() + 1;



    if (mask == ((1 << i) | 3))
    {
        return fGraph[1][i];
    }
    // memoization

    if (memo[i][mask] != 0)
        return memo[i][mask];


    int res = 1e9; // result of this sub-problem

    int lIndex = 0;


    for (int j = 1; j <= n; j++)

        if ((mask & (1 << j)) && j != i && j != 1)
        {

            res = min(res, fun(j, mask & (~(1 << i))) + fGraph[j][i]);
        }

    //res = std::min(res, fun(j, mask & (~(1 << i))) + fGraph[j][i]);
//cout << lIndex << "," << i << endl;
    return memo[i][mask] = res;
}