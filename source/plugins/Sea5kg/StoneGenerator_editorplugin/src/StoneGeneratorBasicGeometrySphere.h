#pragma once

#include <string>
#include <vector>

#include <StoneGeneratorTriangle.h>
#include <StoneGeneratorConfig.h>
#include <StoneGeneratorBasicGeometry.h>

class StoneGeneratorBasicSphere : public StoneGeneratorBasicGeometry {
    public:
        StoneGeneratorBasicSphere();
        virtual bool generate(StoneGeneratorModel *pModel, int nExpectedTriangles, float nRadius) override;
};
