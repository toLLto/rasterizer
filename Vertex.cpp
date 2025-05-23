#include "Vertex.hpp"

Vertex::Vertex(const rtx::Vector3& position, const rtx::Vector3& normal, Color color)
	: position(position), normal(normal), color(color)
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

Color Vertex::GetColor() const
{
	return color;
}

void Vertex::SetPosition(const rtx::Vector3& v)
{
	position = v;
}

void Vertex::SetNormal(const rtx::Vector3& v)
{
	normal = v;
}

void Vertex::SetColor(const Color c)
{
	color = c;
}
