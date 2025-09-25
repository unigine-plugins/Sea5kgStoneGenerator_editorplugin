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