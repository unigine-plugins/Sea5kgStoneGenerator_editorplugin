#pragma once

#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QPaintDevice>
#include <vector>

class TextureStoneGenerator {

    public:
        TextureStoneGenerator();

        void generate();
        
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