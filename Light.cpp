#include "Light.hpp"

Light::Light()
{
	ambient = Color(0.4f, 0.4f, 0.4f);
	diffuse = Color(0.6f, 0.6f, 0.6f);
	specular = Color(0.1f, 0.1f, 0.1f);
	shine = 0.f;
}

Light::Light(Color ambient, Color diffuse, Color specular, float shine) 
	: ambient(ambient), diffuse(diffuse), specular(specular), shine(shine)
{
}

Color Light::GetAmbient()
{
	return ambient;
}

Color Light::GetDiffuse()
{
	return diffuse;
}

Color Light::GetSpecular()
{
	return specular;
}

float Light::GetShine()
{
	return shine;
}
