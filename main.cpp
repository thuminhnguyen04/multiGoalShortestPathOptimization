#include <iostream>
#include <vector>
#include <string>
#include "SearchCreator.h"
#include "SearchBase.h"

using namespace std;


int main(int argc, char* argv[])
{


	if (argc != 3)
	{
		cout << "Invalid input!" << endl;
		return 1;
	}
	for (size_t i = 1; i < argc; i++)
	{
		cout << argv[i] << " ";
	}

	const string fp = argv[1];
	const string searchType = argv[2];

	
	
	try {
		SearchCreator myFactory;
		SearchBase* mySearch = myFactory.GetSearchType(searchType, fp);

		if (mySearch->isDone())
		{
			cout << "Start cell is also the goal cell" << endl;
			return 1;
		}
		if (mySearch->search())
		{
			mySearch->displayResult();
		
		}
		else cout << "No path found.";
	}
	catch (...)
	{
		cout << "Invalid file input format!" << endl;
	}
	cout << endl;
	
	return 1;
}
