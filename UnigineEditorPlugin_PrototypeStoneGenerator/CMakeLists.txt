##==============================================================================
## General.
##==============================================================================
cmake_minimum_required(VERSION 3.19)
set(target UnigineEditorPlugin_PrototypeStoneGenerator_x64)
if (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
	set(target UnigineEditorPlugin_PrototypeStoneGenerator_x64d)
endif()
project(${target} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "$ORIGIN")

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTOUIC TRUE)
set(CMAKE_AUTORCC TRUE)

##==============================================================================
## Environment.
##==============================================================================
set(UNIGINE_DOUBLE 0)
set(UNIGINE_SDK_PATH ${PROJECT_SOURCE_DIR}/../)
set(UNIGINE_BIN_DIR ${UNIGINE_SDK_PATH}bin/)
set(UNIGINE_LIB_DIR ${UNIGINE_SDK_PATH}lib/)
set(UNIGINE_INCLUDE_DIR ${UNIGINE_SDK_PATH}include/)
set(UNIGINE_OUTPUT_EDITOR_RELEASE_DIR ${UNIGINE_BIN_DIR}editor/)
set(UNIGINE_OUTPUT_EDITOR_DEBUG_DIR ${UNIGINE_BIN_DIR}editor_debug/)

##==============================================================================
## Dependencies.
##==============================================================================
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
find_package(Engine REQUIRED MODULE QUIET)
find_package(Editor REQUIRED MODULE QUIET)

# UNIGINE_QTROOT is Unigine related global variable that points to the effective
# Qt's distributive.
set(QT5_ROOT "$ENV{UNIGINE_QTROOT}")
if (QT5_ROOT AND EXISTS "${QT5_ROOT}")
	list(APPEND CMAKE_PREFIX_PATH ${QT5_ROOT})
endif()

# The following construct is required as Editor's Debug build
# uses Release binaries of QT5 framework
set(temp_map_imported ${CMAKE_MAP_IMPORTED_CONFIG_DEBUG})
set(CMAKE_MAP_IMPORTED_CONFIG_DEBUG RELEASE)
cmake_policy(PUSH)
cmake_policy(SET CMP0111 OLD)
# Find additional required packages
find_package(Qt5 5.12.8 CONFIG EXACT COMPONENTS Core Gui Widgets)
# Restore the actual value
set(CMAKE_MAP_IMPORTED_CONFIG_DEBUG ${temp_map_imported})
unset(temp_map_imported)
cmake_policy(POP)

if (NOT Qt5_FOUND)
	message(FATAL_ERROR "The required Qt version is not found on your computer, "
	"please follow this link to see the instructions on resolving this issue. "
	"https://developer.unigine.com/en/docs/latest/editor2/extensions/environment")
endif()

##==============================================================================
## Target.
##==============================================================================

file (STRINGS "../version" PrototypeStoneGenerator_VERSION)

add_definitions(-DPrototypeStoneGenerator_VERSION="${PrototypeStoneGenerator_VERSION}")

message(STATUS " PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS " CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/UnigineEditorPlugin_PrototypeStoneGenerator.json.in)
	message(FATAL_ERROR "Required file is missed! - ${CMAKE_CURRENT_SOURCE_DIR}/UnigineEditorPlugin_PrototypeStoneGenerator.json.in")
endif()

set(PLUGIN_VERSION ${PrototypeStoneGenerator_VERSION})
set(PLUGIN_COMPAT_VERSION ${PrototypeStoneGenerator_VERSION})
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/UnigineEditorPlugin_PrototypeStoneGenerator.json.in
	${CMAKE_CURRENT_BINARY_DIR}/UnigineEditorPlugin_PrototypeStoneGenerator.json
	)

add_library(${target} SHARED
	${PROJECT_SOURCE_DIR}/src/UnigineEditorPlugin_PrototypeStoneGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/AsyncRunGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/TextureStoneGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/DialogConfigurator.cpp
	)

target_include_directories(${target} SYSTEM
	PRIVATE
	${PROJECT_SOURCE_DIR}/src/
	${UNIGINE_INCLUDE_DIR}/
	${CMAKE_CURRENT_BINARY_DIR}/
	${CMAKE_CURRENT_SOURCE_DIR}/
	)

target_link_libraries(${target}
	PRIVATE
	Unigine::Engine
	Unigine::Editor
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	)

target_compile_definitions(${target}
	PRIVATE
	$<$<BOOL:${UNIX}>:_LINUX>
	QT_NO_DEBUG
	)

set_target_properties(${target}
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ${UNIGINE_OUTPUT_EDITOR_RELEASE_DIR}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${UNIGINE_OUTPUT_EDITOR_DEBUG_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${UNIGINE_OUTPUT_EDITOR_DEBUG_DIR}
	RUNTIME_OUTPUT_DIRECTORY ${UNIGINE_OUTPUT_EDITOR_RELEASE_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${UNIGINE_OUTPUT_EDITOR_DEBUG_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${UNIGINE_OUTPUT_EDITOR_DEBUG_DIR}
	CXX_VISIBILITY_PRESET hidden
	)

if(MSVC)
	target_compile_options(${target}
		PRIVATE
    	/arch:SSE4.1
	)
else()
	target_compile_options(${target}
		PRIVATE
		-m64
		-march=athlon64
		-msse4.2
		# Optimizations.
		-ffast-math
		-fno-strict-aliasing
	)
endif()