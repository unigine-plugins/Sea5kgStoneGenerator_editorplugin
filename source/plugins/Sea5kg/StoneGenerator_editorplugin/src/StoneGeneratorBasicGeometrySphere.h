#pragma once

#include <string>
#include <vector>

#include <StoneGeneratorTriangle.h>
#include <StoneGeneratorConfig.h>
#include <StoneGeneratorBasicGeometry.h>

class StoneGeneratorBasicSphere : public StoneGeneratorBasicGeometry {
    public:
        StoneGeneratorBasicSphere();
        virtual bool generate(const StoneGeneratorConfig &conf) override;
};

static std::vector<StoneGeneratorBasicGeometry *> getStoneGeneratorBasicGeometries() {
    std::vector<StoneGeneratorBasicGeometry *> vRet;
    vRet.push_back(new StoneGeneratorBasicSphere());
    // vRet.push_back(new StoneGeneratorBasicCube());
    return vRet;
};