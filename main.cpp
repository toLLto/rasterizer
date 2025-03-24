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

    rasterizer.Render(0xFFFF0000);

    return 0;
}