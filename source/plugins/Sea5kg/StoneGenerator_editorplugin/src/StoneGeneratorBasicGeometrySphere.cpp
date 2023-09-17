#include "StoneGeneratorBasicGeometrySphere.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

#include <StoneGeneratorTriangle.h>

// ---------------------------------------------------------------------
// StoneGeneratorBasicSphere

StoneGeneratorBasicSphere::StoneGeneratorBasicSphere() : StoneGeneratorBasicGeometry(0, "Sphere") {

}

bool StoneGeneratorBasicSphere::generate(StoneGeneratorModel *pModel, int nExpectedTriangles, float nRadius) {
    pModel->clear();

    struct XYPoint {
        float x;
        float y;
    };

    struct ZLevel {
        float z;
        float z_radius;
        std::vector<XYPoint> xy_sectors;
    };

    // TODO redesign
    int nK = nExpectedTriangles / 2;
    // std::cout << "nK = " << nK << std::endl;
    nK = sqrt(nK);
    // std::cout << "nK = " << nK << std::endl;
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
        lvl.z_radius = nRadius * sin( z_angel );
        lvl.z = nRadius * cos( z_angel );
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
            StoneGeneratorPoint *pPoint00 = pModel->addPoint(x0y0.x, x0y0.y, lvl_z.z);
            StoneGeneratorPoint *pPoint01 = pModel->addPoint(x0y1.x, x0y1.y, lvl_z.z);
            StoneGeneratorPoint *pPoint10 = pModel->addPoint(x1y0.x, x1y0.y, lvl_z_next.z);
            StoneGeneratorPoint *pPoint11 = pModel->addPoint(x1y1.x, x1y1.y, lvl_z_next.z);

            // 00 * ----- * 01
            //    |       |
            // 10 * ----- * 11
            if (pPoint00 != pPoint01 && pPoint01 != pPoint10 && pPoint10 != pPoint00) {
                pModel->addTriangle(
                    pPoint01,
                    pPoint00,
                    pPoint10

                    // pPoint00,
                    // pPoint01,
                    // pPoint10
                );
            }

            if (i_xy > 0 || i_xy < xy_sectors.size() - 1) {
                // if (pPoint00 != pPoint01 && pPoint01 != pPoint10 && pPoint10 != pPoint00) {
                    pModel->addTriangle(
                        pPoint01,
                        pPoint10,
                        pPoint11
                    );
                // }
            }
        }
    }
    return true;
}
