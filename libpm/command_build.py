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

""" Comamnd for build plugin """

import logging
import sys
from .pm_config import PmConfig
from .utils_files import UtilsFiles

logging.basicConfig()


class CommandBuild:
    """ CommandBuild """
    def __init__(self, config: PmConfig):
        self.__comamnd_name = "build"
        self.__config = config
        self.__log = logging.getLogger("CommandBuild")
        self.__log.setLevel(logging.DEBUG)

    def get_command_name(self):
        """ return command name """
        return self.__comamnd_name

    def register(self, _subparsers):
        """ register """
        _descr = 'Build project'
        build_parser = _subparsers.add_parser(
            name=self.__comamnd_name,
            description=_descr
        )
        build_parser.add_argument(
            '-v', '--verbose',
            dest='verbose',
            help='More prints',
            action='store_true',
        )
        build_parser.set_defaults(subparser=self.__comamnd_name)

    def run(self, _):
        """ run """
        self.__log.info("OK: Start building...")
        self.__log.info("Root directory: %s", self.__config.get_root_dir())

        CMAKE_GEN = ""
        IS_LINUX = False
        IS_WINDOWS = False
        if UtilsFiles.is_linux():
            _PLATFORM = "linux"
            self.__log.info(" * Linux platform")
            IS_LINUX = True
        elif UtilsFiles.is_windows():
            _PLATFORM = "windows"
            self.__log.info(" * Windows platform")
            # TODO check ver of sdk or look in file settings
            CMAKE_GEN = " -G \"Visual Studio 17 2022\" -A x64"
            IS_WINDOWS = True
        else:
            sys.exit("Unknown platform")

        _junk_path = "../../../../junk/Sea5kgStoneGenerator_editorplugin"

        # TODO check binaries and can by add to bin directory
        # TODO upgrade include/Unigine.h
        # TODO detect in docker or not
        # for example can be run this command docker info
        # if not in docker so run

        # _files = UtilsFiles.recoursive_find_files_by_ext(
        #     self.__config.get_root_dir(),
        #     _exts=[".cpp", ".h", ".py"],
        # )
        # _exit_code = 0
        # for _filepath in _files:
        #     if not self.__is_skip(_filepath):
        #         if not self.__check_copyright(_filepath):
        #             _exit_code = 1

        # if _exit_code == 0:
        #     self.__log.info("OK: Looks everything fine...")
        # sys.exit(_exit_code)




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
            "command": "cmake -H. -B" + _junk_rel + " " + CMAKE_GEN + " \
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
            "command": "cmake -H. -B" + _junk_dbg + " " + CMAKE_GEN + " \
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
            "command": "cmake -H. -B" + _junk_rel + " " + CMAKE_GEN + " \
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
            "command": "cmake -H. -B" + _junk_dbg + " " + CMAKE_GEN + " \
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
