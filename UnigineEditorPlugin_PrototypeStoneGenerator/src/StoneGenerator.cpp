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

StoneTriangle::~StoneTriangle() {
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
    m_nBasicGeometry = 0;
    m_nStrongOfAttraction = 1.0f;
    m_nPointsOfAttraction = 0;
}

void StoneGeneratorConfig::setEstimatedExpectedTriangles(int nExpected) {
    m_nExpectedTriangles = nExpected;
}

int StoneGeneratorConfig::getEstimatedExpectedTriangles() const {
    return m_nExpectedTriangles;
}

void StoneGeneratorConfig::setPointsOfAttraction(int nPointsOfAttraction) {
    m_nPointsOfAttraction = nPointsOfAttraction;
}

int StoneGeneratorConfig::getPointsOfAttraction() const {
    return m_nPointsOfAttraction;
}

void StoneGeneratorConfig::setStrongOfAttraction(float nStrongOfAttraction) {
    m_nStrongOfAttraction = nStrongOfAttraction;
}

float StoneGeneratorConfig::getStrongOfAttraction() const {
    return m_nStrongOfAttraction;
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

void StoneGeneratorConfig::setBasicGeometry(int nBasicGeometry) {
    m_nBasicGeometry = nBasicGeometry;
}

int StoneGeneratorConfig::getBasicGeometry() const {
    return m_nBasicGeometry;
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
    
    if (conf.getBasicGeometry() == 0) {
        if (!this->generateBasicSpheres(conf)) {
            return false;
        }
    } else if (conf.getBasicGeometry() == 1) {
        if (!this->generateBasicCubes(conf)) {
            return false;
        }
    } else {
        std::cout << "Unknown basic geometry" << std::endl;
        return false;
    }
    
    this->processAttraction(conf);
    this->processRandom(conf);
    
    
    // calculate texture coordinates
    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneTriangle *pTriangle = m_vTriangles[i];
        setTextureCoordinatesFirst(pTriangle->p1(), pTriangle->p2());
        setTextureCoordinatesFirst(pTriangle->p1(), pTriangle->p3());
    }

    // min max uv
    float nMaxU = 0.0f;
    float nMinU = 0.0f;
    float nMaxV = 0.0f;
    float nMinV = 0.0f;
    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneTriangle *pTriangle = m_vTriangles[i];
        this->minmaxUV(pTriangle->p1(), nMinU, nMaxU, nMinV, nMaxV);
        this->minmaxUV(pTriangle->p2(), nMinU, nMaxU, nMinV, nMaxV);
        this->minmaxUV(pTriangle->p3(), nMinU, nMaxU, nMinV, nMaxV);
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

StonePoint *StoneGenerator::addPoint(const StoneGeneratorConfig &conf, float x, float y, float z) {
    StonePoint *pPoint = nullptr;
    x = conf.getScaleX() * x;
    y = conf.getScaleY() * y;
    z = conf.getScaleZ() * z;
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
        pPoint = new StonePoint(x, y, z);
        m_vPoints.push_back(pPoint);
        pPoint->setIndex(nSize);
    }
    return pPoint;
}

bool StoneGenerator::generateBasicSpheres(const StoneGeneratorConfig &conf) {
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
    float z_spp = M_PI / float(nK); // todo scale z here
    std::cout << "spp = " << spp << std::endl;
	// int nTexX = 0.2;
	// int nTexY = 0.2;
    std::vector<ZLevel> levels_z;
    for (int zz0 = 0; zz0 <= nK; zz0++) {
        ZLevel lvl;
        lvl.xy_sectors.clear();
        float z_angel = z_spp * float(zz0);
        lvl.z_radius = conf.getRadius() * sin( z_angel );
        lvl.z = conf.getRadius() * cos( z_angel );
        for (int rr0 = 0; rr0 < nK; rr0++) {
            XYPoint xy;
            float angel = spp * float(rr0);
            xy.x = lvl.z_radius * cos( angel);
			xy.y = lvl.z_radius * sin( angel);
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
            StonePoint *pPoint00 = addPoint(conf, x0y0.x, x0y0.y, lvl_z.z);
            StonePoint *pPoint01 = addPoint(conf, x0y1.x, x0y1.y, lvl_z.z);
            StonePoint *pPoint10 = addPoint(conf, x1y0.x, x1y0.y, lvl_z_next.z);
            StonePoint *pPoint11 = addPoint(conf, x1y1.x, x1y1.y, lvl_z_next.z);

            // 00 * ----- * 01
            //    |       | 
            // 10 * ----- * 11
            if (pPoint00 != pPoint01 && pPoint01 != pPoint10 && pPoint10 != pPoint00) {
                StoneTriangle *pTriangle1 = new StoneTriangle(
                    pPoint01,
                    pPoint00,
                    pPoint10

                    // pPoint00,
                    // pPoint01,
                    // pPoint10
                );
                m_vTriangles.push_back(pTriangle1);
            }
            
            if (i_xy > 0 || i_xy < xy_sectors.size() - 1) {
                // if (pPoint00 != pPoint01 && pPoint01 != pPoint10 && pPoint10 != pPoint00) {
                    StoneTriangle *pTriangle2 = new StoneTriangle(
                        pPoint01,
                        pPoint10,
                        pPoint11
                    );
                    m_vTriangles.push_back(pTriangle2);
                // }
            }
        }
	}
    return true;
}

bool StoneGenerator::generateBasicCubes(const StoneGeneratorConfig &conf) {
    float nRadius = conf.getRadius();

    float fK = conf.getEstimatedExpectedTriangles() / 6.0; // 6 sides
    fK = fK / 2.0;
    fK = std::sqrt(fK); // squares on each side;
    int nK = std::round(fK);

    float nStep = 2*nRadius / nK;

    float nX0 = -nRadius;
    float nX1 = nRadius;

    float nY0 = -nRadius;
    float nY1 = nRadius;

    float nZ0 = -nRadius;
    float nZ1 = nRadius;

    for (int a = 0; a < nK; a++) {
        for (int b = 0; b < nK; b++) {
            float fA0 = float(a)*nStep - nRadius;
            float fB0 = float(b)*nStep - nRadius;
            float fA1 = fA0 + nStep;
            float fB1 = fB0 + nStep;
            // bottom
            {
                StonePoint *pPoint00 = addPoint(conf, fA0, fB0, nZ0);
                StonePoint *pPoint01 = addPoint(conf, fA0, fB1, nZ0);
                StonePoint *pPoint10 = addPoint(conf, fA1, fB0, nZ0);
                StonePoint *pPoint11 = addPoint(conf, fA1, fB1, nZ0);
                StoneTriangle *pTriangle1 = new StoneTriangle(pPoint00, pPoint01, pPoint11);
                m_vTriangles.push_back(pTriangle1);
                StoneTriangle *pTriangle2 = new StoneTriangle(pPoint00, pPoint11, pPoint10);
                m_vTriangles.push_back(pTriangle2);
            }
            
            // top
            {
                StonePoint *pPoint00 = addPoint(conf, fA0, fB0, nZ1);
                StonePoint *pPoint01 = addPoint(conf, fA0, fB1, nZ1);
                StonePoint *pPoint10 = addPoint(conf, fA1, fB0, nZ1);
                StonePoint *pPoint11 = addPoint(conf, fA1, fB1, nZ1);
                StoneTriangle *pTriangle1 = new StoneTriangle(pPoint11, pPoint01, pPoint00);
                m_vTriangles.push_back(pTriangle1);
                StoneTriangle *pTriangle2 = new StoneTriangle(pPoint10, pPoint11, pPoint00);
                m_vTriangles.push_back(pTriangle2);
            }

            // left
            {
                StonePoint *pPoint00 = addPoint(conf, nX0, fB0, fA0);
                StonePoint *pPoint01 = addPoint(conf, nX0, fB0, fA1);
                StonePoint *pPoint10 = addPoint(conf, nX0, fB1, fA0);
                StonePoint *pPoint11 = addPoint(conf, nX0, fB1, fA1);
                StoneTriangle *pTriangle1 = new StoneTriangle(pPoint00, pPoint01, pPoint11);
                m_vTriangles.push_back(pTriangle1);
                StoneTriangle *pTriangle2 = new StoneTriangle(pPoint00, pPoint11, pPoint10);
                m_vTriangles.push_back(pTriangle2);
            }
            
            // right
            {
                StonePoint *pPoint00 = addPoint(conf, nX1, fB0, fA0);
                StonePoint *pPoint01 = addPoint(conf, nX1, fB0, fA1);
                StonePoint *pPoint10 = addPoint(conf, nX1, fB1, fA0);
                StonePoint *pPoint11 = addPoint(conf, nX1, fB1, fA1);
                StoneTriangle *pTriangle1 = new StoneTriangle(pPoint11, pPoint01, pPoint00);
                m_vTriangles.push_back(pTriangle1);
                StoneTriangle *pTriangle2 = new StoneTriangle(pPoint10, pPoint11, pPoint00);
                m_vTriangles.push_back(pTriangle2);
            }

            // front
            {
                StonePoint *pPoint00 = addPoint(conf, fB0, nY1, fA0);
                StonePoint *pPoint01 = addPoint(conf, fB0, nY1, fA1);
                StonePoint *pPoint10 = addPoint(conf, fB1, nY1, fA0);
                StonePoint *pPoint11 = addPoint(conf, fB1, nY1, fA1);
                StoneTriangle *pTriangle1 = new StoneTriangle(pPoint00, pPoint01, pPoint11);
                m_vTriangles.push_back(pTriangle1);
                StoneTriangle *pTriangle2 = new StoneTriangle(pPoint00, pPoint11, pPoint10);
                m_vTriangles.push_back(pTriangle2);
            }
            
            // end
            {
                StonePoint *pPoint00 = addPoint(conf, fB0, nY0, fA0);
                StonePoint *pPoint01 = addPoint(conf, fB0, nY0, fA1);
                StonePoint *pPoint10 = addPoint(conf, fB1, nY0, fA0);
                StonePoint *pPoint11 = addPoint(conf, fB1, nY0, fA1);
                StoneTriangle *pTriangle1 = new StoneTriangle(pPoint11, pPoint01, pPoint00);
                m_vTriangles.push_back(pTriangle1);
                StoneTriangle *pTriangle2 = new StoneTriangle(pPoint10, pPoint11, pPoint00);
                m_vTriangles.push_back(pTriangle2);
            }
        }
    }
    return true;
}

bool StoneGenerator::processAttraction(const StoneGeneratorConfig &conf) {
    if (conf.getPointsOfAttraction() == 0) {
        return true;
    }
    std::vector<StonePoint *> vAttractionPoints;
    float nStrongAttraction = conf.getStrongOfAttraction();
    float rk = 2.0;
    float fDiametr = conf.getRadius() * 2.0;
    int nWidth = fDiametr * rk * 100.0;
    for (int i = 0; i < conf.getPointsOfAttraction(); i++) {
        float x = float(std::rand() % nWidth) / 100.0;
        x = x - rk * conf.getRadius();
        x = x * conf.getScaleX();
        float y = float(std::rand() % nWidth) / 100.0;
        y = y - rk * conf.getRadius();
        y = y * conf.getScaleY();
        float z = float(std::rand() % nWidth) / 100.0;
        z = z - rk * conf.getRadius();
        z = z * conf.getScaleZ();
        vAttractionPoints.push_back(new StonePoint(x,y,z));
        std::cout << "i = " << i << "; x = " << x << "; y = " << y << "; z = " << z << std::endl;
    }

    for (int i = 0; i < m_vPoints.size(); i++) {
        float dx = 0.0f;
        float dy = 0.0f;
        float dz = 0.0f;
        int nCloseA = 0;
        float fMaxDistance = 50000.0;
        for (int a = 0; a < vAttractionPoints.size(); a++) {
            float fDistance = this->distance(m_vPoints[i], vAttractionPoints[a]);
            if (fDistance < fMaxDistance) {
                nCloseA = a;
                fMaxDistance = fDistance;
            }
        }
        float fK = std::exp(-1 * fMaxDistance / nStrongAttraction );
        m_vPoints[i]->addOffset(
            fK * (vAttractionPoints[nCloseA]->x() - m_vPoints[i]->x()),
            fK * (vAttractionPoints[nCloseA]->y() - m_vPoints[i]->y()),
            fK * (vAttractionPoints[nCloseA]->z() - m_vPoints[i]->z())
        );
    }
    for (int i = 0; i < vAttractionPoints.size(); i++) {
        delete vAttractionPoints[i];
    }
    vAttractionPoints.clear();
    return true;
}

bool StoneGenerator::processRandom(const StoneGeneratorConfig &conf) {
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
    return true;
}

bool StoneGenerator::processNormalize(const StoneGeneratorConfig &conf) {
    // TODO 
    return true;
}

float StoneGenerator::distance(StonePoint *p1, StonePoint *p2) {
    float dx = p1->x() - p2->x();
    float dy = p1->y() - p2->y();
    float dz = p1->z() - p2->z();
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

float StoneGenerator::distanceUV(StonePoint *p1, StonePoint *p2) {
    float dx = p1->getTextureCoordinateU() - p2->getTextureCoordinateU();
    float dy = p1->getTextureCoordinateV() - p2->getTextureCoordinateV();
    return std::sqrt(dx*dx + dy*dy);
}

float StoneGenerator::angelXY(StonePoint *p1, StonePoint *p2) {
    float dy = p2->y() - p1->y();
    float dx = p2->x() - p1->x();
    float c = std::sqrt(dx*dx + dy*dy);
    // std::cout << "dy = " << dy << std::endl;
    // std::cout << "dx = " << dx << std::endl;
    // std::cout << "c = " << c << std::endl;
    // std::cout << "std::asin(dy/c) = " << std::asin(dy/c) << std::endl;
    // std::cout << "std::acos(dy/c) = " << std::acos(dx/c) << std::endl;
    return std::asin(dx/c);
}

float StoneGenerator::angelZX(StonePoint *p1, StonePoint *p2) {
    float dz = p2->z() - p1->z();
    float dx = p2->x() - p1->x();
    float c = std::sqrt(dx*dx + dz*dz);
    // float dx = p2->x() - p1->x();
    // float c = distance(p1,p2);
    // std::cout << "dz = " << dz << std::endl;
    // std::cout << "dx = " << dx << std::endl;
    // std::cout << "c = " << c << std::endl;
    // std::cout << "std::asin(dy/c) = " << std::asin(dy/c) << std::endl;
    // std::cout << "std::acos(dy/c) = " << std::acos(dx/c) << std::endl;
    return std::acos(dz/c);
}

void StoneGenerator::minmaxUV(StonePoint *p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV) {
    nMinU = std::min(nMinU, p1->getTextureCoordinateU());
    nMaxU = std::max(nMaxU, p1->getTextureCoordinateU());
    nMinV = std::min(nMinV, p1->getTextureCoordinateV());
    nMaxV = std::max(nMaxV, p1->getTextureCoordinateV());
}

void StoneGenerator::minXYZ(StonePoint *p1, float &nMinX, float &nMinY, float &nMinZ) {
    nMinX = std::min(nMinX, p1->x());
    nMinY = std::min(nMinY, p1->y());
    nMinZ = std::min(nMinZ, p1->z());
}

void StoneGenerator::maxXYZ(StonePoint *p1, float &nMaxX, float &nMaxY, float &nMaxZ) {
    nMaxX = std::max(nMaxX, p1->x());
    nMaxY = std::max(nMaxY, p1->y());
    nMaxZ = std::max(nMaxZ, p1->z());
}


void StoneGenerator::setTextureCoordinatesFirst(StonePoint *p1, StonePoint *p2) {
    // first
    float nLength = this->distance(p1, p2);
    float nAngleXY = this->angelXY(p1, p2);
    float nAngleZX = this->angelZX(p1, p2);

    // nAngleZX = (M_PI/2 - nAngleZX); // + 2*M_PI;
    // if (nAngleZX < 0) {
    //     nAngleZX += M_PI;
    // }

    // nAngleXY = M_PI/2 - nAngleXY + 2*M_PI;


    // std::cout << "nLength12 " << nLength12 << std::endl;
    // std::cout << "nAngle12 " << nAngle12 << std::endl;

    float nU = nLength * std::sin(-1*nAngleZX) * std::sin(nAngleXY);
    float nV = nLength * std::sin(-1*nAngleZX) * std::cos(nAngleXY);

    // float nU = nLength * std::sin(nAngleXY);
    // float nV = nLength * std::cos(nAngleXY);

    
    // nU += p1->x(); // pTriangle->p1()->getTextureCoordinateU();
    // nV += p1->x(); // pTriangle->p1()->getTextureCoordinateV();
    nU += p1->getTextureCoordinateU();
    nV += p1->getTextureCoordinateV();
    // std::cout << "offset nU2 " << nU2 << std::endl;
    // std::cout << "offset nV2 " << nV2 << std::endl;
    p2->setTextureCoordinates(nU, nV);
}