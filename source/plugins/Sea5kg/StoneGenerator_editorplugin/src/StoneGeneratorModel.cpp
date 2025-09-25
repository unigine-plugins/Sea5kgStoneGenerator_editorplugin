/*
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

#include "StoneGeneratorModel.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

// ---------------------------------------------------------------------
// StoneGeneratorModel

std::vector<StoneGeneratorPoint *> &StoneGeneratorModel::getPoints() {
    return m_vPoints;
}

std::vector<StoneGeneratorTriangle *> &StoneGeneratorModel::getTriangles() {
    return m_vTriangles;
}

void StoneGeneratorModel::clear() {

    for (int i = 0; i < m_vPoints.size(); i++) {
        delete m_vPoints[i];
        m_vPoints[i] = nullptr;
    }
    m_vPoints.clear();

    for (int i = 0; i < m_vTriangles.size(); i++) {
        delete m_vTriangles[i];
        m_vTriangles[i] = nullptr;
    }
    m_vTriangles.clear();
}

StoneGeneratorPoint *StoneGeneratorModel::addPoint(float x, float y, float z) {
    StoneGeneratorPoint *pPoint = nullptr;
    int nX = x*100;
    int nY = y*100;
    int nZ = z*100;
    int nThreshold = 15; // 0.15
    int nSize = m_vPoints.size();
    for (int i = 0; i < nSize; i++) {
        if (m_vPoints[i]->compare(nX, nY, nZ, nThreshold)) {
            pPoint = m_vPoints[i];
            break;
        }
    }
    if (pPoint == nullptr) {
        pPoint = new StoneGeneratorPoint(x, y, z);
        m_vPoints.push_back(pPoint);
        pPoint->setIndex(nSize);
    }
    return pPoint;
}

StoneGeneratorTriangle *StoneGeneratorModel::addTriangle(StoneGeneratorPoint *p0, StoneGeneratorPoint *p1, StoneGeneratorPoint *p2) {
    StoneGeneratorTriangle *pTriangle = new StoneGeneratorTriangle(p0, p1, p2);
    m_vTriangles.push_back(pTriangle);
    return pTriangle;
}