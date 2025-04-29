#pragma once

#include "Color.hpp"
#include "RasTerX/include/Vector3.hpp"

class Light
{
private:
	Color ambient;
	Color diffuse;
	Color specular;
	float shine;

public:
	Light();
	Light(Color ambient, Color diffuse, Color specular, float shine);

	virtual ~Light() = default;

	Color GetAmbient() const;
	Color GetDiffuse() const;
	Color GetSpecular() const;
	float GetShine() const;
};

