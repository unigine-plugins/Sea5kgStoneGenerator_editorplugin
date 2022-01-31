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

        void setTextureCoordinates(float nU, float nV);
        float getTextureCoordinateU();
        float getTextureCoordinateV();

    private:
        float m_nX, m_nY, m_nZ;
        float m_nU;
        float m_nV;
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

class StoneGeneratorConfig {
    public:
        StoneGeneratorConfig();

        void setEstimatedExpectedTriangles(int nExpected);
        int getEstimatedExpectedTriangles() const;
        
        void setRadius(float nRadius);
        float getRadius() const;
        void setRandomOffsetMin(float nRandomOffsetMin);
        float getRandomOffsetMin() const;
        void setRandomOffsetMax(float nRandomOffsetMax);
        float getRandomOffsetMax() const;

        void setScaleX(float nScaleX);
        float getScaleX() const;
        void setScaleY(float nScaleY);
        float getScaleY() const;
        void setScaleZ(float nScaleZ);
        float getScaleZ() const;

    private:
        float m_nRadius;
        int m_nExpectedTriangles;
        float m_nRandomOffsetMin;
        float m_nRandomOffsetMax;
        float m_nScaleX;
        float m_nScaleY;
        float m_nScaleZ;
};

class StoneGenerator {
    public:
        StoneGenerator();
        ~StoneGenerator();

        void clear();
        bool generate(const StoneGeneratorConfig &conf);
        const std::vector<StoneTriangle *> &triangles();
        const std::vector<StonePoint *> &points();

        StonePoint *addPoint(float x, float y, float z);
    private:
        float distance(StonePoint *p1, StonePoint *p2);
        float angelXY(StonePoint *p1, StonePoint *p2);
        void setTextureCoordinates(StonePoint *pCenter, StonePoint *p1);
        void minmaxUV(StonePoint *p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV);
        std::vector<StonePoint *> m_vPoints;
        std::vector<StoneTriangle *> m_vTriangles;
};