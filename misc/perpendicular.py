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

""" Test calculation perpendicular """

import math


def angle(va, vb):
    """ calculate angle """
    ab = va[0] * vb[0] + va[1] * vb[1] + va[2] * vb[2]
    la = math.sqrt(va[0] * va[0] + va[1] * va[1] + va[2] * va[2])
    lb = math.sqrt(vb[0] * vb[0] + vb[1] * vb[1] + vb[2] * vb[2])
    cos_a = ab / (la * lb)
    if cos_a >= 1:
        return 0
    if cos_a <= -1:
        return 180
    angle_rad = math.acos(cos_a)
    return math.degrees(angle_rad)


a = [1.1, 3, 4]

# -4, 0, 1
# -3, 1, 0

# -3.5, 0.5, 0.5

# b1 = [1.5 , -2.5, 1.5]
# _angle = angle(a, b1)
# print(b1, _angle)


# sys.exit(0)

possible_values = [0]
for x in a:
    possible_values.append(x)
    possible_values.append(-x)

for x in possible_values:
    for y in possible_values:
        for z in possible_values:
            b = [x, y, z]
            if b == [0.0, 0.0, 0.0]:
                continue

            _angle = angle(a, b)
            if _angle == 90.0:
                print(b, _angle)
