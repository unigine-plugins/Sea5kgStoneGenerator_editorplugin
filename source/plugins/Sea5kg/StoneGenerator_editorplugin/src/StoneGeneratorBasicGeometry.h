#pragma once

#include <string>
#include <vector>

#include "StoneGeneratorModel.h"

class StoneGeneratorBasicGeometry {
    public:
        StoneGeneratorBasicGeometry(int nId, const std::string &sName);
        std::string getName() const;
        int getId() const;

        // will be override in childs
        virtual bool generate(StoneGeneratorModel *pModel, int nExpectedTriangles, float nRadius) = 0;

    private:
        std::string m_sName;
        int m_nId;
};
