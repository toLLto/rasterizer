#include <iostream>
#include "Buffer.hpp"
#include "Rasterizer.hpp"

using namespace std;

const unsigned int WIDTH = 256;
const unsigned int HEIGHT = 256;

const unsigned int BLACK = 0xFF000000;
const unsigned int WHITE = 0xFFFFFFFF;
const unsigned int RED = 0xFFFF0000;
const unsigned int GREEN = 0xFF00FF00;
const unsigned int BLUE = 0xFF0000FF;
const unsigned int YELLOW = 0xFFFFFF00;
const unsigned int MAGENTA = 0xFFFF00FF;
const unsigned int CYAN = 0xFF00FFFF;

int main() 
{
    Rasterizer::Buffer buffer(WIDTH, HEIGHT);

    Rasterizer::Rasterizer rasterizer(WIDTH, HEIGHT);

    Triangle triangle(
        Vector3(0.f, 0.5f, 0.f),
        Vector3(0.6f, -0.5f, 0.f),
        Vector3(-0.6f, -0.5f, 0.f)
    );

    rasterizer.Render(triangle, RED, BLACK);

    return 0;
}