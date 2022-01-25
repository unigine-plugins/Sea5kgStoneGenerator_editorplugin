#include "StoneGenerator.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

// StonePoint

StonePoint::StonePoint(float x, float y, float z) {
    m_nX = x;
    m_nY = y;
    m_nZ = z;
    m_nX100 = m_nX*100;
    m_nY100 = m_nY*100;
    m_nZ100 = m_nZ*100;
    m_nIndex = 0;
    m_nU = 0.0f;
    m_nV = 0.0f;
}

float StonePoint::x() {
    return m_nX;
}

float StonePoint::y() {
    return m_nY;
}

float StonePoint::z() {
    return m_nZ;
}

void StonePoint::addOffset(float x, float y, float z) {
    m_nX = m_nX + x;
    m_nY = m_nY + y;
    m_nZ = m_nZ + z;
    m_nX100 = m_nX*100;
    m_nY100 = m_nY*100;
    m_nZ100 = m_nZ*100;
}

bool StonePoint::compare(int nX, int nY, int nZ, int nThreshold) {
    return std::abs(nX - m_nX100) < nThreshold 
        && std::abs(nY - m_nY100) < nThreshold 
        && std::abs(nZ - m_nZ100) < nThreshold 
    ;
}

void StonePoint::setIndex(int nIndex) {
    m_nIndex = nIndex;
}

int StonePoint::getIndex() {
    return m_nIndex;
}

void StonePoint::setTextureCoordinates(float nU, float nV) {
    m_nU = nU;
    m_nV = nV;
}

float StonePoint::getTextureCoordinateU() {
    return m_nU;
}

float StonePoint::getTextureCoordinateV() {
    return m_nV;
}


// StoneTriangle

StoneTriangle::StoneTriangle(
    StonePoint *p1,
    StonePoint *p2,
    StonePoint *p3
) {
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
}

StonePoint *StoneTriangle::p1() {
    return m_p1;
}

StonePoint *StoneTriangle::p2() {
    return m_p2;
}

StonePoint *StoneTriangle::p3() {
    return m_p3;
}

// StoneGeneratorConfig

StoneGeneratorConfig::StoneGeneratorConfig() {
    m_nRandomOffsetMin = 0.0f;
    m_nRandomOffsetMax = 0.0f;
    m_nRadius = 2.0f;
    m_nExpectedTriangles = 300;
    m_nScaleX = 1.0f;
    m_nScaleY = 1.0f;
    m_nScaleZ = 1.0f;
}

void StoneGeneratorConfig::setEstimatedExpectedTriangles(int nExpected) {
    m_nExpectedTriangles = nExpected;
}

int StoneGeneratorConfig::getEstimatedExpectedTriangles() const {
    return m_nExpectedTriangles;
}

void StoneGeneratorConfig::setRadius(float nRadius) {
    m_nRadius = nRadius;
}

float StoneGeneratorConfig::getRadius() const {
    return m_nRadius;
}

void StoneGeneratorConfig::setRandomOffsetMin(float nRandomOffsetMin) {
    m_nRandomOffsetMin = nRandomOffsetMin;
}

float StoneGeneratorConfig::getRandomOffsetMin() const {
    return m_nRandomOffsetMin;
}

void StoneGeneratorConfig::setRandomOffsetMax(float nRandomOffsetMax) {
    m_nRandomOffsetMax = nRandomOffsetMax;
}

float StoneGeneratorConfig::getRandomOffsetMax() const {
    return m_nRandomOffsetMax;
}

void StoneGeneratorConfig::setScaleX(float nScaleX) {
    m_nScaleX = nScaleX;
}

float StoneGeneratorConfig::getScaleX() const {
    return m_nScaleX;
}

void StoneGeneratorConfig::setScaleY(float nScaleY) {
    m_nScaleY = nScaleY;
}

float StoneGeneratorConfig::getScaleY() const {
    return m_nScaleY;
}

void StoneGeneratorConfig::setScaleZ(float nScaleZ) {
    m_nScaleZ = nScaleZ;
}

float StoneGeneratorConfig::getScaleZ() const {
    return m_nScaleZ;
}


// StoneGenerator

StoneGenerator::StoneGenerator() {
}

StoneGenerator::~StoneGenerator() {
    this->clear();
}

void StoneGenerator::clear() {
    for (int i = 0; i < m_vPoints.size(); i++) {
        StonePoint *pPoint = m_vPoints[i];
        delete pPoint;
        m_vPoints[i] = nullptr;
    }
    m_vPoints.clear();

    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneTriangle *pTri = m_vTriangles[i];
        delete pTri;
        m_vTriangles[i] = nullptr;
    }
    m_vTriangles.clear();
}

struct XYPoint {
    float x;
    float y;
};

struct ZLevel {
    float z;
    float z_radius;
    std::vector<XYPoint> xy_sectors;
};

bool StoneGenerator::generate(const StoneGeneratorConfig &conf) {
    std::cout << "m_nExpectedTriangles = " << conf.getEstimatedExpectedTriangles() << std::endl;
    // TODO redesign
    int nK = conf.getEstimatedExpectedTriangles()/2;
    std::cout << "nK = " << nK << std::endl;
    nK = sqrt(nK);
    std::cout << "nK = " << nK << std::endl;
    if (nK % 2 == 1) {
        // kostyl
        nK += 1; // to even number 
    }
    std::cout << "nK = " << nK << std::endl;

    // calculate coordinates
    float spp = 2*M_PI / float(nK);
    float z_spp = M_PI / float(nK);
    std::cout << "spp = " << spp << std::endl;
	// int nTexX = 0.2;
	// int nTexY = 0.2;
    std::vector<ZLevel> levels_z;
    for (int zz0 = 0; zz0 <= nK; zz0++) {
        ZLevel lvl;
        lvl.xy_sectors.clear();
        float z_angel = z_spp * float(zz0);
        lvl.z_radius = conf.getRadius() * sin( z_angel ); // todo scale z
        lvl.z = conf.getRadius() * cos( z_angel );
        for (int rr0 = 0; rr0 < nK; rr0++) {
            XYPoint xy;
            float angel = spp * float(rr0);
            xy.x = lvl.z_radius * cos( angel); // todo scale x
			xy.y = lvl.z_radius * sin( angel); // todo scale y
            lvl.xy_sectors.push_back(xy);
        }
        levels_z.push_back(lvl);
    }

	for (int zz0 = 0; zz0 < levels_z.size() - 1; zz0++) {
        ZLevel lvl_z = levels_z[zz0];
        ZLevel lvl_z_next = levels_z[zz0+1];
        
        std::vector<XYPoint> xy_sectors = lvl_z.xy_sectors;
        for (int i_xy = 0; i_xy < xy_sectors.size(); i_xy++) {
            int i_xy_next = (i_xy+1) % nK;
            XYPoint x0y0 = xy_sectors[i_xy];
            XYPoint x0y1 = xy_sectors[i_xy_next];
            XYPoint x1y0 = lvl_z_next.xy_sectors[i_xy];
            XYPoint x1y1 = lvl_z_next.xy_sectors[i_xy_next];
            StonePoint *pPoint00 = addPoint(
                conf.getScaleX() * x0y0.x,
                conf.getScaleY() * x0y0.y,
                conf.getScaleZ() * lvl_z.z
            );
            StonePoint *pPoint01 = addPoint(
                conf.getScaleX() * x0y1.x,
                conf.getScaleY() * x0y1.y,
                conf.getScaleZ() * lvl_z.z
            );
            StonePoint *pPoint10 = addPoint(
                conf.getScaleX() * x1y0.x,
                conf.getScaleY() * x1y0.y,
                conf.getScaleZ() * lvl_z_next.z
            );
            StonePoint *pPoint11 = addPoint(
                conf.getScaleX() * x1y1.x,
                conf.getScaleY() * x1y1.y,
                conf.getScaleZ() * lvl_z_next.z
            );

            // 00 * ----- * 01
            //    |       | 
            // 10 * ----- * 11
            StoneTriangle *pTriangle1 = new StoneTriangle(
                pPoint01,
                pPoint00,
                pPoint10

                // pPoint00,
                // pPoint01,
                // pPoint10
            );
            m_vTriangles.push_back(pTriangle1);
            if (i_xy > 0 || i_xy < xy_sectors.size() - 1) {
                StoneTriangle *pTriangle2 = new StoneTriangle(
                    pPoint01,
                    pPoint10,
                    pPoint11
                );
                m_vTriangles.push_back(pTriangle2);
            }

            // TODO text coord 
            // TODO normales
			// textCoord.push_back(Unigine::Math::vec4(nTexX, 0, 0, 0));
			// textCoord.push_back(Unigine::Math::vec4(nTexX + 0.2, 0, 0, 0));
			// textCoord.push_back(Unigine::Math::vec4(nTexX + 0.2, nTexY + 0.2, 0, 0));

			// textCoord.push_back(Unigine::Math::vec4(nTexX, 0, 0, 0));
			// textCoord.push_back(Unigine::Math::vec4(nTexX + 0.2, 0, 0, 0));
			// textCoord.push_back(Unigine::Math::vec4(nTexX + 0.2, nTexY + 0.2, 0, 0));
        }
	}
    int nRandomDiff = 100.0 * (conf.getRandomOffsetMax() - conf.getRandomOffsetMin());
    std::cout << "nRandomDiff: " << nRandomDiff << std::endl;
    if (nRandomDiff > 0) {
        for (int i = 0; i < m_vPoints.size(); i++) {
            float nOffsetX = conf.getRandomOffsetMin() + float(std::rand() % nRandomDiff) / 100.0;
            float nOffsetY = conf.getRandomOffsetMin() + float(std::rand() % nRandomDiff) / 100.0;
            float nOffsetZ = conf.getRandomOffsetMin() + float(std::rand() % nRandomDiff) / 100.0;
            m_vPoints[i]->addOffset(nOffsetX, nOffsetY, nOffsetZ);
        }
    }
    
    // TODO calculate texture coordinates
    float tk = std::sin(1.570796327);
    float nMaxU = 0.0f;
    float nMinU = 0.0f;
    float nMaxV = 0.0f;
    float nMinV = 0.0f;
    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneTriangle *pTriangle = m_vTriangles[i];
        float nLength12 = this->distance(pTriangle->p1(), pTriangle->p2());
        float nAngle12 = this->angelXY(pTriangle->p1(), pTriangle->p2());

        float nU2 = nLength12 * tk * std::sin(nAngle12);
        float nV2 = nLength12 * tk * std::cos(nAngle12);
        nU2 += pTriangle->p1()->getTextureCoordinateU();
        nV2 += pTriangle->p1()->getTextureCoordinateV();
        nMaxU = std::max(nMaxU, nU2);
        nMinU = std::max(nMinU, nU2);
        nMaxV = std::max(nMaxV, nV2);
        nMinV = std::max(nMinV, nV2);
        pTriangle->p2()->setTextureCoordinates(nU2, nV2);

        float nLength13 = this->distance(pTriangle->p1(), pTriangle->p3());
        float nAngle13 = this->angelXY(pTriangle->p1(), pTriangle->p3());

        float nU3 = nLength13 * tk * std::sin(nAngle13);
        float nV3 = nLength13 * tk * std::cos(nAngle13);
        nU3 += pTriangle->p1()->getTextureCoordinateU();
        nV3 += pTriangle->p1()->getTextureCoordinateV();
        nMaxU = std::max(nMaxU, nU3);
        nMinU = std::max(nMinU, nU3);
        nMaxV = std::max(nMaxV, nV3);
        nMinV = std::max(nMinV, nV3);
        pTriangle->p3()->setTextureCoordinates(nU3, nV3);
    }

    // normalize coordinates to 0..1
    float dU = nMaxU - nMinU;
    float dV = nMaxV - nMinV;
    for (int i = 0; i < m_vPoints.size(); i++) {
        float u = m_vPoints[i]->getTextureCoordinateU();
        float v = m_vPoints[i]->getTextureCoordinateV();
        u = (u - nMinU) / dU;
        v = (v - nMinV) / dV;
        m_vPoints[i]->setTextureCoordinates(u,v);
    }

    return true;
}

const std::vector<StoneTriangle *> &StoneGenerator::triangles() {
    return m_vTriangles;
}

const std::vector<StonePoint *> &StoneGenerator::points() {
    return m_vPoints;
}

StonePoint *StoneGenerator::addPoint(float x, float y, float z) {
    StonePoint *pPoint = nullptr;
    int nX = x*100;
    int nY = y*100;
    int nZ = z*100;
    int nThreshold = 15; // 0.15
    int nSize = m_vPoints.size();
    for (int i = 0; i < nSize; i++) {
        if (m_vPoints[i]->compare(nX, nY, nZ, nThreshold)) {
            pPoint = m_vPoints[i];
            break;
        }
    }
    if (pPoint == nullptr) {
        pPoint = new StonePoint(x,y,z);
        m_vPoints.push_back(pPoint);
        pPoint->setIndex(nSize);
    }
    return pPoint;
}

float StoneGenerator::distance(StonePoint *p1, StonePoint *p2) {
    float dx = p1->x() - p2->x();
    float dy = p1->y() - p2->y();
    float dz = p1->z() - p2->z();
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

float StoneGenerator::angelXY(StonePoint *p1, StonePoint *p2) {
    float dx = p1->x() - p2->x();
    float dy = p1->y() - p2->y();
    if (dx == 0) {
        // TODO check it later
        if (dy > 0) {
            return M_PI / 2;
        } else {
            return 3 * M_PI / 2;
        }
    }
    return std::asin(dy/dx);
}