#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os
import math
import platform



def angle(va, vb):
    ab = va[0] * vb[0] + va[1] * vb[1] + va[2] * vb[2]
    la = math.sqrt(va[0]*va[0] + va[1]*va[1] + va[2]*va[2])
    lb = math.sqrt(vb[0]*vb[0] + vb[1]*vb[1] + vb[2]*vb[2])
    cos_a = ab / (la*lb)
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
            b = [x,y,z]
            if b == [0.0,0.0,0.0]:
                continue

            _angle = angle(a, b)
            if _angle == 90.0:
                print(b, _angle)
