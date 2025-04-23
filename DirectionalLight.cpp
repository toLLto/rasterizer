#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() : Light()
{
	direction = rtx::Vector3(0.f, -1.f, 0.f).Normal();
}

DirectionalLight::DirectionalLight(Color ambient, Color diffuse, Color specular, float shine, rtx::Vector3 direction) 
	: Light(ambient, diffuse, specular, shine), direction(direction)
{
}

rtx::Vector3 DirectionalLight::GetDirection()
{
	return direction;
}
