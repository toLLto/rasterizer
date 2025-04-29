#include "Light.hpp"

Light::Light()
{
	ambient = Color(0.1f, 0.1f, 0.1f);
	diffuse = Color(0.8f, 0.8f, 0.8f);
	specular = Color(0.1f, 0.1f, 0.1f);
	shine = 0.f;
}

Light::Light(Color ambient, Color diffuse, Color specular, float shine) 
	: ambient(ambient), diffuse(diffuse), specular(specular), shine(shine)
{
}

Color Light::GetAmbient() const
{
	return ambient;
}

Color Light::GetDiffuse() const
{
	return diffuse;
}

Color Light::GetSpecular() const
{
	return specular;
}

float Light::GetShine() const
{
	return shine;
}
