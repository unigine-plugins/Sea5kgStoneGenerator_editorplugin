#pragma once

#include <string>
#include <vector>

#include <StoneGeneratorTriangle.h>
#include <StoneGeneratorConfig.h>
#include <StoneGeneratorBasicGeometry.h>

class StoneGeneratorBasicGeometryPlane : public StoneGeneratorBasicGeometry {
    public:
        StoneGeneratorBasicGeometryPlane();
        virtual bool generate(StoneGeneratorModel *pModel, int nExpectedTriangles, float nRadius) override;
};
