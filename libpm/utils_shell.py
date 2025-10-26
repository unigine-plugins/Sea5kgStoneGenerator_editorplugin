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

""" Utils Shell """

import sys
import os
import subprocess


class UtilsShell:
    """ Utils Shell """

    @staticmethod
    def run_command(_command, print_output=True, exit_on_error=True):
        """ run_command """
        _retcode = -1  # error
        _retoutput = ""
        if print_output:
            print("Run command: " + " ".join(_command))
        with subprocess.Popen(
            _command,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            shell=False
        ) as _proc:
            _retcode = _proc.poll()
            while _retcode is None:
                _retcode = _proc.poll()
                _line = _proc.stdout.readline()
                if _line:
                    _line = _line.decode("utf-8").rstrip()
                    _retoutput += _line + "\n"
                    if print_output:
                        print(_line)
            while _line:
                _line = _proc.stdout.readline()
                if _line:
                    _line = _line.decode("utf-8").rstrip()
                    _retoutput += _line + "\n"
                    if print_output:
                        print(_line)
                else:
                    break
            if _retcode != 0:
                if print_output:
                    print("ERROR: returncode " + str(_retcode))
                if exit_on_error:
                    sys.exit(_retcode)
                return _retcode, _retoutput
            return _retcode, _retoutput
        if exit_on_error:
            sys.exit("Could not start process")
        return _retcode, _retoutput

    @staticmethod
    def get_current_root_path():
        """ get_current_root_path """
        _dir = os.path.dirname(__file__)
        _dir = os.path.join(_dir, "..")
        _dir = os.path.normpath(_dir)
        return _dir

    @staticmethod
    def is_linux():
        """ is host system is linux """
        return sys.platform.startswith("linux")

    @staticmethod
    def is_windows():
        """ is host system is windows """
        return sys.platform.startswith("win")
