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

#pragma once

#include <vector>

#include "StoneGeneratorConfig.h"
#include "StoneGeneratorBasicGeometry.h"
#include "StoneGeneratorPseudoRandom.h"


class StoneGenerator {
    public:
        StoneGenerator();
        ~StoneGenerator();

        bool generate(const StoneGeneratorConfig &conf);
        const std::vector<StoneGeneratorTriangle *> &triangles();
        const std::vector<StoneGeneratorPoint *> &points();

    private:
        StoneGeneratorPoint *addPoint(const StoneGeneratorConfig &conf, float x, float y, float z);

        bool processAttraction(const StoneGeneratorConfig &conf);
        bool processSurfaceDistortion(const StoneGeneratorConfig &conf);
        bool processResizeAndShift(const StoneGeneratorConfig &conf);
        bool processRemoveUnusefulTriangles(const StoneGeneratorConfig &conf);
        StoneGeneratorPoint calculateNormalForPoint(const StoneGeneratorConfig &conf, const StoneGeneratorPoint &triangleNormal0, StoneGeneratorPoint *p0);
        bool processNormals(const StoneGeneratorConfig &conf);
        bool processTangents(const StoneGeneratorConfig &conf);
        bool processTexturing(const StoneGeneratorConfig &conf);

        void findTrianglesByPoint(StoneGeneratorPoint *p1, std::vector<StoneGeneratorTriangle *> &vTriangles);
        void findTrianglesByPoints2(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2, std::vector<StoneGeneratorTriangle *> &vTriangles);

        float distance(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2);
        float distanceUV(StoneGeneratorTexturePoint &p1, StoneGeneratorTexturePoint &p2);

        float angel(float x1, float y1, float x2, float y2);
        float angelXAxis(const StoneGeneratorPoint &p1, const StoneGeneratorPoint &p2);
        float angelYAxis(const StoneGeneratorPoint &p1, const StoneGeneratorPoint &p2);
        float angelXY(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2);
        float angelZX(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2);
        float angelZY(StoneGeneratorPoint *p1, StoneGeneratorPoint *p2);
        float angelTex(StoneGeneratorTexturePoint &t11, StoneGeneratorTexturePoint &t12, StoneGeneratorTexturePoint &t21, StoneGeneratorTexturePoint &t22);
        bool hasTriangle(const std::vector<StoneGeneratorTriangle *> &vTriangles, StoneGeneratorTriangle *p);
        void minmaxUV(StoneGeneratorTexturePoint &p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV);
        void normalizeUV(StoneGeneratorTexturePoint &p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV);
        void minXYZ(StoneGeneratorPoint *p1, float &nMinX, float &nMinY, float &nMinZ);
        void maxXYZ(StoneGeneratorPoint *p1, float &nMaxX, float &nMaxY, float &nMaxZ);

        StoneGeneratorModel *m_pModel;
        float m_nBasicRadius;
        StoneGeneratorPseudoRandom m_random;
};