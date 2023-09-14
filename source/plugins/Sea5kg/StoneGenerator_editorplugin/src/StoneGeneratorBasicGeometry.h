#pragma once

#include <string>
#include <vector>

#include <StoneGeneratorTriangle.h>

class StoneGeneratorConfig;

class StoneGeneratorBasicGeometry {
    public:
        StoneGeneratorBasicGeometry(int nId, const std::string &sName);
        std::string getName();
        int getId();
        const std::vector<StoneGeneratorPoint *> &getPoints() const;

        // will be override in childs
        virtual bool generate(const StoneGeneratorConfig &conf) = 0;

    private:
        std::string m_sName;
        int m_nId;

    protected:
        StoneGeneratorPoint *addPoint(const StoneGeneratorConfig &conf, float x, float y, float z);
        std::vector<StoneGeneratorPoint *> m_vPoints;
        std::vector<StoneGeneratorTriangle *> m_vTriangles;
};
