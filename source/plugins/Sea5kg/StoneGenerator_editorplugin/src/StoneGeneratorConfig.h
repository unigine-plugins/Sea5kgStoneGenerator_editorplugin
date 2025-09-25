/*
MIT License

Copyright (c) 2022-2025 mrseakg@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Repository: https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin
*/

#pragma once

#include <string>
#include <map>
#include <vector>

#include "StoneGeneratorBasicGeometry.h"

class StoneGeneratorConfig {
    public:
        StoneGeneratorConfig();

        void setEstimatedExpectedTriangles(int nExpected);
        int getEstimatedExpectedTriangles() const;
        void setSeedRandom(unsigned int nSeedRandom);
        unsigned int getSeedRandom() const;
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
        float getScaleMinAny() const;
        float getScaleMaxAny() const;
        void setShowNormales(bool bShowNormales);
        bool getShowNormales() const;
        void setDeviationOfNormals(float nDeviationOfNormals);
        float getDeviationOfNormals() const;
        void setRegenerateGeometry(bool bRegenerateGeometry);
        bool getRegenerateGeometry() const;
        void setRegenerateTexture(bool bRegenerateTexture);
        bool getRegenerateTexture() const;


        void setBasicGeometry(StoneGeneratorBasicGeometry *pBasicGeometry);
        StoneGeneratorBasicGeometry *getBasicGeometry() const;

        std::string toXmlString() const;


    private:
        StoneGeneratorBasicGeometry *m_pBasicGeometry;
        float m_nRadius;
        int m_nExpectedTriangles;
        unsigned int m_nSeedRandom;
        int m_nPointsOfAttraction;
        float m_nStrongOfAttraction;
        float m_nSurfaceDistortion;
        float m_nScaleX;
        float m_nScaleY;
        float m_nScaleZ;
        float m_nScaleMinAny;
        float m_nScaleMaxAny;
        float m_nDeviationOfNormals;
        bool m_bShowNormales;

        // system
        bool m_bRegenerateGeometry;
        bool m_bRegenerateTexture;
};