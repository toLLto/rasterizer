#include "Torus.hpp"
#include "RasTerX/include/MathUtils.hpp"

Torus::Torus(const float outerRadius, const float innerRadius, const int outerSegments, const int innerSegments)
{
	float innerStep = TAU / innerSegments;
	float outerStep = TAU / outerSegments;

	for (int i = 0; i < innerSegments; ++i)
	{
		for (int j = 0; j < outerSegments; ++j)
		{
			float innerAngle1 = i * innerStep;
			float innerAngle2 = (i + 1) * innerStep;
			float outerAngle1 = j * outerStep;
			float outerAngle2 = (j + 1) * outerStep;

			rtx::Vector3 point1 = TorusPoint(innerRadius, outerRadius, innerAngle1, outerAngle1);
			Vertex vertex1(point1, CalculateNormal(point1, innerRadius, outerRadius));

			rtx::Vector3 point2 = TorusPoint(innerRadius, outerRadius, innerAngle1, outerAngle2);
			Vertex vertex2(point2, CalculateNormal(point2, innerRadius, outerRadius));

			rtx::Vector3 point3 = TorusPoint(innerRadius, outerRadius, innerAngle2, outerAngle2);
			Vertex vertex3(point3, CalculateNormal(point3, innerRadius, outerRadius));

			rtx::Vector3 point4 = TorusPoint(innerRadius, outerRadius, innerAngle2, outerAngle1);
			Vertex vertex4(point4, CalculateNormal(point4, innerRadius, outerRadius));

			VTriangle triangle1(vertex2, vertex1, vertex3);
			VTriangle triangle2(vertex3, vertex1, vertex4);

			tris.emplace_back(triangle1);
			tris.emplace_back(triangle2);
		}
	}
}

rtx::Vector3 Torus::TorusPoint(const float outerRadius, const float innerRadius, const float outerAngle, const float innerAngle)
{
	return rtx::Vector3(
		(innerRadius + outerRadius * std::cos(outerAngle)) * std::cos(innerAngle),
		(innerRadius + outerRadius * std::cos(outerAngle)) * std::sin(innerAngle),
		outerRadius * std::sin(outerAngle)
	);
}

rtx::Vector3 Torus::CalculateNormal(const rtx::Vector3& point, const float outerRadius, const float innerRadius)
{
	float normal = std::sqrt(point.x * point.x + point.y * point.y);

	return rtx::Vector3(
		point.x / normal,
		point.y / normal,
		point.z / outerRadius
	);
}
