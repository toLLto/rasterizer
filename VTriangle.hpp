#pragma once

#include "RasTerX/include/Vector3.hpp"
#include <vector>
#include "Vertex.hpp"
#include "Color.hpp"

class VTriangle
{
private:
	std::vector<Vertex> vertices;
	std::vector<rtx::Vector3> indices;
	std::vector<Color> colors;

public:
	VTriangle() = default;
	VTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
	VTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3,
		Color c1, Color c2, Color c3);

	Vertex GetVertexA() const { return vertices[0]; }
	Vertex GetVertexB() const { return vertices[1]; }
	Vertex GetVertexC() const { return vertices[2]; }

	Vertex& GetVertexARef() { return vertices[0]; }
	Vertex& GetVertexBRef() { return vertices[1]; }
	Vertex& GetVertexCRef() { return vertices[2]; }

	// Also add const versions if needed
	const Vertex& GetVertexARef() const { return vertices[0]; }
	const Vertex& GetVertexBRef() const { return vertices[1]; }
	const Vertex& GetVertexCRef() const { return vertices[2]; }
};
