#include "Torus.hpp"
#include "RasTerX/include/MathUtils.hpp"

Torus::Torus(const float majorRadius, const float minorRadius, const int majorSegments, const int minorSegments)
{
    float thetaStep = TAU / majorSegments;  // Step around the main circle of the torus
    float phiStep = TAU / minorSegments;    // Step around the tube cross-section

    for (int i = 0; i < minorSegments; ++i)
    {
        for (int j = 0; j < majorSegments; ++j)
        {
            float phi1 = i * phiStep;       // Current angle around tube cross-section
            float phi2 = (i + 1) * phiStep; // Next angle around tube cross-section
            float theta1 = j * thetaStep;   // Current angle around torus
            float theta2 = (j + 1) * thetaStep; // Next angle around torus

            // Calculate the four corners of our quad
            rtx::Vector3 point1 = TorusPoint(majorRadius, minorRadius, phi1, theta1);
            Vertex vertex1(point1, CalculateNormal(point1, majorRadius, minorRadius), CYAN);

            rtx::Vector3 point2 = TorusPoint(majorRadius, minorRadius, phi1, theta2);
            Vertex vertex2(point2, CalculateNormal(point2, majorRadius, minorRadius), CYAN);

            rtx::Vector3 point3 = TorusPoint(majorRadius, minorRadius, phi2, theta2);
            Vertex vertex3(point3, CalculateNormal(point3, majorRadius, minorRadius), CYAN);

            rtx::Vector3 point4 = TorusPoint(majorRadius, minorRadius, phi2, theta1);
            Vertex vertex4(point4, CalculateNormal(point4, majorRadius, minorRadius), CYAN);

            // Create two triangles from the quad
            VTriangle triangle1(vertex2, vertex1, vertex3);
            VTriangle triangle2(vertex3, vertex1, vertex4);

            tris.emplace_back(triangle1);
            tris.emplace_back(triangle2);
        }
    }
}

rtx::Vector3 Torus::TorusPoint(const float R, const float r, const float phi, const float theta)
{
    // R = major radius (distance from center of torus to center of tube)
    // r = minor radius (radius of the tube)
    // phi = angle around the tube cross-section
    // theta = angle around the torus center

    return rtx::Vector3(
        (R + r * std::cos(phi)) * std::cos(theta),
        (R + r * std::cos(phi)) * std::sin(theta),
        r * std::sin(phi)
    );
}

rtx::Vector3 Torus::CalculateNormal(const rtx::Vector3& point, const float R, const float r)
{
    // For a torus, the normal at a point can be calculated by finding the center
    // of the circular cross-section that contains the point

    // Calculate the projection of the point onto the xy-plane
    rtx::Vector3 toCenter(point.x, point.y, 0);
    float centerDist = toCenter.Length();

    // Handle edge case - should not happen with a valid torus
    if (centerDist < 1e-6f) {
        return rtx::Vector3(0, 0, point.z > 0 ? 1 : -1);
    }

    // Direction from origin to the projection
    toCenter = toCenter * (1.0f / centerDist);

    // Calculate the center of the circular cross-section
    rtx::Vector3 circleCenter = toCenter * R;

    // The normal is the direction from circle center to the point
    rtx::Vector3 normal = point - circleCenter;

    // Return normalized vector
    return normal.Normal();
}