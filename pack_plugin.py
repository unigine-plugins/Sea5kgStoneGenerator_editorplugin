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

""" Pack plugin """

import sys
import os
import zipfile
import platform


_PLATFORM = platform.platform().lower()
IS_LINUX = False
IS_WINDOWS = False
if _PLATFORM.startswith("linux"):
    _PLATFORM = "linux"
    IS_LINUX = True
elif _PLATFORM.startswith("windows"):
    _PLATFORM = "windows"
    IS_WINDOWS = True
else:
    sys.exit("Unknown platform")

if IS_WINDOWS:
    ret = os.system("python3 build_plugin.py")
    if ret != 0:
        sys.exit("Could not build...")
elif IS_LINUX:
    _COMMAND = "docker run --rm -it "
    _COMMAND += " -v `pwd`:/opt/sources sea5kg/unigine-editor-pluigns:v2.16.1 ./build_plugin.py"
    ret = os.system(_COMMAND)
    if ret != 0:
        sys.exit("Could not build...")


with open("version", encoding="utf-8") as _file:
    content = _file.read()
    _version = content.strip()

folder_inside = "UnigineEditorPlugin_PrototypeStoneGenerator_" + _version
_zip_filename = _PLATFORM + "_" + folder_inside + ".zip"
BASE_LIBNAME = "UnigineEditorPlugin_PrototypeStoneGenerator"

if os.path.isfile(_zip_filename):
    os.remove(_zip_filename)

with zipfile.ZipFile(_zip_filename, 'w', zipfile.ZIP_DEFLATED) as zf:
    if IS_LINUX:
        zf.write(
            "bin/editor/lib" + BASE_LIBNAME + "_x64.so",
            folder_inside + "/bin/editor/lib" + BASE_LIBNAME + "_x64.so",
        )
        zf.write(
            "bin/editor_debug/lib" + BASE_LIBNAME + "_x64d.so",
            folder_inside + "/bin/editor_debug/lib" + BASE_LIBNAME + "_x64d.so",
        )
        zf.write(
            "bin/editor/lib" + BASE_LIBNAME + "_double_x64.so",
            folder_inside + "/bin/editor/lib" + BASE_LIBNAME + "_double_x64.so",
        )
        zf.write(
            "bin/editor_debug/lib" + BASE_LIBNAME + "_double_x64d.so",
            folder_inside + "/bin/editor_debug/lib" + BASE_LIBNAME + "_double_x64d.so",
        )

    if IS_WINDOWS:
        zf.write(
            "bin/editor/" + BASE_LIBNAME + "_x64.dll",
            folder_inside + "/bin/editor/" + BASE_LIBNAME + "_x64.dll",
        )
        zf.write(
            "bin/editor_debug/" + BASE_LIBNAME + "_x64d.dll",
            folder_inside + "/bin/editor_debug/" + BASE_LIBNAME + "_x64d.dll",
        )
        zf.write(
            "bin/editor/" + BASE_LIBNAME + "_double_x64.dll",
            folder_inside + "/bin/editor/" + BASE_LIBNAME + "_double_x64.dll",
        )
        zf.write(
            "bin/editor_debug/" + BASE_LIBNAME + "_double_x64d.dll",
            folder_inside + "/bin/editor_debug/" + BASE_LIBNAME + "_double_x64d.dll",
        )
