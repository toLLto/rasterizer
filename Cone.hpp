#pragma once

#include "Mesh.hpp"
#include "VTriangle.hpp"
#include "RasTerX/include/Vector2.hpp"

class Cone : public Mesh
{
public:
	Cone(const float radius, const float height, const int distribution);

	rtx::Vector2 TexCoords(float x, float y, float z, float height);
};