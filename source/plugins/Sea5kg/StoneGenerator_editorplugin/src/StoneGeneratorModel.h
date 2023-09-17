#pragma once

#include <string>
#include <vector>

#include "StoneGeneratorTriangle.h"

class StoneGeneratorModel {
    public:
        void clear();
        std::vector<StoneGeneratorPoint *> &getPoints();
        std::vector<StoneGeneratorTriangle *> &getTriangles();
        StoneGeneratorPoint *addPoint(float x, float y, float z);
        StoneGeneratorTriangle *addTriangle(StoneGeneratorPoint *p0, StoneGeneratorPoint *p1, StoneGeneratorPoint *p2);
    private:
        std::vector<StoneGeneratorPoint *> m_vPoints;
        std::vector<StoneGeneratorTriangle *> m_vTriangles;
};
