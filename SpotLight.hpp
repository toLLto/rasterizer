#pragma once

#include "Light.hpp"

class SpotLight : public Light
{
private:
	rtx::Vector3 position;
	rtx::Vector3 direction;
	float cutOff;

public:
	SpotLight();
	SpotLight(Color ambient, Color diffuse, Color specular, float shine, rtx::Vector3 position, rtx::Vector3 direction, const float cutOff);

	rtx::Vector3 GetPosition();
	rtx::Vector3 GetDirection();
	float GetCutOff();
};

