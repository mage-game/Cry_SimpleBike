#pragma once

#include <CrySystem/ICryPlugin.h>
    
namespace SimpleVehicle
{
	class CPlugin_Vehicle
		: public Cry::IEnginePlugin
		, public ISystemEventListener
	{
		CRYINTERFACE_SIMPLE(Cry::IEnginePlugin)
		CRYGENERATE_SINGLETONCLASS_GUID(CPlugin_Vehicle, "Plugin_SimpleVehicle", "8D9AAE27-9F87-4c3c-AB83-E99984A35AED"_cry_guid)

		PLUGIN_FLOWNODE_REGISTER
		PLUGIN_FLOWNODE_UNREGISTER

		virtual ~CPlugin_Vehicle();

	public:
		//! Retrieve name of plugin.
		virtual const char* GetName() const override { return "SimpleVehicle"; }
		//! Retrieve category for the plugin.
		virtual const char* GetCategory() const override { return "Plugin"; }
		//! This is called to initialize the new plugin.
		virtual bool Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams) override;

		// ISystemEventListener
		virtual void OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;
		// ~ISystemEventListener

	};
}
