
#include "AsyncRunGenerator.h"
#include <iostream>
#include <QCoreApplication>

AsyncRunGenerator::AsyncRunGenerator(ISignalGun *pSignalGun) {
    m_pStoneGenerator = new StoneGenerator();
    m_bWorked = false;
    m_pSignalGun = pSignalGun;
}

AsyncRunGenerator::~AsyncRunGenerator() {
    
}

void AsyncRunGenerator::setConfig(const StoneGeneratorConfig &conf) {
    m_conf = conf;
}

StoneGenerator *AsyncRunGenerator::getStoneGenerator() {
    return m_pStoneGenerator;
}

void AsyncRunGenerator::run() {
    std::cout << "AsyncRunGenerator::run() start" << std::endl;
    m_pStoneGenerator->clear();
    m_pStoneGenerator->generate(m_conf);
    std::cout << "AsyncRunGenerator::run() end" << std::endl;
    m_pSignalGun->generationComplited(QString("done"));
}