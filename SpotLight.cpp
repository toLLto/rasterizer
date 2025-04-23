#include "SpotLight.hpp"

SpotLight::SpotLight() : Light()
{
	position = rtx::Vector3::Zero();
	direction = rtx::Vector3(0.f, 01.f, 0.f);
	cutOff = 45.f;
}

SpotLight::SpotLight(Color ambient, Color diffuse, Color specular, float shine, rtx::Vector3 position, rtx::Vector3 direction, const float cutOff) 
	: Light(ambient, diffuse, specular, shine), position(position), direction(direction), cutOff(cutOff)
{
}

rtx::Vector3 SpotLight::GetPosition()
{
	return position;
}

rtx::Vector3 SpotLight::GetDirection()
{
	return direction;
}

float SpotLight::GetCutOff()
{
	return cutOff;
}
