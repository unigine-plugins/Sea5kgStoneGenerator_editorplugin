#pragma once

#include <vector>

class StoneGeneratorTriangle;

class StoneGeneratorPoint {
    public:
        StoneGeneratorPoint();
        StoneGeneratorPoint(float x, float y, float z);

        float x() const;
        float y() const;
        float z() const;

        void addOffset(float x, float y, float z);
        void setXYZ(float x, float y, float z);

        bool compare(int nX, int nY, int nZ, int nThreshold);
        void setIndex(int nIndex);
        int getIndex();

        void setNormal(float nX, float nY, float nZ);
        float getNormalX();
        float getNormalY();
        float getNormalZ();

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
        float m_nNormalX, m_nNormalY, m_nNormalZ;
        float m_nTangentX, m_nTangentY, m_nTangentZ, m_nTangentW;
        std::vector<StoneGeneratorTriangle *> m_vLinkedTriangles;
};
