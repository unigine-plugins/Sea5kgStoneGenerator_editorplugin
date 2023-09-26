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

        StoneGeneratorPoint *normalP1();
        StoneGeneratorPoint *normalP2();
        StoneGeneratorPoint *normalP3();

        bool hasPoint(StoneGeneratorPoint *p);
        StoneGeneratorPoint *getPointByIndex(int nIndex);

        StoneGeneratorTexturePoint &t1();
        StoneGeneratorTexturePoint &t2();
        StoneGeneratorTexturePoint &t3();

        StoneGeneratorTexturePoint &getTexPointByIndex(int nIndex);

        void calculateMiddlePoint(StoneGeneratorPoint &point) const;
        void calculateNormal(StoneGeneratorPoint &normal) const;
        void rotateInXAxisAroundPoint(StoneGeneratorPoint &p1, float fRot);
        void rotateInYAxisAroundPoint(StoneGeneratorPoint &p1, float fRot);

        void copy(StoneGeneratorTriangle *p);

        void rotateTexPointsBy(int nIndex0, float fAngle);

        void moveTexPointsBy(int nIndex0, const StoneGeneratorTexturePoint &t);

    private:
        StoneGeneratorPoint **m_points;

        StoneGeneratorPoint m_pointNormalP1;
        StoneGeneratorPoint m_pointNormalP2;
        StoneGeneratorPoint m_pointNormalP3;

        StoneGeneratorTexturePoint *m_pTexPoints;
};