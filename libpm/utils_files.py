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


class UtilsFiles:
    """ UtilsFiles """

    @staticmethod
    def get_all_files(_startdir):
        """ recursive find all files in dir """
        _ret = []
        _rec = [_startdir]
        while len(_rec) > 0:
            _dirpath = _rec[0]
            del _rec[0]
            for _file in os.listdir(_dirpath):
                _filepath = os.path.join(_dirpath, _file)
                if os.path.isdir(_filepath):
                    _rec.append(_filepath)
                    continue
                if os.path.isfile(_filepath):
                    _ret.append(_filepath)
        return _ret

    @staticmethod
    def find_fullpath_by_dirname(_root, _dirname):
        """ Recursive search and return path if found it """
        _found = []
        _find_in_dirs = [_root]
        while len(_find_in_dirs) > 0:
            _find_in_dir = _find_in_dirs[0]
            del _find_in_dirs[0]
            for _file in os.listdir(_find_in_dir):
                _filepath = os.path.join(_find_in_dir, _file)
                if os.path.isdir(_filepath):
                    _find_in_dirs.append(_filepath)
                if _file == _dirname:
                    _found.append(_filepath)
        if len(_found) == 1:
            # print(_found[0])
            return _found[0]
        sys.exit("Could not find by dirname: " + _dirname)

    @staticmethod
    def find_file_ignorecase(_cpppath):
        """ find correct file with ignorecase """
        _cpppath = os.path.normpath(_cpppath)
        _dir = os.path.dirname(_cpppath)
        _cppname = os.path.basename(_cpppath)
        if not os.path.isdir(_dir):
            sys.exit("ERROR(find_file_ignorecase): not found dir " + _dir)
        for _file in os.listdir(_dir):
            _filepath = os.path.join(_dir, _file)
            if _file.lower() == _cppname.lower():
                return _filepath
        if not os.path.isfile(_cpppath):
            sys.exit("ERROR(find_file_ignorecase): not found file " + _cpppath)
        return _cpppath

    @staticmethod
    def has_ext(_fullpath, _exts):
        """ has_ext """
        _lo_fullpath = _fullpath.lower()
        for _ext in _exts:
            if _lo_fullpath.endswith(_ext):
                return True
        return False

    @staticmethod
    def recoursive_find_files_by_ext(_dir, _exts=None):
        """ recoursive_find_files_by_ext """
        _ret = []
        for _file in os.listdir(_dir):
            _fullpath = os.path.join(_dir, _file)
            if _file == "ThirdParty":
                continue
            if _exts is None or UtilsFiles.has_ext(_fullpath, _exts):
                _ret.append(_fullpath)
            if os.path.isdir(_fullpath):
                _ret.extend(UtilsFiles.recoursive_find_files_by_ext(_fullpath, _exts))
        return _ret

    @staticmethod
    def human_readable_size(size, decimal_places=2):
        """ convert bytes to humanable view """
        for unit in ['B', 'KiB', 'MiB', 'GiB', 'TiB', 'PiB']:
            if size < 1024.0 or unit == 'PiB':
                break
            size /= 1024.0
        return f"{size:.{decimal_places}f} {unit}"

    @staticmethod
    def safe_read_file(_filepath, exit_on_error=True):
        """ __test_utf8_encoding """
        # print(_filepath)
        _lines = []
        try:
            with open(_filepath, "rt", encoding="utf-8") as _file:
                _lines = _file.readlines()
        except UnicodeDecodeError as _err:
            print(_err)
            if exit_on_error:
                sys.exit("Problem with encoding in file: " + _filepath)
            return []
        return _lines

    @staticmethod
    def safe_read_source_file_with_normalizing_lines(_filepath):
        """ Safe read file and remove all comments from code """
        _lines = UtilsFiles.safe_read_file(_filepath)
        _line_number = 0
        _processed_lines = 0
        _ret = []
        _multicomment0 = False
        for _line in _lines:
            _processed_lines += 1
            _line_number += 1
            if '//' in _line:
                _line = _line[:_line.index('//')]
            _line = _line.strip()
            if _line == "":
                continue
            if _line.startswith("/*") and _line.endswith("*/"):
                continue
            if _line.startswith("/*"):
                _multicomment0 = True
                continue
            if _multicomment0 and _line.endswith("*/"):
                _multicomment0 = False
                continue
            if _multicomment0:
                continue
            _ret.append({
                "line": _line,
                "number": _line_number
            })
        return _ret, _processed_lines

    @staticmethod
    def test_read_textfile(filepath):
        """ test read file like a text """
        _lines_number = 0
        _is_text = True
        try:
            with open(filepath, "rt", encoding="utf-8") as _file:
                _lines = _file.readlines()
                _lines_number = len(_lines)
        except UnicodeDecodeError as _err:
            _is_text = False
        return _is_text, _lines_number
