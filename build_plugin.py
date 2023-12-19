#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os
import platform


_platform = platform.platform().lower()
_cmake_gen = ""
is_linux = False
is_windows = False
if _platform.startswith("linux"):
    _platform = "linux"
    is_linux = True
elif _platform.startswith("windows"):
    _platform = "windows"
    _cmake_gen = " -G \"Visual Studio 17 2022\" -A x64"
    is_windows = True
else:
    sys.exit("Unknown platform")

_junk_path = "../../../../junk/Sea5kgStoneGenerator_editorplugin"


build_commands = [
    # build float
    {
        "name": "cmake configure release (float)",
        "command": "cmake -H. -B" + _junk_path + "_release_float_" + _platform + " " + _cmake_gen + " -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
        -DCMAKE_INSTALL_PREFIX=../../../../bin",
    },
    {
        "name": "cmake build release (float)",
        "command": "cmake --build " + _junk_path + "_release_float_" + _platform + " --parallel 8 --config Release",
    },
    # {
    #     "name": "cmake configure debug (float)",
    #     "command": "cmake -H. -B" + _junk_path + "_debug_float_" + _platform + " " + _cmake_gen + " -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    #     -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    #     -DCMAKE_INSTALL_PREFIX=../../../../bin",
    # },
    # {
    #     "name": "cmake build debug (float)",
    #     "command": "cmake --build " + _junk_path + "_debug_float_" + _platform + " --parallel 8 --config RelWithDebInfo",
    # },
    # # build double
    # {
    #     "name": "cmake configure release (double)",
    #     "command": "cmake -H. -B" + _junk_path + "_release_double_" + _platform + " " + _cmake_gen + " -DCMAKE_BUILD_TYPE=Release \
    #     -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    #     -DUNIGINE_DOUBLE=ON \
    #     -DCMAKE_INSTALL_PREFIX=../../../../bin",
    # },
    # {
    #     "name": "cmake build release (double)",
    #     "command": "cmake --build " + _junk_path + "_release_double_" + _platform + " --parallel 8 --config Release",
    # },
    # {
    #     "name": "cmake configure debug (double)",
    #     "command": "cmake -H. -B" + _junk_path + "_debug_double_" + _platform + " " + _cmake_gen + " -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    #     -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    #     -DUNIGINE_DOUBLE=ON \
    #     -DCMAKE_INSTALL_PREFIX=../bin",
    # },
    # {
    #     "name": "cmake build debug (double)",
    #     "command": "cmake --build " + _junk_path + "_debug_double_" + _platform + " --parallel 8 --config RelWithDebInfo",
    # },
]

os.chdir("source/plugins/Sea5kg/StoneGenerator_editorplugin")

for _cmd in build_commands:
    print("Starting... " + _cmd["name"])
    print("command: " + _cmd["command"])
    ret = os.system(_cmd["command"])
    if ret != 0:
        print("Failed... " + _cmd["name"])
        sys.exit(-1)
    print("Done. " + _cmd["name"] + "\n\n-----\n\n")
