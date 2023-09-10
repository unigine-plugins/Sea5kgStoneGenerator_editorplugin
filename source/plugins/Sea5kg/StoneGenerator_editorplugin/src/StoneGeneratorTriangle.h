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

        bool hasPoint(StoneGeneratorPoint *p);
        StoneGeneratorPoint *getPointByIndex(int nIndex);

        StoneGeneratorTexturePoint &t1();
        StoneGeneratorTexturePoint &t2();
        StoneGeneratorTexturePoint &t3();

        StoneGeneratorTexturePoint &getTexPointByIndex(int nIndex);

        void calculateMiddlePointAndNormal(StoneGeneratorPoint &middle_p, StoneGeneratorPoint &middle_p_normal);
        void rotateInXAxisAroundPoint(StoneGeneratorPoint &p1, float fRot);
        void rotateInYAxisAroundPoint(StoneGeneratorPoint &p1, float fRot);

        void copy(StoneGeneratorTriangle *p);

        void rotateTexPointsBy(int nIndex0, float fAngle);

        void moveTexPointsBy(int nIndex0, const StoneGeneratorTexturePoint &t);

    private:
        StoneGeneratorPoint **m_points;

        StoneGeneratorTexturePoint *m_pTexPoints;
};