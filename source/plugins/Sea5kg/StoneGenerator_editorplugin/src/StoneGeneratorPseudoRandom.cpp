/*
MIT License

Copyright (c) 2022-2025 mrseakg@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Repository: https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin
*/

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
