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

""" Comamnd for update binaries-sdk """

import os
import sys
import logging
import hashlib
import shutil
from .pm_config import PmConfig
from .utils_shell import UtilsShell

logging.basicConfig()


class CommandUpdateBinariesSdk:
    """ CommandUpdateBinariesSdk """
    def __init__(self, config: PmConfig):
        self.__comamnd_name = "update-binaries-sdk"
        self.__config = config
        self.__log = logging.getLogger("CommandUpdateBinariesSdk")
        self.__log.setLevel(logging.DEBUG)

    def get_command_name(self):
        """ return command name """
        return self.__comamnd_name

    def register(self, _subparsers):
        """ register """
        _descr = 'Update binaries'
        build_parser = _subparsers.add_parser(
            name=self.__comamnd_name,
            description=_descr
        )
        build_parser.add_argument(
            '--sdk-bin-path',
            dest='sdk_bin_path',
            help='Customize sdk path (default: sdk-bin)',
            default="sdk-bin",
            required=False,
        )
        build_parser.set_defaults(subparser=self.__comamnd_name)

    def __get_sdk_path(self, args):
        root_dir = self.__config.get_root_dir()
        sdk_bin_dir = os.path.join(root_dir, args.sdk_bin_path)
        if not os.path.isdir(sdk_bin_dir):
            self.__log.error("Did not found %s", sdk_bin_dir)
            sys.exit(-1)
        if UtilsShell.is_linux():
            sdk_bin_dir = os.path.join(sdk_bin_dir, "lin")
        if UtilsShell.is_windows():
            sdk_bin_dir = os.path.join(sdk_bin_dir, "win")
        if not os.path.isdir(sdk_bin_dir):
            self.__log.error("Did not found %s", sdk_bin_dir)
            sys.exit(-1)
        self.__log.info("SDK-bin-dir: %s", sdk_bin_dir)
        return sdk_bin_dir

    def __detect_sdk_version(self, sdk_bin_dir):
        file_version = os.path.join(sdk_bin_dir, "include", "UnigineVersion.h")
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
        self.__log.info("Found SDK-version: %s", ret)
        return ret

    def __calculate_sha1_of_file(self, filepath):
        chunk_size = 4096
        sha1_hash = hashlib.sha1()
        try:
            with open(filepath, 'rb') as fil:
                while True:
                    chunk = fil.read(chunk_size)
                    if not chunk:
                        break  # End of file
                    sha1_hash.update(chunk)
            return sha1_hash.hexdigest()
        except FileNotFoundError:
            self.__log.error("File not found: %s", filepath)
            return "File not found."
        except Exception as err:  # pylint: disable=broad-except
            return f"An error occurred: {err}"

    def __copy_file(self, src_dir, trg_dir, filename):
        if not os.path.isdir(trg_dir):
            os.makedirs(trg_dir, exist_ok=True)
        trg_file = os.path.join(trg_dir, filename)
        trg_file_sha1 = ""
        if os.path.isfile(trg_file):
            trg_file_sha1 = self.__calculate_sha1_of_file(trg_file)
        src_file = os.path.join(src_dir, filename)
        src_file_sha1 = self.__calculate_sha1_of_file(src_file)
        if trg_file_sha1 == src_file_sha1:
            self.__log.info("File OK: %s", src_file)
            return
        if os.path.isfile(trg_file):
            os.remove(trg_file)
        if os.path.isfile(src_file):
            try:
                shutil.copyfile(src_file, trg_file)
                self.__log.error("File '%s' copied to '%s' successfully.", src_file, trg_file)
            except FileNotFoundError:
                self.__log.error("Error: Source file '%s' not found.", src_file)
            except PermissionError:
                self.__log.error("Error: Insufficient permissions to access or write to files.")
            except shutil.SameFileError:
                self.__log.error("Error: Source and destination are the same file.")
            except Exception as err:  # pylint: disable=broad-except
                self.__log.error("An unexpected error occurred: %s", str(err))

    def __sync_files(self, _, sdk_bin_dir):
        root_dir = self.__config.get_root_dir()
        _copy_dirs = [{
            "from": os.path.join(sdk_bin_dir, "include"),
            "to": os.path.join(root_dir, "include")
        }, {
            "from": os.path.join(sdk_bin_dir, "bin"),
            "to": os.path.join(root_dir, "bin")
        }]

        while len(_copy_dirs) > 0:
            _dirs = _copy_dirs.pop()

            for _file in os.listdir(_dirs["from"]):
                _source_file = os.path.join(_dirs["from"], _file)
                if os.path.isfile(_source_file):
                    self.__copy_file(_dirs["from"], _dirs["to"], _file)
                elif os.path.isdir(_source_file):
                    _copy_dirs.append({
                        "from": _source_file,
                        "to": os.path.join(_dirs["to"], _file)
                    })

    def run(self, args):
        """ run """
        self.__log.info("Start updating binaries...")
        # root_dir = self.__config.get_root_dir()
        sdk_bin_dir = self.__get_sdk_path(args)
        sdk_ver = self.__detect_sdk_version(sdk_bin_dir)
        self.__sync_files(sdk_ver, sdk_bin_dir)

        sys.exit(0)
