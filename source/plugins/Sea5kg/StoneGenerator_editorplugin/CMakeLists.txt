##==============================================================================
## General.
##==============================================================================
cmake_minimum_required(VERSION 3.19)
set(current_target Sea5kgStoneGenerator_editorplugin)

project(${current_target} LANGUAGES CXX)

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
option(UNIGINE_DOUBLE "build double or not" FALSE)

set(UNIGINE_SDK_PATH ${PROJECT_SOURCE_DIR}/../../../../)
set(UNIGINE_BIN_DIR ${UNIGINE_SDK_PATH}bin/)
set(UNIGINE_LIB_DIR ${UNIGINE_SDK_PATH}lib/)
set(UNIGINE_INCLUDE_DIR ${UNIGINE_SDK_PATH}include/)
set(UNIGINE_OUTPUT_EDITOR_RELEASE_DIR ${UNIGINE_BIN_DIR}plugins/Sea5kg/StoneGenerator/)
set(UNIGINE_OUTPUT_EDITOR_DEBUG_DIR ${UNIGINE_BIN_DIR}plugins/Sea5kg/StoneGenerator/)

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
find_package(Qt5 5.12 REQUIRED COMPONENTS Core Gui Widgets)

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

# file (STRINGS "../../../../version" PrototypeStoneGenerator_VERSION)

set(PrototypeStoneGenerator_VERSION "v2.19.1.1_v0.0.5")
add_definitions(-DPrototypeStoneGenerator_VERSION="${PrototypeStoneGenerator_VERSION}")

message(STATUS " PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS " CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${current_target}.json.in)
	message(FATAL_ERROR "Required file is missed! - ${CMAKE_CURRENT_SOURCE_DIR}/${current_target}.json.in")
endif()

set(PLUGIN_VERSION ${PrototypeStoneGenerator_VERSION})
set(PLUGIN_COMPAT_VERSION ${PrototypeStoneGenerator_VERSION})
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/${current_target}.json.in
	${CMAKE_CURRENT_BINARY_DIR}/${current_target}.json
	)

add_library(${current_target} SHARED
	${PROJECT_SOURCE_DIR}/src/AsyncRunGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/DialogConfigurator.cpp
	${PROJECT_SOURCE_DIR}/src/DialogConfiguratorParameterSliderFloat.cpp
	${PROJECT_SOURCE_DIR}/src/DialogConfiguratorParameterSliderInt.cpp
	${PROJECT_SOURCE_DIR}/src/DialogConfiguratorParameterEditBoxUInt.cpp
	${PROJECT_SOURCE_DIR}/src/Sea5kgStoneGenerator_editorplugin.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGeneratorBasicGeometry.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGeneratorBasicGeometryCube.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGeneratorBasicGeometryPlane.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGeneratorBasicGeometrySphere.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGeneratorConfig.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGeneratorModel.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGeneratorPoint.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGeneratorPseudoRandom.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGeneratorTexturePoint.cpp
	${PROJECT_SOURCE_DIR}/src/StoneGeneratorTriangle.cpp
	${PROJECT_SOURCE_DIR}/src/TextureStoneGenerator.cpp
	)

target_include_directories(${current_target} SYSTEM
	PRIVATE
	${PROJECT_SOURCE_DIR}/src/
	${UNIGINE_INCLUDE_DIR}/
	${CMAKE_CURRENT_BINARY_DIR}/
	${CMAKE_CURRENT_SOURCE_DIR}/
	)

target_link_libraries(${current_target}
	PRIVATE
	Unigine::Engine
	Unigine::Editor
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	)

target_compile_definitions(${current_target}
	PRIVATE
	$<$<BOOL:${UNIX}>:_LINUX>
	QT_NO_DEBUG
	)

set(current_postfix "")
if (UNIGINE_DOUBLE)
	string(APPEND current_postfix "_double")
endif ()

string(APPEND current_postfix "_x64")

set_target_properties(${current_target} PROPERTIES RELEASE_POSTFIX "${current_postfix}")
set_target_properties(${current_target} PROPERTIES DEBUG_POSTFIX "${current_postfix}d")
set_target_properties(${current_target} PROPERTIES RELWITHDEBINFO_POSTFIX "${current_postfix}d")

set_target_properties(${current_target}
	PROPERTIES
	OUTPUT_NAME ${current_target}
	LIBRARY_OUTPUT_DIRECTORY ${UNIGINE_OUTPUT_EDITOR_RELEASE_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${UNIGINE_OUTPUT_EDITOR_RELEASE_DIR}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${UNIGINE_OUTPUT_EDITOR_DEBUG_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${UNIGINE_OUTPUT_EDITOR_DEBUG_DIR}
	RUNTIME_OUTPUT_DIRECTORY ${UNIGINE_OUTPUT_EDITOR_RELEASE_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${UNIGINE_OUTPUT_EDITOR_RELEASE_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${UNIGINE_OUTPUT_EDITOR_DEBUG_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${UNIGINE_OUTPUT_EDITOR_DEBUG_DIR}
	CXX_VISIBILITY_PRESET hidden
	)

if(MSVC)
	target_compile_options(${current_target}
		PRIVATE
    	/arch:SSE4.1
	)
else()
	target_compile_options(${current_target}
		PRIVATE
		-m64
		-march=athlon64
		-msse4.2
		# Optimizations.
		-ffast-math
		-fno-strict-aliasing
	)
endif()


