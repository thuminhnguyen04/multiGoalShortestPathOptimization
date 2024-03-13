#include "SearchCreator.h"

SearchBase* SearchCreator::GetSearchType(string searchType, string fp)
{

	if (searchType == "BFS")
		return new BFS(fp);
	if (searchType == "DFS")
		return new DFS(fp);
	if (searchType == "GBFS")
		return new GBFS(fp);
	if (searchType == "AS")
		return new AS(fp);
	if (searchType == "CUS1")
		return new CUS1(fp);
	if (searchType == "CUS2")
		return new CUS2(fp);
	if (searchType == "MGPF")
		return new MGPFSearch(fp);
	throw std::exception("Error");
}