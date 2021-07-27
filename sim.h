#include "cell.h"
#include "area.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;


class Sim	{

	private:

		string configFile;
		string popFile;
		string regionFile;
		int areaStart;
		int infPeriod;
		int contRate;
		int availVac;
		int rows;
		int cols;
		int dayNum;
		bool stopSim;
		vector <Cell*> region;
		vector <Area*> areas;
		int degPeak;
		int degPeakDay;
		int degDayEnd;
		int degTotalInf;
                int randPeak;
                int randPeakDay;
                int randDayEnd;
                int randTotalInf;
                int eqPeak;
                int eqPeakDay;
                int eqDayEnd;
                int eqTotalInf;
                int closePeak;
                int closePeakDay;
                int closeDayEnd;
                int closeTotalInf;


	public:

		Sim();
		void SetConfigFile(string configFile);
		void SetPopFile(string popFile);
		void SetRegionFile(string regionFile);
		void SetAreaStart(int areaStart);
		void SetInfPeriod(int infPeriod);
		void SetContRate(int contRate);
		void SetAvailVac(int availVac);
		string GetConfigFile();
		string GetPopFile();
		string GetRegionFile();
		int GetAreaStart();
		int GetInfPeriod();
		int GetContRate();
		int GetAvailVac();
		void Config();
		void ConfigPops();
		void SetRows(int rows);
		void SetCols(int cols);
		int GetRows();
		int GetCols();
		void ConfigRegion();
		void SetCords();
		void PrintCords();
		void SetAreaAdj();
		void PrintAdjList();
		void PrintAreaPops();
		void CalcClose();
		void DegreeSim();
		void CalcDegree();
		void ConfigAreas();
		void ConfigDegreeSim();
		void SetDayNum(int dayNum);
		int GetDayNum();
		void SetStopSim(bool stopSim);
		bool GetStopSim();
		void ResetAreas();
                void ConfigRandSim();
		void RandSim();
		void SetDegPeak(int degPeak);
		void SetDegPeakDay(int degPeakDay);
		void SetDegDayEnd(int degDayEnd);
		void SetDegTotalInf(int degTotalInf);
                int GetDegPeak();
                int GetDegPeakDay();
                int GetDegDayEnd();
                int GetDegTotalInf();
		void PrintResults();
                void SetRandPeak(int randPeak);
                void SetRandPeakDay(int randPeakDay);
                void SetRandDayEnd(int randDayEnd);
                void SetRandTotalInf(int randTotalInf);
                int GetRandPeak();
                int GetRandPeakDay();
                int GetRandDayEnd();
                int GetRandTotalInf();
                void SetEqPeak(int eqPeak);
                void SetEqPeakDay(int eqPeakDay);
                void SetEqDayEnd(int eqDayEnd);
                void SetEqTotalInf(int eqTotalInf);
                int GetEqPeak();
                int GetEqPeakDay();
                int GetEqDayEnd();
                int GetEqTotalInf();
		void ConfigEqSim();
                void EqSim();
                void SetClosePeak(int closePeak);
                void SetClosePeakDay(int closePeakDay);
                void SetCloseDayEnd(int closeDayEnd);
                void SetCloseTotalInf(int closeTotalInf);
                int GetClosePeak();
                int GetClosePeakDay();
                int GetCloseDayEnd();
                int GetCloseTotalInf();
		void ConfigCloseSim();
                void CloseSim();


};


