#pragma once
#include <unordered_map>
#include <iostream>
#include <set>
#include "InformedSearch.h"

class AS : public InformedSearch
{
public:
	AS(string fp);

	~AS();
	AS(SearchBase&, Coordinate);

	bool search();
	unsigned int computeHeuristicValue();
};