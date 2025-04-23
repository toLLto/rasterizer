#pragma once

#include "RasTerX/include/Vector3.hpp"
#include "Color.hpp"

class Vertex
{
private:
	rtx::Vector3 position;
	rtx::Vector3 normal;
	Color color;

public:
	Vertex() = default;
	Vertex(const rtx::Vector3& position, const rtx::Vector3& normal = rtx::Vector3::Up(), Color color = WHITE);

	rtx::Vector3 GetPosition();
	rtx::Vector3 GetNormal();
	Color GetColor();

	void SetPosition(const rtx::Vector3& v);
	void SetNormal(const rtx::Vector3& v);
	void SetColor(const Color c);
};