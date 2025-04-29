#include "Cone.hpp"
#include "RasTerX/include/MathUtils.hpp"
#include <cmath>

Cone::Cone(const float radius, const float height, const int distribution)
{
	float step = 360.f / distribution * HALF_PI;

	for (float i = 0.f; i < TAU; i += step)
	{
		rtx::Vector3 circlePoint1 = Mesh::CirclePoint(i, radius);
		rtx::Vector3 circlePoint2 = Mesh::CirclePoint(i + step, radius);

		rtx::Vector3 sideNormal = (circlePoint2 - circlePoint1).Cross(rtx::Vector3(0.f, -height, 0.f)).Normal();

		Vertex sideVertA(circlePoint2, sideNormal, WHITE);
		Vertex sideVertB(rtx::Vector3(0.f, height, 0.f), rtx::Vector3::Up(), WHITE);
		Vertex sideVertC(circlePoint1, sideNormal, WHITE);
		VTriangle sideTriangle(
			sideVertA, sideVertB, sideVertC,
			TexCoords(sideVertA.GetPosition().x, sideVertA.GetPosition().y, sideVertA.GetPosition().z, height),
			TexCoords(sideVertB.GetPosition().x, sideVertB.GetPosition().y, sideVertB.GetPosition().z, height),
			TexCoords(sideVertC.GetPosition().x, sideVertC.GetPosition().y, sideVertC.GetPosition().z, height)
		);
		tris.emplace_back(sideTriangle);

		Vertex baseVertA(circlePoint1, sideNormal, WHITE);
		Vertex baseVertB(rtx::Vector3::Zero(), -rtx::Vector3::Up(), WHITE);
		Vertex baseVertC(circlePoint2, sideNormal, WHITE);
		VTriangle baseTriangle(
			baseVertA, baseVertB, baseVertC,
			TexCoords(baseVertA.GetPosition().x, baseVertA.GetPosition().y, baseVertA.GetPosition().z, height),
			TexCoords(baseVertB.GetPosition().x, baseVertB.GetPosition().y, baseVertB.GetPosition().z, height),
			TexCoords(baseVertC.GetPosition().x, baseVertC.GetPosition().y, baseVertC.GetPosition().z, height)
		);
		tris.emplace_back(baseTriangle);
	}

	verts.push_back({ rtx::Vector3(0.f, height, 0.f), -rtx::Vector3::Up(), WHITE });
}

rtx::Vector2 Cone::TexCoords(float x, float y, float z, float height)
{
	float phi = atan2f(z, x);
	float theta = acosf(y / sqrt(x * x + y * y + z * z));

	float u = phi / (2 * PI) + 0.5f;
	float v = theta / PI;	

	return rtx::Vector2(u, v);
}
