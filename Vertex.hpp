#pragma once
#include "RasTerX/include/Vector3.hpp"

class Vertex
{
private:
	rtx::Vector3 position;
	rtx::Vector3 normal;

public:
	Vertex() = default;
	Vertex(const rtx::Vector3& position, const rtx::Vector3& normal = rtx::Vector3::Up());

	rtx::Vector3 GetPosition();
	rtx::Vector3 GetNormal();

	void SetPosition(const rtx::Vector3& v);
	void SetNormal(const rtx::Vector3& v);
};