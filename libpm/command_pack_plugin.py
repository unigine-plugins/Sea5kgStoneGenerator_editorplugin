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

""" Comamnd for pack plugin """

import sys
import os
import logging
import zipfile
from .pm_config import PmConfig
from .utils_shell import UtilsShell
from .utils_bin_sdk import UtilsBinSdk

logging.basicConfig()


class CommandPackPlugin:
    """ CommandPackPlugin """
    def __init__(self, config: PmConfig):
        self.__comamnd_name = "pack-plugin"
        self.__config = config
        self.__log = logging.getLogger("CommandPackPlugin")
        self.__log.setLevel(logging.DEBUG)

    def get_command_name(self):
        """ return command name """
        return self.__comamnd_name

    def register(self, _subparsers):
        """ register """
        _descr = 'Pack plugin (zip or...)'
        pack_plugin_parser = _subparsers.add_parser(
            name=self.__comamnd_name,
            description=_descr
        )
        pack_plugin_parser.add_argument(
            '-z', '--zip',
            dest='pzck_zip',
            help='Pack zip archive',
            action='store_true',
            default=False,
            required=False,
        )
        pack_plugin_parser.set_defaults(subparser=self.__comamnd_name)

    def run(self, _):
        """ run """
        self.__log.info("OK: Start building...")
        self.__log.info("Root directory: %s", self.__config.get_root_dir())

        sdk_ver = UtilsBinSdk.detect_sdk_version(self.__config.get_root_dir())

        pltfrm = ""
        if UtilsShell.is_linux():
            pltfrm = "linux"
        elif UtilsShell.is_windows():
            pltfrm = "windows"
        else:
            sys.exit("Unknown platform")

        if UtilsShell.is_windows():
            ret = os.system("python3 build_plugin.py")
            if ret != 0:
                sys.exit("Could not build...")
        elif UtilsShell.is_linux():
            _cmd = "docker run --rm -it "
            _cmd += " -v `pwd`:/opt/sources "
            _cmd += " sea5kg/unigine-editor-pluigns:v" + sdk_ver + " ./build_plugin.py"
            ret = os.system(_cmd)
            if ret != 0:
                sys.exit("Could not build...")

        plugin_ver = UtilsBinSdk.find_plugin_version(
            self.__config.get_root_dir(),
            "Sea5kg",
            "StoneGenerator_editorplugin",
        )

        # 2.16.1
        # folder_inside = "UnigineEditorPlugin_PrototypeStoneGenerator_" + _version
        # _zip_filename = pltfrm + "_" + folder_inside + ".zip"
        # base_libname = "UnigineEditorPlugin_PrototypeStoneGenerator"

        # 2.19.1
        folder_inside = "Sea5kgStoneGenerator_editorplugin_v" + sdk_ver + "_" + plugin_ver
        _zip_filename = pltfrm + "_" + folder_inside + ".zip"
        base_libname = "Sea5kgStoneGenerator_editorplugin"
        base_path = "bin/plugins/Sea5kg/StoneGenerator/"
        if os.path.isfile(_zip_filename):
            os.remove(_zip_filename)

        with zipfile.ZipFile(_zip_filename, 'w', zipfile.ZIP_DEFLATED) as zf:
            if UtilsShell.is_linux():
                zf.write(
                    base_path + "lib" + base_libname + "_x64.so",
                    folder_inside + "/" + base_path + "lib" + base_libname + "_x64.so",
                )
                zf.write(
                    base_path + "lib" + base_libname + "_x64d.so",
                    folder_inside + "/" + base_path + "lib" + base_libname + "_x64d.so",
                )
                zf.write(
                    base_path + "lib" + base_libname + "_double_x64.so",
                    folder_inside + "/" + base_path + "lib" + base_libname + "_double_x64.so",
                )
                zf.write(
                    base_path + "lib" + base_libname + "_double_x64d.so",
                    folder_inside + "/" + base_path + "lib" + base_libname + "_double_x64d.so",
                )

            if UtilsShell.is_windows():
                zf.write(
                    base_path + base_libname + "_x64.dll",
                    folder_inside + "/" + base_path + base_libname + "_x64.dll",
                )
                zf.write(
                    base_path + base_libname + "_x64d.dll",
                    folder_inside + "/" + base_path + base_libname + "_x64d.dll",
                )
                zf.write(
                    base_path + base_libname + "_double_x64.dll",
                    folder_inside + "/" + base_path + base_libname + "_double_x64.dll",
                )
                zf.write(
                    base_path + base_libname + "_double_x64d.dll",
                    folder_inside + "/" + base_path + base_libname + "_double_x64d.dll",
                )
