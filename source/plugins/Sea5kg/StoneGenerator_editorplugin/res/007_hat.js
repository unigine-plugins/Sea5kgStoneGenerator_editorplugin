var generatorName = "Hat";
var generatorId = 7;

function generate(expected_triangles, radius) {
    print(expected_triangles);
    print(radius);

    // Model.clear();
    
    var subdivisions = Math.round(Math.sqrt(expected_triangles / 10));
    if (subdivisions < 3) subdivisions = 3;
    
    // Choose hat style based on triangle count
    if (expected_triangles < 800) {
        createWizardHat(radius, subdivisions);
    } else if (expected_triangles < 2000) {
        createTopHat(radius, subdivisions);
    } else {
        createBaseballCap(radius, subdivisions);
    }
}

function createWizardHat(radius, subdivisions) {
    var brimRadius = radius * 1.2;
    var brimHeight = radius * 0.1;
    var coneHeight = radius * 2.5;
    
    // Create brim
    createCircularBrim(0, 0, brimRadius, brimHeight, subdivisions);
    
    // Create conical hat body
    createCone(0, brimHeight, radius * 0.8, coneHeight, subdivisions);
    
    // Add bent tip for classic wizard hat
    createBentTip(0, brimHeight + coneHeight, radius * 0.1, subdivisions);
}

function createTopHat(radius, subdivisions) {
    var brimRadius = radius * 1.5;
    var brimHeight = radius * 0.08;
    var cylinderHeight = radius * 1.2;
    var cylinderRadius = radius * 0.7;
    var topRadius = radius * 0.6;
    
    // Bottom brim
    createCircularBrim(0, 0, brimRadius, brimHeight, subdivisions);
    
    // Main cylinder
    createCylinder(0, brimHeight, cylinderRadius, cylinderHeight, subdivisions);
    
    // Top part
    createCircularLid(0, brimHeight + cylinderHeight, topRadius, radius * 0.05, subdivisions);
}

function createBaseballCap(radius, subdivisions) {
    var visorLength = radius * 1.0;
    var capHeight = radius * 0.8;
    var capRadius = radius * 0.9;
    
    // Create dome for head
    createDome(0, capHeight * 0.3, capRadius, capHeight, subdivisions);
    
    // Create visor
    createVisor(0, 0, visorLength, radius * 0.3, subdivisions);
    
    // Add button on top
    createButton(0, capHeight * 0.3 + capHeight, radius * 0.08, 4);
}

function createCircularBrim(centerX, centerY, brimRadius, brimHeight, subdivisions) {
    var topVertices = [];
    var bottomVertices = [];
    
    // Create vertices for top and bottom of brim
    for (var i = 0; i <= subdivisions; i++) {
        var angle = 2 * Math.PI * i / subdivisions;
        var x = centerX + Math.cos(angle) * brimRadius;
        var z = Math.sin(angle) * brimRadius;
        
        // Top surface vertices
        var topPoint = Model.addPoint(x, centerY + brimHeight, z);
        topVertices.push(topPoint);
        
        // Bottom surface vertices
        var bottomPoint = Model.addPoint(x, centerY, z);
        bottomVertices.push(bottomPoint);
    }
    
    // Create top surface
    for (var i = 1; i < subdivisions - 1; i++) {
        Model.addTriangle(topVertices[0], topVertices[i], topVertices[i + 1]);
    }
    
    // Create side triangles
    for (var i = 0; i < subdivisions; i++) {
        var next = (i + 1) % subdivisions;
        Model.addTriangle(topVertices[i], bottomVertices[next], bottomVertices[i]);
        Model.addTriangle(topVertices[i], topVertices[next], bottomVertices[next]);
    }
}

function createCone(centerX, baseY, baseRadius, height, subdivisions) {
    var baseVertices = [];
    var midVertices = [];
    
    // Create base vertices
    for (var i = 0; i < subdivisions; i++) {
        var angle = 2 * Math.PI * i / subdivisions;
        var x = centerX + Math.cos(angle) * baseRadius;
        var z = Math.sin(angle) * baseRadius;
        var basePoint = Model.addPoint(x, baseY, z);
        baseVertices.push(basePoint);
    }
    
    // Create mid-level vertices for smoother cone
    var midRadius = baseRadius * 0.3;
    for (var i = 0; i < subdivisions; i++) {
        var angle = 2 * Math.PI * i / subdivisions;
        var x = centerX + Math.cos(angle) * midRadius;
        var z = Math.sin(angle) * midRadius;
        var midPoint = Model.addPoint(x, baseY + height * 0.7, z);
        midVertices.push(midPoint);
    }
    
    // Create apex
    var apex = Model.addPoint(centerX, baseY + height, 0);
    
    // Create triangles from base to mid
    for (var i = 0; i < subdivisions; i++) {
        var next = (i + 1) % subdivisions;
        Model.addTriangle(baseVertices[i], baseVertices[next], midVertices[next]);
        Model.addTriangle(baseVertices[i], midVertices[next], midVertices[i]);
    }
    
    // Create triangles from mid to apex
    for (var i = 0; i < subdivisions; i++) {
        var next = (i + 1) % subdivisions;
        Model.addTriangle(midVertices[i], midVertices[next], apex);
    }
    
    // Create base cap
    for (var i = 1; i < subdivisions - 1; i++) {
        Model.addTriangle(baseVertices[0], baseVertices[i], baseVertices[i + 1]);
    }
}

function createCylinder(centerX, baseY, radius, height, subdivisions) {
    var bottomVertices = [];
    var topVertices = [];
    
    // Create bottom and top circles
    for (var i = 0; i <= subdivisions; i++) {
        var angle = 2 * Math.PI * i / subdivisions;
        var x = centerX + Math.cos(angle) * radius;
        var z = Math.sin(angle) * radius;
        
        var bottomPoint = Model.addPoint(x, baseY, z);
        var topPoint = Model.addPoint(x, baseY + height, z);
        
        bottomVertices.push(bottomPoint);
        topVertices.push(topPoint);
    }
    
    // Create side faces
    for (var i = 0; i < subdivisions; i++) {
        var next = (i + 1) % subdivisions;
        Model.addTriangle(bottomVertices[i], bottomVertices[next], topVertices[next]);
        Model.addTriangle(bottomVertices[i], topVertices[next], topVertices[i]);
    }
    
    // Create top cap
    for (var i = 1; i < subdivisions - 1; i++) {
        Model.addTriangle(topVertices[0], topVertices[i], topVertices[i + 1]);
    }
    
    // Create bottom cap
    for (var i = 1; i < subdivisions - 1; i++) {
        Model.addTriangle(bottomVertices[0], bottomVertices[i + 1], bottomVertices[i]);
    }
}

function createDome(centerX, baseY, radius, height, subdivisions) {
    var vertices = [];
    
    // Create hemisphere vertices
    for (var i = 0; i <= subdivisions; i++) {
        var row = [];
        var theta = Math.PI * 0.5 * i / subdivisions; // Only top half sphere
        
        for (var j = 0; j <= subdivisions; j++) {
            var phi = 2 * Math.PI * j / subdivisions;
            
            var x = centerX + Math.sin(theta) * Math.cos(phi) * radius;
            var y = baseY + Math.cos(theta) * height;
            var z = Math.sin(theta) * Math.sin(phi) * radius;
            
            var point = Model.addPoint(x, y, z);
            row.push(point);
        }
        vertices.push(row);
    }
    
    // Create triangles
    for (var i = 0; i < subdivisions; i++) {
        for (var j = 0; j < subdivisions; j++) {
            var p1 = vertices[i][j];
            var p2 = vertices[i][j + 1];
            var p3 = vertices[i + 1][j];
            var p4 = vertices[i + 1][j + 1];
            
            Model.addTriangle(p1, p2, p4);
            Model.addTriangle(p1, p4, p3);
        }
    }
    
    // Create base rim
    var baseVertices = vertices[subdivisions];
    for (var j = 1; j < subdivisions - 1; j++) {
        Model.addTriangle(baseVertices[0], baseVertices[j], baseVertices[j + 1]);
    }
}

function createVisor(centerX, centerY, length, width, subdivisions) {
    var vertices = [];
    
    // Create curved visor shape
    for (var i = 0; i <= subdivisions; i++) {
        var t = i / subdivisions;
        var curve = Math.sin(t * Math.PI) * width;
        var x = centerX - length * t;
        
        for (var j = 0; j <= subdivisions; j++) {
            var angle = Math.PI * 0.5 * (j / subdivisions - 0.5);
            var y = centerY + Math.sin(angle) * curve;
            var z = Math.cos(angle) * curve;
            
            var point = Model.addPoint(x, y, z);
            if (!vertices[i]) vertices[i] = [];
            vertices[i].push(point);
        }
    }
    
    // Create visor triangles
    for (var i = 0; i < subdivisions; i++) {
        for (var j = 0; j < subdivisions; j++) {
            var p1 = vertices[i][j];
            var p2 = vertices[i][j + 1];
            var p3 = vertices[i + 1][j];
            var p4 = vertices[i + 1][j + 1];
            
            Model.addTriangle(p1, p2, p4);
            Model.addTriangle(p1, p4, p3);
        }
    }
}

function createBentTip(centerX, baseY, radius, subdivisions) {
    var vertices = [];
    var bendAngle = Math.PI * 0.3; // 30 degree bend
    
    // Create bent tube for wizard hat tip
    for (var i = 0; i <= subdivisions; i++) {
        var t = i / subdivisions;
        var currentAngle = bendAngle * t;
        var x = centerX + Math.sin(currentAngle) * radius * 2;
        var y = baseY + Math.cos(currentAngle) * radius * 3;
        
        for (var j = 0; j < subdivisions; j++) {
            var circleAngle = 2 * Math.PI * j / subdivisions;
            var circleX = Math.cos(circleAngle) * radius * (1 - t * 0.5);
            var circleZ = Math.sin(circleAngle) * radius * (1 - t * 0.5);
            
            // Rotate circle to follow bend
            var finalX = x + circleX * Math.cos(currentAngle);
            var finalY = y + circleX * Math.sin(currentAngle);
            var finalZ = circleZ;
            
            var point = Model.addPoint(finalX, finalY, finalZ);
            if (!vertices[i]) vertices[i] = [];
            vertices[i].push(point);
        }
    }
    
    // Create triangles for bent tip
    for (var i = 0; i < subdivisions; i++) {
        for (var j = 0; j < subdivisions; j++) {
            var nextJ = (j + 1) % subdivisions;
            var p1 = vertices[i][j];
            var p2 = vertices[i][nextJ];
            var p3 = vertices[i + 1][j];
            var p4 = vertices[i + 1][nextJ];
            
            Model.addTriangle(p1, p2, p4);
            Model.addTriangle(p1, p4, p3);
        }
    }
}

function createCircularLid(centerX, centerY, radius, thickness, subdivisions) {
    var topVertices = [];
    var bottomVertices = [];
    
    // Create top and bottom vertices
    for (var i = 0; i <= subdivisions; i++) {
        var angle = 2 * Math.PI * i / subdivisions;
        var x = centerX + Math.cos(angle) * radius;
        var z = Math.sin(angle) * radius;
        
        var topPoint = Model.addPoint(x, centerY + thickness, z);
        var bottomPoint = Model.addPoint(x, centerY, z);
        
        topVertices.push(topPoint);
        bottomVertices.push(bottomPoint);
    }
    
    // Create top surface
    for (var i = 1; i < subdivisions - 1; i++) {
        Model.addTriangle(topVertices[0], topVertices[i], topVertices[i + 1]);
    }
    
    // Create side
    for (var i = 0; i < subdivisions; i++) {
        var next = (i + 1) % subdivisions;
        Model.addTriangle(topVertices[i], bottomVertices[next], bottomVertices[i]);
        Model.addTriangle(topVertices[i], topVertices[next], bottomVertices[next]);
    }
    
    // Create bottom surface
    for (var i = 1; i < subdivisions - 1; i++) {
        Model.addTriangle(bottomVertices[0], bottomVertices[i + 1], bottomVertices[i]);
    }
}

function createButton(centerX, centerY, radius, sides) {
    var vertices = [];
    
    // Create button vertices
    for (var i = 0; i < sides; i++) {
        var angle = 2 * Math.PI * i / sides;
        var x = centerX + Math.cos(angle) * radius;
        var z = Math.sin(angle) * radius;
        var point = Model.addPoint(x, centerY, z);
        vertices.push(point);
    }
    
    // Create top point (domed button)
    var top = Model.addPoint(centerX, centerY + radius * 0.3, 0);
    
    // Create side triangles
    for (var i = 0; i < sides; i++) {
        var next = (i + 1) % sides;
        Model.addTriangle(vertices[i], vertices[next], top);
    }
    
    // Create bottom face
    for (var i = 1; i < sides - 1; i++) {
        Model.addTriangle(vertices[0], vertices[i], vertices[i + 1]);
    }
}