#pragma once

#include <string>
#include <map>
#include <vector>

class StoneGeneratorBasicGeometry;

enum class StoneGeneratorBasicGeomery {
    SPHERE = 0,
    CUBE = 1
};

static std::map<std::string, StoneGeneratorBasicGeomery> getAllStoneGeneratorBasicGeometries() {
    std::map<std::string, StoneGeneratorBasicGeomery> ret;
    ret["sphere"] = StoneGeneratorBasicGeomery::SPHERE;
    ret["cube"] = StoneGeneratorBasicGeomery::CUBE;
    return ret;
};

class StoneGeneratorConfig {
    public:
        StoneGeneratorConfig();

        void setEstimatedExpectedTriangles(int nExpected);
        int getEstimatedExpectedTriangles() const;
        void setPointsOfAttraction(int nPointsOfAttraction);
        int getPointsOfAttraction() const;
        void setStrongOfAttraction(float nStrongOfAttraction);
        float getStrongOfAttraction() const;
        void setRadius(float nRadius);
        float getRadius() const;
        void setSurfaceDistortion(float nSurfaceDistortion);
        float getSurfaceDistortion() const;
        void setScaleX(float nScaleX);
        float getScaleX() const;
        void setScaleY(float nScaleY);
        float getScaleY() const;
        void setScaleZ(float nScaleZ);
        float getScaleZ() const;
        void setShowNormales(bool bShowNormales);
        bool getShowNormales() const;
        void setRegenerateGeometry(bool bRegenerateGeometry);
        bool getRegenerateGeometry() const;
        void setRegenerateTexture(bool bRegenerateTexture);
        bool getRegenerateTexture() const;

        void setBasicGeometry(StoneGeneratorBasicGeomery nBasicGeometry);
        StoneGeneratorBasicGeomery getBasicGeometry() const;

        std::string toXmlString() const;


    private:
        StoneGeneratorBasicGeomery m_nBasicGeometry;
        float m_nRadius;
        int m_nExpectedTriangles;
        int m_nPointsOfAttraction;
        float m_nStrongOfAttraction;
        float m_nSurfaceDistortion;
        float m_nScaleX;
        float m_nScaleY;
        float m_nScaleZ;
        bool m_bShowNormales;

        // system
        bool m_bRegenerateGeometry;
        bool m_bRegenerateTexture;
};