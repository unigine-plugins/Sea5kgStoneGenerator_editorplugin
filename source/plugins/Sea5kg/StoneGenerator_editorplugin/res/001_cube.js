var generatorName = "Cube";
var generatorId = 1;

function generate(expected_triangles, radius) {
    print(expected_triangles);
    print(radius);

    // Model.clear();
    var fK = expected_triangles / 6.0; // 6 sides
    fK = fK / 2.0;
    fK = Math.sqrt(fK); // squares on each side;
    var nK = Math.round(fK);

    var nStep = 2 * radius / nK;

    var nX0 = -radius;
    var nX1 = radius;

    var nY0 = -radius;
    var nY1 = radius;

    var nZ0 = -radius;
    var nZ1 = radius;

    for (var a = 0; a < nK; a++) {
        var fA0 = a*nStep - radius;
        var fA1 = fA0 + nStep;

        for (var b = 0; b < nK; b++) {
            var fB0 = b*nStep - radius;
            var fB1 = fB0 + nStep;
            // print("fB0: " + fB0);
            // print("fB1: " + fB1);

            // bottom
            {
                var pPoint00 = Model.addPoint(fA0, fB0, nZ0);
                var pPoint01 = Model.addPoint(fA0, fB1, nZ0);
                var pPoint10 = Model.addPoint(fA1, fB0, nZ0);
                var pPoint11 = Model.addPoint(fA1, fB1, nZ0);
                Model.addTriangle(pPoint00, pPoint01, pPoint11);
                Model.addTriangle(pPoint00, pPoint11, pPoint10);
            }

            // top
            {
                var pPoint00 = Model.addPoint(fA0, fB0, nZ1);
                var pPoint01 = Model.addPoint(fA0, fB1, nZ1);
                var pPoint10 = Model.addPoint(fA1, fB0, nZ1);
                var pPoint11 = Model.addPoint(fA1, fB1, nZ1);
                Model.addTriangle(pPoint11, pPoint01, pPoint00);
                Model.addTriangle(pPoint10, pPoint11, pPoint00);
            }

            // left
            {
                var pPoint00 = Model.addPoint(nX0, fB0, fA0);
                var pPoint01 = Model.addPoint(nX0, fB0, fA1);
                var pPoint10 = Model.addPoint(nX0, fB1, fA0);
                var pPoint11 = Model.addPoint(nX0, fB1, fA1);
                Model.addTriangle(pPoint00, pPoint01, pPoint11);
                Model.addTriangle(pPoint00, pPoint11, pPoint10);
            }

            // right
            {
                var pPoint00 = Model.addPoint(nX1, fB0, fA0);
                var pPoint01 = Model.addPoint(nX1, fB0, fA1);
                var pPoint10 = Model.addPoint(nX1, fB1, fA0);
                var pPoint11 = Model.addPoint(nX1, fB1, fA1);
                Model.addTriangle(pPoint11, pPoint01, pPoint00);
                Model.addTriangle(pPoint10, pPoint11, pPoint00);
            }

            // front
            {
                var pPoint00 = Model.addPoint(fB0, nY1, fA0);
                var pPoint01 = Model.addPoint(fB0, nY1, fA1);
                var pPoint10 = Model.addPoint(fB1, nY1, fA0);
                var pPoint11 = Model.addPoint(fB1, nY1, fA1);
                Model.addTriangle(pPoint00, pPoint01, pPoint11);
                Model.addTriangle(pPoint00, pPoint11, pPoint10);
            }

            // end
            {
                var pPoint00 = Model.addPoint(fB0, nY0, fA0);
                var pPoint01 = Model.addPoint(fB0, nY0, fA1);
                var pPoint10 = Model.addPoint(fB1, nY0, fA0);
                var pPoint11 = Model.addPoint(fB1, nY0, fA1);
                Model.addTriangle(pPoint11, pPoint01, pPoint00);
                Model.addTriangle(pPoint10, pPoint11, pPoint00);
            }
        }
    }
}