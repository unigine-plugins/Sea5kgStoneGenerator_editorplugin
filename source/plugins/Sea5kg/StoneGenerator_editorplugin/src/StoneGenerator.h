#pragma once

#include <vector>
#include "StoneGeneratorConfig.h"

class StoneTriangle;

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

        void setNormal(float nX, float nY, float nZ);
        float getNormalX();
        float getNormalY();
        float getNormalZ();

        void addLinkToTriangle(StoneTriangle *pTriangle);
        void removeLinkToTriangle(StoneTriangle *pTriangle);

    private:
        float m_nX, m_nY, m_nZ;
        int m_nX100;
        int m_nY100;
        int m_nZ100;
        int m_nIndex;
        float m_nNormalX, m_nNormalY, m_nNormalZ;
        std::vector<StoneTriangle *> m_vLinkedTriangles;
};

class StoneLine {
    public:
        StoneLine(StonePoint *p1, StonePoint *p2);
        bool equals(const StoneLine& line) const;
        StonePoint *p1() const;
        StonePoint *p2() const;
        StonePoint *crossPoint(const StoneLine& line) const;

    private:
        StonePoint *m_p1;
        StonePoint *m_p2;
};

class StoneTexturePoint {
    public:
        StoneTexturePoint();

        float x() const;
        float y() const;

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
        ~StoneTriangle();

        StonePoint *p1();
        StonePoint *p2();
        StonePoint *p3();

        bool hasPoint(StonePoint *p);
        StonePoint *getPointByIndex(int nIndex);

        StoneTexturePoint &t1();
        StoneTexturePoint &t2();
        StoneTexturePoint &t3();

        StoneTexturePoint &getTexPointByIndex(int nIndex);

        void calculateMiddlePointAndNormal(StonePoint &middle_p, StonePoint &middle_p_normal);
        void rotateInXAxisAroundPoint(StonePoint &p1, float fRot);
        void rotateInYAxisAroundPoint(StonePoint &p1, float fRot);

        void copy(StoneTriangle *p);

        void rotateTexPointsBy(int nIndex0, float fAngle);

        void moveTexPointsBy(int nIndex0, const StoneTexturePoint &t);

    private:
        StonePoint **m_points;

        StoneTexturePoint *m_pTexPoints;
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
        bool generateBasicCube(const StoneGeneratorConfig &conf);
        bool processAttraction(const StoneGeneratorConfig &conf);
        bool processRandom(const StoneGeneratorConfig &conf);
        bool processResizeAndShift(const StoneGeneratorConfig &conf);
        bool processRemoveUnusefulTriangles(const StoneGeneratorConfig &conf);
        bool processNormals(const StoneGeneratorConfig &conf);
        bool processTexturing(const StoneGeneratorConfig &conf);

        void findTrianglesByPoint(StonePoint *p1, std::vector<StoneTriangle *> &vTriangles);
        void findTrianglesByPoints2(StonePoint *p1, StonePoint *p2, std::vector<StoneTriangle *> &vTriangles);

        float distance(StonePoint *p1, StonePoint *p2);
        float distanceUV(StoneTexturePoint &p1, StoneTexturePoint &p2);

        float angel(float x1, float y1, float x2, float y2);
        float angelXAxis(const StonePoint &p1, const StonePoint &p2);
        float angelYAxis(const StonePoint &p1, const StonePoint &p2);
        float angelXY(StonePoint *p1, StonePoint *p2);
        float angelZX(StonePoint *p1, StonePoint *p2);
        float angelZY(StonePoint *p1, StonePoint *p2);
        float angelTex(StoneTexturePoint &t11, StoneTexturePoint &t12, StoneTexturePoint &t21, StoneTexturePoint &t22);
        bool hasTriangle(const std::vector<StoneTriangle *> &vTriangles, StoneTriangle *p);
        void minmaxUV(StoneTexturePoint &p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV);
        void normalizeUV(StoneTexturePoint &p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV);
        void minXYZ(StonePoint *p1, float &nMinX, float &nMinY, float &nMinZ);
        void maxXYZ(StonePoint *p1, float &nMaxX, float &nMaxY, float &nMaxZ);

        std::vector<StonePoint *> m_vPoints;
        std::vector<StoneTriangle *> m_vTriangles;
};