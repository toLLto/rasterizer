#pragma once

#include "Mesh.hpp"
#include "VTriangle.hpp"

class Torus : public Mesh
{
public:
	// majorRadius = distance from center of torus to center of tube (R)
	// minorRadius = radius of the tube itself (r)
	Torus(const float majorRadius, const float minorRadius, const int majorSegments, const int minorSegments);

private:
	// R = major radius (distance from center of torus to center of tube)
	// r = minor radius (radius of the tube)
	// phi = angle around the tube cross-section
	// theta = angle around the torus center

	rtx::Vector3 TorusPoint(const float R, const float r, const float phi, const float theta);

	rtx::Vector3 CalculateNormal(const rtx::Vector3& point, const float R, const float r);

	rtx::Vector2 TexCoords(float majorAngle, float minorAngle, int texWidth, int texHeight);
};