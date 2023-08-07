#pragma once
#include <UnigineMaterial.h>
#include <UnigineComponentSystem.h>

#include "StoneGeneratorConfig.h"

class StoneGeneratorDataComponent: public Unigine::ComponentBase {
public:
    // methods
    COMPONENT(StoneGeneratorDataComponent, Unigine::ComponentBase);
    COMPONENT_INIT(init);
    COMPONENT_UPDATE(update);

    // property name
    PROP_NAME("stone_generator_data_component");

    // parameters
    // int m_nBasicGeometry;
    // PROP_PARAM(Int, min_spawn_delay, 1.0f);
    PROP_PARAM(Switch, basic_geometry, 0, "Sphere,Cube", "Basic Geometry", "", "Parameters of stone generator");
    PROP_PARAM(Int, expected_triangles, 500.0f, "Expected Triangles", "Approximate number of triangles", "Parameters of stone generator", "max=15000;min=100");
    PROP_PARAM(Float, radius, 2.0f, "Radius", "Max radius of object", "Parameters of stone generator", "max=4.0;min=0.1");

        // int m_nPointsOfAttraction;
        // float m_nStrongOfAttraction;
        // float m_nSurfaceDistortion;
        // float m_nScaleX;
        // float m_nScaleY;
        // float m_nScaleZ;

    PROP_PARAM(Node, spawn_node);
    PROP_PARAM(Float, min_spawn_delay, 1.0f);
    PROP_PARAM(Float, max_spawn_delay, 4.0f);

protected:
    // world main loop
    void init();
    void update();

private:
    float start_turn_speed = 0;
    float color_offset = 0;
    float time_to_spawn = 0;
    // Unigine::MaterialPtr material;

    // converter from HSV to RGB color model
    Unigine::Math::vec3 hsv2rgb(float h, float s, float v);
};
