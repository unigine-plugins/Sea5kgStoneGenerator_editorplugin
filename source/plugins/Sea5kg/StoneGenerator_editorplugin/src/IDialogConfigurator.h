#pragma once

#include <QString>

enum class IDialogConfiguratorUpdatedValue {
    BASIC_GEOMETRY = 0,
    EXPECTED_TRIANGLES = 10,
    RADIUS = 20,
    POINDS_OF_ATTRACTION = 30,
    STRONG_OF_ATTRACTION = 40,
    SURFACE_DISTORTION = 50,
    SCALE_X = 60,
    SCALE_Y = 61,
    SCALE_Z = 62,
};

class IDialogConfigurator {
    public:
        // virtual void generationComplited(QString sDone) = 0;
        virtual void updateValueFloat(IDialogConfiguratorUpdatedValue nIdValue, float nValue) = 0;
        virtual void updateValueInt(IDialogConfiguratorUpdatedValue nIdValue, int nValue) = 0;
        virtual int getLabelSize() = 0;
        virtual int getLabelValueSize() = 0;
};