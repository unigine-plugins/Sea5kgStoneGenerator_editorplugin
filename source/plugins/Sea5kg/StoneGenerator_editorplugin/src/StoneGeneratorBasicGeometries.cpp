#include "StoneGeneratorBasicGeometries.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

#include <StoneGeneratorTriangle.h>

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

// ---------------------------------------------------------------------
// StoneGeneratorBasicSphere

StoneGeneratorBasicSphere::StoneGeneratorBasicSphere() : StoneGeneratorBasicGeometry(0, "Sphere") {

}

bool StoneGeneratorBasicSphere::generate(const StoneGeneratorConfig &conf) {
    /*
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
    */
    return true;
}



// ---------------------------------------------------------------------
// StoneGeneratorBasicCube

StoneGeneratorBasicCube::StoneGeneratorBasicCube()  : StoneGeneratorBasicGeometry(1, "Cube") {

}

bool StoneGeneratorBasicCube::generate(const StoneGeneratorConfig &conf) {
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

