#include <iostream>
#include "Buffer.hpp"
#include "Rasterizer.hpp"

using namespace std;

const unsigned int WIDTH = 256;
const unsigned int HEIGHT = 256;

int main() 
{
    Rasterizer::Buffer buffer(WIDTH, HEIGHT);

    Rasterizer::Rasterizer rasterizer(WIDTH, HEIGHT);

    Triangle triangle(
        Vector3(0.f, -0.4f, 0.f),
        Vector3(-0.8f, 0.2f, 0.f),
        Vector3(0.3f, 0.9f, 0.f)
    );

    rasterizer.Render(triangle, 0xFFFF0000, 0xFF000000);

    return 0;
}