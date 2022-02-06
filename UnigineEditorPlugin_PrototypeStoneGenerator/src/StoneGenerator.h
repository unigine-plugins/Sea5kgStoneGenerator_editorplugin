#pragma once

#include <vector>

class StonePoint {
    public:
        StonePoint();
        StonePoint(float x, float y, float z);

        float x() const;
        float y() const;
        float z() const;

        void addOffset(float x, float y, float z);
        void setXYZ(float x, float y, float z);

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

class StoneTexturePoint {
    public:
        StoneTexturePoint();

        float x();
        float y();

        void setXY(float x, float y);

    private:
        float m_nX, m_nY;
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

        StoneTexturePoint &t1();
        StoneTexturePoint &t2();
        StoneTexturePoint &t3();

        void calculateMiddlePointAndNormal(StonePoint &middle_p, StonePoint &middle_p_normal);
        void rotateInXAxisAroundPoint(StonePoint &p1, float fRot);
        void rotateInYAxisAroundPoint(StonePoint &p1, float fRot);
        
        void copy(StoneTriangle *p);

    private:
        StonePoint *m_p1;
        StonePoint *m_p2;
        StonePoint *m_p3;

        StoneTexturePoint m_t1;
        StoneTexturePoint m_t2;
        StoneTexturePoint m_t3;
};

class StoneGeneratorConfig {
    public:
        StoneGeneratorConfig();

        void setEstimatedExpectedTriangles(int nExpected);
        int getEstimatedExpectedTriangles() const;
        void setPointsOfAttraction(int nPointsOfAttraction);
        int getPointsOfAttraction() const;
        void setStrongOfAttraction(float nStrongOfAttraction);
        float getStrongOfAttraction() const;
        void setRadius(float nRadius);
        float getRadius() const;
        void setSurfaceDistortion(float nSurfaceDistortion);
        float getSurfaceDistortion() const;
        void setScaleX(float nScaleX);
        float getScaleX() const;
        void setScaleY(float nScaleY);
        float getScaleY() const;
        void setScaleZ(float nScaleZ);
        float getScaleZ() const;

        void setBasicGeometry(int nBasicGeometry);
        int getBasicGeometry() const;

    private:
        int m_nBasicGeometry;
        float m_nRadius;
        int m_nExpectedTriangles;
        int m_nPointsOfAttraction;
        float m_nStrongOfAttraction;
        float m_nSurfaceDistortion;
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

        
    private:
        StonePoint *addPoint(const StoneGeneratorConfig &conf, float x, float y, float z);

        bool generateBasicSpheres(const StoneGeneratorConfig &conf);
        bool generateBasicCubes(const StoneGeneratorConfig &conf);
        bool processAttraction(const StoneGeneratorConfig &conf);
        bool processRandom(const StoneGeneratorConfig &conf);
        bool processResizeAndShift(const StoneGeneratorConfig &conf);
        bool processRemoveUnusefulTriangles(const StoneGeneratorConfig &conf);
        bool processTexturing(const StoneGeneratorConfig &conf);

        float distance(StonePoint *p1, StonePoint *p2);
        float distanceUV(StoneTexturePoint &p1, StoneTexturePoint &p2);

        float angel(float x1, float y1, float x2, float y2);
        float angelXAxis(const StonePoint &p1, const StonePoint &p2);
        float angelYAxis(const StonePoint &p1, const StonePoint &p2);

        float angelXY(StonePoint *p1, StonePoint *p2);
        float angelZX(StonePoint *p1, StonePoint *p2);
        float angelZY(StonePoint *p1, StonePoint *p2);
        void minmaxUV(StoneTexturePoint &p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV);
        void normalizeUV(StoneTexturePoint &p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV);
        void minXYZ(StonePoint *p1, float &nMinX, float &nMinY, float &nMinZ);
        void maxXYZ(StonePoint *p1, float &nMaxX, float &nMaxY, float &nMaxZ);

        std::vector<StonePoint *> m_vPoints;
        std::vector<StoneTriangle *> m_vTriangles;
};