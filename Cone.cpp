#include "Cone.hpp"
#include "RasTerX/include/MathUtils.hpp"

Cone::Cone(const float radius, const float height, const int distribution)
{
	float step = 360.f / distribution * HALF_PI;

	for (float i = 0.f; i < TAU; i += step)
	{
		rtx::Vector3 circlePoint1 = Mesh::CirclePoint(i, radius);
		rtx::Vector3 circlePoint2 = Mesh::CirclePoint(i + step, radius);

		Vertex sideVertA(circlePoint2);
		Vertex sideVertB(rtx::Vector3(0.f, height, 0.f));
		Vertex sideVertC(circlePoint1);
		VTriangle sideTriangle(sideVertA, sideVertB, sideVertC);
		tris.emplace_back(sideTriangle);

		Vertex baseVertA(circlePoint1);
		Vertex baseVertB(rtx::Vector3::Zero());
		Vertex baseVertC(circlePoint2);
		VTriangle baseTriangle(baseVertA, baseVertB, baseVertC);
	}
}
