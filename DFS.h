#pragma once
#include "UninformedSearch.h"

class DFS : public UninformedSearch
{
public:
	DFS(string fp);
	~DFS();

	bool search();
	bool expand();
};
