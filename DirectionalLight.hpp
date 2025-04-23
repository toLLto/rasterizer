#pragma once

#include "Light.hpp"

class DirectionalLight : public Light
{
private:
	rtx::Vector3 direction;

public:
	DirectionalLight();
	DirectionalLight(Color ambient, Color diffuse, Color specular, float shine, rtx::Vector3 direction);

	rtx::Vector3 GetDirection();
};

