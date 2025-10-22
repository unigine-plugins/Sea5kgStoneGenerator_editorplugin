#!/usr/bin/env python3

# MIT License

# Copyright (c) 2022-2025 mrseakg@gmail.com

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Repository:
# https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin

""" Project Manager for Sea5kgStoneGenerator """

import sys
import os
import argparse
import libpm

ROOT_DIR = os.path.dirname(os.path.realpath(__file__))
# find the root dir (dir which contains dir '.git')
_NEW_ROOT_DIR = ROOT_DIR
while not os.path.isdir(os.path.join(_NEW_ROOT_DIR, '.git')):
    _NEW_ROOT_DIR = os.path.join(_NEW_ROOT_DIR, '..')
    _NEW_ROOT_DIR = os.path.normpath(_NEW_ROOT_DIR)
if len(_NEW_ROOT_DIR) > 3:  # not a "C:" and not a "/"
    ROOT_DIR = _NEW_ROOT_DIR

CONFIG = libpm.PmConfig(ROOT_DIR)

COMMANDS = [
    # libpm.CommandCheckUtf8Encoding(CONFIG),
    libpm.CommandPyCheck(CONFIG),
    # libpm.CommandClangFormat(CONFIG),
    # libpm.CommandStats(CONFIG),
    libpm.CommandCopyrightsCheck(CONFIG),
    # libpm.CommandCopyrightsUpdate(CONFIG),
]


def print_custom_help(parser):
    """ print more comfortabl help with subcomamnds"""
    parser.print_help()
    # retrieve subparsers from parser
    subparsers_actions = [
        action for action in parser._actions  # pylint: disable=protected-access
        if isinstance(action, argparse._SubParsersAction)  # pylint: disable=protected-access
    ]
    print("")
    subcommand_name_maxlen = 0
    for subparsers_action in subparsers_actions:
        for choice, subparser in subparsers_action.choices.items():
            subcommand_name_maxlen = max(subcommand_name_maxlen, len(choice))
    subcommand_name_maxlen += 3
    for subparsers_action in subparsers_actions:
        for choice, subparser in subparsers_action.choices.items():
            subcommand_short_help = "  " + choice.ljust(subcommand_name_maxlen, " ")
            subcommand_short_help += subparser.description
            print(subcommand_short_help)
            # print(subparser.format_help())
    print("")
    parser.exit()


class CustomActionHelp(argparse._HelpAction):  # pylint: disable=protected-access
    """ custom help action """
    def __call__(self, parser, namespace, values, option_string=None):
        print_custom_help(parser)


if __name__ == "__main__":
    MAIN_PARSER = argparse.ArgumentParser(
        prog='txpm',
        description='Project Manager for StoneGenerator',
        epilog='Helper tools for work with current project',
        add_help=False
    )
    MAIN_PARSER.add_argument('--help', '-h', action=CustomActionHelp, help='help')

    SUBCOMMANDS = MAIN_PARSER.add_subparsers(title='subcommands')
    for _comamnd in COMMANDS:
        _comamnd.register(SUBCOMMANDS)
    ARGS = MAIN_PARSER.parse_args()
    if 'subparser' not in ARGS:
        print_custom_help(MAIN_PARSER)
        sys.exit(1)
    SUBCOMMAND = ARGS.subparser
    for _comamnd in COMMANDS:
        if _comamnd.get_command_name() == SUBCOMMAND:
            _comamnd.run(ARGS)
