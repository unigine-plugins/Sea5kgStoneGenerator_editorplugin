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