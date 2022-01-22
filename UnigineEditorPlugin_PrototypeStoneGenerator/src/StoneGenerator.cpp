#include "StoneGenerator.h"
#include <math.h>
#include <iostream>
// StonePoint

StonePoint::StonePoint(float x, float y, float z) {
    m_nX = x;
    m_nY = y;
    m_nZ = z;
    m_nX100 = m_nX*100;
    m_nY100 = m_nY*100;
    m_nZ100 = m_nZ*100;
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


// StoneGenerator

StoneGenerator::StoneGenerator() {
    m_nRandomOffsetMin = 0.0f;
    m_nRandomOffsetMax = 0.0f;
    m_nRadius = 2.0f;
    m_nExpectedTriangles = 300;
}

StoneGenerator::~StoneGenerator() {
    this->clear();
}

void StoneGenerator::setRaidus(float nRadius) {
    m_nRadius = nRadius;
}

float StoneGenerator::getRaidus() {
    return m_nRadius;
}

void StoneGenerator::setRandomOffsetMin(float nRandomOffsetMin) {
    m_nRandomOffsetMin = nRandomOffsetMin;
}

int StoneGenerator::getRandomOffsetMin() {
    return m_nRandomOffsetMin;
}

void StoneGenerator::setRandomOffsetMax(float nRandomOffsetMax) {
    m_nRandomOffsetMax = nRandomOffsetMax;
}

int StoneGenerator::getRandomOffsetMax() {
    return m_nRandomOffsetMax;
}

void StoneGenerator::setEstimatedExpectedTriangles(int nExpected) {
    m_nExpectedTriangles = nExpected;
}

int StoneGenerator::getEstimatedExpectedTriangles() {
    return m_nExpectedTriangles;
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

bool StoneGenerator::generate() {
    std::cout << "m_nExpectedTriangles = " << m_nExpectedTriangles << std::endl;
    int nK = m_nExpectedTriangles/2;
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
    for (int zz0 = 0; zz0 < nK; zz0++) {
        ZLevel lvl;
        lvl.xy_sectors.clear();
        float z_angel = z_spp * float(zz0);
        lvl.z_radius = m_nRadius * sin( z_angel );
        lvl.z = m_nRadius * cos( z_angel );
        for (int rr0 = 0; rr0 < nK; rr0++) {
            XYPoint xy;
            float angel = spp * float(rr0);
            xy.x = lvl.z_radius * cos( angel);
			xy.y = lvl.z_radius * sin( angel);
            lvl.xy_sectors.push_back(xy);
        }
        // int sorted = 1;
        // while(sorted > 0) {
        //     sorted = 0;
        //     for (int rr0 = 0; rr0 < lvl.xy_sectors.size()-1; rr0++) {
        //         if (lvl.xy_sectors[rr0].x > lvl.xy_sectors[rr0+1].x) {
        //             XYPoint xy0 = lvl.xy_sectors[rr0];
        //             lvl.xy_sectors[rr0] = lvl.xy_sectors[rr0+1];
        //             lvl.xy_sectors[rr0+1] = xy0;
        //             sorted++;
        //         }
        //     }
        // }
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
            StonePoint *pPoint00 = addPoint(x0y0.x, x0y0.y, lvl_z.z);
            StonePoint *pPoint01 = addPoint(x0y1.x, x0y1.y, lvl_z.z);
            StonePoint *pPoint10 = addPoint(x1y0.x, x1y0.y, lvl_z_next.z);
            StonePoint *pPoint11 = addPoint(x1y1.x, x1y1.y, lvl_z_next.z);

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
            StoneTriangle *pTriangle2 = new StoneTriangle(
                pPoint01,
                pPoint10,
                pPoint11
            );

            // delete pTriangle2;
            m_vTriangles.push_back(pTriangle2);

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

    int nRandomDiff = (m_nRandomOffsetMax - m_nRandomOffsetMin)*100;
    if (nRandomDiff > 0) {
        for (int i = 0; i < m_vPoints.size(); i++) {
            float nOffsetX = m_nRandomOffsetMin + float(std::rand() % nRandomDiff) / 100;
            float nOffsetY = m_nRandomOffsetMin + float(std::rand() % nRandomDiff) / 100;
            float nOffsetZ = m_nRandomOffsetMin + float(std::rand() % nRandomDiff) / 100;
            m_vPoints[i]->addOffset(nOffsetX, nOffsetY, nOffsetZ);
        }
    }
    
    return true;
}

const std::vector<StoneTriangle *> &StoneGenerator::triangles() {
    return m_vTriangles;
}

StonePoint *StoneGenerator::addPoint(float x, float y, float z) {
    StonePoint *pPoint = nullptr;
    int nX = x*100;
    int nY = y*100;
    int nZ = z*100;
    int nThreshold = 15; // 0.15
    for (int i = 0; i < m_vPoints.size(); i++) {
        if (m_vPoints[i]->compare(nX, nY, nZ, nThreshold)) {
            pPoint = m_vPoints[i];
            break;
        }
    }
    if (pPoint == nullptr) {
        pPoint = new StonePoint(x,y,z);
        m_vPoints.push_back(pPoint);
    }
    return pPoint;
}