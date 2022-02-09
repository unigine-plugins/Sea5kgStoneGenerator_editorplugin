#include "StoneGenerator.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

// StonePoint

StonePoint::StonePoint() {
    setXYZ(0,0,0);
    m_nIndex = 0;
}

StonePoint::StonePoint(float x, float y, float z) {
    setXYZ(x,y,z);
    m_nIndex = 0;
}

float StonePoint::x() const {
    return m_nX;
}

float StonePoint::y() const {
    return m_nY;
}

float StonePoint::z() const {
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

void StonePoint::setXYZ(float x, float y, float z) {
    m_nX = x;
    m_nY = y;
    m_nZ = z;
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

void StonePoint::setNormal(float nX, float nY, float nZ) {
    m_nNormalX = nX;
    m_nNormalY = nY;
    m_nNormalZ = nZ;
}

float StonePoint::getNormalX() {
    return m_nNormalX;
}

float StonePoint::getNormalY() {
    return m_nNormalY;
}

float StonePoint::getNormalZ() {
    return m_nNormalZ;
}


// StoneTexturePoint

StoneTexturePoint::StoneTexturePoint() {
    setXY(0.0f,0.0f);
}

float StoneTexturePoint::x() {
    return m_nX;
}

float StoneTexturePoint::y() {
    return m_nY;
}

void StoneTexturePoint::setXY(float x, float y) {
    m_nX = x;
    m_nY = y;
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

bool StoneTriangle::hasPoint(StonePoint *p) {
    return m_p1 == p || m_p2 == p || m_p3 == p;
}

StoneTexturePoint &StoneTriangle::t1() {
    return m_t1;
}

StoneTexturePoint &StoneTriangle::t2() {
    return m_t2;
}

StoneTexturePoint &StoneTriangle::t3() {
    return m_t3;
}

void StoneTriangle::calculateMiddlePointAndNormal(StonePoint &middle_p, StonePoint &middle_p_normal) {
    middle_p.setXYZ(
        (m_p1->x() + m_p2->x() + m_p3->x()) / 3.0,
        (m_p1->y() + m_p2->y() + m_p3->y()) / 3.0,
        (m_p1->z() + m_p2->z() + m_p3->z()) / 3.0
    );
    float x10 = m_p2->x() - m_p1->x();
    float y10 = m_p2->y() - m_p1->y();
    float z10 = m_p2->z() - m_p1->z();
    float x20 = m_p3->x() - m_p1->x();
    float y20 = m_p3->y() - m_p1->y();
    float z20 = m_p3->z() - m_p1->z();

    middle_p_normal.setXYZ(
        middle_p.x() + (y10*z20 - y20*z10),
        middle_p.y() - (x10*z20 - x20*z10),
        middle_p.z() + (x10*y20 - x20*y10)
    );
}

void StoneTriangle::rotateInXAxisAroundPoint(StonePoint &p1, float fRot) {

    // help here:
    // https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space
    
    // x axis
    // |1     0           0| |x|   |        x        |   |x'|
    // |0   cos θ    −sin θ| |y| = |y cos θ − z sin θ| = |y'|
    // |0   sin θ     cos θ| |z|   |y sin θ + z cos θ|   |z'|

    float dx1 = m_p1->x() - p1.x();
    float dy1 = m_p1->y() - p1.y();
    float dz1 = m_p1->z() - p1.z();

    m_p1->setXYZ(
        p1.x() + dx1,
        p1.y() + dy1 * std::cos(fRot) - dz1 * std::sin(fRot),
        p1.z() + dy1 * std::sin(fRot) + dz1 * std::cos(fRot)
    );
    
    float dx2 = m_p2->x() - p1.x();
    float dy2 = m_p2->y() - p1.y();
    float dz2 = m_p2->z() - p1.z();

    m_p2->setXYZ(
        p1.x() + dx2,
        p1.y() + dy2 * std::cos(fRot) - dz2 * std::sin(fRot),
        p1.z() + dy2 * std::sin(fRot) + dz2 * std::cos(fRot)
    );

    float dx3 = m_p3->x() - p1.x();
    float dy3 = m_p3->y() - p1.y();
    float dz3 = m_p3->z() - p1.z();

    m_p3->setXYZ(
        p1.x() + dx3,
        p1.y() + dy3 * std::cos(fRot) - dz3 * std::sin(fRot),
        p1.z() + dy3 * std::sin(fRot) + dz3 * std::cos(fRot)
    );
}

void StoneTriangle::rotateInYAxisAroundPoint(StonePoint &p1, float fRot) {
    
    // help here:
    // https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space
    
    // y axis
    // | cos θ    0   sin θ| |x|   | x cos θ + z sin θ|   |x'|
    // |   0      1       0| |y| = |         y        | = |y'|
    // |−sin θ    0   cos θ| |z|   |−x sin θ + z cos θ|   |z'|

    float dx1 = m_p1->x() - p1.x();
    float dy1 = m_p1->y() - p1.y();
    float dz1 = m_p1->z() - p1.z();

    m_p1->setXYZ(
        p1.x() + dx1 * std::cos(fRot) + dz1 * std::sin(fRot),
        p1.y() + dy1,
        p1.z() - dx1 * std::sin(fRot) + dz1 * std::cos(fRot)
    );

    float dx2 = m_p2->x() - p1.x();
    float dy2 = m_p2->y() - p1.y();
    float dz2 = m_p2->z() - p1.z();

    m_p2->setXYZ(
        p1.x() + dx2 * std::cos(fRot) + dz2 * std::sin(fRot),
        p1.y() + dy2,
        p1.z() - dx2 * std::sin(fRot) + dz2 * std::cos(fRot)
    );

    float dx3 = m_p3->x() - p1.x();
    float dy3 = m_p3->y() - p1.y();
    float dz3 = m_p3->z() - p1.z();

    m_p3->setXYZ(
        p1.x() + dx3 * std::cos(fRot) + dz3 * std::sin(fRot),
        p1.y() + dy3,
        p1.z() - dx3 * std::sin(fRot) + dz3 * std::cos(fRot)
    );
}

void StoneTriangle::copy(StoneTriangle *pTriangle) {
    m_p1->setXYZ(pTriangle->p1()->x(), pTriangle->p1()->y(), pTriangle->p1()->z());
    m_p2->setXYZ(pTriangle->p2()->x(), pTriangle->p2()->y(), pTriangle->p2()->z());
    m_p3->setXYZ(pTriangle->p3()->x(), pTriangle->p3()->y(), pTriangle->p3()->z());
}

// StoneGeneratorConfig

StoneGeneratorConfig::StoneGeneratorConfig() {
    m_nSurfaceDistortion = 0.0f;
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

void StoneGeneratorConfig::setSurfaceDistortion(float nSurfaceDistortion) {
    m_nSurfaceDistortion = nSurfaceDistortion;
}

float StoneGeneratorConfig::getSurfaceDistortion() const {
    return m_nSurfaceDistortion;
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
    
    this->processRemoveUnusefulTriangles(conf);
    this->processAttraction(conf);
    this->processRandom(conf);
    this->processResizeAndShift(conf);
    this->processNormals(conf);
    this->processTexturing(conf);

    std::cout << "got triangles = " << m_vTriangles.size() << std::endl;
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
    int nRandomDiff = 100.0 * conf.getSurfaceDistortion();
    float fMin = conf.getSurfaceDistortion();
    std::cout << "nRandomDiff: " << nRandomDiff << std::endl;
    if (nRandomDiff > 0) {
        for (int i = 0; i < m_vPoints.size(); i++) {
            float nOffsetX = fMin + float(std::rand() % nRandomDiff) / 100.0;
            float nOffsetY = fMin + float(std::rand() % nRandomDiff) / 100.0;
            float nOffsetZ = fMin + float(std::rand() % nRandomDiff) / 100.0;
            m_vPoints[i]->addOffset(nOffsetX, nOffsetY, nOffsetZ);
        }
    }
    return true;
}

bool StoneGenerator::processResizeAndShift(const StoneGeneratorConfig &conf) {
    if (m_vPoints.size() == 0) {
        return false;
    }

    float fDiameter = conf.getRadius()*2.0;
    float nSizeX = fDiameter * conf.getScaleX();
    float nSizeY = fDiameter * conf.getScaleY();
    float nSizeZ = fDiameter * conf.getScaleZ();

    float fMinX = m_vPoints[0]->x();
    float fMinY = m_vPoints[0]->y();
    float fMinZ = m_vPoints[0]->z();
    float fMaxX = m_vPoints[0]->x();
    float fMaxY = m_vPoints[0]->y();
    float fMaxZ = m_vPoints[0]->z();

    for (int i = 0; i < m_vPoints.size(); i++) {
        this->minXYZ(m_vPoints[i], fMinX, fMinY, fMinZ);
        this->maxXYZ(m_vPoints[i], fMaxX, fMaxY, fMaxZ);
    }

    // resize
    float fKX = nSizeX / (fMaxX - fMinX);
    float fKY = nSizeY / (fMaxY - fMinY);
    float fKZ = nSizeZ / (fMaxZ - fMinZ);

    // shift
    float fSX = -1.0 * (fMinX + (fMaxX - fMinX) / 2.0);
    float fSY = -1.0 * (fMinY + (fMaxY - fMinY) / 2.0);
    float fSZ = -1.0 * (fMinZ + (fMaxZ - fMinZ) / 2.0);

    for (int i = 0; i < m_vPoints.size(); i++) {
        m_vPoints[i]->setXYZ(
            fKX * (m_vPoints[i]->x() + fSX),
            fKY * (m_vPoints[i]->y() + fSY),
            fKZ * (m_vPoints[i]->z() + fSZ)
        );
    }

    return true;
}

bool StoneGenerator::processRemoveUnusefulTriangles(const StoneGeneratorConfig &conf) {
    std::vector<int> m_nRemoveTriangles;
    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneTriangle *pTri = m_vTriangles[i];
        if (pTri->p1() == pTri->p2() || pTri->p1() == pTri->p3() || pTri->p2() == pTri->p3()) {
            m_nRemoveTriangles.push_back(i);
        }
    }
    for (int i = m_nRemoveTriangles.size()-1; i >= 0; i--) {
        int nIndex = m_nRemoveTriangles[i];
        std::cout << "Removing triangle " << nIndex << std::endl;
        StoneTriangle *pTri = m_vTriangles[nIndex];
        delete pTri;
        m_vTriangles[nIndex] = nullptr;
        m_vTriangles.erase(m_vTriangles.begin() + nIndex);
    }
    std::cout << "Removed " << m_nRemoveTriangles.size() << std::endl;
    return true;
}

bool StoneGenerator::processNormals(const StoneGeneratorConfig &conf) {
    std::cout << "processNormals start" << std::endl;
    std::vector<StoneTriangle *> vFoundTriangles;
    StonePoint pCenter(0.0, 0.0, 0.0);
    float nPointsSize = m_vPoints.size();
    for (int i = 0; i < m_vPoints.size(); i++) {
        pCenter.addOffset(
            m_vPoints[i]->x(),
            m_vPoints[i]->y(),
            m_vPoints[i]->z()
        );
    }
    pCenter.setXYZ(
        pCenter.x() / nPointsSize,
        pCenter.y() / nPointsSize,
        pCenter.z() / nPointsSize
    );

    for (int i = 0; i < m_vPoints.size(); i++) {
        // std::cout << "processNormals " << i << std::endl;

        StonePoint *p0 = m_vPoints[i];
        
        vFoundTriangles.clear();
        findTrianglesByPoint(p0, vFoundTriangles);
        // std::cout << "processNormals vFoundTriangles.size() = " << vFoundTriangles.size() << std::endl;
        if (vFoundTriangles.size() == 0) {
            continue;
        }
        StonePoint pNormal(0.0, 0.0, 0.0);
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
        float x_n = 0.0;
        float y_n = 0.0;
        float z_n = 0.0;
        StonePoint middle_p;
        StonePoint middle_p_normal;
        for (int n = 0; n < vFoundTriangles.size(); n++) {
            /// std::cout << "processNormals n = " << n << std::endl;
            vFoundTriangles[n]->calculateMiddlePointAndNormal(middle_p, middle_p_normal);
            float fDistance1 = distance(&pCenter, &middle_p);
            float fDistance2 = distance(&pCenter, &middle_p_normal);
            float fM = 1.0;
            if (fDistance1 > fDistance2) {
                fM *= -1.0;
            }

            pNormal.addOffset(
                fM * (middle_p_normal.x() - middle_p.x()),
                fM * (middle_p_normal.y() - middle_p.y()),
                fM * (middle_p_normal.z() - middle_p.z())
            );
        }
        
        float size = vFoundTriangles.size();
        // // std::cout << "processNormals vFoundTriangles.size() 2 = " << size << std::endl;
        pNormal.setXYZ(
            pNormal.x() / size,
            pNormal.y() / size,
            pNormal.z() / size
        );

        // tangent
        // // by x to 90
        // float dx1 = x_n - x;
        // float dy1 = y_n - y;
        // float dz1 = z_n - z;
        // x_n = x + dx1;
        // y_n = y + dy1 * std::cos(M_PI/2) - dz1 * std::sin(M_PI/2);
        // z_n = z + dy1 * std::sin(M_PI/2) + dz1 * std::cos(M_PI/2);

        // // by y to 90
        // dx1 = x_n - x;
        // dy1 = y_n - y;
        // dz1 = z_n - z;
        // x_n = x + dx1 * std::cos(M_PI/2) + dz1 * std::sin(M_PI/2);
        // y_n = y + dy1;
        // z_n = z - dx1 * std::sin(M_PI/2) + dz1 * std::cos(M_PI/2);
        // p0
        // normal
        p0->setNormal(
            pNormal.x(),
            pNormal.y(),
            pNormal.z()
        );

    }
    std::cout << "processNormals end" << std::endl;
    return true;
}

bool StoneGenerator::processTexturing(const StoneGeneratorConfig &conf) {
    // calculate texture coordinates
    StonePoint *p1 = new StonePoint();
    StonePoint *p2 = new StonePoint();
    StonePoint *p3 = new StonePoint();
    StoneTriangle *pTriangle = new StoneTriangle(p1, p2, p3);

    // min max uv
    float nMaxU = 0.0f;
    float nMinU = 0.0f;
    float nMaxV = 0.0f;
    float nMinV = 0.0f;

    for (int i = 0; i < m_vTriangles.size(); i++) {
        pTriangle->copy(m_vTriangles[i]);

        StonePoint middle_p;
        StonePoint middle_p_normal;
        pTriangle->calculateMiddlePointAndNormal(middle_p, middle_p_normal);
        float fRotX = this->angelXAxis(middle_p, middle_p_normal);
        pTriangle->rotateInXAxisAroundPoint(middle_p, fRotX);
    
        float fRotY = this->angelYAxis(middle_p, middle_p_normal);
        pTriangle->rotateInYAxisAroundPoint(middle_p, fRotY);

        m_vTriangles[i]->t1().setXY(pTriangle->p1()->x(), pTriangle->p1()->y());
        m_vTriangles[i]->t2().setXY(pTriangle->p2()->x(), pTriangle->p2()->y());
        m_vTriangles[i]->t3().setXY(pTriangle->p3()->x(), pTriangle->p3()->y());
    }
    delete p1;
    delete p2;
    delete p3;
    delete pTriangle;

    // for (int i = 0; i < m_vTriangles.size(); i++) {
    //     StoneTriangle *pTri = m_vTriangles[i];
    //     int x = std::rand() % m_vTriangles.size();
    //     StoneTriangle *pTriFound = m_vTriangles[x];
    //     // StoneTriangle *pTriFound = findTriangleByPoints2(pTri->p1(), pTri->p2(), pTri);
    //     if (pTriFound != nullptr) {
    //         float dx1 = pTriFound->t1().x() - pTri->t1().x();
    //         float dy1 = pTriFound->t1().y() - pTri->t1().y();

    //         pTri->t1().setXY(
    //             pTri->t1().x() + dx1,
    //             pTri->t1().y() + dy1
    //         );

    //         pTri->t2().setXY(
    //             pTri->t2().x() + dx1,
    //             pTri->t2().y() + dy1
    //         );

    //         pTri->t3().setXY(
    //             pTri->t3().x() + dx1,
    //             pTri->t3().y() + dy1
    //         );
    //     }
    // }


    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneTriangle *pTri = m_vTriangles[i];
        this->minmaxUV(pTri->t1(), nMinU, nMaxU, nMinV, nMaxV);
        this->minmaxUV(pTri->t2(), nMinU, nMaxU, nMinV, nMaxV);
        this->minmaxUV(pTri->t3(), nMinU, nMaxU, nMinV, nMaxV);
    }

    // normalize coordinates to 0..1
    float dU = nMaxU - nMinU;
    float dV = nMaxV - nMinV;
    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneTriangle *pTri = m_vTriangles[i];
        this->normalizeUV(pTri->t1(), nMinU, nMaxU, nMinV, nMaxV);
        this->normalizeUV(pTri->t2(), nMinU, nMaxU, nMinV, nMaxV);
        this->normalizeUV(pTri->t3(), nMinU, nMaxU, nMinV, nMaxV);
    }
    return true;
}

StoneTriangle *StoneGenerator::findTriangleByPoints2(StonePoint *p1, StonePoint *p2, StoneTriangle *pExclude) {
    StoneTriangle *pRet = nullptr;
    for (int i = 0; i < m_vTriangles.size(); i++) {
        StoneTriangle *pTri = m_vTriangles[i];
        if (pExclude == pTri) {
            continue;
        }
        if (pTri->hasPoint(p1) && pTri->hasPoint(p2)) {
            pRet = pTri;
            break;
        }
    }
    return pRet;
}

void StoneGenerator::findTrianglesByPoint(StonePoint *p1, std::vector<StoneTriangle *> &vTriangles) {
    for (int i = 0; i < m_vTriangles.size(); i++) {
        if (m_vTriangles[i]->hasPoint(p1)) {
            vTriangles.push_back(m_vTriangles[i]);
        }
    }
}

float StoneGenerator::distance(StonePoint *p1, StonePoint *p2) {
    float dx = p1->x() - p2->x();
    float dy = p1->y() - p2->y();
    float dz = p1->z() - p2->z();
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

float StoneGenerator::distanceUV(StoneTexturePoint &p1, StoneTexturePoint &p2) {
    float dx = p1.x() - p2.x();
    float dy = p1.y() - p2.y();
    return std::sqrt(dx*dx + dy*dy);
}

float StoneGenerator::angel(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float _len = std::sqrt(dx * dx + dy * dy);
    int nLen = std::abs(_len*100000);
    if (nLen < 1000) {
        return 0.0;
    }
    float ret = std::asin(dx / _len);
    if (dy < 0) {
        ret = -1 * ret;
    } else {
        ret = ret;
    }
    return ret;
}

float StoneGenerator::angelXAxis(const StonePoint &p1, const StonePoint &p2) {
    float rot = angel(p1.y(), p1.z(), p2.y(), p2.z());
    return rot;
}

float StoneGenerator::angelYAxis(const StonePoint &p1, const StonePoint &p2) {
    float rot = this->angel(p1.x(), p1.z(), p2.x(), p2.z());
    rot = -1.0 * rot;
    return rot;
}

float StoneGenerator::angelXY(StonePoint *p1, StonePoint *p2) {
    float dy = p2->y() - p1->y();
    float dx = p2->x() - p1->x();
    float c = std::sqrt(dx*dx + dy*dy);
    return std::asin(dx/c);
}

float StoneGenerator::angelZX(StonePoint *p1, StonePoint *p2) {
    float dz = p2->z() - p1->z();
    float dx = p2->x() - p1->x();
    float c = std::sqrt(dx*dx + dz*dz);
    return std::acos(dz/c);
}

float StoneGenerator::angelZY(StonePoint *p1, StonePoint *p2) {
    float dz = p2->z() - p1->z();
    float dy = p2->y() - p1->y();
    float c = std::sqrt(dy*dy + dz*dz);
    return std::acos(dz/c);
}

void StoneGenerator::minmaxUV(StoneTexturePoint &p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV) {
    nMinU = std::min(nMinU, p1.x());
    nMaxU = std::max(nMaxU, p1.x());
    nMinV = std::min(nMinV, p1.y());
    nMaxV = std::max(nMaxV, p1.y());
}

void StoneGenerator::normalizeUV(StoneTexturePoint &p1, float &nMinU, float &nMaxU, float &nMinV, float &nMaxV) {
    float fMainSide = nMaxU - nMinU;
    float dV = nMaxV - nMinV;
    float vK = fMainSide / dV;

    float u = p1.x();
    float v = p1.y();
    u = (u - nMinU) / fMainSide;
    v = ((v - vK * nMinV) / fMainSide);
    p1.setXY(u, v);
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
