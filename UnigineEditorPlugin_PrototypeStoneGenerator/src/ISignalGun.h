#pragma once

#include <QString>

class ISignalGun {
    public:
        virtual void generationComplited(QString sDone) = 0;
};