
#include "AsyncRunGenerator.h"
#include <iostream>
#include <QCoreApplication>

AsyncRunGenerator::AsyncRunGenerator(ISignalGun *pSignalGun) {
    m_pStoneGenerator = new StoneGenerator();
    m_pSignalGun = pSignalGun;
    m_bRegenerateGeometry = false;
    m_bRegenerateTexture = false;
}

AsyncRunGenerator::~AsyncRunGenerator() {
    
}

void AsyncRunGenerator::setStoneGeneratorConfig(const StoneGeneratorConfig &conf) {
    m_conf = conf;
}

void AsyncRunGenerator::setTextureStoneGeneratorConfig(const TextureStoneGeneratorConfig &conf) {
    m_texConf = conf;
}

void AsyncRunGenerator::setRegenerateGeometry(bool bVal) {
    m_bRegenerateGeometry = bVal;
}

bool AsyncRunGenerator::getRegenerateGeometry() {
    return m_bRegenerateGeometry;
}

void AsyncRunGenerator::setRegenerateTexture(bool bVal) {
    m_bRegenerateTexture = bVal;
}

bool AsyncRunGenerator::getRegenerateTexture() {
    return m_bRegenerateTexture;
}

StoneGenerator *AsyncRunGenerator::getStoneGenerator() {
    return m_pStoneGenerator;
}

void AsyncRunGenerator::run() {
    std::cout << "AsyncRunGenerator::run() start" << std::endl;
    if (m_bRegenerateGeometry) {
        std::cout << "AsyncRunGenerator::run() RegenerateGeometry" << std::endl;
        m_pStoneGenerator->clear();
        m_pStoneGenerator->generate(m_conf);
    }

    if (m_bRegenerateTexture) {
        std::cout << "AsyncRunGenerator::run() RegenerateTexture" << std::endl;
        TextureStoneGenerator tex;
        tex.generate(m_texConf);
    }

    std::cout << "AsyncRunGenerator::run() end" << std::endl;
    m_pSignalGun->generationComplited(QString("done"));
}