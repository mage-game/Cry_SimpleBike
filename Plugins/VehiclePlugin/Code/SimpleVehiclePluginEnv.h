#pragma once
#include "CrySchematyc/Env/IEnvRegistry.h"
#include "CrySchematyc/Env/Elements/EnvComponent.h"

#define TITLE "[SimpleVehiclePlugin] "

#define Log(...) do {  CryLog (TITLE __VA_ARGS__); } while(0)
#define LogAlways(...) do { CryLogAlways (TITLE __VA_ARGS__); } while(0)
#define LogWarning(...) do { CryWarning(VALIDATOR_MODULE_RENDERER, VALIDATOR_WARNING, TITLE __VA_ARGS__); } while(0)
#define LogError(...) do { CryWarning(VALIDATOR_MODULE_RENDERER, VALIDATOR_ERROR, TITLE __VA_ARGS__); } while(0)

#define AUTO_REGISTER_COMPONENT(classname)\
static void Register##classname(Schematyc::IEnvRegistrar& registrar)\
{  \
	Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID()); \
	{ \
		Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(classname));\
	}\
}\
CRY_STATIC_AUTO_REGISTER_FUNCTION(&Register##classname)
