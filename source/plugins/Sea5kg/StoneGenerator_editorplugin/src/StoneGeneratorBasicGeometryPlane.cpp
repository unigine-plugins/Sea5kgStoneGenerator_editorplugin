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

#include "StoneGeneratorBasicGeometryPlane.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

#include <StoneGeneratorTriangle.h>

// ---------------------------------------------------------------------
// StoneGeneratorBasicGeometryPlane

StoneGeneratorBasicGeometryPlane::StoneGeneratorBasicGeometryPlane() : StoneGeneratorBasicGeometry("Plane") {

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
