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

#include <QString>

enum class IDialogConfiguratorUpdatedValue {
    BASIC_GEOMETRY = 0,
    EXPECTED_TRIANGLES = 10,
    SEED_RANDOM = 15,
    RADIUS = 20,
    POINDS_OF_ATTRACTION = 30,
    STRONG_OF_ATTRACTION = 40,
    SURFACE_DISTORTION = 50,
    DEVIATION_OF_NORMALS = 55,
    SCALE_X = 60,
    SCALE_Y = 61,
    SCALE_Z = 62,
};

class IDialogConfigurator {
    public:
        // virtual void generationComplited(QString sDone) = 0;
        virtual void updateValueFloat(IDialogConfiguratorUpdatedValue nIdValue, float nValue) = 0;
        virtual void updateValueInt(IDialogConfiguratorUpdatedValue nIdValue, int nValue) = 0;
        virtual void updateValueUInt(IDialogConfiguratorUpdatedValue nIdValue, int nValue) = 0;
        virtual int getLabelSize() = 0;
        virtual int getLabelValueSize() = 0;
};