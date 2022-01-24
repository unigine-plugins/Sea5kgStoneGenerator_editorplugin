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
        void setIndex(int nIndex);
        int getIndex();

    private:
        float m_nX, m_nY, m_nZ;
        int m_nX100;
        int m_nY100;
        int m_nZ100;
        int m_nIndex;
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

        void setScaleX(float nScaleX);
        float getScaleX();
        void setScaleY(float nScaleY);
        float getScaleY();
        void setScaleZ(float nScaleZ);
        float getScaleZ();

        void setEstimatedExpectedTriangles(int nExpected);
        int getEstimatedExpectedTriangles();

        void clear();
        bool generate();
        const std::vector<StoneTriangle *> &triangles();
        const std::vector<StonePoint *> &points();

        StonePoint *addPoint(float x, float y, float z);
    private:
        std::vector<StonePoint *> m_vPoints;
        std::vector<StoneTriangle *> m_vTriangles;
        float m_nRadius;
        int m_nExpectedTriangles;
        float m_nRandomOffsetMin;
        float m_nRandomOffsetMax;
        float m_nScaleX;
        float m_nScaleY;
        float m_nScaleZ;
};