#include "stdafx.h"
#include "EuroScopePlugIn.h"
#include "tefs.hpp"

TEFSPlugin* tefsPlugin = NULL;

void    __declspec (dllexport)    EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** ppPlugInInstance)
{
	// create the instance
	*ppPlugInInstance = tefsPlugin = new TEFSPlugin();
}

TEFSPlugin::TEFSPlugin() : CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE, MY_PLUGIN_NAME, MY_PLUGIN_VERSION, MY_PLUGIN_DEVELOPER, MY_PLUGIN_COPYRIGHT) {
	DisplayUserMessage("TEFS", "TEFS", "Hello world!", true, true, false, false, false);
}

TEFSPlugin::~TEFSPlugin() {
	// delete instances here
}

void TEFSPlugin::OnFlightPlanControllerAssignedDataUpdate(CFlightPlan FlightPlan, int DataType) {
}

void TEFSPlugin::OnFlightPlanFlightPlanDataUpdate(CFlightPlan FlightPlan) {
}

void TEFSPlugin::OnTimer(int Count) {
}

void TEFSPlugin::OnFlightPlanDisconnect(CFlightPlan FlightPlan) {
}

void TEFSPlugin::OnFlightPlanFlightStripPushed(CFlightPlan FlightPlan, const char* sSenderController, const char* sTargetController) {
}

void TEFSPlugin::OnAirportRunwayActivityChanged() {
}

void    __declspec (dllexport)    EuroScopePlugInExit(void)
{
	delete gpMyPlugin;
}
