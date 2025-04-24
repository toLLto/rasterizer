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
		Vertex sideVertA(baseCirclePoint2, sideNormal2, YELLOW);
		Vertex sideVertB(topCirclePoint2, sideNormal2, YELLOW);
		Vertex sideVertC(baseCirclePoint1, sideNormal1, YELLOW);
		Vertex sideVertD(topCirclePoint1, sideNormal1, YELLOW);

		VTriangle sideTriangle1(sideVertB, sideVertA, sideVertC);
		VTriangle sideTriangle2(sideVertB, sideVertC, sideVertD);

		tris.emplace_back(sideTriangle1);
		tris.emplace_back(sideTriangle2);

		// Base
		rtx::Vector3 down = rtx::Vector3::Up() * -1;
		Vertex baseVertA(baseCirclePoint1, down, YELLOW);
		Vertex baseVertB(rtx::Vector3::Zero(), down, YELLOW);
		Vertex baseVertC(baseCirclePoint2, down, YELLOW);
		VTriangle baseTriangle(baseVertA, baseVertB, baseVertC);
		tris.emplace_back(baseTriangle);

		// Top
		Vertex topVertA(topCirclePoint1, rtx::Vector3::Up(), YELLOW);
		Vertex topVertB(rtx::Vector3(0.f, height, 0.f), rtx::Vector3::Up(), YELLOW);
		Vertex topVertC(topCirclePoint2, rtx::Vector3::Up(), YELLOW);
		VTriangle topTriangle(topVertA, topVertB, topVertC);
		tris.emplace_back(topTriangle);
	}
}
