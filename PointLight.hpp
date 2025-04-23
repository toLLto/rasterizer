#pragma once

#include "Light.hpp"

class PointLight : public Light
{
private:
	rtx::Vector3 position;

public:
	PointLight();
	PointLight(Color ambient, Color diffuse, Color specular, float shine, rtx::Vector3 position);

	rtx::Vector3 GetPosition();
};

