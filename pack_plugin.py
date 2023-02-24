#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os
import zipfile
import platform


_platform = platform.platform().lower()
is_linux = False
is_windows = False
if _platform.startswith("linux"):
    _platform = "linux"
    is_linux = True
elif _platform.startswith("windows"):
    _platform = "windows"
    is_windows = True
else:
    sys.exit("Unknown platform")

if is_windows:
    ret = os.system("python3 build_plugin.py")
    if ret != 0:
        sys.exit("Could not build...")
elif is_linux:
    ret = os.system("docker run --rm -it -v `pwd`:/opt/sources sea5kg/unigine-editor-pluigns:v2.16.1 ./build_plugin.py")
    if ret != 0:
        sys.exit("Could not build...")


with open("version") as _file:
    content = _file.read()
    _version = content.strip()

folder_inside = "UnigineEditorPlugin_PrototypeStoneGenerator_" + _version
_zip_filename = _platform + "_" + folder_inside + ".zip"

if os.path.isfile(_zip_filename):
    os.remove(_zip_filename)

zf = zipfile.ZipFile(_zip_filename, 'w', zipfile.ZIP_DEFLATED)

if is_linux:
    zf.write(
        "bin/editor/libUnigineEditorPlugin_PrototypeStoneGenerator_x64.so",
        folder_inside + "/bin/editor/libUnigineEditorPlugin_PrototypeStoneGenerator_x64.so",
    )
    zf.write(
        "bin/editor_debug/libUnigineEditorPlugin_PrototypeStoneGenerator_x64d.so",
        folder_inside + "/bin/editor_debug/libUnigineEditorPlugin_PrototypeStoneGenerator_x64d.so",
    )

if is_windows:
    zf.write(
        "bin/editor/UnigineEditorPlugin_PrototypeStoneGenerator_x64.dll",
        folder_inside + "/bin/editor/UnigineEditorPlugin_PrototypeStoneGenerator_x64.dll",
    )
    zf.write(
        "bin/editor_debug/UnigineEditorPlugin_PrototypeStoneGenerator_x64d.dll",
        folder_inside + "/bin/editor_debug/UnigineEditorPlugin_PrototypeStoneGenerator_x64d.dll",
    )

zf.close()
