#include "StoneGeneratorPseudoRandom.h"

#include <cmath>

StoneGeneratorPseudoRandom::StoneGeneratorPseudoRandom() {
    this->setInitSeed(1);
}

void StoneGeneratorPseudoRandom::setInitSeed(unsigned int nSeed) {
    m_nSeed = nSeed;
    m_nInitSeed = nSeed;
}

unsigned int StoneGeneratorPseudoRandom::getNextRandom() {
    // 100 generations ~ 10453ns
    // m_nSeed = std::sin(m_nSeed + 1) * float(m_nSeed + 6947504120) + 144;

    //  100 generations ~  39 ns
    m_nSeed = ((m_nSeed * 144) ^ (m_nSeed + 6947504120)) + 144;
    return m_nSeed;
}

unsigned int StoneGeneratorPseudoRandom::getInitSeed() {
    return m_nInitSeed;
}

unsigned int StoneGeneratorPseudoRandom::getSeed() {
    return m_nSeed;
}
