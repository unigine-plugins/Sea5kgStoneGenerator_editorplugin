var generatorName = "CassetteTape";
var generatorId = 8;

function generate(expected_triangles, scale) {
    print("Generating Cassette Tape with " + expected_triangles + " triangles");
    print("Scale: " + scale);

    // Model.clear();
    
    // Cassette tape dimensions (normalized, will be scaled)
    var length = 10.0 * scale;
    var width = 6.5 * scale;
    var height = 1.5 * scale;
    
    // Calculate subdivisions based on expected triangles
    var faces = 12; // main body + various details
    var trianglesPerFace = expected_triangles / faces;
    var subdivisions = Math.max(2, Math.floor(Math.sqrt(trianglesPerFace / 2)));
    
    print("Subdivisions: " + subdivisions);

    // Main cassette body
    createCuboid(-length/2, -width/2, -height/2, length/2, width/2, height/2, subdivisions);
    
    // Tape reels (circular)
    var reelRadius = 2.0 * scale;
    createReel(-2.5 * scale, 0, height/2 + 0.01, reelRadius, 0.2 * scale, 16);
    createReel(2.5 * scale, 0, height/2 + 0.01, reelRadius, 0.2 * scale, 16);
    
    // Center window
    createWindow(0, 0, height/2 + 0.02, 6 * scale, 3 * scale, 0.1 * scale, 8);
    
    // Label area
    createLabelArea(0, -width/2 + 0.5 * scale, height/2 + 0.03, 8 * scale, 4 * scale, 0.05 * scale, 4);
    
    // Write protection tabs
    createTab(-4 * scale, width/2 - 0.5 * scale, height/2 + 0.02, 0.5 * scale, 4);
    createTab(4 * scale, width/2 - 0.5 * scale, height/2 + 0.02, 0.5 * scale, 4);
}

function createCuboid(x0, y0, z0, x1, y1, z1, subdivisions) {
    var stepX = (x1 - x0) / subdivisions;
    var stepY = (y1 - y0) / subdivisions;
    var stepZ = (z1 - z0) / subdivisions;
    
    // Create all 6 faces
    for (var i = 0; i < subdivisions; i++) {
        for (var j = 0; j < subdivisions; j++) {
            // Front face (Y max)
            var fY0 = y0 + i * stepY;
            var fY1 = fY0 + stepY;
            var fZ0 = z0 + j * stepZ;
            var fZ1 = fZ0 + stepZ;
            
            var p00 = Model.addPoint(x0, y1, fZ0);
            var p01 = Model.addPoint(x0, y1, fZ1);
            var p10 = Model.addPoint(x1, y1, fZ0);
            var p11 = Model.addPoint(x1, y1, fZ1);
            Model.addTriangle(p00, p01, p11);
            Model.addTriangle(p00, p11, p10);
            
            // Back face (Y min)
            p00 = Model.addPoint(x0, y0, fZ0);
            p01 = Model.addPoint(x0, y0, fZ1);
            p10 = Model.addPoint(x1, y0, fZ0);
            p11 = Model.addPoint(x1, y0, fZ1);
            Model.addTriangle(p11, p01, p00);
            Model.addTriangle(p10, p11, p00);
            
            // Right face (X max)
            var fX0 = x0 + i * stepX;
            var fX1 = fX0 + stepX;
            
            p00 = Model.addPoint(x1, fY0, fZ0);
            p01 = Model.addPoint(x1, fY0, fZ1);
            p10 = Model.addPoint(x1, fY1, fZ0);
            p11 = Model.addPoint(x1, fY1, fZ1);
            Model.addTriangle(p11, p01, p00);
            Model.addTriangle(p10, p11, p00);
            
            // Left face (X min)
            p00 = Model.addPoint(x0, fY0, fZ0);
            p01 = Model.addPoint(x0, fY0, fZ1);
            p10 = Model.addPoint(x0, fY1, fZ0);
            p11 = Model.addPoint(x0, fY1, fZ1);
            Model.addTriangle(p00, p01, p11);
            Model.addTriangle(p00, p11, p10);
            
            // Top face (Z max)
            p00 = Model.addPoint(fX0, fY0, z1);
            p01 = Model.addPoint(fX0, fY1, z1);
            p10 = Model.addPoint(fX1, fY0, z1);
            p11 = Model.addPoint(fX1, fY1, z1);
            Model.addTriangle(p00, p01, p11);
            Model.addTriangle(p00, p11, p10);
            
            // Bottom face (Z min)
            p00 = Model.addPoint(fX0, fY0, z0);
            p01 = Model.addPoint(fX0, fY1, z0);
            p10 = Model.addPoint(fX1, fY0, z0);
            p11 = Model.addPoint(fX1, fY1, z0);
            Model.addTriangle(p11, p01, p00);
            Model.addTriangle(p10, p11, p00);
        }
    }
}

function createReel(centerX, centerY, centerZ, radius, thickness, segments) {
    var angleStep = 2 * Math.PI / segments;
    
    // Create top circle
    var topCenter = Model.addPoint(centerX, centerY, centerZ + thickness/2);
    var topPoints = [];
    
    for (var i = 0; i < segments; i++) {
        var angle = i * angleStep;
        var x = centerX + Math.cos(angle) * radius;
        var y = centerY + Math.sin(angle) * radius;
        var z = centerZ + thickness/2;
        topPoints.push(Model.addPoint(x, y, z));
    }
    
    // Create bottom circle
    var bottomCenter = Model.addPoint(centerX, centerY, centerZ - thickness/2);
    var bottomPoints = [];
    
    for (var i = 0; i < segments; i++) {
        var angle = i * angleStep;
        var x = centerX + Math.cos(angle) * radius;
        var y = centerY + Math.sin(angle) * radius;
        var z = centerZ - thickness/2;
        bottomPoints.push(Model.addPoint(x, y, z));
    }
    
    // Create top face triangles
    for (var i = 0; i < segments; i++) {
        var next = (i + 1) % segments;
        Model.addTriangle(topCenter, topPoints[i], topPoints[next]);
    }
    
    // Create bottom face triangles
    for (var i = 0; i < segments; i++) {
        var next = (i + 1) % segments;
        Model.addTriangle(bottomCenter, bottomPoints[next], bottomPoints[i]);
    }
    
    // Create side triangles
    for (var i = 0; i < segments; i++) {
        var next = (i + 1) % segments;
        Model.addTriangle(topPoints[i], bottomPoints[i], bottomPoints[next]);
        Model.addTriangle(topPoints[i], bottomPoints[next], topPoints[next]);
    }
}

function createWindow(centerX, centerY, centerZ, width, height, thickness, segments) {
    var halfW = width / 2;
    var halfH = height / 2;
    
    // Create window frame (hollow rectangle)
    createCuboid(centerX - halfW, centerY - halfH, centerZ, 
                 centerX + halfW, centerY + halfH, centerZ + thickness, 2);
}

function createLabelArea(centerX, centerY, centerZ, width, height, thickness, segments) {
    var halfW = width / 2;
    var halfH = height / 2;
    
    createCuboid(centerX - halfW, centerY - halfH, centerZ, 
                 centerX + halfW, centerY + halfH, centerZ + thickness, segments);
}

function createTab(centerX, centerY, centerZ, radius, segments) {
    // Create a small cylindrical tab
    createReel(centerX, centerY, centerZ, radius, 0.1, segments);
}