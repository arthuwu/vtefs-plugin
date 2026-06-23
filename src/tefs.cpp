#include "stdafx.h"
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")
#include "tefs.hpp"

TEFSPlugin* tefsPlugin = NULL;

void    __declspec (dllexport)    EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** ppPlugInInstance)
{
	*ppPlugInInstance = tefsPlugin = new TEFSPlugin();
}

TEFSPlugin::TEFSPlugin() : CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE, MY_PLUGIN_NAME, MY_PLUGIN_VERSION, MY_PLUGIN_DEVELOPER, MY_PLUGIN_COPYRIGHT) {
	DisplayUserMessage("vTEFS", "vTEFS", "Hello world!", true, true, false, false, false);
	ws = new WebSocketManager();
}

TEFSPlugin::~TEFSPlugin() {
	ws->Stop();
	delete ws;
}

void TEFSPlugin::InitSocket() {
	ws->Start();

	ws->Subscribe("send_chat", [this](const std::string& rawMessage) {
		OutputDebugStringA("called\n");
		SubTest();
		});
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

bool TEFSPlugin::OnCompileCommand(const char* sCommandLine) {
	if (strcmp(sCommandLine, ".tefs up") == 0) {
		DisplayUserMessage("vTEFS", "vTEFS", "vTEFS websocket starting...", true, true, false, false, false);
		try {
			InitSocket();
		}
		catch (...) {
			DisplayUserMessage("vTEFS", "vTEFS", "vTEFS websocket failed to start", true, true, false, false, false);
		}
		return true;
	}
	else if (strcmp(sCommandLine, ".tefs send") == 0) {
		ws->BroadcastEvent("test_event", "test payload");
		DisplayUserMessage("vTEFS", "vTEFS", "message sent", true, true, false, false, false);
	}
	else {
		return false;
	}
}

void TEFSPlugin::SubTest() {
	DisplayUserMessage("vTEFS", "vTEFS", "subTest", true, true, false, false, false);
}

void    __declspec (dllexport)    EuroScopePlugInExit(void)
{
	delete tefsPlugin;
}
