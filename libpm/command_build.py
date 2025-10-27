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
from .pm_config import PmConfig

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
        _descr = 'Check copyrights (now only for rc+h files)'
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
