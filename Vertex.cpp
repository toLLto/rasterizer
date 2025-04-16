#include "Vertex.hpp"

Vertex::Vertex(const rtx::Vector3& position, const rtx::Vector3& normal) 
	: position(position), normal(normal)
{
}

rtx::Vector3 Vertex::GetPosition()
{
	return position;
}

rtx::Vector3 Vertex::GetNormal()
{
	return normal;
}

void Vertex::SetPosition(const rtx::Vector3& v)
{
	position = v;
}

void Vertex::SetNormal(const rtx::Vector3& v)
{
	normal = v;
}
