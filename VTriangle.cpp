#include "VTriangle.hpp"

VTriangle::VTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	colors.push_back(v1.GetColor());
	colors.push_back(v2.GetColor());
	colors.push_back(v3.GetColor());

	indices.push_back(rtx::Vector3(0.f, 1.f, 2.f));
}

VTriangle::VTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3,
	Color c1, Color c2, Color c3)
{
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	colors.push_back(c1);
	colors.push_back(c2);
	colors.push_back(c3);

	indices.push_back(rtx::Vector3(0.f, 1.f, 2.f));
}
