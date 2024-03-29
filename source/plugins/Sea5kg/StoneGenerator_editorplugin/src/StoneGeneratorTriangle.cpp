#include "StoneGeneratorTriangle.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

// ---------------------------------------------------------------------
// StoneGeneratorTriangle

StoneGeneratorTriangle::StoneGeneratorTriangle(
    StoneGeneratorPoint *p1,
    StoneGeneratorPoint *p2,
    StoneGeneratorPoint *p3
) {
    m_points = new StoneGeneratorPoint* [3];
    m_pTexPoints = new StoneGeneratorTexturePoint [3];
    m_points[0] = p1;
    m_points[1] = p2;
    m_points[2] = p3;
    m_points[0]->addLinkToTriangle(this);
    m_points[1]->addLinkToTriangle(this);
    m_points[2]->addLinkToTriangle(this);
}

StoneGeneratorTriangle::~StoneGeneratorTriangle() {
    m_points[0]->removeLinkToTriangle(this);
    m_points[1]->removeLinkToTriangle(this);
    m_points[2]->removeLinkToTriangle(this);
    delete[] m_points;
    delete[] m_pTexPoints;
}

StoneGeneratorPoint *StoneGeneratorTriangle::p1() {
    return m_points[0];
}

StoneGeneratorPoint *StoneGeneratorTriangle::p2() {
    return m_points[1];
}

StoneGeneratorPoint *StoneGeneratorTriangle::p3() {
    return m_points[2];
}

StoneGeneratorPoint *StoneGeneratorTriangle::normalP1() {
    return &m_pointNormalP1;
}

StoneGeneratorPoint *StoneGeneratorTriangle::normalP2() {
    return &m_pointNormalP2;
}

StoneGeneratorPoint *StoneGeneratorTriangle::normalP3() {
    return &m_pointNormalP3;
}

bool StoneGeneratorTriangle::hasPoint(StoneGeneratorPoint *p) {
    return m_points[0] == p || m_points[1] == p || m_points[2] == p;
}

StoneGeneratorPoint *StoneGeneratorTriangle::getPointByIndex(int nIndex) {
    return m_points[nIndex];
}

StoneGeneratorTexturePoint &StoneGeneratorTriangle::t1() {
    return m_pTexPoints[0];
}

StoneGeneratorTexturePoint &StoneGeneratorTriangle::t2() {
    return m_pTexPoints[1];
}

StoneGeneratorTexturePoint &StoneGeneratorTriangle::t3() {
    return m_pTexPoints[2];
}

StoneGeneratorTexturePoint &StoneGeneratorTriangle::getTexPointByIndex(int nIndex) {
    return m_pTexPoints[nIndex];
}

void StoneGeneratorTriangle::calculateMiddlePoint(StoneGeneratorPoint &point) const {
    point.setXYZ(
        (m_points[0]->getX() + m_points[1]->getX() + m_points[2]->getX()) / 3.0,
        (m_points[0]->getY() + m_points[1]->getY() + m_points[2]->getY()) / 3.0,
        (m_points[0]->getZ() + m_points[1]->getZ() + m_points[2]->getZ()) / 3.0
    );
}

void StoneGeneratorTriangle::calculateNormal(StoneGeneratorPoint &normal) const {
    // StoneGeneratorPoint middlePoint;
    // this->calculateMiddlePoint(middlePoint);

    // here math:
    // http://mathprofi.ru/uravnenie_ploskosti.html

    //
    // | x - x1, x2 - x1, x3 - x1 |
    // | y - y1, y2 - y1, y3 - y1 | == 0
    // | z - z1, z2 - z1, z3 - z1 |
    // (x - x1) * | y2 - y1, y3 - y1 | - (y - y1) * | x2 - x1, x3 - x1 | + (z - z1) * | x2 - x1, x3 - x1 |
    //            | z2 - z1, z3 - z1 |              | z2 - z1, z3 - z1 |              | y2 - y1, y3 - y1 |
    //
    // (x - x1) * ((y2 - y1) *(z3 - z1) - (z2 - z1)*(y3 - y1))
    // - (y - y1) * ((x2 - x1)*(z3 - z1) - (x3 - x1)*(z2 - z1))
    // + (z - z1) * ((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1))
    //
    // x = ((y2 - y1) *(z3 - z1) - (z2 - z1)*(y3 - y1))
    // y = - ((x2 - x1)*(z3 - z1) - (x3 - x1)*(z2 - z1))
    // z = ((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1))

    float x21 = m_points[1]->getX() - m_points[0]->getX();
    float y21 = m_points[1]->getY() - m_points[0]->getY();
    float z21 = m_points[1]->getZ() - m_points[0]->getZ();
    float x31 = m_points[2]->getX() - m_points[0]->getX();
    float y31 = m_points[2]->getY() - m_points[0]->getY();
    float z31 = m_points[2]->getZ() - m_points[0]->getZ();

    normal.setXYZ(
        + (y21*z31 - z21*y31),
        - (x21*z31 - z21*x31),
        + (x21*y31 - y21*x31)
    );
    normal.normalizeToUnitVector();
}

void StoneGeneratorTriangle::rotateInXAxisAroundPoint(StoneGeneratorPoint &p1, float fRot) {

    // help here:
    // https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space

    // x axis
    // |1     0           0| |x|   |        x        |   |x'|
    // |0   cos θ    −sin θ| |y| = |y cos θ − z sin θ| = |y'|
    // |0   sin θ     cos θ| |z|   |y sin θ + z cos θ|   |z'|

    float dx1 = m_points[0]->getX() - p1.getX();
    float dy1 = m_points[0]->getY() - p1.getY();
    float dz1 = m_points[0]->getZ() - p1.getZ();

    m_points[0]->setXYZ(
        p1.getX() + dx1,
        p1.getY() + dy1 * std::cos(fRot) - dz1 * std::sin(fRot),
        p1.getZ() + dy1 * std::sin(fRot) + dz1 * std::cos(fRot)
    );

    float dx2 = m_points[1]->getX() - p1.getX();
    float dy2 = m_points[1]->getY() - p1.getY();
    float dz2 = m_points[1]->getZ() - p1.getZ();

    m_points[1]->setXYZ(
        p1.getX() + dx2,
        p1.getY() + dy2 * std::cos(fRot) - dz2 * std::sin(fRot),
        p1.getZ() + dy2 * std::sin(fRot) + dz2 * std::cos(fRot)
    );

    float dx3 = m_points[2]->getX() - p1.getX();
    float dy3 = m_points[2]->getY() - p1.getY();
    float dz3 = m_points[2]->getZ() - p1.getZ();

    m_points[2]->setXYZ(
        p1.getX() + dx3,
        p1.getY() + dy3 * std::cos(fRot) - dz3 * std::sin(fRot),
        p1.getZ() + dy3 * std::sin(fRot) + dz3 * std::cos(fRot)
    );
}

void StoneGeneratorTriangle::rotateInYAxisAroundPoint(StoneGeneratorPoint &p1, float fRot) {

    // help here:
    // https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space

    // y axis
    // | cos θ    0   sin θ| |x|   | x cos θ + z sin θ|   |x'|
    // |   0      1       0| |y| = |         y        | = |y'|
    // |−sin θ    0   cos θ| |z|   |−x sin θ + z cos θ|   |z'|

    float dx1 = m_points[0]->getX() - p1.getX();
    float dy1 = m_points[0]->getY() - p1.getY();
    float dz1 = m_points[0]->getZ() - p1.getZ();

    m_points[0]->setXYZ(
        p1.getX() + dx1 * std::cos(fRot) + dz1 * std::sin(fRot),
        p1.getY() + dy1,
        p1.getZ() - dx1 * std::sin(fRot) + dz1 * std::cos(fRot)
    );

    float dx2 = m_points[1]->getX() - p1.getX();
    float dy2 = m_points[1]->getY() - p1.getY();
    float dz2 = m_points[1]->getZ() - p1.getZ();

    m_points[1]->setXYZ(
        p1.getX() + dx2 * std::cos(fRot) + dz2 * std::sin(fRot),
        p1.getY() + dy2,
        p1.getZ() - dx2 * std::sin(fRot) + dz2 * std::cos(fRot)
    );

    float dx3 = m_points[2]->getX() - p1.getX();
    float dy3 = m_points[2]->getY() - p1.getY();
    float dz3 = m_points[2]->getZ() - p1.getZ();

    m_points[2]->setXYZ(
        p1.getX() + dx3 * std::cos(fRot) + dz3 * std::sin(fRot),
        p1.getY() + dy3,
        p1.getZ() - dx3 * std::sin(fRot) + dz3 * std::cos(fRot)
    );
}

void StoneGeneratorTriangle::copy(StoneGeneratorTriangle *pTriangle) {
    m_points[0]->setXYZ(pTriangle->p1()->getX(), pTriangle->p1()->getY(), pTriangle->p1()->getZ());
    m_points[1]->setXYZ(pTriangle->p2()->getX(), pTriangle->p2()->getY(), pTriangle->p2()->getZ());
    m_points[2]->setXYZ(pTriangle->p3()->getX(), pTriangle->p3()->getY(), pTriangle->p3()->getZ());
}

void StoneGeneratorTriangle::rotateTexPointsBy(int nIndex0, float fAngle) {
    float ca = std::cos(fAngle);
    float sa = std::sin(fAngle);

    float x0 = m_pTexPoints[nIndex0].x();
    float y0 = m_pTexPoints[nIndex0].y();

    int nIndex1 = (nIndex0 + 1) % 3;
    float dX1 = m_pTexPoints[nIndex1].x() - x0;
    float dY1 = m_pTexPoints[nIndex1].y() - y0;
    m_pTexPoints[nIndex1].setXY(
        x0 + (dX1 * ca - dY1 * sa),
        y0 + (dX1 * sa + dY1 * ca)
    );

    int nIndex2 = (nIndex0 + 2) % 3;
    float dX2 = m_pTexPoints[nIndex2].x() - x0;
    float dY2 = m_pTexPoints[nIndex2].y() - y0;
    m_pTexPoints[nIndex2].setXY(
        x0 + (dX2 * ca - dY2 * sa),
        y0 + (dX2 * sa + dY2 * ca)
    );
}

void StoneGeneratorTriangle::moveTexPointsBy(int nIndex0, const StoneGeneratorTexturePoint &t) {
    float dx = t.x() - m_pTexPoints[nIndex0].x();
    float dy = t.y() - m_pTexPoints[nIndex0].y();

    m_pTexPoints[nIndex0].setXY(
        t.x(),
        t.y()
    );

    int nIndex1 = (nIndex0 + 1) % 3;
    m_pTexPoints[nIndex1].setXY(
        m_pTexPoints[nIndex1].x() + dx,
        m_pTexPoints[nIndex1].y() + dy
    );

    int nIndex2 = (nIndex0 + 2) % 3;
    m_pTexPoints[nIndex2].setXY(
        m_pTexPoints[nIndex2].x() + dx,
        m_pTexPoints[nIndex2].y() + dy
    );
}