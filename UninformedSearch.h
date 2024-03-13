#pragma once
#include "SearchBase.h"


class UninformedSearch : public SearchBase
{
public:

	UninformedSearch(string fp);
	UninformedSearch(SearchBase&, Coordinate);

	virtual bool search() = 0;


};
