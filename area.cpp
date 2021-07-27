#include "area.h"


Area::Area()	{

	this->value = 0;
	this->close = 0;
	this->degree = 0;
        this->pop = 0;
        this->sus = 0;
        this->inf = 0;
        this->rec = 0;
        this->vac = 0;
        this->daysWithInf = 0;
	this->daysWithRec = 0;
	this->orgSus = 0;
	this-> maxInf = false;
}

void Area::SetValue(int value)	{

	this-> value = value;
}

void Area::SetClose(int close)	{

	this-> close = close;
}

void Area::SetDegree(int degree)	{

	this-> degree = degree;
}

void Area::SetPop(int pop)	{

	this-> pop = pop;
}

void Area::SetSus(int sus)	{

	this-> sus = sus;
}

void Area::SetInf(int inf)	{

	this-> inf = inf;
}

void Area::SetRec(int rec)	{

	this-> rec = rec;
}

void Area::SetVac(int vac)	{

	this-> vac = vac;
}

void Area::SetDaysWithInf(int daysWithInf)	{

	this-> daysWithInf = daysWithInf;
}

int Area::GetValue()	{

	return this-> value;
}

int Area::GetClose()	{

	return this-> close;
}

int Area::GetDegree()	{

	return this-> degree;
}

int Area::GetPop()	{

	return this-> pop;
}

int Area::GetSus()	{

	return this-> sus;
}

int Area::GetInf()	{

	return this-> inf;
}

int Area::GetRec()	{

	return this -> rec;
}

int Area::GetVac()	{

	return this-> vac;
}

int Area::GetDaysWithInf()	{

	return this-> daysWithInf;
}

vector <int> Area::GetAdjAreas()	{

	return this-> adjAreas;
}

vector <int> Area::GetInfRecord()	{

	return this-> infRecord;
}

void Area::PushAdjAreas(int adjArea)	{

	this-> adjAreas.push_back(adjArea);
}
void Area::PushInfRecord(int infRecord)	{

	this-> infRecord.push_back(infRecord);
}

void Area::SetDaysWithRec(int daysWithRec)	{

	this-> daysWithRec = daysWithRec;
}

int Area::GetDaysWithRec()	{

	return this-> daysWithRec;
}

void Area::SetOrgSus(int orgSus)	{

	this-> orgSus = orgSus;
}

int Area::GetOrgSus()	{

	return this-> orgSus;
}

void Area::SetMaxInf(bool maxInf)	{

	this-> maxInf = maxInf;
}

bool Area::GetMaxInf()	{

	return this-> maxInf;
}

void Area::PushSusRecord(int susRecord)	{

	this-> susRecord.push_back(susRecord);
}

vector <int> Area::GetSusRecord()	{

	return this-> susRecord;
}

