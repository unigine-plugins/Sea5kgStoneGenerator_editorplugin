#include "StoneGeneratorConfig.h"

// ---------------------------------------------------------------------
// StoneGeneratorConfig

StoneGeneratorConfig::StoneGeneratorConfig() {
    m_nBasicGeometry = StoneGeneratorBasicGeomery::SPHERE;
    m_nExpectedTriangles = 300;
    m_nRadius = 2.0f;
    m_nPointsOfAttraction = 0;
    m_nStrongOfAttraction = 3.14f;
    m_nSurfaceDistortion = 0.05f;
    m_nScaleX = 1.0f;
    m_nScaleY = 1.0f;
    m_nScaleZ = 1.0f;
    m_nScaleMinAny = 0.1f;
    m_nScaleMaxAny = 10.0f;
    m_bShowNormales = false;
    m_bRegenerateGeometry = false;
    m_bRegenerateTexture = false;
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

float StoneGeneratorConfig::getScaleMinAny() const {
    return m_nScaleMinAny;
}

float StoneGeneratorConfig::getScaleMaxAny() const {
    return m_nScaleMaxAny;
}

void StoneGeneratorConfig::setShowNormales(bool bShowNormales) {
    m_bShowNormales = bShowNormales;
}

bool StoneGeneratorConfig::getShowNormales() const {
    return m_bShowNormales;
}

void StoneGeneratorConfig::setRegenerateGeometry(bool bRegenerateGeometry) {
    m_bRegenerateGeometry = bRegenerateGeometry;
}

bool StoneGeneratorConfig::getRegenerateGeometry() const {
    return m_bRegenerateGeometry;
}

void StoneGeneratorConfig::setRegenerateTexture(bool bRegenerateTexture) {
    m_bRegenerateTexture = bRegenerateTexture;
}

bool StoneGeneratorConfig::getRegenerateTexture() const {
    return m_bRegenerateTexture;
}

void StoneGeneratorConfig::setBasicGeometry(StoneGeneratorBasicGeomery nBasicGeometry) {
    m_nBasicGeometry = nBasicGeometry;
}

StoneGeneratorBasicGeomery StoneGeneratorConfig::getBasicGeometry() const {
    return m_nBasicGeometry;
}

std::string StoneGeneratorConfig::toXmlString() const {

    std::string sGeometryItems = "";
    std::map<std::string, StoneGeneratorBasicGeomery> mapGeometries = getAllStoneGeneratorBasicGeometries();
    int nDefaultGeometry = -1;
    for (const auto& item : mapGeometries) {
        if (sGeometryItems == "") {
            nDefaultGeometry = (int)item.second;
        } else {
            sGeometryItems += ",";
        }
        sGeometryItems += item.first;
    }

    std::string sRet =
        "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
        "<property version=\"2.17.0.1\" manual=\"1\" editable=\"0\" name=\"sea5kg_stone_generator2\">"
        "    <parameter name=\"basic_geometry\" type=\"switch\" items=\"" + sGeometryItems + "\">" + std::to_string(nDefaultGeometry) + "</parameter>"
        "</property>"
    ;

    // "    <parameter name=\"attack\" type=\"toggle\">1</parameter>"
    // "    <parameter name=\"damage\" type=\"int\" max=\"1000\">1</parameter>"
    // "    <parameter name=\"velocity\" type=\"float\" max=\"100\">30</parameter>"
    // "    <parameter name=\"material\" type=\"string\"/>"
    return sRet;
}