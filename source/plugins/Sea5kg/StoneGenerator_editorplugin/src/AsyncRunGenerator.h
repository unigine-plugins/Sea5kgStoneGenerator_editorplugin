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
        void setRegenerateGeometry(bool bVal);
        bool getRegenerateGeometry();
        void setRegenerateTexture(bool bVal);
        bool getRegenerateTexture();

        StoneGenerator *getStoneGenerator();

    private:
        void run();
        bool m_bRegenerateTexture;
        bool m_bRegenerateGeometry;
        StoneGenerator *m_pStoneGenerator;
        ISignalGun *m_pSignalGun;
        StoneGeneratorConfig m_conf;
        TextureStoneGeneratorConfig m_texConf;
};