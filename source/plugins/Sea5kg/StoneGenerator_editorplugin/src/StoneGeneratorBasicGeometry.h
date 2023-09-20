#pragma once

#include <string>
#include <vector>

#include "StoneGeneratorModel.h"

class StoneGeneratorBasicGeometry {
    public:
        StoneGeneratorBasicGeometry(int nId, const std::string &sName);
        int getId() const;
        std::string getName() const;

        // will be override in childs
        virtual bool generate(StoneGeneratorModel *pModel, int nExpectedTriangles, float nRadius) = 0;

    private:
        int m_nId;
        std::string m_sName;
};
