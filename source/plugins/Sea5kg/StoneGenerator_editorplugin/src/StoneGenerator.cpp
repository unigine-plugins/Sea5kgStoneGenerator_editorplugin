#include "StoneGenerator.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

// ---------------------------------------------------------------------
// StoneGenerator

StoneGenerator::StoneGenerator() {
}

StoneGenerator::~StoneGenerator() {
    this->clear();
}

void StoneGenerator::clear() {
    for (int i = 0; i < m_vPoints.size(); i++) {
        StoneGeneratorPoint *pPoint = m_vPoints[i];
        delete pPoint;
        m_vPoints[i] = nullptr;
    }
    m_vPoints.clear();

    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneGeneratorTriangle *pTri = m_vTriangles[i];
        delete pTri;
        m_vTriangles[i] = nullptr;
    }
    m_vTriangles.clear();
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

    if (conf.getBasicGeometry() == StoneGeneratorBasicGeomery::SPHERE) {
        if (!this->generateBasicSpheres(conf)) {
            return false;
        }
    } else if (conf.getBasicGeometry() == StoneGeneratorBasicGeomery::CUBE) {
        if (!this->generateBasicCube(conf)) {
            return false;
        }
    } else {
        std::cout << "Unknown basic geometry" << std::endl;
        return false;
    }

    this->processRemoveUnusefulTriangles(conf);
    // TODO reunion triangles
    this->processAttraction(conf);
    this->processRandom(conf);
    this->processResizeAndShift(conf);
    this->processNormals(conf);
    // this->processTangents(conf);
    this->processTexturing(conf);

    std::cout << "got triangles = " << m_vTriangles.size() << std::endl;
    return true;
}

const std::vector<StoneGeneratorTriangle *> &StoneGenerator::triangles() {
    return m_vTriangles;
}

const std::vector<StoneGeneratorPoint *> &StoneGenerator::points() {
    return m_vPoints;
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

bool StoneGenerator::generateBasicSpheres(const StoneGeneratorConfig &conf) {
    // TODO redesign
    int nK = conf.getEstimatedExpectedTriangles()/2;
    // std::cout << "nK = " << nK << std::endl;
    nK = sqrt(nK);
    // std::cout << "nK = " << nK << std::endl;
    if (nK % 2 == 1) {
        // kostyl
        nK += 1; // to even number
    }
    std::cout << "nK = " << nK << std::endl;

    // calculate coordinates
    float spp = 2*M_PI / float(nK);
    float z_spp = M_PI / float(nK); // todo scale z here
    std::cout << "spp = " << spp << std::endl;
    // int nTexX = 0.2;
    // int nTexY = 0.2;
    std::vector<ZLevel> levels_z;
    for (int zz0 = 0; zz0 <= nK; zz0++) {
        ZLevel lvl;
        lvl.xy_sectors.clear();
        float z_angel = z_spp * float(zz0);
        lvl.z_radius = conf.getRadius() * sin( z_angel );
        lvl.z = conf.getRadius() * cos( z_angel );
        for (int rr0 = 0; rr0 < nK; rr0++) {
            XYPoint xy;
            float angel = spp * float(rr0);
            xy.x = lvl.z_radius * cos( angel);
            xy.y = lvl.z_radius * sin( angel);
            lvl.xy_sectors.push_back(xy);
        }
        levels_z.push_back(lvl);
    }

    for (int zz0 = 0; zz0 < levels_z.size() - 1; zz0++) {
        ZLevel lvl_z = levels_z[zz0];
        ZLevel lvl_z_next = levels_z[zz0+1];

        std::vector<XYPoint> xy_sectors = lvl_z.xy_sectors;
        for (int i_xy = 0; i_xy < xy_sectors.size(); i_xy++) {
            int i_xy_next = (i_xy+1) % nK;
            XYPoint x0y0 = xy_sectors[i_xy];
            XYPoint x0y1 = xy_sectors[i_xy_next];
            XYPoint x1y0 = lvl_z_next.xy_sectors[i_xy];
            XYPoint x1y1 = lvl_z_next.xy_sectors[i_xy_next];
            StoneGeneratorPoint *pPoint00 = addPoint(conf, x0y0.x, x0y0.y, lvl_z.z);
            StoneGeneratorPoint *pPoint01 = addPoint(conf, x0y1.x, x0y1.y, lvl_z.z);
            StoneGeneratorPoint *pPoint10 = addPoint(conf, x1y0.x, x1y0.y, lvl_z_next.z);
            StoneGeneratorPoint *pPoint11 = addPoint(conf, x1y1.x, x1y1.y, lvl_z_next.z);

            // 00 * ----- * 01
            //    |       | 
            // 10 * ----- * 11
            if (pPoint00 != pPoint01 && pPoint01 != pPoint10 && pPoint10 != pPoint00) {
                StoneGeneratorTriangle *pTriangle1 = new StoneGeneratorTriangle(
                    pPoint01,
                    pPoint00,
                    pPoint10

                    // pPoint00,
                    // pPoint01,
                    // pPoint10
                );
                m_vTriangles.push_back(pTriangle1);
            }

            if (i_xy > 0 || i_xy < xy_sectors.size() - 1) {
                // if (pPoint00 != pPoint01 && pPoint01 != pPoint10 && pPoint10 != pPoint00) {
                    StoneGeneratorTriangle *pTriangle2 = new StoneGeneratorTriangle(
                        pPoint01,
                        pPoint10,
                        pPoint11
                    );
                    m_vTriangles.push_back(pTriangle2);
                // }
            }
        }
    }
    return true;
}

bool StoneGenerator::generateBasicCube(const StoneGeneratorConfig &conf) {
    float nRadius = conf.getRadius();

    float fK = conf.getEstimatedExpectedTriangles() / 6.0; // 6 sides
    fK = fK / 2.0;
    fK = std::sqrt(fK); // squares on each side;
    int nK = std::round(fK);

    float nStep = 2*nRadius / nK;

    float nX0 = -nRadius;
    float nX1 = nRadius;

    float nY0 = -nRadius;
    float nY1 = nRadius;

    float nZ0 = -nRadius;
    float nZ1 = nRadius;

    for (int a = 0; a < nK; a++) {
        for (int b = 0; b < nK; b++) {
            float fA0 = float(a)*nStep - nRadius;
            float fB0 = float(b)*nStep - nRadius;
            float fA1 = fA0 + nStep;
            float fB1 = fB0 + nStep;
            // bottom
            {
                StoneGeneratorPoint *pPoint00 = addPoint(conf, fA0, fB0, nZ0);
                StoneGeneratorPoint *pPoint01 = addPoint(conf, fA0, fB1, nZ0);
                StoneGeneratorPoint *pPoint10 = addPoint(conf, fA1, fB0, nZ0);
                StoneGeneratorPoint *pPoint11 = addPoint(conf, fA1, fB1, nZ0);
                StoneGeneratorTriangle *pTriangle1 = new StoneGeneratorTriangle(pPoint00, pPoint01, pPoint11);
                m_vTriangles.push_back(pTriangle1);
                StoneGeneratorTriangle *pTriangle2 = new StoneGeneratorTriangle(pPoint00, pPoint11, pPoint10);
                m_vTriangles.push_back(pTriangle2);
            }

            // top
            {
                StoneGeneratorPoint *pPoint00 = addPoint(conf, fA0, fB0, nZ1);
                StoneGeneratorPoint *pPoint01 = addPoint(conf, fA0, fB1, nZ1);
                StoneGeneratorPoint *pPoint10 = addPoint(conf, fA1, fB0, nZ1);
                StoneGeneratorPoint *pPoint11 = addPoint(conf, fA1, fB1, nZ1);
                StoneGeneratorTriangle *pTriangle1 = new StoneGeneratorTriangle(pPoint11, pPoint01, pPoint00);
                m_vTriangles.push_back(pTriangle1);
                StoneGeneratorTriangle *pTriangle2 = new StoneGeneratorTriangle(pPoint10, pPoint11, pPoint00);
                m_vTriangles.push_back(pTriangle2);
            }

            // left
            {
                StoneGeneratorPoint *pPoint00 = addPoint(conf, nX0, fB0, fA0);
                StoneGeneratorPoint *pPoint01 = addPoint(conf, nX0, fB0, fA1);
                StoneGeneratorPoint *pPoint10 = addPoint(conf, nX0, fB1, fA0);
                StoneGeneratorPoint *pPoint11 = addPoint(conf, nX0, fB1, fA1);
                StoneGeneratorTriangle *pTriangle1 = new StoneGeneratorTriangle(pPoint00, pPoint01, pPoint11);
                m_vTriangles.push_back(pTriangle1);
                StoneGeneratorTriangle *pTriangle2 = new StoneGeneratorTriangle(pPoint00, pPoint11, pPoint10);
                m_vTriangles.push_back(pTriangle2);
            }

            // right
            {
                StoneGeneratorPoint *pPoint00 = addPoint(conf, nX1, fB0, fA0);
                StoneGeneratorPoint *pPoint01 = addPoint(conf, nX1, fB0, fA1);
                StoneGeneratorPoint *pPoint10 = addPoint(conf, nX1, fB1, fA0);
                StoneGeneratorPoint *pPoint11 = addPoint(conf, nX1, fB1, fA1);
                StoneGeneratorTriangle *pTriangle1 = new StoneGeneratorTriangle(pPoint11, pPoint01, pPoint00);
                m_vTriangles.push_back(pTriangle1);
                StoneGeneratorTriangle *pTriangle2 = new StoneGeneratorTriangle(pPoint10, pPoint11, pPoint00);
                m_vTriangles.push_back(pTriangle2);
            }

            // front
            {
                StoneGeneratorPoint *pPoint00 = addPoint(conf, fB0, nY1, fA0);
                StoneGeneratorPoint *pPoint01 = addPoint(conf, fB0, nY1, fA1);
                StoneGeneratorPoint *pPoint10 = addPoint(conf, fB1, nY1, fA0);
                StoneGeneratorPoint *pPoint11 = addPoint(conf, fB1, nY1, fA1);
                StoneGeneratorTriangle *pTriangle1 = new StoneGeneratorTriangle(pPoint00, pPoint01, pPoint11);
                m_vTriangles.push_back(pTriangle1);
                StoneGeneratorTriangle *pTriangle2 = new StoneGeneratorTriangle(pPoint00, pPoint11, pPoint10);
                m_vTriangles.push_back(pTriangle2);
            }

            // end
            {
                StoneGeneratorPoint *pPoint00 = addPoint(conf, fB0, nY0, fA0);
                StoneGeneratorPoint *pPoint01 = addPoint(conf, fB0, nY0, fA1);
                StoneGeneratorPoint *pPoint10 = addPoint(conf, fB1, nY0, fA0);
                StoneGeneratorPoint *pPoint11 = addPoint(conf, fB1, nY0, fA1);
                StoneGeneratorTriangle *pTriangle1 = new StoneGeneratorTriangle(pPoint11, pPoint01, pPoint00);
                m_vTriangles.push_back(pTriangle1);
                StoneGeneratorTriangle *pTriangle2 = new StoneGeneratorTriangle(pPoint10, pPoint11, pPoint00);
                m_vTriangles.push_back(pTriangle2);
            }
        }
    }
    return true;
}

bool StoneGenerator::processAttraction(const StoneGeneratorConfig &conf) {
    if (conf.getPointsOfAttraction() == 0) {
        return true;
    }
    std::vector<StoneGeneratorPoint *> vAttractionPoints;
    float nStrongAttraction = conf.getStrongOfAttraction();
    float rk = 2.0;
    float fDiametr = conf.getRadius() * 2.0;
    int nWidth = fDiametr * rk * 100.0;
    for (int i = 0; i < conf.getPointsOfAttraction(); i++) {
        float x = float(std::rand() % nWidth) / 100.0;
        x = x - rk * conf.getRadius();
        x = x * conf.getScaleX();
        float y = float(std::rand() % nWidth) / 100.0;
        y = y - rk * conf.getRadius();
        y = y * conf.getScaleY();
        float z = float(std::rand() % nWidth) / 100.0;
        z = z - rk * conf.getRadius();
        z = z * conf.getScaleZ();
        vAttractionPoints.push_back(new StoneGeneratorPoint(x,y,z));
        std::cout << "i = " << i << "; x = " << x << "; y = " << y << "; z = " << z << std::endl;
    }

    for (int i = 0; i < m_vPoints.size(); i++) {
        float dx = 0.0f;
        float dy = 0.0f;
        float dz = 0.0f;
        int nCloseA = 0;
        float fMaxDistance = 50000.0;
        for (int a = 0; a < vAttractionPoints.size(); a++) {
            float fDistance = this->distance(m_vPoints[i], vAttractionPoints[a]);
            if (fDistance < fMaxDistance) {
                nCloseA = a;
                fMaxDistance = fDistance;
            }
        }
        float fK = std::exp(-1 * fMaxDistance / nStrongAttraction );
        m_vPoints[i]->addOffset(
            fK * (vAttractionPoints[nCloseA]->x() - m_vPoints[i]->x()),
            fK * (vAttractionPoints[nCloseA]->y() - m_vPoints[i]->y()),
            fK * (vAttractionPoints[nCloseA]->z() - m_vPoints[i]->z())
        );
    }
    for (int i = 0; i < vAttractionPoints.size(); i++) {
        delete vAttractionPoints[i];
    }
    vAttractionPoints.clear();
    return true;
}

bool StoneGenerator::processRandom(const StoneGeneratorConfig &conf) {
    int nRandomDiff = 100.0 * conf.getSurfaceDistortion();
    float fMin = conf.getSurfaceDistortion();
    std::cout << "nRandomDiff: " << nRandomDiff << std::endl;
    if (nRandomDiff > 0) {
        for (int i = 0; i < m_vPoints.size(); i++) {
            float nOffsetX = fMin + float(std::rand() % nRandomDiff) / 100.0;
            float nOffsetY = fMin + float(std::rand() % nRandomDiff) / 100.0;
            float nOffsetZ = fMin + float(std::rand() % nRandomDiff) / 100.0;
            m_vPoints[i]->addOffset(nOffsetX, nOffsetY, nOffsetZ);
        }
    }
    return true;
}

bool StoneGenerator::processResizeAndShift(const StoneGeneratorConfig &conf) {
    if (m_vPoints.size() == 0) {
        return false;
    }

    float fDiameter = conf.getRadius()*2.0;
    float nSizeX = fDiameter * conf.getScaleX();
    float nSizeY = fDiameter * conf.getScaleY();
    float nSizeZ = fDiameter * conf.getScaleZ();

    float fMinX = m_vPoints[0]->x();
    float fMinY = m_vPoints[0]->y();
    float fMinZ = m_vPoints[0]->z();
    float fMaxX = m_vPoints[0]->x();
    float fMaxY = m_vPoints[0]->y();
    float fMaxZ = m_vPoints[0]->z();

    for (int i = 1; i < m_vPoints.size(); i++) {
        this->minXYZ(m_vPoints[i], fMinX, fMinY, fMinZ);
        this->maxXYZ(m_vPoints[i], fMaxX, fMaxY, fMaxZ);
    }

    // resize
    float fKX = nSizeX / (fMaxX - fMinX);
    float fKY = nSizeY / (fMaxY - fMinY);
    float fKZ = nSizeZ / (fMaxZ - fMinZ);

    // shift
    float fSX = -1.0 * (fMinX + (fMaxX - fMinX) / 2.0);
    float fSY = -1.0 * (fMinY + (fMaxY - fMinY) / 2.0);
    float fSZ = -1.0 * (fMinZ + (fMaxZ - fMinZ) / 2.0);

    for (int i = 0; i < m_vPoints.size(); i++) {
        m_vPoints[i]->setXYZ(
            fKX * (m_vPoints[i]->x() + fSX),
            fKY * (m_vPoints[i]->y() + fSY),
            fKZ * (m_vPoints[i]->z() + fSZ)
        );
    }

    return true;
}

bool StoneGenerator::processRemoveUnusefulTriangles(const StoneGeneratorConfig &conf) {
    std::vector<int> m_nRemoveTriangles;
    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneGeneratorTriangle *pTri = m_vTriangles[i];
        if (pTri->p1() == pTri->p2() || pTri->p1() == pTri->p3() || pTri->p2() == pTri->p3()) {
            m_nRemoveTriangles.push_back(i);
        }
    }
    for (int i = m_nRemoveTriangles.size()-1; i >= 0; i--) {
        int nIndex = m_nRemoveTriangles[i];
        // std::cout << "Removing triangle " << nIndex << std::endl;
        StoneGeneratorTriangle *pTri = m_vTriangles[nIndex];
        delete pTri;
        m_vTriangles[nIndex] = nullptr;
        m_vTriangles.erase(m_vTriangles.begin() + nIndex);
    }
    std::cout << "Removed " << m_nRemoveTriangles.size() << std::endl;
    return true;
}

bool StoneGenerator::processNormals(const StoneGeneratorConfig &conf) {
    std::cout << "processNormals start" << std::endl;
    std::vector<StoneGeneratorTriangle *> vFoundTriangles;
    StoneGeneratorPoint pCenter(0.0, 0.0, 0.0);
    for (int p_i = 0; p_i < m_vPoints.size(); p_i++) {
        StoneGeneratorPoint *p0 = m_vPoints[p_i];

        vFoundTriangles.clear();
        findTrianglesByPoint(p0, vFoundTriangles);
        if (vFoundTriangles.size() == 0) {
            continue;
        }
        StoneGeneratorPoint normal(0.0, 0.0, 0.0);
        StoneGeneratorPoint middle_p;
        StoneGeneratorPoint middle_p_normal;
        for (int n = 0; n < vFoundTriangles.size(); n++) {
            vFoundTriangles[n]->calculateMiddlePointAndNormal(middle_p, middle_p_normal);

            middle_p_normal.setXYZ(
                (middle_p_normal.x() - middle_p.x()),
                (middle_p_normal.y() - middle_p.y()),
                (middle_p_normal.z() - middle_p.z())
            );
            middle_p_normal.normalizeToUnitVector();
            normal.addOffset(middle_p_normal.x(), middle_p_normal.y(), middle_p_normal.z());
        }
        float size = vFoundTriangles.size();
        normal.setXYZ(
            normal.x() / size,
            normal.y() / size,
            normal.z() / size
        );
        normal.normalizeToUnitVector();
        p0->setNormal(
            normal.x(),
            normal.y(),
            normal.z()
        );
    }
    std::cout << "processNormals end" << std::endl;
    return true;
}

bool StoneGenerator::processTangents(const StoneGeneratorConfig &conf) {
    std::cout << "processTangents start" << std::endl;
    // TODO
    std::vector<StoneGeneratorTriangle *> vFoundTriangles;

    for (int p_i = 0; p_i < m_vPoints.size(); p_i++) {
        // std::cout << "processNormals " << i << std::endl;

        StoneGeneratorPoint *p0 = m_vPoints[p_i];

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
    if (m_vTriangles.size() == 0) {
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

    for (int i = 0; i < m_vTriangles.size(); i++) {
        pTriangle->copy(m_vTriangles[i]);

        StoneGeneratorPoint middle_p;
        StoneGeneratorPoint middle_p_normal;
        pTriangle->calculateMiddlePointAndNormal(middle_p, middle_p_normal);
        float fRotX = this->angelXAxis(middle_p, middle_p_normal);
        pTriangle->rotateInXAxisAroundPoint(middle_p, fRotX);

        float fRotY = this->angelYAxis(middle_p, middle_p_normal);
        pTriangle->rotateInYAxisAroundPoint(middle_p, fRotY);

        m_vTriangles[i]->t1().setXY(pTriangle->p1()->x(), pTriangle->p1()->y());
        m_vTriangles[i]->t2().setXY(pTriangle->p2()->x(), pTriangle->p2()->y());
        m_vTriangles[i]->t3().setXY(pTriangle->p3()->x(), pTriangle->p3()->y());
    }
    delete p1;
    delete p2;
    delete p3;
    delete pTriangle;

    // moving trinagles for pazzle
    std::vector<StoneGeneratorTriangle *> vTrianglesHandled;
    std::vector<StoneGeneratorTriangle *> vTrianglesHandling;
    vTrianglesHandling.push_back(m_vTriangles[m_vTriangles.size()/2]);
    while (vTrianglesHandling.size() > 0) {
        StoneGeneratorTriangle *pTri = vTrianglesHandling[vTrianglesHandling.size()-1];
        vTrianglesHandling.pop_back();

        for (int i = 0; i < m_vTriangles.size(); i++) {
            StoneGeneratorTriangle *pTri2 = m_vTriangles[i];
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

    if (vTrianglesHandled.size() != m_vTriangles.size()) {
        std::cout << "vTrianglesHandled.size() = " << vTrianglesHandled.size() << std::endl;
        std::cout << "m_vTriangles.size() = " << m_vTriangles.size() << std::endl;
    } else {
        std::cout << "m_vTriangles.size() == vTrianglesHandled.size() " << std::endl;
    }

    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneGeneratorTriangle *pTri = m_vTriangles[i];
        this->minmaxUV(pTri->t1(), nMinU, nMaxU, nMinV, nMaxV);
        this->minmaxUV(pTri->t2(), nMinU, nMaxU, nMinV, nMaxV);
        this->minmaxUV(pTri->t3(), nMinU, nMaxU, nMinV, nMaxV);
    }

    // normalize coordinates to 0..1
    float dU = nMaxU - nMinU;
    float dV = nMaxV - nMinV;
    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneGeneratorTriangle *pTri = m_vTriangles[i];
        this->normalizeUV(pTri->t1(), nMinU, nMaxU, nMinV, nMaxV);
        this->normalizeUV(pTri->t2(), nMinU, nMaxU, nMinV, nMaxV);
        this->normalizeUV(pTri->t3(), nMinU, nMaxU, nMinV, nMaxV);
    }
    return true;
}

void StoneGenerator::findTrianglesByPoint(StoneGeneratorPoint *p1, std::vector<StoneGeneratorTriangle *> &vTriangles) {
    for (int i = 0; i < m_vTriangles.size(); i++) {
        if (m_vTriangles[i]->hasPoint(p1)) {
            vTriangles.push_back(m_vTriangles[i]);
        }
    }
}

void StoneGenerator::findTrianglesByPoints2(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2, std::vector<StoneGeneratorTriangle *> &vTriangles) {
    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneGeneratorTriangle *pTri = m_vTriangles[i];
        if (pTri->hasPoint(p1) && pTri->hasPoint(p2)) {
            vTriangles.push_back(pTri);
        }
    }
}

float StoneGenerator::distance(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2) {
    float dx = p1->x() - p2->x();
    float dy = p1->y() - p2->y();
    float dz = p1->z() - p2->z();
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
    float rot = angel(p1.y(), p1.z(), p2.y(), p2.z());
    return rot;
}

float StoneGenerator::angelYAxis(const StoneGeneratorPoint &p1, const StoneGeneratorPoint &p2) {
    float rot = this->angel(p1.x(), p1.z(), p2.x(), p2.z());
    rot = -1.0 * rot;
    return rot;
}

float StoneGenerator::angelXY(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2) {
    float dy = p2->y() - p1->y();
    float dx = p2->x() - p1->x();
    float c = std::sqrt(dx*dx + dy*dy);
    return std::asin(dx/c);
}

float StoneGenerator::angelZX(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2) {
    float dz = p2->z() - p1->z();
    float dx = p2->x() - p1->x();
    float c = std::sqrt(dx*dx + dz*dz);
    return std::acos(dz/c);
}

float StoneGenerator::angelZY(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2) {
    float dz = p2->z() - p1->z();
    float dy = p2->y() - p1->y();
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
    nMinX = std::min(nMinX, p1->x());
    nMinY = std::min(nMinY, p1->y());
    nMinZ = std::min(nMinZ, p1->z());
}

void StoneGenerator::maxXYZ(StoneGeneratorPoint *p1, float &nMaxX, float &nMaxY, float &nMaxZ) {
    nMaxX = std::max(nMaxX, p1->x());
    nMaxY = std::max(nMaxY, p1->y());
    nMaxZ = std::max(nMaxZ, p1->z());
}
