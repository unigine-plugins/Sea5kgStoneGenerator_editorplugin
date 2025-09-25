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

#include <StoneGeneratorPoint.h>
#include <StoneGeneratorTexturePoint.h>

class StoneGeneratorTriangle {
    public:
        StoneGeneratorTriangle(
            StoneGeneratorPoint *p1,
            StoneGeneratorPoint *p2,
            StoneGeneratorPoint *p3
        );
        ~StoneGeneratorTriangle();

        StoneGeneratorPoint *p1();
        StoneGeneratorPoint *p2();
        StoneGeneratorPoint *p3();

        StoneGeneratorPoint *normalP1();
        StoneGeneratorPoint *normalP2();
        StoneGeneratorPoint *normalP3();

        bool hasPoint(StoneGeneratorPoint *p);
        StoneGeneratorPoint *getPointByIndex(int nIndex);

        StoneGeneratorTexturePoint &t1();
        StoneGeneratorTexturePoint &t2();
        StoneGeneratorTexturePoint &t3();

        StoneGeneratorTexturePoint &getTexPointByIndex(int nIndex);

        void calculateMiddlePoint(StoneGeneratorPoint &point) const;
        void calculateNormal(StoneGeneratorPoint &normal) const;
        void rotateInXAxisAroundPoint(StoneGeneratorPoint &p1, float fRot);
        void rotateInYAxisAroundPoint(StoneGeneratorPoint &p1, float fRot);

        void copy(StoneGeneratorTriangle *p);

        void rotateTexPointsBy(int nIndex0, float fAngle);

        void moveTexPointsBy(int nIndex0, const StoneGeneratorTexturePoint &t);

    private:
        StoneGeneratorPoint **m_points;

        StoneGeneratorPoint m_pointNormalP1;
        StoneGeneratorPoint m_pointNormalP2;
        StoneGeneratorPoint m_pointNormalP3;

        StoneGeneratorTexturePoint *m_pTexPoints;
};