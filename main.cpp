#include <iostream>
#include "Buffer.hpp"
#include "Rasterizer.hpp"
#include "Color.hpp"
#include "RasTerX/include/Matrix4.hpp"
#include "VertexProcessor.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "Torus.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "DirectionalLight.hpp"
#include "TGA.hpp"

using namespace std;

const unsigned int WIDTH = 512;
const unsigned int HEIGHT = 512;

const float fov = 120.f;
const float aspect = 1.f;

int main() 
{
    Buffer buffer(WIDTH, HEIGHT);

    Buffer texture1(WIDTH, HEIGHT);
    Buffer texture2(WIDTH, HEIGHT);
    unsigned short width = 0;
    unsigned short height = 0;

    TGA::Load("tex1.tga", texture1.GetDirColorBuffer(), width, height);
    TGA::Load("tex2.tga", texture2.GetDirColorBuffer(), width, height);

    Rasterizer rasterizer(WIDTH, HEIGHT, fov, aspect);

    std::vector<Renderable> renderables;

    Cone cone(0.4f, 2.f, 12);
    rtx::Matrix4 coneModel;
    coneModel.LoadIdentity();
    coneModel = coneModel 
        * VertexProcessor::Translate(rtx::Vector3(40.f, 0.f, 0.f))
        * VertexProcessor::Rotate(-15.f, rtx::Vector3::Forward())
        * VertexProcessor::Rotate(60.f, rtx::Vector3::Right());
    renderables.emplace_back(cone, texture2, coneModel, true, false);

    Cylinder cylinder(0.5, 1.5f, 0, 0, 24);
    rtx::Matrix4 cylinderModel;
    cylinderModel.LoadIdentity();
    cylinderModel = cylinderModel * VertexProcessor::Translate(rtx::Vector3(10.f, -30.f, 0.f));
    renderables.emplace_back(cylinder, texture2, cylinderModel, false, false);

    Torus torus(0.4f, 0.3f, 12, 10);
    rtx::Matrix4 torusModel;
    torusModel.LoadIdentity();
    torusModel = torusModel 
        * VertexProcessor::Translate(rtx::Vector3(-25.f, 25.f, 0.f))
        * VertexProcessor::Rotate(-60.f, rtx::Vector3::Forward())
        * VertexProcessor::Rotate(-30.f, rtx::Vector3::Right());
    renderables.emplace_back(torus, texture1, torusModel, true, false);

    Torus torus2(0.4f, 0.3f, 12, 10);
    rtx::Matrix4 torusModel2;
    torusModel2.LoadIdentity();
    torusModel2 = torusModel2
        * VertexProcessor::Translate(rtx::Vector3(-25.f, -25.f, 0.f))
        * VertexProcessor::Rotate(60.f, rtx::Vector3::Forward())
        * VertexProcessor::Rotate(30.f, rtx::Vector3::Right());
    renderables.emplace_back(torus2, texture1, torusModel2, false, true);

    std::vector<std::shared_ptr<Light>> lights = 
    {
        std::make_shared<PointLight>(PointLight(
            Color(0.3f, 0.3f, 0.3f),
            Color(1.f, 1.f, 1.f),
            Color(0.7f, 0.7f, 0.7f),
            32.f,
            rtx::Vector3(0.f, 0.f, 8.f)
        )),

        /*std::make_shared<SpotLight>(SpotLight(
            Color(0.2f, 0.2f, 0.2f),
            Color(0.8f, 0.8f, 0.8f),
            Color(0.1f, 0.1f, 0.1f),
            0.f,
            rtx::Vector3(0.f, 0.5f, 0.f),
            -rtx::Vector3::Up(),
            50.f
        )),*/

        std::make_shared<DirectionalLight>(DirectionalLight())
    };

    rasterizer.Render(renderables, lights, BLACK);

    return 0;
}