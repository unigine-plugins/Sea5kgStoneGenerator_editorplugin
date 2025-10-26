#!/usr/bin/env python3

# MIT License

# Copyright (c) 2022-2025 mrseakg@gmail.com

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Repository: https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin


""" BUILD PLUGIN SCRIPT """

import sys
import os
import platform


_PLATFORM = platform.platform().lower()
_CMAKE_GEN = ""
IS_LINUX = False
IS_WINDOWS = False
if _PLATFORM.startswith("linux"):
    _PLATFORM = "linux"
    print(" * Linux platform")
    IS_LINUX = True
elif _PLATFORM.startswith("windows"):
    _PLATFORM = "windows"
    print(" * Windows platform")
    _CMAKE_GEN = " -G \"Visual Studio 17 2022\" -A x64"
    IS_WINDOWS = True
else:
    sys.exit("Unknown platform")

_JUNK_PATH = "../../../../junk/Sea5kgStoneGenerator_editorplugin"

HAS_FLOAT = False
HAS_DOUBLE = False

for _file in os.listdir("./bin"):
    if _file == "libUnigine_x64.so":
        print(" * Found engine (float)")
        HAS_FLOAT = True
    if _file == "libUnigine_double_x64.so":
        print(" * Found double (engine)")
        HAS_DOUBLE = True

build_commands = []

if HAS_FLOAT:
    _junk_rel = _JUNK_PATH + "_release_float_" + _PLATFORM
    _junk_dbg = _JUNK_PATH + "_release_debug_" + _PLATFORM
    build_commands.extend([
        # build float
        {
            "name": "cmake configure release (float)",
            "command": "cmake -H. -B" + _junk_rel + " " + _CMAKE_GEN + " \
            -DCMAKE_BUILD_TYPE=Release \
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
            -DCMAKE_INSTALL_PREFIX=../../../../bin",
        },
        {
            "name": "cmake build release (float)",
            "command": "cmake --build " + _junk_rel + " --parallel 8 --config Release",
        },
        {
            "name": "cmake configure debug (float)",
            "command": "cmake -H. -B" + _junk_dbg + " " + _CMAKE_GEN + " \
            -DCMAKE_BUILD_TYPE=RelWithDebInfo \
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
            -DCMAKE_INSTALL_PREFIX=../../../../bin",
        },
        {
            "name": "cmake build debug (float)",
            "command": "cmake --build " + _junk_dbg + " --parallel 8 --config RelWithDebInfo",
        },
    ])

if HAS_DOUBLE:
    _junk_rel = _JUNK_PATH + "_release_double_" + _PLATFORM
    _junk_dbg = _JUNK_PATH + "_debug_double_" + _PLATFORM
    build_commands.extend([
        {
            "name": "cmake configure release (double)",
            "command": "cmake -H. -B" + _junk_rel + " " + _CMAKE_GEN + " \
            -DCMAKE_BUILD_TYPE=Release \
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
            -DUNIGINE_DOUBLE=ON \
            -DCMAKE_INSTALL_PREFIX=../../../../bin",
        },
        {
            "name": "cmake build release (double)",
            "command": "cmake --build " + _junk_rel + " --parallel 8 --config Release",
        },
        {
            "name": "cmake configure debug (double)",
            "command": "cmake -H. -B" + _junk_dbg + " " + _CMAKE_GEN + " \
            -DCMAKE_BUILD_TYPE=RelWithDebInfo \
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
            -DUNIGINE_DOUBLE=ON \
            -DCMAKE_INSTALL_PREFIX=../bin",
        },
        {
            "name": "cmake build debug (double)",
            "command": "cmake --build " + _junk_dbg + " --parallel 8 --config RelWithDebInfo",
        },
    ])

os.chdir("source/plugins/Sea5kg/StoneGenerator_editorplugin")

for _cmd in build_commands:
    print("Starting... " + _cmd["name"])
    print("command: " + _cmd["command"])
    ret = os.system(_cmd["command"])
    if ret != 0:
        print("Failed... " + _cmd["name"])
        sys.exit(-1)
    print("Done. " + _cmd["name"] + "\n\n-----\n\n")
