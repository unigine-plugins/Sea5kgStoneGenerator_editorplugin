#pragma once

class StoneGeneratorTexturePoint {
    public:
        StoneGeneratorTexturePoint();

        float x() const;
        float y() const;

        void setXY(float x, float y);

    private:
        float m_nX, m_nY;
};