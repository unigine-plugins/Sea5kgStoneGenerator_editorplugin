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

#include "StoneGenerator.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

// ---------------------------------------------------------------------
// StoneGenerator

StoneGenerator::StoneGenerator() {
    m_pModel = nullptr;
    m_nBasicRadius = 2.0f;
}

StoneGenerator::~StoneGenerator() {
    if (m_pModel != nullptr) {
        m_pModel->clear();
    }
}

struct XYPoint {
    float x;
    float y;
};

struct ZLevel {
    float z;
    float z_radius;
    std::vector<XYPoint> xy_sectors;
};

bool StoneGenerator::generate(const StoneGeneratorConfig &conf) {
    std::cout << "m_nExpectedTriangles = " << conf.getEstimatedExpectedTriangles() << std::endl;

    if (m_pModel == nullptr) {
        m_pModel = new StoneGeneratorModel();
    }
    m_pModel->clear();
    if (!conf.getBasicGeometry()->generate(m_pModel, conf.getEstimatedExpectedTriangles(), m_nBasicRadius)) {
        return false;
    }

    m_random.setInitSeed(conf.getSeedRandom());

    this->processRemoveUnusefulTriangles(conf);
    // TODO reunion triangles
    this->processAttraction(conf);
    this->processSurfaceDistortion(conf);
    this->processResizeAndShift(conf);
    this->processNormals(conf);
    // this->processTangents(conf);
    this->processTexturing(conf);

    std::cout << "got triangles = " << m_pModel->getTriangles().size() << std::endl;
    return true;
}

const std::vector<StoneGeneratorTriangle *> &StoneGenerator::triangles() {
    return m_pModel->getTriangles();
}

const std::vector<StoneGeneratorPoint *> &StoneGenerator::points() {
    return m_pModel->getPoints();
}

StoneGeneratorPoint *StoneGenerator::addPoint(const StoneGeneratorConfig &conf, float x, float y, float z) {
    StoneGeneratorPoint *pPoint = nullptr;
    x = conf.getScaleX() * x;
    y = conf.getScaleY() * y;
    z = conf.getScaleZ() * z;
    int nX = x*100;
    int nY = y*100;
    int nZ = z*100;
    int nThreshold = 15; // 0.15
    int nSize = m_pModel->getPoints().size();
    for (int i = 0; i < nSize; i++) {
        if (m_pModel->getPoints()[i]->compare(nX, nY, nZ, nThreshold)) {
            pPoint = m_pModel->getPoints()[i];
            break;
        }
    }
    if (pPoint == nullptr) {
        pPoint = new StoneGeneratorPoint(x, y, z);
        m_pModel->getPoints().push_back(pPoint);
        pPoint->setIndex(nSize);
    }
    return pPoint;
}

bool StoneGenerator::processAttraction(const StoneGeneratorConfig &conf) {
    if (conf.getPointsOfAttraction() == 0) {
        return true;
    }
    float nStrongAttraction = conf.getStrongOfAttraction();
    if (nStrongAttraction < 0.1) {
        return true;
    }

    std::vector<StoneGeneratorPoint *> vAttractionPoints;

    float rk = 2.0;
    float fDiametr = m_nBasicRadius * 2.0; // TODO attraction radius
    int nWidth = fDiametr * rk * 100.0;
    for (int i = 0; i < conf.getPointsOfAttraction(); i++) {
        float x = float(m_random.getNextRandom() % nWidth) / 100.0;
        x = x - rk * m_nBasicRadius;
        x = x * conf.getScaleX();
        float y = float(m_random.getNextRandom() % nWidth) / 100.0;
        y = y - rk * m_nBasicRadius;
        y = y * conf.getScaleY();
        float z = float(m_random.getNextRandom() % nWidth) / 100.0;
        z = z - rk * m_nBasicRadius;
        z = z * conf.getScaleZ();
        vAttractionPoints.push_back(new StoneGeneratorPoint(x,y,z));
        std::cout << "i = " << i << "; x = " << x << "; y = " << y << "; z = " << z << std::endl;
    }

    for (int i = 0; i < m_pModel->getPoints().size(); i++) {
        float dx = 0.0f;
        float dy = 0.0f;
        float dz = 0.0f;
        int nCloseA = 0;
        float fMaxDistance = 50000.0;
        for (int a = 0; a < vAttractionPoints.size(); a++) {
            float fDistance = this->distance(m_pModel->getPoints()[i], vAttractionPoints[a]);
            if (fDistance < fMaxDistance) {
                nCloseA = a;
                fMaxDistance = fDistance;
            }
        }
        float fK = std::exp(-1 * fMaxDistance / nStrongAttraction );
        m_pModel->getPoints()[i]->addOffset(
            fK * (vAttractionPoints[nCloseA]->getX() - m_pModel->getPoints()[i]->getX()),
            fK * (vAttractionPoints[nCloseA]->getY() - m_pModel->getPoints()[i]->getY()),
            fK * (vAttractionPoints[nCloseA]->getZ() - m_pModel->getPoints()[i]->getZ())
        );
    }
    for (int i = 0; i < vAttractionPoints.size(); i++) {
        delete vAttractionPoints[i];
    }
    vAttractionPoints.clear();
    return true;
}

bool StoneGenerator::processSurfaceDistortion(const StoneGeneratorConfig &conf) {
    int nRandomDiff = 100.0 * conf.getSurfaceDistortion();
    float fMin = conf.getSurfaceDistortion();
    // std::cout << "nRandomDiff: " << nRandomDiff << std::endl;
    if (nRandomDiff > 0) {
        for (int i = 0; i < m_pModel->getPoints().size(); i++) {
            float nOffsetX = fMin + float(m_random.getNextRandom() % nRandomDiff) / 100.0;
            float nOffsetY = fMin + float(m_random.getNextRandom() % nRandomDiff) / 100.0;
            float nOffsetZ = fMin + float(m_random.getNextRandom() % nRandomDiff) / 100.0;
            m_pModel->getPoints()[i]->addOffset(nOffsetX, nOffsetY, nOffsetZ);
        }
    }
    return true;
}

bool StoneGenerator::processResizeAndShift(const StoneGeneratorConfig &conf) {
    if (m_pModel->getPoints().size() == 0) {
        return false;
    }

    float fDiameter = conf.getRadius()*2.0;
    float nSizeX = fDiameter * conf.getScaleX();
    float nSizeY = fDiameter * conf.getScaleY();
    float nSizeZ = fDiameter * conf.getScaleZ();

    float fMinX = m_pModel->getPoints()[0]->getX();
    float fMinY = m_pModel->getPoints()[0]->getY();
    float fMinZ = m_pModel->getPoints()[0]->getZ();
    float fMaxX = m_pModel->getPoints()[0]->getX();
    float fMaxY = m_pModel->getPoints()[0]->getY();
    float fMaxZ = m_pModel->getPoints()[0]->getZ();

    for (int i = 1; i < m_pModel->getPoints().size(); i++) {
        this->minXYZ(m_pModel->getPoints()[i], fMinX, fMinY, fMinZ);
        this->maxXYZ(m_pModel->getPoints()[i], fMaxX, fMaxY, fMaxZ);
    }

    // resize
    float fKX = nSizeX / (fMaxX - fMinX);
    float fKY = nSizeY / (fMaxY - fMinY);
    float fKZ = nSizeZ / (fMaxZ - fMinZ);

    if (conf.getBasicGeometry()->getId() == 2) { // if it's plane, TODO magic numbers
        fKZ = 1.0f;
    }

    // shift
    float fSX = -1.0 * (fMinX + (fMaxX - fMinX) / 2.0);
    float fSY = -1.0 * (fMinY + (fMaxY - fMinY) / 2.0);
    float fSZ = -1.0 * (fMinZ + (fMaxZ - fMinZ) / 2.0);

    for (int i = 0; i < m_pModel->getPoints().size(); i++) {
        m_pModel->getPoints()[i]->setXYZ(
            fKX * (m_pModel->getPoints()[i]->getX() + fSX),
            fKY * (m_pModel->getPoints()[i]->getY() + fSY),
            fKZ * (m_pModel->getPoints()[i]->getZ() + fSZ)
        );
    }

    return true;
}

bool StoneGenerator::processRemoveUnusefulTriangles(const StoneGeneratorConfig &conf) {
    std::vector<int> m_nRemoveTriangles;
    for (int i = 0; i < m_pModel->getTriangles().size(); i++) {
        StoneGeneratorTriangle *pTri = m_pModel->getTriangles()[i];
        if (pTri->p1() == pTri->p2() || pTri->p1() == pTri->p3() || pTri->p2() == pTri->p3()) {
            m_nRemoveTriangles.push_back(i);
        }
    }
    for (int i = m_nRemoveTriangles.size()-1; i >= 0; i--) {
        int nIndex = m_nRemoveTriangles[i];
        // std::cout << "Removing triangle " << nIndex << std::endl;
        StoneGeneratorTriangle *pTri = m_pModel->getTriangles()[nIndex];
        delete pTri;
        m_pModel->getTriangles()[nIndex] = nullptr;
        m_pModel->getTriangles().erase(m_pModel->getTriangles().begin() + nIndex);
    }
    std::cout << "Removed " << m_nRemoveTriangles.size() << std::endl;
    return true;
}

StoneGeneratorPoint StoneGenerator::calculateNormalForPoint(const StoneGeneratorConfig &conf, const StoneGeneratorPoint &triangleNormal0, StoneGeneratorPoint *p0) {
    std::vector<StoneGeneratorTriangle *> vFoundTriangles;
    StoneGeneratorPoint normal(0.0, 0.0, 0.0);
    vFoundTriangles.clear();
    findTrianglesByPoint(p0, vFoundTriangles);
    if (vFoundTriangles.size() == 0) {
        return normal;
    }

    for (int n = 0; n < vFoundTriangles.size(); n++) {
        StoneGeneratorPoint tmpNormal;
        vFoundTriangles[n]->calculateNormal(tmpNormal);
        normal.addOffset(tmpNormal.getX(), tmpNormal.getY(), tmpNormal.getZ());
    }
    float size = vFoundTriangles.size();
    normal.setXYZ(
        normal.getX() / size,
        normal.getY() / size,
        normal.getZ() / size
    );
    normal.normalizeToUnitVector();

    // deviation
    StoneGeneratorPoint tmpOffset;
    tmpOffset.setXYZ(
        normal.getX() - triangleNormal0.getX(),
        normal.getY() - triangleNormal0.getY(),
        normal.getZ() - triangleNormal0.getZ()
    );
    normal.setXYZ(triangleNormal0);

    float nLen = tmpOffset.length();
    if (nLen < 0.001f && nLen > -0.001f) {
        std::cout << "nLen " << nLen << std::endl;
    }
    // float k = nLen / conf.getDeviationOfNormals();
    float k = conf.getDeviationOfNormals();
    tmpOffset.setXYZ(
        k * tmpOffset.getX(),
        k * tmpOffset.getY(),
        k * tmpOffset.getZ()
    );

    normal.addOffset(
        tmpOffset.getX(),
        tmpOffset.getY(),
        tmpOffset.getZ()
    );
    normal.normalizeToUnitVector();

    return normal;
}

bool StoneGenerator::processNormals(const StoneGeneratorConfig &conf) {
    // std::cout << "processNormals start" << std::endl;
    std::vector<StoneGeneratorTriangle *> vFoundTriangles;
    StoneGeneratorPoint pCenter(0.0, 0.0, 0.0);

    for (int i = 0; i < m_pModel->getTriangles().size(); i++) {
        StoneGeneratorTriangle *pTriangle = m_pModel->getTriangles()[i];

        StoneGeneratorPoint triangleNormal0;
        pTriangle->calculateNormal(triangleNormal0);

        StoneGeneratorPoint triangleNormal1;

        triangleNormal1 = calculateNormalForPoint(conf, triangleNormal0, pTriangle->p1());
        pTriangle->normalP1()->setXYZ(triangleNormal1);

        triangleNormal1 = calculateNormalForPoint(conf, triangleNormal0, pTriangle->p2());
        pTriangle->normalP2()->setXYZ(triangleNormal1);

        triangleNormal1 = calculateNormalForPoint(conf, triangleNormal0, pTriangle->p3());
        pTriangle->normalP3()->setXYZ(triangleNormal1);
    }
    // std::cout << "processNormals end" << std::endl;
    return true;
}

bool StoneGenerator::processTangents(const StoneGeneratorConfig &conf) {
    std::cout << "processTangents start" << std::endl;
    // TODO
    std::vector<StoneGeneratorTriangle *> vFoundTriangles;

    for (int p_i = 0; p_i < m_pModel->getPoints().size(); p_i++) {
        // std::cout << "processNormals " << i << std::endl;

        StoneGeneratorPoint *p0 = m_pModel->getPoints()[p_i];

        vFoundTriangles.clear();
        findTrianglesByPoint(p0, vFoundTriangles);
        // std::cout << "processNormals vFoundTriangles.size() = " << vFoundTriangles.size() << std::endl;
        if (vFoundTriangles.size() == 0) {
            std::cout << "Warning: Not found triangles for point" << std::endl;
            continue;
        }
    }
    std::cout << "processTangents end" << std::endl;
    return true;
}

bool StoneGenerator::processTexturing(const StoneGeneratorConfig &conf) {
    if (m_pModel->getTriangles().size() == 0) {
        return false;
    }

    // calculate texture coordinates
    StoneGeneratorPoint *p1 = new StoneGeneratorPoint();
    StoneGeneratorPoint *p2 = new StoneGeneratorPoint();
    StoneGeneratorPoint *p3 = new StoneGeneratorPoint();
    StoneGeneratorTriangle *pTriangle = new StoneGeneratorTriangle(p1, p2, p3);

    // min max uv
    float nMaxU = 0.0f;
    float nMinU = 0.0f;
    float nMaxV = 0.0f;
    float nMinV = 0.0f;

    for (int i = 0; i < m_pModel->getTriangles().size(); i++) {
        pTriangle->copy(m_pModel->getTriangles()[i]);

        StoneGeneratorPoint middle_p;
        StoneGeneratorPoint middle_p_normal;
        pTriangle->calculateMiddlePoint(middle_p);
        pTriangle->calculateNormal(middle_p_normal);
        middle_p_normal.addOffset(
            middle_p.getX(),
            middle_p.getY(),
            middle_p.getZ()
        );

        float fRotX = this->angelXAxis(middle_p, middle_p_normal);
        pTriangle->rotateInXAxisAroundPoint(middle_p, fRotX);

        float fRotY = this->angelYAxis(middle_p, middle_p_normal);
        pTriangle->rotateInYAxisAroundPoint(middle_p, fRotY);

        m_pModel->getTriangles()[i]->t1().setXY(pTriangle->p1()->getX(), pTriangle->p1()->getY());
        m_pModel->getTriangles()[i]->t2().setXY(pTriangle->p2()->getX(), pTriangle->p2()->getY());
        m_pModel->getTriangles()[i]->t3().setXY(pTriangle->p3()->getX(), pTriangle->p3()->getY());
    }
    delete p1;
    delete p2;
    delete p3;
    delete pTriangle;

    // moving trinagles for pazzle
    std::vector<StoneGeneratorTriangle *> vTrianglesHandled;
    std::vector<StoneGeneratorTriangle *> vTrianglesHandling;
    vTrianglesHandling.push_back(m_pModel->getTriangles()[m_pModel->getTriangles().size()/2]);
    while (vTrianglesHandling.size() > 0) {
        StoneGeneratorTriangle *pTri = vTrianglesHandling[vTrianglesHandling.size()-1];
        vTrianglesHandling.pop_back();

        for (int i = 0; i < m_pModel->getTriangles().size(); i++) {
            StoneGeneratorTriangle *pTri2 = m_pModel->getTriangles()[i];
            if (pTri2 == pTri) {
                // std::cout << "Skip same trinagle" << std::endl;
                continue;
            }
            if (hasTriangle(vTrianglesHandled, pTri2)) {
                // std::cout << "Skip handled trinagle" << std::endl;
                continue;
            }
            bool bFound = false;
            for (int nT11 = 0; nT11 < 3; nT11++) {
                if (bFound) {
                    break;
                }
                for (int nT21 = 0; nT21 < 3; nT21++) {
                    if (pTri->getPointByIndex(nT11) == pTri2->getPointByIndex(nT21)) {
                        bFound = true;
                        int nT12 = -1;
                        int nT22 = -1;
                        if (pTri->getPointByIndex((nT11 + 1) % 3) == pTri2->getPointByIndex((nT21 + 1) % 3)) {
                            nT12 = (nT11 + 1) % 3;
                            nT22 = (nT21 + 1) % 3;
                        } else if (pTri->getPointByIndex((nT11 + 1) % 3) == pTri2->getPointByIndex((nT21 - 1) % 3)) {
                            nT12 = (nT11 + 1) % 3;
                            nT22 = (nT21 - 1) % 3;
                        } else if (pTri->getPointByIndex((nT11 - 1) % 3) == pTri2->getPointByIndex((nT21 + 1) % 3)) {
                            nT12 = (nT11 - 1) % 3;
                            nT22 = (nT21 + 1) % 3;
                        } else if (pTri->getPointByIndex((nT11 - 1) % 3) == pTri2->getPointByIndex((nT21 - 1) % 3)) {
                            nT12 = (nT11 - 1) % 3;
                            nT22 = (nT21 - 1) % 3;
                        }
                        if (nT12 == -1 || nT22 == -1)  {
                            bFound = false;
                            // std::cout << "Failed " << std::endl;
                            continue;
                        } else {
                            if (!hasTriangle(vTrianglesHandling, pTri2)) {
                                vTrianglesHandling.push_back(pTri2);
                            }
                            float fAngle = this->angelTex(
                                pTri->getTexPointByIndex(nT11),
                                pTri->getTexPointByIndex(nT12),
                                pTri2->getTexPointByIndex(nT21),
                                pTri2->getTexPointByIndex(nT22)
                            );
                            if (isnan(fAngle)) {
                                // std::cout << "fAngle " << fAngle << std::endl;
                                fAngle = 0.0;
                            }
                            pTri2->rotateTexPointsBy(nT21, fAngle);
                            pTri2->moveTexPointsBy(nT21, pTri->getTexPointByIndex(nT11));
                            break;
                        }
                    }
                }
            }
        }
        vTrianglesHandled.push_back(pTri);
    }

    // if (vTrianglesHandled.size() != m_pModel->getTriangles().size()) {
    //     std::cout << "vTrianglesHandled.size() = " << vTrianglesHandled.size() << std::endl;
    //     // std::cout << "m_pModel->getTriangles().size() = " << m_pModel->getTriangles().size() << std::endl;
    // } else {
    //     // std::cout << "m_pModel->getTriangles().size() == vTrianglesHandled.size() " << std::endl;
    // }

    for (int i = 0; i < m_pModel->getTriangles().size(); i++) {
        StoneGeneratorTriangle *pTri = m_pModel->getTriangles()[i];
        this->minmaxUV(pTri->t1(), nMinU, nMaxU, nMinV, nMaxV);
        this->minmaxUV(pTri->t2(), nMinU, nMaxU, nMinV, nMaxV);
        this->minmaxUV(pTri->t3(), nMinU, nMaxU, nMinV, nMaxV);
    }

    // normalize coordinates to 0..1
    float dU = nMaxU - nMinU;
    float dV = nMaxV - nMinV;
    for (int i = 0; i < m_pModel->getTriangles().size(); i++) {
        StoneGeneratorTriangle *pTri = m_pModel->getTriangles()[i];
        this->normalizeUV(pTri->t1(), nMinU, nMaxU, nMinV, nMaxV);
        this->normalizeUV(pTri->t2(), nMinU, nMaxU, nMinV, nMaxV);
        this->normalizeUV(pTri->t3(), nMinU, nMaxU, nMinV, nMaxV);
    }
    return true;
}

void StoneGenerator::findTrianglesByPoint(StoneGeneratorPoint *p1, std::vector<StoneGeneratorTriangle *> &vTriangles) {
    for (int i = 0; i < m_pModel->getTriangles().size(); i++) {
        if (m_pModel->getTriangles()[i]->hasPoint(p1)) {
            vTriangles.push_back(m_pModel->getTriangles()[i]);
        }
    }
}

void StoneGenerator::findTrianglesByPoints2(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2, std::vector<StoneGeneratorTriangle *> &vTriangles) {
    for (int i = 0; i < m_pModel->getTriangles().size(); i++) {
        StoneGeneratorTriangle *pTri = m_pModel->getTriangles()[i];
        if (pTri->hasPoint(p1) && pTri->hasPoint(p2)) {
            vTriangles.push_back(pTri);
        }
    }
}

float StoneGenerator::distance(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2) {
    float dx = p1->getX() - p2->getX();
    float dy = p1->getY() - p2->getY();
    float dz = p1->getZ() - p2->getZ();
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

float StoneGenerator::distanceUV(StoneGeneratorTexturePoint &p1, StoneGeneratorTexturePoint &p2) {
    float dx = p1.x() - p2.x();
    float dy = p1.y() - p2.y();
    return std::sqrt(dx*dx + dy*dy);
}

float StoneGenerator::angel(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float _len = std::sqrt(dx * dx + dy * dy);
    int nLen = std::abs(_len*100000);
    if (nLen < 1000) {
        return 0.0;
    }
    float ret = std::asin(dx / _len);
    if (dy < 0) {
        ret = -1 * ret;
    } else {
        ret = ret;
    }
    return ret;
}

float StoneGenerator::angelXAxis(const StoneGeneratorPoint &p1, const StoneGeneratorPoint &p2) {
    float rot = angel(p1.getY(), p1.getZ(), p2.getY(), p2.getZ());
    return rot;
}

float StoneGenerator::angelYAxis(const StoneGeneratorPoint &p1, const StoneGeneratorPoint &p2) {
    float rot = this->angel(p1.getX(), p1.getZ(), p2.getX(), p2.getZ());
    rot = -1.0 * rot;
    return rot;
}

float StoneGenerator::angelXY(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2) {
    float dy = p2->getY() - p1->getY();
    float dx = p2->getX() - p1->getX();
    float c = std::sqrt(dx*dx + dy*dy);
    return std::asin(dx/c);
}

float StoneGenerator::angelZX(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2) {
    float dz = p2->getZ() - p1->getZ();
    float dx = p2->getX() - p1->getX();
    float c = std::sqrt(dx*dx + dz*dz);
    return std::acos(dz/c);
}

float StoneGenerator::angelZY(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2) {
    float dz = p2->getZ() - p1->getZ();
    float dy = p2->getY() - p1->getY();
    float c = std::sqrt(dy*dy + dz*dz);
    return std::acos(dz/c);
}

float StoneGenerator::angelTex(StoneGeneratorTexturePoint &t11, StoneGeneratorTexturePoint &t12, StoneGeneratorTexturePoint &t21, StoneGeneratorTexturePoint &t22) {
    float dx1 = t12.x() - t11.x();
    float dy1 = t12.y() - t11.y();
    float dx2 = t22.x() - t21.x();
    float dy2 = t22.y() - t21.y();
    float dxy_scalar = dx1 * dx2 + dy2 * dy1;
    float a = std::sqrt(dx1*dx1 + dy1*dy1);
    float b = std::sqrt(dx2*dx2 + dy2*dy2);
    return std::acos(dxy_scalar / (a*b));
}

bool StoneGenerator::hasTriangle(const std::vector<StoneGeneratorTriangle *> &vTriangles, StoneGeneratorTriangle *p) {
    for (int i = 0; i < vTriangles.size(); i++) {
        if (p == vTriangles[i]) {
            return true;
        }
    }
    return false;
}

void StoneGenerator::minmaxUV(StoneGeneratorTexturePoint &p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV) {
    nMinU = std::min(nMinU, p1.x());
    nMaxU = std::max(nMaxU, p1.x());
    nMinV = std::min(nMinV, p1.y());
    nMaxV = std::max(nMaxV, p1.y());
}

void StoneGenerator::normalizeUV(StoneGeneratorTexturePoint &p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV) {
    float fMainSide = nMaxU - nMinU;
    float dV = nMaxV - nMinV;
    float vK = fMainSide / dV;

    float u = p1.x();
    float v = p1.y();
    u = (u - nMinU) / fMainSide;
    v = ((v - vK * nMinV) / fMainSide);
    p1.setXY(u, v);
}

void StoneGenerator::minXYZ(StoneGeneratorPoint *p1, float &nMinX, float &nMinY, float &nMinZ) {
    nMinX = std::min(nMinX, p1->getX());
    nMinY = std::min(nMinY, p1->getY());
    nMinZ = std::min(nMinZ, p1->getZ());
}

void StoneGenerator::maxXYZ(StoneGeneratorPoint *p1, float &nMaxX, float &nMaxY, float &nMaxZ) {
    nMaxX = std::max(nMaxX, p1->getX());
    nMaxY = std::max(nMaxY, p1->getY());
    nMaxZ = std::max(nMaxZ, p1->getZ());
}
