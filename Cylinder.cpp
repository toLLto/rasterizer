#include "Cylinder.hpp"
#include "RasTerX/include/MathUtils.hpp"

Cylinder::Cylinder(const float radius, const float height, const int radialSegments, const int heightSegments, const float distribution)
{
	float step = 360.f / distribution * HALF_PI;
	rtx::Vector3 heightVector(0.f, height, 0.f);

	for (float i = 0.f; i < TAU; i += step)
	{
		rtx::Vector3 baseCirclePoint1 = Mesh::CirclePoint(i, radius);
		rtx::Vector3 baseCirclePoint2 = Mesh::CirclePoint(i + step, radius);

		rtx::Vector3 topCirclePoint1 = baseCirclePoint1 + heightVector;
		rtx::Vector3 topCirclePoint2 = baseCirclePoint2 + heightVector;

		rtx::Vector3 sideNormal1 = rtx::Vector3(baseCirclePoint1.x, 0.f, baseCirclePoint1.z).Normal();
		rtx::Vector3 sideNormal2 = rtx::Vector3(baseCirclePoint2.x, 0.f, baseCirclePoint2.z).Normal();


		// Wall square (Two tris)
		Vertex sideVertA(baseCirclePoint2, sideNormal2, WHITE);
		Vertex sideVertB(topCirclePoint2, sideNormal2, WHITE);
		Vertex sideVertC(baseCirclePoint1, sideNormal1, WHITE);
		Vertex sideVertD(topCirclePoint1, sideNormal1, WHITE);

		VTriangle sideTriangle1(
			sideVertB, sideVertA, sideVertC,
			TexCoords(sideVertB.GetPosition().x, sideVertB.GetPosition().y, sideVertB.GetPosition().z, height),
			TexCoords(sideVertA.GetPosition().x, sideVertA.GetPosition().y, sideVertA.GetPosition().z, height),
			TexCoords(sideVertC.GetPosition().x, sideVertC.GetPosition().y, sideVertC.GetPosition().z, height)
		);
		VTriangle sideTriangle2(
			sideVertB, sideVertC, sideVertD,
			TexCoords(sideVertB.GetPosition().x, sideVertB.GetPosition().y, sideVertB.GetPosition().z, height),
			TexCoords(sideVertC.GetPosition().x, sideVertC.GetPosition().y, sideVertC.GetPosition().z, height),
			TexCoords(sideVertD.GetPosition().x, sideVertD.GetPosition().y, sideVertD.GetPosition().z, height)
		);

		tris.emplace_back(sideTriangle1);
		tris.emplace_back(sideTriangle2);

		// Base
		rtx::Vector3 down = rtx::Vector3::Up() * -1;
		Vertex baseVertA(baseCirclePoint1, down, WHITE);
		Vertex baseVertB(rtx::Vector3::Zero(), down, WHITE);
		Vertex baseVertC(baseCirclePoint2, down, WHITE);
		VTriangle baseTriangle(baseVertA, baseVertB, baseVertC,
			TexCoords(baseVertA.GetPosition().x, baseVertA.GetPosition().y, baseVertA.GetPosition().z, height),
			TexCoords(baseVertB.GetPosition().x, baseVertB.GetPosition().y, baseVertB.GetPosition().z, height),
			TexCoords(baseVertC.GetPosition().x, baseVertC.GetPosition().y, baseVertC.GetPosition().z, height)
		);
		tris.emplace_back(baseTriangle);

		// Top
		Vertex topVertA(topCirclePoint1, rtx::Vector3::Up(), WHITE);
		Vertex topVertB(rtx::Vector3(0.f, height, 0.f), rtx::Vector3::Up(), WHITE);
		Vertex topVertC(topCirclePoint2, rtx::Vector3::Up(), WHITE);
		VTriangle topTriangle(topVertA, topVertB, topVertC,
			TexCoords(topVertA.GetPosition().x, topVertA.GetPosition().y, topVertA.GetPosition().z, height),
			TexCoords(topVertB.GetPosition().x, topVertB.GetPosition().y, topVertB.GetPosition().z, height),
			TexCoords(topVertC.GetPosition().x, topVertC.GetPosition().y, topVertC.GetPosition().z, height)
		);
		tris.emplace_back(topTriangle);
	}
}

rtx::Vector2 Cylinder::TexCoords(float x, float y, float z, float height)
{
	float phi = atan2f(z, x);
	float u = phi / (2 * PI) + 0.5f;
	float v = (y / height) + 0.5f;

	return rtx::Vector2(u, v);
}
