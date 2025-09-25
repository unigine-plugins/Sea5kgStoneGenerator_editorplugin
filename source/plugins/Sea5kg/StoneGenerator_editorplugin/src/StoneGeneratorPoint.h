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

class StoneGeneratorTriangle;

class StoneGeneratorPoint {
    public:
        StoneGeneratorPoint();
        StoneGeneratorPoint(float x, float y, float z);

        float getX() const;
        float getY() const;
        float getZ() const;

        void addOffset(float x, float y, float z);
        void setXYZ(float x, float y, float z);
        void setXYZ(const StoneGeneratorPoint &point);

        bool compare(int nX, int nY, int nZ, int nThreshold);
        void setIndex(int nIndex);
        int getIndex();

        void setTangent(float nX, float nY, float nZ, float nW);
        float getTangentX();
        float getTangentY();
        float getTangentZ();
        float getTangentW();

        void addLinkToTriangle(StoneGeneratorTriangle *pTriangle);
        void removeLinkToTriangle(StoneGeneratorTriangle *pTriangle);

        void normalizeToUnitVector();
        float lengthToPoint(const StoneGeneratorPoint *p1) const;
        float length() const;

    private:
        float m_nX, m_nY, m_nZ;
        int m_nX100;
        int m_nY100;
        int m_nZ100;
        int m_nIndex;
        float m_nTangentX, m_nTangentY, m_nTangentZ, m_nTangentW;
        std::vector<StoneGeneratorTriangle *> m_vLinkedTriangles;
};
