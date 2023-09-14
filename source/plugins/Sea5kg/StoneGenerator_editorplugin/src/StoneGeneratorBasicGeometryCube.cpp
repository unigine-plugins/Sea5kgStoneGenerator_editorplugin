#include "StoneGeneratorBasicGeometryCube.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

#include <StoneGeneratorConfig.h>

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

