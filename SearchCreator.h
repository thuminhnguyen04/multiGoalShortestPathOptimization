#pragma once
#include "BFS.h"
#include "DFS.h"
#include "GBFS.h"
#include "AS.h"
#include "CUS1.h"
#include "CUS2.h"
#include "MGPFSearch.h"

class SearchCreator
{
public:
	
	virtual ~SearchCreator() {};
	SearchBase* GetSearchType(string searchType, string fp);
};

