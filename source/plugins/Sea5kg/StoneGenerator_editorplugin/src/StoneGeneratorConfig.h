#pragma once

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

        void setBasicGeometry(int nBasicGeometry);
        int getBasicGeometry() const;

    private:
        int m_nBasicGeometry;
        float m_nRadius;
        int m_nExpectedTriangles;
        int m_nPointsOfAttraction;
        float m_nStrongOfAttraction;
        float m_nSurfaceDistortion;
        float m_nScaleX;
        float m_nScaleY;
        float m_nScaleZ;
};