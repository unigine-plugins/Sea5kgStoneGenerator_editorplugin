#pragma once

#include <vector>

class StonePoint {
    public:
        StonePoint(float x, float y, float z);

        float x();
        float y();
        float z();

        void addOffset(float x, float y, float z);

        bool compare(int nX, int nY, int nZ, int nThreshold);

    private:
        float m_nX, m_nY, m_nZ;
        int m_nX100;
        int m_nY100;
        int m_nZ100;
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

        void setRandomOffsetMin(float nRandomOffsetMin);
        int getRandomOffsetMin();
        void setRandomOffsetMax(float nRandomOffsetMax);
        int getRandomOffsetMax();

        void setEstimatedExpectedTriangles(int nExpected);
        int getEstimatedExpectedTriangles();

        void clear();
        bool generate();
        const std::vector<StoneTriangle *> &triangles();

        StonePoint *addPoint(float x, float y, float z);
    private:
        std::vector<StonePoint *> m_vPoints;
        std::vector<StoneTriangle *> m_vTriangles;
        float m_nRadius;
        int m_nExpectedTriangles;
        float m_nRandomOffsetMin;
        float m_nRandomOffsetMax;
};