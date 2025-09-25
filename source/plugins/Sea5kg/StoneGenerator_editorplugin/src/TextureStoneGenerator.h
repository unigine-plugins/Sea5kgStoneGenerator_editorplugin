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

#pragma once

#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QPaintDevice>
#include <vector>

class TextureStoneGeneratorConfig {
    public:
        TextureStoneGeneratorConfig();
        void setFilepath(QString sPath);
        QString getFilepath() const;

    private:
        QString m_sFilepath;
};

class TextureStoneGenerator {

    public:
        TextureStoneGenerator();

        void generate(const TextureStoneGeneratorConfig &conf);

    private:
        int randInt(int low, int high);
        int calcOneColor(float x, float xmax, float x_s, float x_k);
        int calcOneColor2(
            float x, float xmax,
            float x_s, float x_k,
            float y, float ymax,
            float y_s, float y_k,
            int nMin, int nMax
        );
        QColor createColor(int red, int green, int blue);
        void randomNets(QPainter &p, QVector<int> &paths, int x, int y, int nWidth, int nHeight, QColor nColor);

        int m_nWidth;
        int m_nHeight;

};