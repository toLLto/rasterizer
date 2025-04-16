#pragma once

#include "Mesh.hpp"
#include "VTriangle.hpp"

class Cone : public Mesh
{
public:
	Cone(const float radius, const float height, const int distribution);
};