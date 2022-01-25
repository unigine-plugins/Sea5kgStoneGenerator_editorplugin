#pragma once

#include <QRunnable>
#include "StoneGenerator.h"
#include "ISignalGun.h"

class AsyncRunGenerator : public QRunnable {
    public:
        AsyncRunGenerator(ISignalGun *pSignalGun);
        ~AsyncRunGenerator();

        void setConfig(const StoneGeneratorConfig &conf);
        StoneGenerator *getStoneGenerator();

    private:
        void run();
        bool m_bWorked;
        StoneGenerator *m_pStoneGenerator;
        ISignalGun *m_pSignalGun;
        StoneGeneratorConfig m_conf;
};