#include "StoneGenerator.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

// ---------------------------------------------------------------------
// StoneGeneratorPoint

StoneGeneratorPoint::StoneGeneratorPoint() {
    setXYZ(0,0,0);
    m_nIndex = 0;
}

StoneGeneratorPoint::StoneGeneratorPoint(float x, float y, float z) {
    setXYZ(x,y,z);
    m_nIndex = 0;
    m_nTangentX = 0.0f;
    m_nTangentY = 0.0f;
    m_nTangentZ = 0.0f;
    m_nTangentW = 0.0f;
}

float StoneGeneratorPoint::getX() const {
    return m_nX;
}

float StoneGeneratorPoint::getY() const {
    return m_nY;
}

float StoneGeneratorPoint::getZ() const {
    return m_nZ;
}

void StoneGeneratorPoint::addOffset(float x, float y, float z) {
    m_nX = m_nX + x;
    m_nY = m_nY + y;
    m_nZ = m_nZ + z;
    m_nX100 = m_nX*100;
    m_nY100 = m_nY*100;
    m_nZ100 = m_nZ*100;
}

void StoneGeneratorPoint::setXYZ(float x, float y, float z) {
    m_nX = x;
    m_nY = y;
    m_nZ = z;
    m_nX100 = m_nX*100;
    m_nY100 = m_nY*100;
    m_nZ100 = m_nZ*100;
}

void StoneGeneratorPoint::setXYZ(const StoneGeneratorPoint &point) {
    this->setXYZ(
        point.getX(),
        point.getY(),
        point.getZ()
    );
}

bool StoneGeneratorPoint::compare(int nX, int nY, int nZ, int nThreshold) {
    return std::abs(nX - m_nX100) < nThreshold
        && std::abs(nY - m_nY100) < nThreshold
        && std::abs(nZ - m_nZ100) < nThreshold
    ;
}

void StoneGeneratorPoint::setIndex(int nIndex) {
    m_nIndex = nIndex;
}

int StoneGeneratorPoint::getIndex() {
    return m_nIndex;
}

void StoneGeneratorPoint::setTangent(float nX, float nY, float nZ, float nW) {
    m_nTangentX = nX;
    m_nTangentY = nY;
    m_nTangentZ = nZ;
    m_nTangentW = nW;
}

float StoneGeneratorPoint::getTangentX() {
    return m_nTangentX;
}
float StoneGeneratorPoint::getTangentY() {
    return m_nTangentY;
}
float StoneGeneratorPoint::getTangentZ() {
    return m_nTangentZ;
}
float StoneGeneratorPoint::getTangentW() {
    return m_nTangentW;
}

void StoneGeneratorPoint::addLinkToTriangle(StoneGeneratorTriangle *pTriangle) {
    m_vLinkedTriangles.push_back(pTriangle);
}

void StoneGeneratorPoint::removeLinkToTriangle(StoneGeneratorTriangle *pTriangle) {
    // TODO
    // m_vLinkedTriangles.push_back(pTriangle);
}

void StoneGeneratorPoint::normalizeToUnitVector() {
    float len = std::sqrt(m_nX*m_nX + m_nY*m_nY + m_nZ*m_nZ);
    float k = 1.0 / len;
    m_nX = k * m_nX;
    m_nY = k * m_nY;
    m_nZ = k * m_nZ;
}

float StoneGeneratorPoint::lengthToPoint(const StoneGeneratorPoint *p1) const {
    float nDX = p1->getX() - m_nX;
    float nDY = p1->getY() - m_nY;
    float nDZ = p1->getZ() - m_nZ;
    return std::sqrt(nDX*nDX + nDY*nDY + nDZ*nDZ);
}

float StoneGeneratorPoint::length() const {
    return std::sqrt(m_nX*m_nX + m_nY*m_nY + m_nZ*m_nZ);
}