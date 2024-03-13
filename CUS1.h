#pragma once
#include "SearchBase.h"
#include "BFS.h"
class CUS1 : public BFS
{
public:
	CUS1(string fp);
	~CUS1();

	bool search();
	Coordinate getIntersaction(UninformedSearch* aOtherSearch);

};
