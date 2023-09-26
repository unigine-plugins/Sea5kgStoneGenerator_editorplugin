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
        void setXYZ(StoneGeneratorPoint &point);

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

    private:
        float m_nX, m_nY, m_nZ;
        int m_nX100;
        int m_nY100;
        int m_nZ100;
        int m_nIndex;
        float m_nTangentX, m_nTangentY, m_nTangentZ, m_nTangentW;
        std::vector<StoneGeneratorTriangle *> m_vLinkedTriangles;
};
