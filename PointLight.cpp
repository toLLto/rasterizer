#include "PointLight.hpp"

PointLight::PointLight() : Light()
{
	position = rtx::Vector3::Zero();
}

PointLight::PointLight(Color ambient, Color diffuse, Color specular, float shine, rtx::Vector3 position) 
	: Light(ambient, diffuse, specular, shine), position(position)
{
}

rtx::Vector3 PointLight::GetPosition()
{
	return position;
}
