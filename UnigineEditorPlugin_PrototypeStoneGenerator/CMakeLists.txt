cmake_minimum_required(VERSION 3.14)
set(proj_name UnigineEditorPlugin_PrototypeStoneGenerator_x64)
if (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
	set(proj_name UnigineEditorPlugin_PrototypeStoneGenerator_x64d)
endif()
project(${proj_name} CXX)

# set(PrototypeStoneGenerator_VERSION "0.0.2")
file (STRINGS "../version" PrototypeStoneGenerator_VERSION)

add_definitions(-DPrototypeStoneGenerator_VERSION="${PrototypeStoneGenerator_VERSION}")

include(${PROJECT_SOURCE_DIR}/cmake/Unigine.cmake)

if (EXISTS ${PROJECT_SOURCE_DIR}/UnigineEditorPlugin_PrototypeStoneGenerator.json.in)
	set(PLUGIN_VERSION ${UNIGINE_VERSION})
	set(PLUGIN_COMPAT_VERSION ${PrototypeStoneGenerator_VERSION})
	configure_file(
		${PROJECT_SOURCE_DIR}/UnigineEditorPlugin_PrototypeStoneGenerator.json.in
		${CMAKE_CURRENT_BINARY_DIR}/Plugin.json
		)
endif()

# message(FATAL_ERROR ${CMAKE_CURRENT_BINARY_DIR})

# Create code for QObjects
set(CMAKE_AUTOMOC ON)

# set(CMAKE_AUTOUIC ON)

# Create code from resource files
# set(CMAKE_AUTORCC ON)

IF (WIN32)
	# windows
	find_package(Qt5 HINTS "$ENV{QTDIR}" COMPONENTS Core Widgets Gui REQUIRED)
ELSE()
	# linux
	find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
ENDIF()

add_library(${proj_name} SHARED
	${PROJECT_SOURCE_DIR}/src/UnigineEditorPlugin_PrototypeStoneGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/AsyncRunGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/TextureStoneGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/DialogConfigurator.cpp
	)

target_include_directories(${proj_name} SYSTEM
	PRIVATE
	${PROJECT_SOURCE_DIR}/src/
	${CMAKE_CURRENT_BINARY_DIR}
	)

if (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
    target_compile_definitions(${proj_name}
		PRIVATE
		DEBUG
		# QT_DEBUG
	)
else()
	target_compile_definitions(${proj_name}
		PRIVATE
		NDEBUG
		# QT_NO_DEBUG
	)
endif()


set_target_properties(${proj_name}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../bin/editor/
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../bin/editor/
	# ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../lib/editor/
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../bin/editor_debug/
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../bin/editor_debug/
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../bin/editor_debug/
	LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../bin/editor_debug/
	# ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../lib/editor_debug/
	C_VISIBILITY_PRESET hidden
	CXX_VISIBILITY_PRESET hidden
)

target_link_libraries(${proj_name}
	PRIVATE
	Unigine::CompilerFlags
	Unigine::Engine
	Unigine::Editor
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	)
