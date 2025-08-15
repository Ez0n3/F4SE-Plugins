// User Defines
#include "config.h"
// F4SE
#include "f4se/GameAPI.h"
#include "f4se/PluginAPI.h"
#include "f4se/PapyrusNativeFunctions.h"
#include "f4se_common/SafeWrite.h"
// Windows
#include <shlobj.h>	// CSIDL_MYCODUMENTS

// ================================
// Handles
// ================================

// Handle for the plugin
PluginHandle g_pluginHandle = kPluginHandle_Invalid;

// Handle for the papyrus interface
static F4SEPapyrusInterface* g_papyrus = NULL;

// Handle for other things...

/* // Uncomment to use messaging
// Handle for the messaging interface
static F4SEMessagingInterface* g_messaging = NULL;
*/

// ================================
// User Code
// ================================

// Example namespace and test bool function to print Hello World!
namespace Plugin_Example_Functions
{
	bool Test(StaticFunctionTag *base)
	{
		_MESSAGE("Hello World!"); // print to the plugin log
		Console_Print("Hello Console!"); // print to the in-game console
		return true;
	}
}

// Register the function(s) in the Plugin_Example_Functions namespace
bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		// EzF4seTestClass is defined in: .\Data\Scripts\Source\EzF4seTestClass.psc
		new NativeFunction0 <StaticFunctionTag, bool>("Test", "EzF4seTestClass", Plugin_Example_Functions::Test, vm));
	
	return true; // return false if something goes wrong, EG: if doing other stuff
}

// ================================
// Plugin Listener
// ================================

/* // Uncomment to use messaging
// Listener for the plugin
static void PluginListener(F4SEMessagingInterface::Message* msg) noexcept
{
	switch (msg->type) {
		// case F4SEMessagingInterface::kMessage_PostLoad:
		case F4SEMessagingInterface::kMessage_PostPostLoad:
		{
			_MESSAGE("PluginListener: kMessage_PostPostLoad");
			break;
		}
		// case F4SEMessagingInterface::kMessage_PreLoadGame:
		// case F4SEMessagingInterface::kMessage_PostLoadGame:
		// case F4SEMessagingInterface::kMessage_PreSaveGame:
		// case F4SEMessagingInterface::kMessage_PostSaveGame:
		// case F4SEMessagingInterface::kMessage_DeleteGame:
		// case F4SEMessagingInterface::kMessage_InputLoaded:
		// case F4SEMessagingInterface::kMessage_NewGame:
		// case F4SEMessagingInterface::kMessage_GameLoaded:
		// case F4SEMessagingInterface::kMessage_GameDataReady:
	}
}
*/

// ================================
// Plugin Compatibility Check
// ================================

// Check that the runtime and plugin versions are compatible
const bool IsCompatible(const F4SEInterface* f4se)
{
	// disable the plugin if it's in the editor
	if (f4se->isEditor) {
		_MESSAGE("ERROR::IsCompatible: Plugin is not compatible with the editor, disabling");
		_FATALERROR("ERROR::IsCompatible: Plugin is not compatible with the editor, disabling");
		return false;
	}
	// check for compatible version. if strict=true, runtime and supported versions must match. if strict=false, runtime version must be above the minimum
	else if (!IVersionCheck::IsCompatibleVersion(f4se->runtimeVersion, MINIMUM_RUNTIME_VERSION, SUPPORTED_RUNTIME_VERSION, SUPPORTED_RUNTIME_VERSION_STRICT)) { // not strict
		_MESSAGE("ERROR::IsCompatible: Plugin is not compatible with runtime version, disabling");
		_FATALERROR("ERROR::IsCompatible: Plugin is not compatible with runtime version, disabling");
		
		// not compatible
		return false;
	}
	
	// compatible
	return true;
}

// ================================
// Plugin Export, Query and Load - Start Extern-C
// ================================

extern "C" { // Start: extern "C"

// ================================
// Plugin Version Data - Not Used In All SE SDK's
// ================================

// Export the plugin version data to f4se, without this the plugin will fail to load. See: PluginAPI.h
__declspec(dllexport) F4SEPluginVersionData F4SEPlugin_Version =
{
	F4SEPluginVersionData::kVersion, // f4se expects plugin version info to follow this structure
	
	PLUGIN_VERSION_DLL,		// set in config.h
	PLUGIN_NAME_LONG, 		// set in config.h
	PLUGIN_AUTHOR, 			// set in config.h

	0,	// not version independent
	0,	// not version independent (extended field)
	
	// { RUNTIME_VERSION_1_10_980, 0 },	// compatible with 1.10.980 // NextGen
	// { RUNTIME_VERSION_1_10_984, 0 }, // compatible with NextGen plus Hotfix, See: f4se_version.h
	{ SUPPORTED_RUNTIME_VERSION, 0 }, // set in config.h
	
	0,	// works with any version of the script extender. you probably do not need to put anything here
	
	// 0, 0, 0
};

// ================================
// Plugin Query - Not Used In All SE SDK's
// ================================

// F4SE Plugin Query - Called when the plugin is queried
bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info)
{
	// open the plugin log file
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE);
	
	_MESSAGE(PLUGIN_VERSION_INFO); // write the plugin version to the log
	_MESSAGE("Plugin_Query: Querying");

	// populate info structure
	info->infoVersion =	PluginInfo::kInfoVersion;
	info->name =		PLUGIN_NAME_LONG;		// set in config.h
	info->version =		PLUGIN_VERSION_DLL;		// set in config.h
	
	// check for compatible versions
	if (!IsCompatible(f4se)) {
		_MESSAGE("ERROR::Plugin_Query: Incompatible | Disabling Plugin");
		_FATALERROR("ERROR::Plugin_Query: Incompatible | Disabling Plugin");
		// incompatible
		return false;
	}
	
	// ######################################################
	// Note: Nothing should be assigned below this point
	// Get the necessary info about the plugin and return
	// ######################################################
	
	_MESSAGE("Plugin_Query: Queried Successfully"); // log the successful query

	// supported runtime version
	return true;
}

// ================================
// Plugin Preload - Not Used In All SE SDK's
// ================================

/*
// If your plugin needs to make modifications before global initializers, add and export this:
// Note: Game and N4SE functionality may be limited during preload
bool F4SEPlugin_Preload(const F4SEInterface* f4se)
{
	_MESSAGE("Plugin_Preload: Preloading");
	
	// User Code
	
	_MESSAGE("Plugin_Preload: Preloaded");
	
	return true;
}
*/

// ================================
// Plugin Load - Used In All SE SDK's
// ================================

// F4SE Plugin Load - Called when the plugin loads everytime
bool F4SEPlugin_Load(const F4SEInterface* f4se)
{
	// open the plugin log file
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE);

	_MESSAGE(PLUGIN_VERSION_INFO); // write the plugin version to the log
	_MESSAGE("Plugin_Load: Loading");
	
	// check for compatible versions
	if (!IsCompatible(f4se)) {
		_MESSAGE("ERROR::Plugin_Load: Incompatible | Disabling Plugin");
		_FATALERROR("ERROR::Plugin_Load: Incompatible | Disabling Plugin");
		// incompatible
		return false;
	}
	
	// store plugin handle for later
	g_pluginHandle = f4se->GetPluginHandle();
	
	// try to get the papyrus interface or disable if it's unable
	g_papyrus = (F4SEPapyrusInterface *)f4se->QueryInterface(kInterface_Papyrus);
	if (!g_papyrus) {
		_MESSAGE("ERROR::Plugin_Load: Could not get the papyrus interface, disabling");
		_FATALERROR("ERROR::Plugin_Load: Could not get the papyrus interface, disabling");
		return false;
	}
	
	// register the new functions
	if (g_papyrus->Register(RegisterFuncs)) {
		_MESSAGE("Plugin_Load: Functions Registered");
	}
	
	/* // Uncomment to use messaging
	// register the listener
	g_messaging = (F4SEMessagingInterface*)f4se->QueryInterface(kInterface_Messaging); // static_cast<F4SEMessagingInterface*>(f4se->QueryInterface(1))
	if (g_messaging) {
		if (g_messaging->RegisterListener(g_pluginHandle, "F4SE", PluginListener)) {
			_MESSAGE("Plugin_Load: Listener Registered");
		}
	}
	*/
	
	_MESSAGE("Plugin_Load: Loaded Successfully"); // log the successful load

	// initialized
	return true;
}

}; // Stop: extern "C"

// ================================
