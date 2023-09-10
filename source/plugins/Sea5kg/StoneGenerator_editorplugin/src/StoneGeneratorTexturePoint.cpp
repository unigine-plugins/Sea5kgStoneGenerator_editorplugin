#include "StoneGeneratorTexturePoint.h"

// ---------------------------------------------------------------------
// StoneGeneratorTexturePoint

StoneGeneratorTexturePoint::StoneGeneratorTexturePoint() {
    setXY(0.0f,0.0f);
}

float StoneGeneratorTexturePoint::x() const {
    return m_nX;
}

float StoneGeneratorTexturePoint::y() const {
    return m_nY;
}

void StoneGeneratorTexturePoint::setXY(float x, float y) {
    m_nX = x;
    m_nY = y;
}