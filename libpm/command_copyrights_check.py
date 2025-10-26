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
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR pm_OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Repository: https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin

""" Comamnd for check copyrights """

import os
import sys
import logging
from .utils_files import UtilsFiles
from .pm_config import PmConfig

logging.basicConfig()


class CommandCopyrightsCheck:
    """ CommandCopyrightsCheck """
    def __init__(self, config: PmConfig):
        self.__comamnd_name = "copyrights-check"
        self.__config = config
        self.__skip_files_or_dirs = [
            os.path.join(self.__config.get_root_dir(), "utils", "upgrade"),
            os.path.join(self.__config.get_root_dir(), "include"),
            os.path.join(
                self.__config.get_root_dir(),
                "source", "plugins", "Sea5kg", "StoneGenerator_editorplugin",
                "src", "thirdparty"
            ),
            os.path.join(
                self.__config.get_root_dir(),
                "source", "plugins", "Sea5kg", "StoneGenerator_editorplugin",
                "src", "UnigineEditor.h"
            ),
            os.path.join(
                self.__config.get_root_dir(),
                "source", "plugins", "Sea5kg", "StoneGenerator_editorplugin",
                "src.wsjcpp"
            ),
        ]
        self.__log = logging.getLogger("CommandCopyrightsCheck")
        self.__log.setLevel(logging.DEBUG)
        self.__expected_cpp_copyright = """/*
MIT License

Copyright (c) 2022-2025 mrseakg@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Repository: https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin
*/
"""
        self.__expected_py_copyrights = """#!/usr/bin/env python3

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

"""

    def get_command_name(self):
        """ return command name """
        return self.__comamnd_name

    def register(self, _subparsers):
        """ register """
        _descr = 'Check copyrights (now only for rc+h files)'
        check_copyright_parser = _subparsers.add_parser(
            name=self.__comamnd_name,
            description=_descr
        )
        check_copyright_parser.add_argument(
            '-v', '--verbose',
            dest='verbose',
            help='More prints',
            action='store_true',
        )
        check_copyright_parser.set_defaults(subparser=self.__comamnd_name)

    def __is_skip(self, filepath):
        for _skip in self.__skip_files_or_dirs:
            if _skip in filepath:
                return True
        return False

    def __check_copyright(self, filepath):
        _content = UtilsFiles.safe_read_file(filepath)
        _content = "".join(_content)
        _expected = self.__expected_cpp_copyright
        if filepath.endswith(".py"):
            _expected = self.__expected_py_copyrights
        if not _content.startswith(_expected):
            self.__log.error(
                "In file %s expected copyright\n%s\n\n, but got:\n%s",
                filepath,
                _expected,
                _content
            )
            return False
        return True

    def run(self, _):
        """ run """
        self.__log.info("OK: Checking copyrights start...")
        _files = UtilsFiles.recoursive_find_files_by_ext(
            self.__config.get_root_dir(),
            _exts=[".cpp", ".h", ".py"],
        )
        _exit_code = 0
        for _filepath in _files:
            if not self.__is_skip(_filepath):
                if not self.__check_copyright(_filepath):
                    _exit_code = 1

        if _exit_code == 0:
            self.__log.info("OK: Looks everything fine...")
        sys.exit(_exit_code)
