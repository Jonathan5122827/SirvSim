
#include "cell.h"

void Cell::SetXcord(int x)	{

	this-> x = x;
}

void Cell::SetYcord(int y)	{

	this-> y = y;
}

void Cell::SetVal(int val)	{

	this-> val = val;
}

int Cell::GetXcord()	{

	return this-> x;
}

int Cell::GetYcord()	{

	return this-> y;
}

int Cell::GetVal()	{

	return this-> val;
}

