
#include "StoneGeneratorConfig.h"


StoneGeneratorConfig::StoneGeneratorConfig() {
    m_nSurfaceDistortion = 0.0f;
    m_nRadius = 2.0f;
    m_nExpectedTriangles = 300;
    m_nScaleX = 1.0f;
    m_nScaleY = 1.0f;
    m_nScaleZ = 1.0f;
    m_nBasicGeometry = 0;
    m_nStrongOfAttraction = 1.0f;
    m_nPointsOfAttraction = 0;
}

void StoneGeneratorConfig::setEstimatedExpectedTriangles(int nExpected) {
    m_nExpectedTriangles = nExpected;
}

int StoneGeneratorConfig::getEstimatedExpectedTriangles() const {
    return m_nExpectedTriangles;
}

void StoneGeneratorConfig::setPointsOfAttraction(int nPointsOfAttraction) {
    m_nPointsOfAttraction = nPointsOfAttraction;
}

int StoneGeneratorConfig::getPointsOfAttraction() const {
    return m_nPointsOfAttraction;
}

void StoneGeneratorConfig::setStrongOfAttraction(float nStrongOfAttraction) {
    m_nStrongOfAttraction = nStrongOfAttraction;
}

float StoneGeneratorConfig::getStrongOfAttraction() const {
    return m_nStrongOfAttraction;
}

void StoneGeneratorConfig::setRadius(float nRadius) {
    m_nRadius = nRadius;
}

float StoneGeneratorConfig::getRadius() const {
    return m_nRadius;
}

void StoneGeneratorConfig::setSurfaceDistortion(float nSurfaceDistortion) {
    m_nSurfaceDistortion = nSurfaceDistortion;
}

float StoneGeneratorConfig::getSurfaceDistortion() const {
    return m_nSurfaceDistortion;
}

void StoneGeneratorConfig::setScaleX(float nScaleX) {
    m_nScaleX = nScaleX;
}

float StoneGeneratorConfig::getScaleX() const {
    return m_nScaleX;
}

void StoneGeneratorConfig::setScaleY(float nScaleY) {
    m_nScaleY = nScaleY;
}

float StoneGeneratorConfig::getScaleY() const {
    return m_nScaleY;
}

void StoneGeneratorConfig::setScaleZ(float nScaleZ) {
    m_nScaleZ = nScaleZ;
}

float StoneGeneratorConfig::getScaleZ() const {
    return m_nScaleZ;
}

void StoneGeneratorConfig::setBasicGeometry(int nBasicGeometry) {
    m_nBasicGeometry = nBasicGeometry;
}

int StoneGeneratorConfig::getBasicGeometry() const {
    return m_nBasicGeometry;
}