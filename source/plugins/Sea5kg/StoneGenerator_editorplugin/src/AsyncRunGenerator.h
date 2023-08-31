#pragma once

#include <QRunnable>
#include "StoneGenerator.h"
#include "TextureStoneGenerator.h"
#include "ISignalGun.h"

class AsyncRunGenerator : public QRunnable {
    public:
        AsyncRunGenerator(ISignalGun *pSignalGun);
        ~AsyncRunGenerator();

        void setStoneGeneratorConfig(const StoneGeneratorConfig &conf);
        void setTextureStoneGeneratorConfig(const TextureStoneGeneratorConfig &conf);

        const StoneGeneratorConfig &getConf();

        StoneGenerator *getStoneGenerator();

    private:
        void run();
        StoneGenerator *m_pStoneGenerator;
        ISignalGun *m_pSignalGun;
        StoneGeneratorConfig m_conf;
        TextureStoneGeneratorConfig m_texConf;
};