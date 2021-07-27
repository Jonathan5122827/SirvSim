#include "sim.h"

int main()	{

	Sim state; // Creates sim class object

	state.Config(); // configures object

	state.ConfigPops();

	state.ConfigRegion();

	state.PrintAreaPops();

	state.PrintAdjList();

        while(state.GetStopSim() != true)       {	//each sim runs till bool value in sim gets set to true

                state.CloseSim();
        }

        state.ResetAreas();

	cout << endl;

	while(state.GetStopSim() != true)	{

		state.DegreeSim();
	}

	state.ResetAreas();

	cout << endl;

	while(state.GetStopSim() != true)  {

                state.RandSim();
        }

        state.ResetAreas();

	cout << endl;

        while(state.GetStopSim() != true)  {

                state.EqSim();
        }

	cout << endl;

	state.PrintResults();	//prints results of the sim

	return 0;
}
