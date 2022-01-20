#pragma once

#include <vector>

class StonePoint {
    public:
        StonePoint(float x, float y, float z);

        float x();
        float y();
        float z();
        
    private:
        float m_nX, m_nY, m_nZ;
};

class StoneTriangle {
    public:
        StoneTriangle(
            StonePoint *p1,
            StonePoint *p2,
            StonePoint *p3
        );
        
        StonePoint *p1();
        StonePoint *p2();
        StonePoint *p3();

    private:
        StonePoint *m_p1;
        StonePoint *m_p2;
        StonePoint *m_p3;
};

class StoneGenerator {
    public:
        StoneGenerator();
        ~StoneGenerator();
        void setRaidus(float nRadius);
        float getRaidus();

        void setEstimatedExpectedTriangles(int nExpected);
        int getEstimatedExpectedTriangles();

        void clear();
        bool generate();
        const std::vector<StoneTriangle *> &triangles();

    private:
        std::vector<StonePoint *> m_vPoints;
        std::vector<StoneTriangle *> m_vTriangles;
        float m_nRadius;
        int m_nExpectedTriangles;
};