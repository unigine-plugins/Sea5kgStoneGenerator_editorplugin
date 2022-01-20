#include "StoneGenerator.h"
#include <math.h>

// StonePoint

StonePoint::StonePoint(float x, float y, float z) {
    m_nX = x;
    m_nY = y;
    m_nZ = z;
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

bool StoneGenerator::generate() {
    int nK = m_nExpectedTriangles/2;
    nK = sqrt(nK);

    float spp = M_PI*2 / float(nK);
	// int nTexX = 0.2;
	// int nTexY = 0.2;
	for (int zz0 = 0; zz0 < nK; zz0++) {
		float small_r0 = m_nRadius * sin( spp * float(zz0) );
		float z0 = m_nRadius * cos( spp * float(zz0) );
		float small_r1 = m_nRadius * sin( spp * float(zz0+1) );
		float z1 = m_nRadius * cos( spp * float(zz0+1) );
		float small_r2 = small_r0;
		float z2 = z0;
		// nTexY += 0.2;
		for (int rr0 = 0; rr0 < nK; rr0++) {
			// nTexX += 0.2;
			float x0 = small_r0 * sin( spp * float(rr0) );
			float y0 = small_r0 * cos( spp * float(rr0) );

			float x1 = small_r1 * sin( spp * float(rr0) );
			float y1 = small_r1 * cos( spp * float(rr0) );

			float x2 = small_r2 * sin( spp * float(rr0 + 1) );
			float y2 = small_r2 * cos( spp * float(rr0 + 1) );

			float x3 = small_r2 * sin( spp * float(rr0 - 1) );
			float y3 = small_r2 * cos( spp * float(rr0 - 1) );

            m_vTriangles.push_back(new StoneTriangle(
                new StonePoint(x0,y0,z0),
                new StonePoint(x1,y1,z1),
                new StonePoint(x2,y2,z2)
            ));

            m_vTriangles.push_back(new StoneTriangle(
                new StonePoint(x0,y0,z0),
                new StonePoint(x1,y1,z1),
                new StonePoint(x3,y3,z2)
            ));

            // TODO text coord 
            // TODO normales
			// textCoord.push_back(Unigine::Math::vec4(nTexX, 0, 0, 0));
			// textCoord.push_back(Unigine::Math::vec4(nTexX + 0.2, 0, 0, 0));
			// textCoord.push_back(Unigine::Math::vec4(nTexX + 0.2, nTexY + 0.2, 0, 0));

			// textCoord.push_back(Unigine::Math::vec4(nTexX, 0, 0, 0));
			// textCoord.push_back(Unigine::Math::vec4(nTexX + 0.2, 0, 0, 0));
			// textCoord.push_back(Unigine::Math::vec4(nTexX + 0.2, nTexY + 0.2, 0, 0));

			// add(x0,y0,z0, vertices);
		}
	}
    return true;
}

const std::vector<StoneTriangle *> &StoneGenerator::triangles() {
    return m_vTriangles;
}