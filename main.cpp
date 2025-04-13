#include <iostream>
#include "Buffer.hpp"
#include "Rasterizer.hpp"
#include "Color.hpp"
#include "RasTerX/include/Matrix4.hpp"
#include "VertexProcessor.hpp"

using namespace std;

const unsigned int WIDTH = 256;
const unsigned int HEIGHT = 256;

const float fov = 120.f;
const float aspect = 1.f;

int main() 
{
    Buffer buffer(WIDTH, HEIGHT);

    Matrix4 model;
    model.LoadIdentity();
    model = model * VertexProcessor::Scale(rtx::Vector3(2.f, 2.f, 2.f));
    model = model * VertexProcessor::Rotate(-45.f, rtx::Vector3(0.f, 0.f, 1.f));
    model = model * VertexProcessor::Translate(rtx::Vector3(-10.f, 0.5f, 0.f));

    Rasterizer rasterizer(WIDTH, HEIGHT, fov, aspect);

    Triangle triangle1(
        Vector3(0.7f, 0.5f, 0.f),
        Vector3(1.3f, -0.5f, 0.f),
        Vector3(0.1f, -0.5f, 0.f)
    );

    Triangle triangle2(
        Vector3(-0.9f, 0.9f, 0.f),
        Vector3(0.8f, 0.75f, 0.f),
        Vector3(0.1f, 0.6f, 0.f)
    );

    Triangle triangle3(
        Vector3(0.1f, 0.5f, 0.3f),
        Vector3(1.3f, 0.5f, 0.3f),
        Vector3(0.7f, -0.5f, 0.3f)
    );

    Triangle triangle4(
        Vector3(-0.8f, 0.5f, 0.f),
        Vector3(-0.5f, 0.f, 0.f),
        Vector3(-0.8f, 0.f, 0.f)
    );

    Triangle triangle5(
        Vector3(-0.8f, 0.f, 0.f),
        Vector3(-0.5f, 0.f, 0.f),
        Vector3(-0.8f, -0.5f, 0.f)
    );

    Triangle triangle6(
        Vector3(-0.4f, -0.6f, 0.f),
        Vector3(0.f, -0.6f, 0.f),
        Vector3(-0.4f, -0.8f, 0.f)
    );

    Triangle triangle7(
        Vector3(-0.4f, -0.8f, 0.f),
        Vector3(0.f, -0.6f, 0.f),
        Vector3(0.f, -0.8f, 0.f)
    );

    rasterizer.Render({ triangle1, triangle2, triangle3, triangle4, triangle5, triangle6, triangle7 }, model, BLACK);

    return 0;
}