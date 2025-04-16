#pragma once

#include "Mesh.hpp"
#include "VTriangle.hpp"

class Torus : public Mesh
{
public:
	Torus(const float outerRadius, const float innerRadius, const int outerSegments, const int innerSegments);

	rtx::Vector3 TorusPoint(const float outerRadius, const float innerRadius, const float outerAngle, const float innerAngle);

	rtx::Vector3 CalculateNormal(const rtx::Vector3& point, const float outerRadius, const float innerRadius);
};