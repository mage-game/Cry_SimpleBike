#include "StdAfx.h"
#include "PluginDll.h"

#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CrySchematyc/Env/IEnvRegistry.h>
#include <CrySchematyc/Env/EnvPackage.h>
#include <CrySchematyc/Utils/SharedString.h>
												
// Included only once per DLL module.
#include <CryCore/Platform/platform_impl.inl>

namespace SimpleVehicle
{
	CPlugin_Vehicle::~CPlugin_Vehicle()
	{
		if (gEnv->pSchematyc)
		{
			gEnv->pSchematyc->GetEnvRegistry().DeregisterPackage(CPlugin_Vehicle::GetCID());
		}
		gEnv->pSystem->GetISystemEventDispatcher()->RemoveListener(this);
	}

	bool CPlugin_Vehicle::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
	{
		gEnv->pSystem->GetISystemEventDispatcher()->RegisterListener(this, "CPlugin_SimpleVehicle");

		return true;
	}

	void CPlugin_Vehicle::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
	{
		switch (event)
		{
		case ESYSTEM_EVENT_REGISTER_SCHEMATYC_ENV:
		{
			// Register all components that belong to this plug-in
			auto staticAutoRegisterLambda = [this](Schematyc::IEnvRegistrar& registrar)
			{
				// Call all static callback registered with the CRY_STATIC_AUTO_REGISTER_WITH_PARAM
				Detail::CStaticAutoRegistrar<Schematyc::IEnvRegistrar&>::InvokeStaticCallbacks(registrar);

			};

			if (gEnv->pSchematyc)
			{
				gEnv->pSchematyc->GetEnvRegistry().RegisterPackage(
					stl::make_unique<Schematyc::CEnvPackage>(
						CPlugin_Vehicle::GetCID(),
						"EntityComponents",
						"Crytek GmbH",
						"Components",
						staticAutoRegisterLambda
						)
				);
			}
		}
		break;
		}
	}

	CRYREGISTER_SINGLETON_CLASS(CPlugin_Vehicle)
}
