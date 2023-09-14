#pragma once

#include <QString>

enum class IDialogConfiguratorUpdatedValue {
    BASIC_GEOMETRY = 0,
    RADIUS = 1,
    POINDS_OF_ATTRACTION = 2,
    STRONG_OF_ATTRACTION = 3,
    SURFACE_DISTORTION = 4,
    SCALE_X = 5,
    SCALE_Y = 6,
    SCALE_Z = 7,
};

class IDialogConfigurator {
    public:
        // virtual void generationComplited(QString sDone) = 0;
        virtual void updateValueFloat(IDialogConfiguratorUpdatedValue nIdValue, float nValue) = 0;
        virtual int getLabelSize() = 0;
        virtual int getLabelValueSize() = 0;
};