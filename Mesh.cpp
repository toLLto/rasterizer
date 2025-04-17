#include "Mesh.hpp"

std::vector<VTriangle> Mesh::GetTris()
{
	return tris;
}

rtx::Vector3 Mesh::CirclePoint(const float angle, const float radius, rtx::Vector3 center)
{
	return rtx::Vector3(radius * std::cos(angle) + center.x, center.y, radius * std::sin(angle) + center.z);
}
