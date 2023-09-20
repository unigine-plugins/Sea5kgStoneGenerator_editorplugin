#include "StoneGeneratorBasicGeometry.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

// ---------------------------------------------------------------------
// StoneGeneratorBasicGeometry

StoneGeneratorBasicGeometry::StoneGeneratorBasicGeometry(int nId, const std::string &sName) {
    m_nId = nId;
    m_sName = sName;
}

int StoneGeneratorBasicGeometry::getId() const {
    return m_nId;
}

std::string StoneGeneratorBasicGeometry::getName() const {
    return m_sName;
}
