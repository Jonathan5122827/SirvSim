
#include <vector>

using namespace std;

class Area	{

	private:

		int value;
		int  close;
		int degree;
		int pop;
		int sus;
		int inf;
		int rec;
		int vac;
		int daysWithInf;
		int daysWithRec;
		int orgSus;
		bool maxInf;
		vector <int> adjAreas;
		vector <int> infRecord;
                vector <int> susRecord;

	public:

		Area();
		void SetValue(int value);
		void SetClose(int close);
		void SetDegree(int degree);
		void SetPop(int pop);
		void SetSus(int sus);
		void SetInf(int inf);
		void SetRec(int rec);
		void SetVac(int vac);
		void SetDaysWithInf(int daysWithInf);
		int GetValue();
		int GetClose();
		int GetDegree();
		int GetPop();
		int GetSus();
		int GetInf();
		int GetRec();
		int GetVac();
		int GetDaysWithInf();
		vector <int> GetAdjAreas();
		vector <int> GetInfRecord();
		void PushAdjAreas(int adjArea);
		void PushInfRecord(int infRecord);
		void SetDaysWithRec(int daysWithRec);
		int GetDaysWithRec();
		void SetOrgSus(int orgSus);
		int GetOrgSus();
		void SetMaxInf(bool maxInf);
		bool GetMaxInf();
		void PushSusRecord(int susRecord);
		vector <int> GetSusRecord();
};
