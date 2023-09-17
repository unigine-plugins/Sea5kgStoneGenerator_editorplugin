#pragma once

#include <string>
#include <vector>

#include <StoneGeneratorBasicGeometry.h>

class StoneGeneratorBasicCube : public StoneGeneratorBasicGeometry {
    public:
        StoneGeneratorBasicCube();
        virtual bool generate(StoneGeneratorModel *pModel, int nExpectedTriangles, float nRadius) override;
};
