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

#include <QApplication>
#include <QString>
#include <QMap>
#include <QDir>
#include <QImage>
#include <QTime>
#include <QPainter>
#include <QFont>
#include <QList>
#include <QPaintDevice>

#include <iostream>
#include <math.h>

#include "TextureStoneGenerator.h"

// TextureStoneGeneratorConfig

TextureStoneGeneratorConfig::TextureStoneGeneratorConfig() {

}

void TextureStoneGeneratorConfig::setFilepath(QString sFilepath) {
    m_sFilepath = sFilepath;
}

QString TextureStoneGeneratorConfig::getFilepath() const {
    return m_sFilepath;
}


// TextureStoneGenerator

TextureStoneGenerator::TextureStoneGenerator() {
    m_nWidth = 1024;
    m_nHeight = 1024;
}


void TextureStoneGenerator::generate(const TextureStoneGeneratorConfig &conf) {
    std::cout << "\t ::: << start !!!!\n\n\n";
    
    // Create seed for the random
    // That is needed only once on application startup
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    float red_vert_s = randInt(0, 300);
    float red_vert_k = randInt(0, 300);
    float red_horz_s = randInt(0, 300);
    float red_horz_k = randInt(0, 300);

    float green_vert_s = randInt(0, 300);
    float green_vert_k = randInt(0, 300);
    float green_horz_s = randInt(0, 300);
    float green_horz_k = randInt(0, 300);

    float blue_vert_s = randInt(0, 300);
    float blue_vert_k = randInt(0, 300);
    float blue_horz_s = randInt(0, 300);
    float blue_horz_k = randInt(0, 300);

    int nColorMin = 70;
    int nColorMax = 140;

    QImage outputImage(m_nWidth, m_nHeight, QImage::Format_ARGB32);



    QPainter p(&outputImage);
    {
        QBrush brush( 0xffffff /*Qt::white*/, Qt::SolidPattern);
        // QPen pen(0xffffff /*Qt::white*/);
        // p.setPen(pen);
        p.setBrush(brush);
        p.drawRect(0,0,outputImage.width(),outputImage.height());
    }

    for (int i = 0; i < 100000; i++) {
        QVector<int> paths;
        int startx = randInt(0, m_nWidth);
        int starty = randInt(0, m_nHeight);
        int nColor = 0xff000000;
        int nC = randInt(nColorMin, nColorMax);
        nColor = nColor | nC << 16;
        nColor = nColor | nC << 8;
        nColor = nColor | nC;
    
        randomNets(
            p, paths,
            startx, starty,
            m_nWidth, m_nHeight,
            nColor
        );
    }

    for (int x = 0; x < m_nWidth; x++) {
        for (int y = 0; y < m_nHeight; y++) {
            int red = calcOneColor2(
                x, m_nWidth, red_vert_s, red_vert_k,
                y, m_nHeight, red_horz_s, red_horz_k,
                nColorMin, nColorMax
            );
            int green = calcOneColor2(
                x, m_nWidth, green_vert_s, green_vert_k,
                y, m_nHeight, green_horz_s, green_horz_k,
                nColorMin, nColorMax
            ); 
            int blue = calcOneColor2(
                x, m_nWidth, blue_vert_s, blue_vert_k,
                y, m_nHeight, blue_horz_s, blue_horz_k,
                nColorMin, nColorMax
            );
            QColor nColor = createColor(red, green, blue);

            // QPen pen(0x7175b0 /*Qt::white*/);
            // QBrush brash(nColor /*Qt::white*/);
            QBrush newbrush = QBrush(p.brush());
            newbrush.setColor(nColor);
            newbrush.setStyle(Qt::SolidPattern);
            p.setBrush(newbrush);

            // // QBrush brush( 0x7175b0 /*Qt::white*/, Qt::SolidPattern);
            p.setPen(Qt::NoPen);
            // p.setBrush(brash);
            p.drawRect(x, y, 1, 1);
        }
    }

    for (int i = 0; i < 30000; i++) {
        QVector<int> paths;
        int startx = randInt(0, m_nWidth);
        int starty = randInt(0, m_nHeight);
        int nC = randInt(nColorMin, 245);
        QColor color (nC, nC, nC, 200);
        randomNets(
            p, paths,
            startx, starty,
            m_nWidth, m_nHeight,
            color
        );
    }

    outputImage.save(conf.getFilepath());

    std::cout << "\t ::: >>> generated!!!!\n\n\n";
}

int TextureStoneGenerator::randInt(int low, int high) {
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
};

int TextureStoneGenerator::calcOneColor(float x, float xmax, float x_s, float x_k) {
    int ret =
        sin(x_s + (x / xmax) * x_k) * 256;
    ret = abs(ret);
    ret = 0x000000FF & ret;
    return ret;
}

int TextureStoneGenerator::calcOneColor2(
    float x, float xmax,
    float x_s, float x_k,
    float y, float ymax,
    float y_s, float y_k,
    int nMin, int nMax
) {
    float fRet = 0.707 * sin(x_s + (x / xmax) * x_k);
    fRet += 0.5 * cos(y_s + (y / ymax) * y_k);
    fRet /= 2;
    int ret = nMin + fRet * (nMax - nMin);
    ret = abs(ret);
    ret = 0x000000FF & ret;
    return ret;
}

QColor TextureStoneGenerator::createColor(int red, int green, int blue) {
    // red = 0.5989 * float(red);
    // green = 0.5870 * float(green);
    // blue = 0.5140 * float(blue);
    int gray = (red + green + blue) / 3;

    // int gray =
    //      * float(red << 16)
    //     + 0.5870 * float(green << 8)
    //     + 0.1140 * float(blue);
    // return gray;

    int nColor = 0x00000000;
    // nColor = nColor | (red << 16);
    // nColor = nColor | (green << 8);
    // nColor = nColor | blue;
    // nColor = nColor | (gray << 16);
    // nColor = nColor | (gray << 8);
    // nColor = nColor | (gray);

    return QColor(gray,gray,gray,175);
}

// ---------------------------------------------------------------------------

void TextureStoneGenerator::randomNets(QPainter &p, QVector<int> &paths, int x, int y, int nWidth, int nHeight, QColor nColor) {
    int xy = x | (y << 16);
    if (paths.contains(xy)) {
        return;
    }

    if (x < 0 || y < 0 || x > nWidth || y > nHeight) {
        return;
    }

    if (randInt(0,100) > 30) {
        return;
    }
    
    QBrush newbrush = QBrush(p.brush());
    newbrush.setColor(nColor);
    newbrush.setStyle(Qt::SolidPattern);
    p.setBrush(newbrush);

    p.drawRect(x, y, 1, 1);
    paths.push_back(xy);
    if (randInt(0,100) > 45) randomNets(p, paths, x + 0, y + 1, nWidth, nHeight, nColor);
    if (randInt(0,100) > 45) randomNets(p, paths, x + 0, y - 1, nWidth, nHeight, nColor);
    if (randInt(0,100) > 45) randomNets(p, paths, x + 1, y + 1, nWidth, nHeight, nColor);
    if (randInt(0,100) > 45) randomNets(p, paths, x + 1, y - 1, nWidth, nHeight, nColor);
    if (randInt(0,100) > 45) randomNets(p, paths, x - 1, y + 1, nWidth, nHeight, nColor);
    if (randInt(0,100) > 45) randomNets(p, paths, x - 1, y - 1, nWidth, nHeight, nColor);
    if (randInt(0,100) > 45) randomNets(p, paths, x - 1, y + 0, nWidth, nHeight, nColor);
    if (randInt(0,100) > 45) randomNets(p, paths, x + 1, y + 0, nWidth, nHeight, nColor);
}
