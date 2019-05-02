cmake_minimum_required (VERSION 3.6.2)
set(CRYENGINE_DIR "D:/Program Files (x86)/Crytek/CRYENGINE Launcher/Crytek/CRYENGINE_5.5")
set(TOOLS_CMAKE_DIR "${CRYENGINE_DIR}/Tools/CMake")

set(PROJECT_BUILD 1)
set(PROJECT_DIR "${CMAKE_SOURCE_DIR}/../")

include("${TOOLS_CMAKE_DIR}/CommonOptions.cmake")

add_subdirectory("${CRYENGINE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/CRYENGINE")

include("${TOOLS_CMAKE_DIR}/Configure.cmake")
start_sources()

sources_platform(ALL)
add_sources("Code_uber.cpp"
    PROJECTS VehiclePlugin
    SOURCE_GROUP "Root"
		"PluginDll.cpp"
		"StdAfx.cpp"
		"PluginDll.h"
		"SimpleVehiclePluginEnv.h"
		"StdAfx.h"
)
add_sources("Common_uber.cpp"
    PROJECTS VehiclePlugin
    SOURCE_GROUP "Common"
)
add_sources("Animation_uber.cpp"
    PROJECTS VehiclePlugin
    SOURCE_GROUP "Common\\\\Animation"
		"Common/Animation/ManualAnimation.cpp"
		"Common/Animation/ManualAnimation.h"
)
add_sources("Components_uber.cpp"
    PROJECTS VehiclePlugin
    SOURCE_GROUP "Common\\\\Components"
		"Common/Components/LocalBikeComponent.cpp"
		"Common/Components/NetBikeComponent.cpp"
		"Common/Components/LocalBikeComponent.h"
		"Common/Components/NetBikeComponent.h"
)
add_sources("Movements_uber.cpp"
    PROJECTS VehiclePlugin
    SOURCE_GROUP "Common\\\\Movements"
		"Common/Movements/LocalBikeMovement.cpp"
		"Common/Movements/NetBikeMovement.cpp"
		"Common/Movements/BikeMovementBase.h"
		"Common/Movements/LocalBikeMovement.h"
		"Common/Movements/NetBikeMovement.h"
)
add_sources("SimpleVehiclePluginAPI_uber.cpp"
    PROJECTS VehiclePlugin
    SOURCE_GROUP "Common\\\\SimpleVehiclePluginAPI"
		"Common/SimpleVehiclePluginAPI/CommonData.h"
)
add_sources("FGNode_uber.cpp"
    PROJECTS VehiclePlugin
    SOURCE_GROUP "FGNode"
		"FGNode/BikeNode.cpp"
)

end_sources()

CryEngineModule(VehiclePlugin FORCE_SHARED PCH "StdAfx.cpp" SOLUTION_FOLDER "Project")

target_include_directories(${THIS_PROJECT}
PRIVATE
    "${CRYENGINE_DIR}/Code/CryEngine/CryCommon"
    "${CRYENGINE_DIR}/Code/CryEngine/CryAction"
    "${CRYENGINE_DIR}/Code/CryEngine/CrySchematyc/Core/Interface"
    "${CRYENGINE_DIR}/Code/CryPlugins/CryDefaultEntities/Module"
)


if(OPTION_ENGINE)
    if(NOT EXISTS "${CRYENGINE_DIR}/Code/Sandbox/EditorQt")
		add_library(Editor STATIC "${CRYENGINE_DIR}/Code/CryEngine/CryCommon/CryCore/Platform/platform.h")
		set_target_properties(Editor PROPERTIES LINKER_LANGUAGE CXX)
		if (WIN32)
			set_visual_studio_debugger_command(Editor "${CRYENGINE_DIR}/bin/win_x64/Sandbox.exe" "-project \"${PROJECT_DIR}VehiclePlugin.cryproject\"")
		endif()
	endif()
else()
	add_library(GameLauncher STATIC "${CRYENGINE_DIR}/Code/CryEngine/CryCommon/CryCore/Platform/platform.h")
	set_target_properties(GameLauncher PROPERTIES LINKER_LANGUAGE CXX)
	if (WIN32)
		set_visual_studio_debugger_command(GameLauncher "${CRYENGINE_DIR}/bin/win_x64/GameLauncher.exe" "-project \"${PROJECT_DIR}VehiclePlugin.cryproject\"")
	endif()

    add_library(Editor STATIC "${CRYENGINE_DIR}/Code/CryEngine/CryCommon/CryCore/Platform/platform.h")
    set_target_properties(Editor PROPERTIES LINKER_LANGUAGE CXX)
    if (WIN32)
        set_visual_studio_debugger_command(Editor "${CRYENGINE_DIR}/bin/win_x64/Sandbox.exe" "-project \"${PROJECT_DIR}VehiclePlugin.cryproject\"")
    endif()

	add_library(GameServer STATIC "${CRYENGINE_DIR}/Code/CryEngine/CryCommon/CryCore/Platform/platform.h")
	set_target_properties(GameServer PROPERTIES LINKER_LANGUAGE CXX)
	if (WIN32)
		set_visual_studio_debugger_command(GameServer "${CRYENGINE_DIR}/bin/win_x64/Game_Server.exe" "-project \"${PROJECT_DIR}VehiclePlugin.cryproject\"")
	endif()
endif()

# Set StartUp project in Visual Studio
set_solution_startup_target(GameLauncher)

if (WIN32)
    set_visual_studio_debugger_command( ${THIS_PROJECT} "${CRYENGINE_DIR}/bin/win_x64/GameLauncher.exe" "-project \"${PROJECT_DIR}VehiclePlugin.cryproject\"" )
endif()

#BEGIN-CUSTOM
# Make any custom changes here, modifications outside of the block will be discarded on regeneration.
#END-CUSTOM