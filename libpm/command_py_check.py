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

""" Comamnd for check py files """

import os
import sys
from .pm_config import PmConfig
from .utils_shell import UtilsShell


class CommandPyCheck:
    """ CommandPyCheck """
    def __init__(self, config: PmConfig):
        self.__comamnd_name = "py-check"
        self.__config = config
        self.__skip_dirs = [
            "ThirdParty",
            "libpm",
        ]

    def get_command_name(self):
        """ return command name """
        return self.__comamnd_name

    def register(self, _subparsers):
        """ register """
        py_check_parser = _subparsers.add_parser(
            name=self.__comamnd_name,
            description='Search all py files and run pylint+pycodestyle for check it'
        )
        py_check_parser.set_defaults(subparser=self.__comamnd_name)

    def __recoursive_find_all_py_files(self, _dir):
        _ret = []
        for _file in os.listdir(_dir):
            _fullpath = os.path.join(_dir, _file)
            if _fullpath.endswith(".py"):
                _ret.append(_fullpath)
            if os.path.isdir(_fullpath):
                if _file not in self.__skip_dirs:
                    _ret.extend(self.__recoursive_find_all_py_files(_fullpath))
        return _ret

    def run(self, _):
        """ run """
        script_path = os.path.dirname(os.path.realpath(__file__))
        pycodestyle_config_path = os.path.join(script_path, "data", "pycodestyle.config")
        py_files = self.__recoursive_find_all_py_files(self.__config.get_root_dir())
        print("Found files: " + str(len(py_files)))
        py_files.append(
            os.path.join(self.__config.get_root_dir(), "libpm")
        )
        os.chdir(self.__config.get_root_dir())

        _ret = 0
        for _file in py_files:
            python_bin = "python3"
            if sys.platform.startswith('win'):
                python_bin = "python"

            ret_pycodestyle, _pycodestyle_output = UtilsShell.run_command(
                [python_bin, "-m", "pycodestyle", "--config=" + pycodestyle_config_path, _file],
                print_output=False,
                exit_on_error=False,
            )
            ret_pylint, _pylint_output = UtilsShell.run_command(
                [python_bin, "-m", "pylint", _file],
                print_output=False,
                exit_on_error=False,
            )
            if ret_pycodestyle != 0 or ret_pylint != 0:
                print("BAD code: ", _file)
                if ret_pycodestyle != 0:
                    print("pycodestyle output for file ", _file)
                    print("**********************************************")
                    print(_pycodestyle_output)
                    print("**********************************************")
                if ret_pylint != 0:
                    print("pylint output for file ", _file)
                    print("**********************************************")
                    print(_pylint_output)
                    print("**********************************************")
                _ret = 1
            else:
                print("OK:", _file)
        sys.exit(_ret)
