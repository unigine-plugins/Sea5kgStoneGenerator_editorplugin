
#include "AsyncRunGenerator.h"
#include <iostream>
#include <QCoreApplication>

AsyncRunGenerator::AsyncRunGenerator(ISignalGun *pSignalGun) {
    m_pStoneGenerator = new StoneGenerator();
    m_pSignalGun = pSignalGun;
}

AsyncRunGenerator::~AsyncRunGenerator() {

}

void AsyncRunGenerator::setStoneGeneratorConfig(const StoneGeneratorConfig &conf) {
    m_conf = conf;
}

void AsyncRunGenerator::setTextureStoneGeneratorConfig(const TextureStoneGeneratorConfig &conf) {
    m_texConf = conf;
}

const StoneGeneratorConfig &AsyncRunGenerator::getConf() {
    return m_conf;
}

StoneGenerator *AsyncRunGenerator::getStoneGenerator() {
    return m_pStoneGenerator;
}

void AsyncRunGenerator::run() {
    std::cout << "AsyncRunGenerator::run() start" << std::endl;
    if (m_conf.getRegenerateGeometry()) {
        std::cout << "AsyncRunGenerator::run() RegenerateGeometry" << std::endl;
        m_pStoneGenerator->generate(m_conf);
    }

    if (m_conf.getRegenerateTexture()) {
        std::cout << "AsyncRunGenerator::run() RegenerateTexture" << std::endl;
        TextureStoneGenerator tex;
        tex.generate(m_texConf);
    }

    std::cout << "AsyncRunGenerator::run() end" << std::endl;
    m_pSignalGun->generationComplited(QString("done"));
}