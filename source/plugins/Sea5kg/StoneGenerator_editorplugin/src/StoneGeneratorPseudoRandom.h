#pragma once

#include <string>
#include <map>
#include <vector>

class StoneGeneratorPseudoRandom {
    public:
        StoneGeneratorPseudoRandom();
        void setInitSeed(unsigned int nSeed);
        unsigned int getInitSeed();
        unsigned int getSeed();
        unsigned int getNextRandom();
    private:
        unsigned int m_nSeed;
        unsigned int m_nInitSeed;
};