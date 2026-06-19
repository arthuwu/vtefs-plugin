#pragma once
#include "EuroScopePlugIn.h"
#include <sstream>
#include <iostream>
#include <string>
#include "constants.hpp"

using namespace std;
using namespace EuroScopePlugIn;

class TEFSPlugin :
	public EuroScopePlugIn::CPlugIn
{
public:
	TEFSPlugin();

	~TEFSPlugin();

	virtual void OnFlightPlanControllerAssignedDataUpdate(CFlightPlan FlightPlan, int DataType);

	virtual void OnFlightPlanFlightPlanDataUpdate(CFlightPlan FlightPlan);

	virtual void OnFlightPlanDisconnect(CFlightPlan FlightPlan);

	virtual void OnFlightPlanFlightStripPushed(CFlightPlan FlightPlan, const char* sSenderController, const char* sTargetController);

	virtual void OnTimer(int Count);

	virtual void OnAirportRunwayActivityChanged();
};
