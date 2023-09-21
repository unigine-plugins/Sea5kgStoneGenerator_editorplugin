#include "StoneGeneratorBasicGeometryPlane.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

#include <StoneGeneratorTriangle.h>

// ---------------------------------------------------------------------
// StoneGeneratorBasicGeometryPlane

StoneGeneratorBasicGeometryPlane::StoneGeneratorBasicGeometryPlane() : StoneGeneratorBasicGeometry(2, "Plane") {

}

bool StoneGeneratorBasicGeometryPlane::generate(StoneGeneratorModel *pModel, int nExpectedTriangles, float nRadius) {
    pModel->clear();


    float fK = nExpectedTriangles; // / 2;
    fK = fK / 2.0;
    fK = std::sqrt(fK); // squares on each side;

    float nStep = 2*nRadius / fK;
    for (int a = 0; a < fK; a++) {
        float fA0 = float(a)*nStep - nRadius;
        float fA1 = fA0 + nStep;

        for (int b = 0; b < fK; b++) {
            float fB0 = float(b)*nStep - nRadius;
            float fB1 = fB0 + nStep;
            // top
            {
                StoneGeneratorPoint *pPoint00 = pModel->addPoint(fA0, fB0, 0.0f);
                StoneGeneratorPoint *pPoint01 = pModel->addPoint(fA0, fB1, 0.0f);
                StoneGeneratorPoint *pPoint10 = pModel->addPoint(fA1, fB0, 0.0f);
                StoneGeneratorPoint *pPoint11 = pModel->addPoint(fA1, fB1, 0.0f);

                // top triangles
                pModel->addTriangle(pPoint11, pPoint01, pPoint00);
                pModel->addTriangle(pPoint10, pPoint11, pPoint00);

                // bottom triangles
                // pModel->addTriangle(pPoint01, pPoint11, pPoint00);
                // pModel->addTriangle(pPoint00, pPoint11, pPoint10);
            }
        }
    }
    return true;
}
