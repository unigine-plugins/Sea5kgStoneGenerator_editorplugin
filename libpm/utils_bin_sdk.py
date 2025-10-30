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

""" Utils Files """

import sys
import os


class UtilsBinSdk:
    """ UtilsBinSdk """

    @staticmethod
    def detect_sdk_version(bin_dir):
        """ search version fo sdk in UnigineVersion.h """
        file_version = os.path.join(bin_dir, "include", "UnigineVersion.h")
        if not os.path.isfile(file_version):
            sys.exit("Missing file with version: " + file_version)
        ret = ""
        with open(file_version, "rt", encoding="utf-8") as _file:
            _lines = _file.readlines()
            for _line in _lines:
                _line = _line.strip()
                if _line.startswith("#define UNIGINE_SDK_VERSION "):
                    ret = _line.split(" ")[-1].strip()
        if ret.endswith('"'):
            ret = ret[:-1]
        if ret.startswith('"'):
            ret = ret[1:]
        return ret

    @staticmethod
    def find_plugin_version(root_dir, author, plugin):
        """ will be patched include file """

        cmake_path = os.path.join(root_dir, "source", "plugins")
        cmake_path = os.path.join(cmake_path, author, plugin)
        cmake_path = os.path.join(cmake_path, "CMakeLists.txt")

        ret = ""
        with open(cmake_path, encoding="utf-8") as _file:
            _lines = _file.readlines()
            for _line in _lines:
                _line = _line.strip()
                if _line.startswith("set(CURRENT_PROJECT_VERSION"):
                    _line = _line.split(" ")[-1]
                    _line = _line.split("_")[-1]
                    ret = _line[:-2]
        return ret
