#include "StoneGeneratorBasicGeometry.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

#include <StoneGeneratorTriangle.h>
#include <StoneGeneratorConfig.h>

// ---------------------------------------------------------------------
// StoneGeneratorBasicGeometry

StoneGeneratorBasicGeometry::StoneGeneratorBasicGeometry(int nId, const std::string &sName) {
    m_sName = sName;
    m_nId = nId;
    // if (g_mapBasicGeometries != nullptr) {
    //     g_mapBasicGeometries = new std::map<int, StoneGeneratorBasicGeometry *>();
    // }
    // (*g_mapBasicGeometries)[m_nId] = this;
}

int StoneGeneratorBasicGeometry::getId() {
    return m_nId;
}

std::string StoneGeneratorBasicGeometry::getName() {
    return m_sName;
}

const std::vector<StoneGeneratorPoint *> &StoneGeneratorBasicGeometry::getPoints() const {
    return m_vPoints;
}

StoneGeneratorPoint *StoneGeneratorBasicGeometry::addPoint(const StoneGeneratorConfig &conf, float x, float y, float z) {
    StoneGeneratorPoint *pPoint = nullptr;
    x = conf.getScaleX() * x;
    y = conf.getScaleY() * y;
    z = conf.getScaleZ() * z;
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
