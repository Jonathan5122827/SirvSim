
#include "sim.h"

Sim::Sim()	{

	this-> configFile = "X";	//holds user prompted config file
        this-> popFile = "X";		// holds name of population file
        this-> regionFile = "X";	// holds name of region file
        this-> areaStart = 100;		// holds area where infection begins
        this-> infPeriod = 100;		//holds infection period
        this-> contRate = 100;		// holds contact rate
        this-> availVac = 100;		// holds number of vaccines
	this-> dayNum = 0;		// hold current day a simulation is on
	this-> stopSim = false;		// bool that could stop the simulation
        this-> degPeak = 0;		// infection peak for degee simulation
        this-> degPeakDay = 0;		// day when infection peak occured
        this-> degDayEnd = 0;		// day the degrtee simulation ended
        this-> degTotalInf = 0;		// total number of infected during the degree siualtion
        this-> randPeak = 0;		// same as degree but for other simuations
        this-> randPeakDay = 0;
        this-> randDayEnd = 0;
        this-> randTotalInf = 0;
        this-> eqPeak = 0;
        this-> eqPeakDay = 0;
        this-> eqDayEnd = 0;
        this-> eqTotalInf = 0;
        this-> closePeak = 0;
        this-> closePeakDay = 0;
        this-> closeDayEnd = 0;
        this-> closeTotalInf = 0;

}

void Sim::SetConfigFile(string configFile)	{	//set and get functions, for all the Sim class private data members

	this-> configFile = configFile;
}

void Sim::SetPopFile(string popFile)	{

	this-> popFile = popFile;
}

void Sim::SetRegionFile(string regionFile)	{

	this-> regionFile = regionFile;
}

void Sim::SetAreaStart(int areaStart)	{

	this-> areaStart = areaStart;
}

void Sim::SetInfPeriod(int infPeriod)	{

	this-> infPeriod = infPeriod;
}

void Sim::SetContRate(int contRate)	{

	this-> contRate = contRate;
}

void Sim::SetAvailVac(int availVac)	{

	this-> availVac = availVac;
}

string Sim::GetConfigFile()	{

	return this-> configFile;
}

string Sim::GetPopFile()	{

	return this-> popFile;
}

string Sim::GetRegionFile()	{

	return this-> regionFile;
}

int Sim::GetAreaStart()	{

	return this-> areaStart;
}

int Sim::GetInfPeriod()	{

	return this-> infPeriod;
}

int Sim::GetContRate()	{

	return this-> contRate;
}

int Sim::GetAvailVac()	{

	return this-> availVac;
}

void Sim::Config()	{	//function that read from and stroes the information in the configuration file

	string temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp12, temp14, temp16, popFile, regionFile, configFile;

	int temp11 = 0;
	int temp13 = 0;
	int temp15 = 0;
	int temp17 = 0;

	cout << "Please enter the name of the configuration file:";	//prompt the user for the name of configuration file
	cin >> configFile;

	ifstream config(configFile);	//opens the file

		getline(config,temp1);	//infream grabs each line of the configuration file
		getline(config,temp2);
		getline(config,temp3);
		getline(config,temp4);
		getline(config,temp5);
		getline(config,temp6);
		getline(config,temp7);

			int pos = temp1.find(":");	//find the position of the : in each line

			int pos2 = temp2.find(":");

			int pos3 = temp4.find(":");

			int pos4 = temp5.find(":");

			int pos5 = temp6.find(":");

			int pos6 = temp7.find(":");

			temp8 = temp1.substr(pos + 1);	// create a substring of each line, just of relevant infomatioon

			temp9 = temp2.substr(pos2 + 1);

			temp10 = temp4.substr(pos3 + 1);

			temp12 = temp5.substr(pos4 + 1);

			temp14 = temp6.substr(pos5 + 1);

			temp16 = temp7.substr(pos6 + 1);

			temp11 = stoi(temp10);	// turns the string numbers, into int type numbers

			temp13 = stoi(temp12);

			temp15 = stoi(temp14);

			temp17 = stoi(temp16);

			SetPopFile(temp8);	// stores the read in content of the config file, into Sim class data members

			SetRegionFile(temp9);

			SetAreaStart(temp11);

			SetInfPeriod(temp13);

			SetContRate(temp15);

			SetAvailVac(temp17);
}

void Sim::ConfigPops()	{	// reads in and stores the dat held the pop configuation file

	ifstream popConfig(GetPopFile());	//opens an ifstream with name of the pop file, returned from the GetPopFile()

	int numOfArea = 1;	// keeps tracks of number of lines in the pop configuation file, also equal to the nubmer of areas in the region

	int temp3 = 0;		// holde the each line of the file, as a string

	string temp, temp2;

	while(getline(popConfig,temp))	{	//grabs each line of the pop config file, and stores it in temp string

		int pos = temp.find(":"); // locates the postion of the : in each line of the file

		temp2 = temp.substr(pos + 1); // makes a substring of number strings

		temp3 = stoi(temp2); // converts the number string, into a usable int type

		Area *a = new Area();	// creates an instacne of an Area object

		a->SetValue(numOfArea); // Area has its value set as its line number

		a->SetPop(temp3); // Area has its pop set as the pop read in from each line

		areas.push_back(a);	// Area object pushed back into a vector, holding the collection of Area objects

		numOfArea++; // incrememnts the line number
	}
}

void Sim::SetRows(int rows)	{	// sets and get for region dimensions

	this->rows = rows;
}

void Sim::SetCols(int cols)	{

	this->cols = cols;
}

int Sim::GetRows()	{

	return this-> rows;
}

int Sim::GetCols()	{

	return this-> cols;
}

void Sim::ConfigRegion()	{		//reads and stores the adjancy matrix

	ifstream regionConfig(GetRegionFile()); // opens an ifstream, from the string stored in GetRegionFile()

	int rows = 0;
	int cols = 0;

	int temp3 = 0;

	int entryNum = 0;

	int rowNum = 0;

	string temp, temp2;

	while(getline(regionConfig,temp))	{	//counts the number of rows in the region

		rows++;
	}

	SetRows(rows); //Set regions's row
        SetCols(rows);	//region is always a square

	regionConfig.clear();	//reset the ifstream, and goes back to the top of the file
	regionConfig.seekg(0);

	if(GetRows() <= 10)	{	// reads and stores the contents of the region file

		while(getline(regionConfig,temp))	{

			cols = temp.length();

			for(int i = 0;  i < rows*2 -1; i++)	{

				temp2 = temp.substr(i,1);

				if(temp2 != ",")	{

					Cell *c = new Cell();

				if(temp2 == " ")	{

					c->SetVal(0);

					region.push_back(c);
				}

				else	{

					temp3 = stoi(temp2);

					c->SetVal(temp3);

					region.push_back(c);
				}
			}
		}
	}
	}

	else	{

		while(getline(regionConfig,temp))       {

			if(rowNum == 0)	{

				for(int i = 0;  i < rows*2 -1; i++)     {

					if(entryNum <= 9)	{

						if(i == 0)	{

							Cell *c = new Cell();

							c->SetVal(0);

                                                        region.push_back(c);

                                                        entryNum++;

							continue;
						}

						else	{

							temp2 = temp.substr(i+1,1);

							i++;

                                			Cell *c = new Cell();

                                        		temp3 = stoi(temp2);

                                        		c->SetVal(temp3);

                                        		region.push_back(c);

							entryNum++;
						}
					}

                                        else      {

                                                temp2 = temp.substr(i+1,2);

                                                Cell *c = new Cell();

                                                temp3 = stoi(temp2);

                                                c->SetVal(temp3);

                                                region.push_back(c);

						entryNum++;

						i++;

						i++;
					}
				}
				rowNum++;

				continue;
			}

			if(rowNum > 0 & rowNum < 10)	{

		                for(int i = 0;  i < rows*2 -1; i++)     {

                		        temp2 = temp.substr(i,1);

			                        if(temp2 != ",")        {

                		                	Cell *c = new Cell();

                                        		temp3 = stoi(temp2);

                                        		c->SetVal(temp3);

                                        		region.push_back(c);
                                		}
                        	}
				rowNum++;
                	}

			else	{

				for(int i = 0;  i < rows*2 ; i++)     {

					if(i == 0)	{

						temp2 = temp.substr(i,2);

						Cell *c = new Cell();

						temp3 = stoi(temp2);

                                                c->SetVal(temp3);

                                                region.push_back(c);

						i++;

						i++;
					}

					else	{

                                                temp2 = temp.substr(i,1);

                                                Cell *c = new Cell();

                                                temp3 = stoi(temp2);

                                                c->SetVal(temp3);

                                                region.push_back(c);

						i++;
					}
				}
				rowNum++;
			}
		}
	}

	SetCords();

	//PrintCords();

	SetAreaAdj();

	CalcClose();

	CalcDegree();
}

void Sim::SetCords()	{	//assigns grid coorndinates to each cell in the region

	int x = 0;
	int y = 0;

	for(int i = 0; i < region.size(); i++)	{

		region.at(i)->SetXcord(x);

		region.at(i)->SetYcord(y);

		x++;

		if(x == GetCols())	{

			x = 0;

			y++;
		}
	}
}

void Sim::PrintCords()	{

	for(int i = 0; i < region.size(); i++)  {

		cout << region.at(i)->GetVal() << ":(" << region.at(i)->GetXcord() << "," << region.at(i)->GetYcord() << ")";

                if(region.at(i)->GetXcord() == GetCols() -1)     {

                        cout << endl;
                }
	}
}

void Sim::SetAreaAdj()	{	//configuration of adjaceny maxtrix

	for(int i = 0; i < region.size(); i++)  {	//itterates over the areas

		if(region.at(i)->GetVal() == 1 & region.at(i)->GetXcord() > 0 & region.at(i)->GetYcord() > 0)	{	//looks for the ones in the region file

			areas.at(region.at(i)->GetYcord() -1)->PushAdjAreas(region.at(i)->GetXcord());	// set adjacent areas with the possition where the one occured
		}
	}
}

void Sim::PrintAdjList()	{	// prints outs each areas adjacency list

	cout << "Adjacency List" << endl;

	for(int i = 0; i < areas.size(); i++)  {

		cout << areas.at(i)->GetValue() << ": ";

		for(int j = 0; j < areas.at(i)->GetAdjAreas().size(); j++)	{		//adjacent areas held in a vector in each areas object

			cout << areas.at(i)->GetAdjAreas().at(j) << " ";	// each element in the vector is outputted
		}

		cout << endl;
	}

	cout << endl;
}

void Sim::PrintAreaPops()	{	// print each areas popuations

	cout << "Regional Population" << endl;

	for(int i = 0; i < areas.size(); i++)  {

		cout << areas.at(i)->GetValue() << " " << areas.at(i)->GetPop() << endl;
	}

	cout << endl;
}

void Sim::CalcClose()	{	//calcualtes closness of each area

	int x = 0;

	int y = 0;

	int z = 0;

	int a = 0;

	int b = 0;

	for(int i = 1; i < areas.size(); i++)  {	//keeps track of desired areas value to look for

		for(int j = 0; j < areas.size(); j++)  {	// iterates over each area

			int dis = 0;

			bool found = false;

			for(int k = 0; k < areas.at(j)->GetAdjAreas().size(); k++)      {

				if(areas.at(j)->GetAdjAreas().at(k) == i & areas.at(j)->GetValue() != i & found == false)	{

					//continue;

					found = true;

					//cout << "found" << i << " for area" << areas.at(j)->GetValue() << " 0 distance awaqy" << endl;

					//areas.at(j)->SetClose(areas.at(j)->GetClose() + 0.0);
				}

			}

			if(found == false)	{

				for(int k = 0; k < areas.at(j)->GetAdjAreas().size(); k++)      {

					 x = areas.at(j)->GetAdjAreas().at(k);

					for(int m = 0; m < areas.at(x-1)->GetAdjAreas().size(); m++)      {

		                                if(areas.at(x-1)->GetAdjAreas().at(m) == i & areas.at(j)->GetValue() != i & found == false)       {

                	                        	//continue;

        	        	                        found = true;

							//cout << "found " << i << " for area" << areas.at(j)->GetValue() << " 1 distance awaqy" << endl;

							areas.at(j)->SetClose(areas.at(j)->GetClose() + 1);	//pushed a distacne of 1
	                                	}
					}
				}
			}

			if(found == false)      {

                                for(int k = 0; k < areas.at(j)->GetAdjAreas().size(); k++)      {

                                         x = areas.at(j)->GetAdjAreas().at(k);

                                        for(int m = 0; m < areas.at(x-1)->GetAdjAreas().size(); m++)      {

						y = areas.at(x-1)->GetAdjAreas().at(m);

						for(int n = 0; n < areas.at(y-1)->GetAdjAreas().size(); n++)      {

					        	if(areas.at(y-1)->GetAdjAreas().at(n) == i & areas.at(j)->GetValue() != i & found == false)       {

                                                        	//continue;

                                                        	found = true;

                                                        	//cout << "found " << i << " for area" << areas.at(j)->GetValue() << " 2 distance awaqy" << endl;

								areas.at(j)->SetClose(areas.at(j)->GetClose() + 2); // distance 2
                                                	}
						}
					}
				}
			}

                        if(found == false)      {

                                for(int k = 0; k < areas.at(j)->GetAdjAreas().size(); k++)      {

                                         x = areas.at(j)->GetAdjAreas().at(k);

                                        for(int m = 0; m < areas.at(x-1)->GetAdjAreas().size(); m++)      {

                                                y = areas.at(x-1)->GetAdjAreas().at(m);

                                                for(int n = 0; n < areas.at(y-1)->GetAdjAreas().size(); n++)      {

							z = areas.at(y-1)->GetAdjAreas().at(n);

		                                	for(int t = 0; t < areas.at(z-1)->GetAdjAreas().size(); t++)      {

                		        	                if(areas.at(z-1)->GetAdjAreas().at(t) == i & areas.at(j)->GetValue() != i & found == false)       {

	                                                                //continue;

        	                                                        found = true;

                	                                               	//cout << "found " << i << " for area" << areas.at(j)->GetValue() << " 3 distance awaqy" << endl;

									areas.at(j)->SetClose(areas.at(j)->GetClose() + 3); // and so on
		                                                 }
	                	                         }
						}
					}
				}
			}

                        if(found == false)      {

                                for(int k = 0; k < areas.at(j)->GetAdjAreas().size(); k++)      {

                                         x = areas.at(j)->GetAdjAreas().at(k);

                                        for(int m = 0; m < areas.at(x-1)->GetAdjAreas().size(); m++)      {

                                                y = areas.at(x-1)->GetAdjAreas().at(m);

                                                for(int n = 0; n < areas.at(y-1)->GetAdjAreas().size(); n++)      {

                                                        z = areas.at(y-1)->GetAdjAreas().at(n);

                                                        for(int t = 0; t < areas.at(z-1)->GetAdjAreas().size(); t++)      {

								a = areas.at(z-1)->GetAdjAreas().at(t);

								for(int u = 0; u < areas.at(a-1)->GetAdjAreas().size(); u++)      {

	                                                                if(areas.at(a-1)->GetAdjAreas().at(u) == i & areas.at(j)->GetValue() != i & found == false)       {

	                                                                        //continue;

        	                                                                found = true;

        	                                                                //cout << "found " << i << " for area" << areas.at(j)->GetValue() << " 4 distance awaqy" << endl;

										areas.at(j)->SetClose(areas.at(j)->GetClose() + 4);
	                                                                 }
								}
							}
						}
					}
				}
			}

                        if(found == false)      {

                                for(int k = 0; k < areas.at(j)->GetAdjAreas().size(); k++)      {

                                         x = areas.at(j)->GetAdjAreas().at(k);

                                        for(int m = 0; m < areas.at(x-1)->GetAdjAreas().size(); m++)      {

                                                y = areas.at(x-1)->GetAdjAreas().at(m);

                                                for(int n = 0; n < areas.at(y-1)->GetAdjAreas().size(); n++)      {

                                                        z = areas.at(y-1)->GetAdjAreas().at(n);

                                                        for(int t = 0; t < areas.at(z-1)->GetAdjAreas().size(); t++)      {

                                                                a = areas.at(z-1)->GetAdjAreas().at(t);

                                                                for(int u = 0; u < areas.at(a-1)->GetAdjAreas().size(); u++)      {

									b = areas.at(a-1)->GetAdjAreas().at(u);

									for(int v = 0; v < areas.at(b-1)->GetAdjAreas().size(); v++)      {

	                                                                        if(areas.at(b-1)->GetAdjAreas().at(v) == i & areas.at(j)->GetValue() != i & found == false)       {

	                                                                                //continue;

	                                                                                found = true;

        	                                                                        //cout << "found " << i << " for area" << areas.at(j)->GetValue() << " 5 distance awaqy" << endl;

											areas.at(j)->SetClose(areas.at(j)->GetClose() + 5);
	                                                                         }
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Sim::CloseSim()	{

        if(GetDayNum() == 0)    {

                ConfigCloseSim();

                cout << "CLOSENESS DISTRIBUTION" << endl;
        }

        cout << "Day " << GetDayNum() << endl;

        for(int i = 0; i < areas.size(); i++)  {

                cout << areas.at(i)->GetValue() << "  POP: " << areas.at(i)->GetPop() << "   S: " << areas.at(i)->GetSus();

                cout << "   I: " << areas.at(i)->GetInf() << "     R: " << areas.at(i)->GetRec() << "     V: " << areas.at(i)->GetVac() << endl;
        }

        int totalInf = 0;

        for(int i = 0; i < areas.size(); i++)  {

                 totalInf = totalInf + areas.at(i)->GetInf();

        }

        if(totalInf > GetClosePeak())     {

                SetClosePeak(totalInf);

                SetClosePeakDay(GetDayNum());
        }

        if(totalInf == 0 || GetDayNum() > 50)   {

                SetStopSim(true);

                SetCloseDayEnd(GetDayNum());

                int totalRec = 0;

                for(int i = 0; i < areas.size(); i++)   {

                        totalRec = totalRec + areas.at(i)->GetRec();
                }

                SetCloseTotalInf(totalRec);
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetInf() > areas.at(i)->GetPop()/2)   {

                        for(int j = 0; j < areas.at(i)->GetAdjAreas().size(); j++)      {

                                if(areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->GetOrgSus() > 0 & areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->GetDaysWithInf() == 0)     {

                                        areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->SetInf(1);

                                        areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->PushInfRecord(1);
                                }
                        }
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() < GetInfPeriod())  {

                        int inf = 0;

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate());

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() == GetInfPeriod() & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod());

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus())      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());;
                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() < GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()) - areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod() -1);

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus())      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() == GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

                        int rec2 = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()*2);

                        int rec =  (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()) + rec2) - areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod() -1);

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus())      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() > GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)     {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()-1) * GetInfPeriod();

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus())      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetMaxInf() == true)    {

                        int pastSus = areas.at(i)->GetSusRecord().at(areas.at(i)->GetSusRecord().size() - GetInfPeriod());

                        areas.at(i)->SetInf(pastSus);

                        areas.at(i)->SetRec(areas.at(i)->GetOrgSus() - areas.at(i)->GetInf());

                        areas.at(i)->SetSus(0);

                        areas.at(i)->PushSusRecord(0);
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetInf() > 0)   {

                                areas.at(i)->SetDaysWithInf(areas.at(i)->GetDaysWithInf() + 1);
                }
        }

        SetDayNum(GetDayNum() + 1);
}

void Sim::ConfigCloseSim()	{

        int minClose = 100;

        int availVac2 = GetAvailVac();

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetClose() < minClose)        {

                        minClose = areas.at(i)->GetClose();
                }
        }

        for(float j = 0; j < 10; j++)      {

                for(int i = 0; i < areas.size(); i++)  {

                        if(areas.at(i)->GetClose() == minClose + j)        {

                                if(availVac2 > areas.at(i)->GetPop() & availVac2 > 0)   {

                                        areas.at(i)->SetVac(areas.at(i)->GetPop());

                                        availVac2 = availVac2 - areas.at(i)->GetPop();

                                        continue;
                                }

                                if(availVac2 < areas.at(i)->GetPop() & availVac2 > 0)      {

                                        areas.at(i)->SetVac(availVac2);

                                        availVac2 = availVac2 - availVac2;
                                }
                        }
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetVac() == 0)  {

                        areas.at(i)->SetSus(areas.at(i)->GetPop() - areas.at(i)->GetInf());
                }

                else    {

                        areas.at(i)->SetSus(areas.at(i)->GetPop() - areas.at(i)->GetVac());
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                areas.at(i)->SetOrgSus(areas.at(i)->GetSus());
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetValue() == GetAreaStart())   {

                        areas.at(i)->SetInf(1);

                        areas.at(i)->PushInfRecord(1);

                        areas.at(i)->SetDaysWithInf(1);

			areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));
                }
        }
        SetDayNum(0);
}

void Sim::DegreeSim()	{

	if(GetDayNum() == 0)	{

		ConfigDegreeSim();

		cout << "DEGREE DISTRIBUTION" << endl;
	}

	cout << "Day " << GetDayNum() << endl;

	for(int i = 0; i < areas.size(); i++)  {

		cout << areas.at(i)->GetValue() << "  POP: " << areas.at(i)->GetPop() << "   S: " << areas.at(i)->GetSus();

		cout << "   I: " << areas.at(i)->GetInf() << "     R: " << areas.at(i)->GetRec() << "     V: " << areas.at(i)->GetVac() << endl;
	}

	int totalInf = 0;

	for(int i = 0; i < areas.size(); i++)  {

		 totalInf = totalInf + areas.at(i)->GetInf();

	}

	if(totalInf > GetDegPeak())	{

		SetDegPeak(totalInf);

		SetDegPeakDay(GetDayNum());
	}

	if(totalInf == 0 || GetDayNum() > 50)	{

		SetStopSim(true);

		SetDegDayEnd(GetDayNum());

                int totalRec = 0;

                for(int i = 0; i < areas.size(); i++)   {

                        totalRec = totalRec + areas.at(i)->GetRec();
                }

                SetDegTotalInf(totalRec);
	}

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetInf() > areas.at(i)->GetPop()/2)   {

                        for(int j = 0; j < areas.at(i)->GetAdjAreas().size(); j++)      {

                                if(areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->GetOrgSus() > 0 & areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->GetDaysWithInf() == 0)     {

                                        areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->SetInf(1);

                                        areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->PushInfRecord(1);
                                }
                        }
                }
        }

	for(int i = 0; i < areas.size(); i++)  {

		if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() < GetInfPeriod())	{

			int inf = 0;

			inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate());

			areas.at(i)->SetInf(inf);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

			areas.at(i)->PushInfRecord(inf);

			areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
		}

		if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() == GetInfPeriod() & areas.at(i)->GetMaxInf() == false)      {

			int inf = 0;

			int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod());

			inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

			areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());;
		}

		if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() < GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()) - areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod() -1);

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

			areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
		}

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() == GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

			int rec2 = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()*2);

                        int rec =  (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()) + rec2) - areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod() -1);

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

			areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() > GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)     {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()-1) * GetInfPeriod();

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

			if(inf > areas.at(i)->GetOrgSus() || inf < 0)	{

				areas.at(i)->SetMaxInf(true);

				continue;
			}

                        areas.at(i)->SetInf(inf);

			areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
                }
	}

	for(int i = 0; i < areas.size(); i++)  {

		if(areas.at(i)->GetMaxInf() == true)	{

			int pastSus = areas.at(i)->GetSusRecord().at(areas.at(i)->GetSusRecord().size() - GetInfPeriod());

                        areas.at(i)->SetInf(pastSus);

			areas.at(i)->SetRec(areas.at(i)->GetOrgSus() - areas.at(i)->GetInf());

                        areas.at(i)->SetSus(0);

                        areas.at(i)->PushSusRecord(0);
                }
	}

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetInf() > 0)   {

                                areas.at(i)->SetDaysWithInf(areas.at(i)->GetDaysWithInf() + 1);
                }
        }


	SetDayNum(GetDayNum() + 1);
}

void Sim::CalcDegree()	{

	for(int i = 0; i < areas.size(); i++)  {

		areas.at(i)->SetDegree(areas.at(i)->GetAdjAreas().size());
	}
}

void Sim::ConfigAreas()	{

	CalcDegree();
}

void Sim::ConfigDegreeSim()	{

	int maxDegree = 0;

	int availVac2 = GetAvailVac();

	for(int i = 0; i < areas.size(); i++)  {

		if(areas.at(i)->GetDegree() > maxDegree)	{

			maxDegree = areas.at(i)->GetDegree();
		}
	}

	for(int j = 0; j < maxDegree; j++)	{

		for(int i = 0; i < areas.size(); i++)  {

			if(areas.at(i)->GetDegree() == maxDegree - j)        {

				if(availVac2 > areas.at(i)->GetPop() & availVac2 > 0)	{

					areas.at(i)->SetVac(areas.at(i)->GetPop());

					availVac2 = availVac2 - areas.at(i)->GetPop();

					continue;
				}

				if(availVac2 < areas.at(i)->GetPop() & availVac2 > 0)      {

					areas.at(i)->SetVac(availVac2);

					availVac2 = availVac2 - availVac2;
				}
			}
		}
	}

        for(int i = 0; i < areas.size(); i++)  {

		if(areas.at(i)->GetVac() == 0)	{

                	areas.at(i)->SetSus(areas.at(i)->GetPop() - areas.at(i)->GetInf());
		}

		else	{

			areas.at(i)->SetSus(areas.at(i)->GetPop() - areas.at(i)->GetVac());
		}
        }

        for(int i = 0; i < areas.size(); i++)  {

		areas.at(i)->SetOrgSus(areas.at(i)->GetSus());
	}

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetValue() == GetAreaStart())   {

                        areas.at(i)->SetInf(1);

                        areas.at(i)->PushInfRecord(1);

                        areas.at(i)->SetDaysWithInf(1);

			areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));
                }
        }
	SetDayNum(0);
}

void Sim::SetDayNum(int dayNum)	{

	this->dayNum = dayNum;
}

int Sim::GetDayNum()	{

	return this->dayNum;
}

void Sim::SetStopSim(bool stopSim)	{

	this->stopSim = stopSim;
}

bool Sim::GetStopSim()	{

	return this-> stopSim;
}

void Sim::ResetAreas()	{

	for(int i = 0; i < areas.size(); i++)  {

		areas.at(i)->GetInfRecord().clear();

		areas.at(i)->GetSusRecord().clear();

		//areas.at(i)->GetRecRecord().clear();

		areas.at(i)->SetInf(0);

		areas.at(i)->SetDaysWithInf(0);

		areas.at(i)->SetOrgSus(0);

		areas.at(i)->SetSus(0);

		areas.at(i)->SetRec(0);

		areas.at(i)->SetVac(0);

		areas.at(i)->SetMaxInf(false);

		SetDayNum(0);

		SetStopSim(false);
	}
}

void Sim::ConfigRandSim()	{

        int availVac2 = GetAvailVac();

	//cout << GetAvailVac() << endl;

                for(int i = 0; i < areas.size(); i++)  {

                                if(availVac2 > areas.at(i)->GetPop() & availVac2 > 0)     {

                                        areas.at(i)->SetVac(areas.at(i)->GetPop());

                                        availVac2 = availVac2 - areas.at(i)->GetPop();

                                        continue;

					//cout << "test" << endl;
                                }

                                if(availVac2 < areas.at(i)->GetPop() & availVac2 > 0)      {

                                        areas.at(i)->SetVac(availVac2);

                                        availVac2 = availVac2 - availVac2;
                                }
                }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetVac() == 0)  {

                        areas.at(i)->SetSus(areas.at(i)->GetPop() - areas.at(i)->GetInf());
                }

                else    {

                        areas.at(i)->SetSus(areas.at(i)->GetPop() - areas.at(i)->GetVac());
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                areas.at(i)->SetOrgSus(areas.at(i)->GetSus());
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetValue() == GetAreaStart())   {

                        areas.at(i)->SetInf(1);

                        areas.at(i)->PushInfRecord(1);

                        areas.at(i)->SetDaysWithInf(1);

			areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));
                }
        }
        SetDayNum(0);
}

void Sim::RandSim()	{

        if(GetDayNum() == 0)    {

                ConfigRandSim();

                cout << "RANDOM DISTRIBUTION" << endl;
        }

        cout << "Day " << GetDayNum() << endl;

        for(int i = 0; i < areas.size(); i++)  {

                cout << areas.at(i)->GetValue() << "  POP: " << areas.at(i)->GetPop() << "   S: " << areas.at(i)->GetSus();

                cout << "   I: " << areas.at(i)->GetInf() << "     R: " << areas.at(i)->GetRec() << "     V: " << areas.at(i)->GetVac() << endl;
        }

        int totalInf = 0;

        for(int i = 0; i < areas.size(); i++)  {

                 totalInf = totalInf + areas.at(i)->GetInf();

        }

        if(totalInf > GetRandPeak() & GetDayNum() > 0)     {

                SetRandPeak(totalInf);

                SetRandPeakDay(GetDayNum());
        }

        if((totalInf == 0 || GetDayNum() > 50) & GetDayNum() > 0)   {

                SetStopSim(true);

                SetRandDayEnd(GetDayNum());

                int totalRec = 0;

                for(int i = 0; i < areas.size(); i++)   {

                        totalRec = totalRec + areas.at(i)->GetRec();
                }

                SetRandTotalInf(totalRec);
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetInf() > areas.at(i)->GetPop()/2)   {

                        for(int j = 0; j < areas.at(i)->GetAdjAreas().size(); j++)      {

                                if(areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->GetOrgSus() > 0 & areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->GetDaysWithInf() == 0)     {

                                        areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->SetInf(1);

                                        areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->PushInfRecord(1);
                                }
                        }
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() < GetInfPeriod())  {

                        int inf = 0;

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate());

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() == GetInfPeriod() & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod());

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());;
                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() < GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()) - areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod() -1);

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() == GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

                        int rec2 = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()*2);

                        int rec =  (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()) + rec2) - areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod() -1);

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() > GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)     {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()-1) * GetInfPeriod();

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        areas.at(i)->PushSusRecord(areas.at(i)->GetSus());
                }
        }

        //for(int i = 0; i < areas.size(); i++)  {

              //  if(areas.at(i)->GetInf() > 0)   {

            //                    areas.at(i)->SetDaysWithInf(areas.at(i)->GetDaysWithInf() + 1);
          //      }
        //}

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetMaxInf() == true)    {

                        int pastSus = areas.at(i)->GetSusRecord().at(areas.at(i)->GetSusRecord().size() - GetInfPeriod());

                        areas.at(i)->SetInf(pastSus);

                        areas.at(i)->SetRec(areas.at(i)->GetOrgSus() - areas.at(i)->GetInf());

                        areas.at(i)->SetSus(0);

                        areas.at(i)->PushSusRecord(0);
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetInf() > 0)   {

                                areas.at(i)->SetDaysWithInf(areas.at(i)->GetDaysWithInf() + 1);
                }
        }


        SetDayNum(GetDayNum() + 1);
}

void Sim::SetDegPeak(int degPeak)	{

	this -> degPeak = degPeak;
}

void Sim::SetDegPeakDay(int degPeakDay)	{

	this-> degPeakDay = degPeakDay;
}

void Sim::SetDegDayEnd(int degDayEnd)	{

	this-> degDayEnd = degDayEnd;
}

void Sim::SetDegTotalInf(int degTotalInf)	{

	this-> degTotalInf = degTotalInf;
}

int Sim::GetDegPeak()	{

	return this-> degPeak;
}

int Sim::GetDegPeakDay()	{

	return this-> degPeakDay;
}

int Sim::GetDegDayEnd()	{

	return this-> degDayEnd;
}

int Sim::GetDegTotalInf()	{

	return this-> degTotalInf;
}

void Sim::SetRandPeak(int randPeak)       {

        this -> randPeak = randPeak;
}

void Sim::SetRandPeakDay(int randPeakDay) {

        this-> randPeakDay = randPeakDay;
}

void Sim::SetRandDayEnd(int randDayEnd)   {

        this-> randDayEnd = randDayEnd;
}

void Sim::SetRandTotalInf(int randTotalInf)       {

        this-> randTotalInf = randTotalInf;
}

int Sim::GetRandPeak()   {

        return this-> randPeak;
}

int Sim::GetRandPeakDay()        {

        return this-> randPeakDay;
}

int Sim::GetRandDayEnd() {

        return this-> randDayEnd;
}

int Sim::GetRandTotalInf()       {

        return this-> randTotalInf;
}

void Sim::SetEqPeak(int eqPeak)       {

        this -> eqPeak = eqPeak;
}

void Sim::SetEqPeakDay(int eqPeakDay) {

        this-> eqPeakDay = eqPeakDay;
}

void Sim::SetEqDayEnd(int eqDayEnd)   {

        this-> eqDayEnd = eqDayEnd;
}

void Sim::SetEqTotalInf(int eqTotalInf)       {

        this-> eqTotalInf = eqTotalInf;
}

int Sim::GetEqPeak()   {

        return this-> eqPeak;
}

int Sim::GetEqPeakDay()        {

        return this-> eqPeakDay;
}

int Sim::GetEqDayEnd() {

        return this-> eqDayEnd;
}

int Sim::GetEqTotalInf()       {

        return this-> eqTotalInf;
}

void Sim::PrintResults()	{

        cout << "Using the closeness centrality distribution method, the peak number of infected was " << GetClosePeak() << " on day " << GetClosePeakDay() << ". The outbreak ended on day " << GetCloseDayEnd() << " and the total number of infected individuals was " << GetCloseTotalInf() << "." << endl;

	cout << "Using the degree centrality distribution method, the peak number of infected was " << GetDegPeak() << " on day " << GetDegPeakDay() << ". The outbreak ended on day " << GetDegDayEnd() << " and the total number of infected individuals was " << GetDegTotalInf() << "." << endl;

        cout << "Using the random centrality distribution method, the peak number of infected was " << GetRandPeak() << " on day " << GetRandPeakDay() << ". The outbreak ended on day " << GetRandDayEnd() << " and the total number of infected individuals was " << GetRandTotalInf() << "." << endl;

        cout << "Using the equal centrality distribution method, the peak number of infected was " << GetEqPeak() << " on day " << GetEqPeakDay() << ". The outbreak ended on day " << GetEqDayEnd() << " and the total number of infected individuals was " << GetEqTotalInf() << "." << endl;

}

void Sim::ConfigEqSim()	{

        int availVac2 = GetAvailVac();

        while(availVac2 > 0)	{

                for(int i = 0; i < areas.size(); i++)  {

                                if(areas.at(i)->GetVac() < areas.at(i)->GetPop() & availVac2 > 0)     {

                                        areas.at(i)->SetVac(areas.at(i)->GetVac() + 1);

                                        availVac2--;

                                        continue;

                                        //cout << "test" << endl;
                                }
                }
	}

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetVac() == 0)  {

                        areas.at(i)->SetSus(areas.at(i)->GetPop() - areas.at(i)->GetInf());
                }

                else    {

                        areas.at(i)->SetSus(areas.at(i)->GetPop() - areas.at(i)->GetVac());
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                areas.at(i)->SetOrgSus(areas.at(i)->GetSus());

		//cout << areas.at(i)->GetOrgSus() << endl;
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetValue() == GetAreaStart())   {

                        areas.at(i)->SetInf(1);

                        areas.at(i)->PushInfRecord(1);

                        areas.at(i)->SetDaysWithInf(1);

			areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));
                }
        }
        SetDayNum(0);
}



void Sim::EqSim()	{

        if(GetDayNum() == 0)    {

                ConfigEqSim();

                cout << "EQUAL DISTRIBUTION" << endl;
        }

        cout << "Day " << GetDayNum() << endl;

        for(int i = 0; i < areas.size(); i++)  {

                cout << areas.at(i)->GetValue() << "  POP: " << areas.at(i)->GetPop() << "   S: " << areas.at(i)->GetSus();

                cout << "   I: " << areas.at(i)->GetInf() << "     R: " << areas.at(i)->GetRec() << "     V: " << areas.at(i)->GetVac() << endl;
        }

        int totalInf = 0;

        for(int i = 0; i < areas.size(); i++)  {

                 totalInf = totalInf + areas.at(i)->GetInf();

        }

        if(totalInf > GetEqPeak() & GetDayNum() > 2 )     {

                SetEqPeak(totalInf);

                SetEqPeakDay(GetDayNum());
        }

        if(totalInf == 0 || GetDayNum() > 50)   {

                SetStopSim(true);

                SetEqDayEnd(GetDayNum());

                int totalRec = 0;

                for(int i = 0; i < areas.size(); i++)   {

                        totalRec = totalRec + areas.at(i)->GetRec();
                }

                SetEqTotalInf(totalRec);
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetInf() > areas.at(i)->GetPop()/2)   {

                        for(int j = 0; j < areas.at(i)->GetAdjAreas().size(); j++)      {

                                if(areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->GetOrgSus() > 0 & areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->GetDaysWithInf() == 0)     {

                                        areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->SetInf(1);

                                        areas.at(areas.at(i)->GetAdjAreas().at(j) - 1)->PushInfRecord(1);
                                }
                        }
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() < GetInfPeriod() & areas.at(i)->GetMaxInf() == false)  {

                        int inf = 0;

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate());

                        areas.at(i)->SetInf(inf);

			areas.at(i)->PushSusRecord(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        //areas.at(i)->PushSusRecord(areas.at(i)->GetSus());

			continue;

                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() == GetInfPeriod() & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod());

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

			if(areas.at(i)->GetMaxInf() == false)	{

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

			areas.at(i)->PushSusRecord(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        //areas.at(i)->PushSusRecord(areas.at(i)->GetSus());

                        continue;

			}

                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() < GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()) - areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod() -1);

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        if(areas.at(i)->GetMaxInf() == false)   {

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

			areas.at(i)->PushSusRecord(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        //areas.at(i)->PushSusRecord(areas.at(i)->GetSus());

                        continue;
			}

                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() == GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)      {

                        int inf = 0;

                        int rec2 = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()*2);

                        int rec =  (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()) + rec2) - areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod() -1);

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        if(areas.at(i)->GetMaxInf() == false)   {

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

			areas.at(i)->PushSusRecord(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        //areas.at(i)->PushSusRecord(areas.at(i)->GetSus());

                        continue;
			}

                }

                if(areas.at(i)->GetDaysWithInf() > 0 & areas.at(i)->GetDaysWithInf() > GetInfPeriod() & areas.at(i)->GetDaysWithInf() > GetInfPeriod()*2 & areas.at(i)->GetMaxInf() == false)     {

                        int inf = 0;

                        int rec =  areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()- GetInfPeriod()-1) * GetInfPeriod();

                        inf = areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) + (areas.at(i)->GetInfRecord().at(areas.at(i)->GetDaysWithInf()-1) * GetContRate()) - rec;

                        if(inf > areas.at(i)->GetOrgSus() || inf < 0)      {

                                areas.at(i)->SetMaxInf(true);

                                continue;
                        }

                        if(areas.at(i)->GetMaxInf() == false)   {

                        areas.at(i)->SetInf(inf);

                        areas.at(i)->SetRec(areas.at(i)->GetRec() + rec);

			areas.at(i)->PushSusRecord(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->SetSus(areas.at(i)->GetOrgSus()-(areas.at(i)->GetInf() + areas.at(i)->GetRec()));

                        areas.at(i)->PushInfRecord(inf);

                        //areas.at(i)->PushSusRecord(areas.at(i)->GetSus());

                        continue;
			}
                }
        }


        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetMaxInf() == true)    {

			//for(int j = 0; j < areas.at(i)->GetSusRecord().size(); j++)	{

				//cout <<  areas.at(i)->GetSusRecord().at(j) << endl;
			//}

                        int pastSus = areas.at(i)->GetSusRecord().at(areas.at(i)->GetSusRecord().size() - GetInfPeriod());

                        areas.at(i)->SetInf(pastSus);

                        areas.at(i)->SetRec(areas.at(i)->GetOrgSus() - areas.at(i)->GetInf());

                        areas.at(i)->SetSus(0);

                        areas.at(i)->PushSusRecord(0);
                }
        }

        for(int i = 0; i < areas.size(); i++)  {

                if(areas.at(i)->GetInf() > 0)   {

                                areas.at(i)->SetDaysWithInf(areas.at(i)->GetDaysWithInf() + 1);
                }
        }


        SetDayNum(GetDayNum() + 1);
}

void Sim::SetClosePeak(int closePeak)       {

        this -> closePeak = closePeak;
}

void Sim::SetClosePeakDay(int closePeakDay) {

        this-> closePeakDay = closePeakDay;
}

void Sim::SetCloseDayEnd(int closeDayEnd)   {

        this-> closeDayEnd = closeDayEnd;
}

void Sim::SetCloseTotalInf(int closeTotalInf)       {

        this-> closeTotalInf = closeTotalInf;
}

int Sim::GetClosePeak()   {

        return this-> closePeak;
}

int Sim::GetClosePeakDay()        {

        return this-> closePeakDay;
}

int Sim::GetCloseDayEnd() {

        return this-> closeDayEnd;
}

int Sim::GetCloseTotalInf()       {

        return this-> closeTotalInf;
}

