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

bool StoneGeneratorBasicCube::generate(StoneGeneratorModel *pModel, int nExpectedTriangles, float nRadius) {
    pModel->clear();

    float fK = nExpectedTriangles / 6.0; // 6 sides
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
        float fA0 = float(a)*nStep - nRadius;
        float fA1 = fA0 + nStep;

        for (int b = 0; b < nK; b++) {
            float fB0 = float(b)*nStep - nRadius;
            float fB1 = fB0 + nStep;

            // bottom
            {
                StoneGeneratorPoint *pPoint00 = pModel->addPoint(fA0, fB0, nZ0);
                StoneGeneratorPoint *pPoint01 = pModel->addPoint(fA0, fB1, nZ0);
                StoneGeneratorPoint *pPoint10 = pModel->addPoint(fA1, fB0, nZ0);
                StoneGeneratorPoint *pPoint11 = pModel->addPoint(fA1, fB1, nZ0);
                pModel->addTriangle(pPoint00, pPoint01, pPoint11);
                pModel->addTriangle(pPoint00, pPoint11, pPoint10);
            }

            // top
            {
                StoneGeneratorPoint *pPoint00 = pModel->addPoint(fA0, fB0, nZ1);
                StoneGeneratorPoint *pPoint01 = pModel->addPoint(fA0, fB1, nZ1);
                StoneGeneratorPoint *pPoint10 = pModel->addPoint(fA1, fB0, nZ1);
                StoneGeneratorPoint *pPoint11 = pModel->addPoint(fA1, fB1, nZ1);
                pModel->addTriangle(pPoint11, pPoint01, pPoint00);
                pModel->addTriangle(pPoint10, pPoint11, pPoint00);
            }

            // left
            {
                StoneGeneratorPoint *pPoint00 = pModel->addPoint(nX0, fB0, fA0);
                StoneGeneratorPoint *pPoint01 = pModel->addPoint(nX0, fB0, fA1);
                StoneGeneratorPoint *pPoint10 = pModel->addPoint(nX0, fB1, fA0);
                StoneGeneratorPoint *pPoint11 = pModel->addPoint(nX0, fB1, fA1);
                pModel->addTriangle(pPoint00, pPoint01, pPoint11);
                pModel->addTriangle(pPoint00, pPoint11, pPoint10);
            }

            // right
            {
                StoneGeneratorPoint *pPoint00 = pModel->addPoint(nX1, fB0, fA0);
                StoneGeneratorPoint *pPoint01 = pModel->addPoint(nX1, fB0, fA1);
                StoneGeneratorPoint *pPoint10 = pModel->addPoint(nX1, fB1, fA0);
                StoneGeneratorPoint *pPoint11 = pModel->addPoint(nX1, fB1, fA1);
                pModel->addTriangle(pPoint11, pPoint01, pPoint00);
                pModel->addTriangle(pPoint10, pPoint11, pPoint00);
            }

            // front
            {
                StoneGeneratorPoint *pPoint00 = pModel->addPoint(fB0, nY1, fA0);
                StoneGeneratorPoint *pPoint01 = pModel->addPoint(fB0, nY1, fA1);
                StoneGeneratorPoint *pPoint10 = pModel->addPoint(fB1, nY1, fA0);
                StoneGeneratorPoint *pPoint11 = pModel->addPoint(fB1, nY1, fA1);
                pModel->addTriangle(pPoint00, pPoint01, pPoint11);
                pModel->addTriangle(pPoint00, pPoint11, pPoint10);
            }

            // end
            {
                StoneGeneratorPoint *pPoint00 = pModel->addPoint(fB0, nY0, fA0);
                StoneGeneratorPoint *pPoint01 = pModel->addPoint(fB0, nY0, fA1);
                StoneGeneratorPoint *pPoint10 = pModel->addPoint(fB1, nY0, fA0);
                StoneGeneratorPoint *pPoint11 = pModel->addPoint(fB1, nY0, fA1);
                pModel->addTriangle(pPoint11, pPoint01, pPoint00);
                pModel->addTriangle(pPoint10, pPoint11, pPoint00);
            }
        }
    }
    return true;
}

