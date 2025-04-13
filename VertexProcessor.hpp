#pragma once
#include "RasTerX/include/Matrix4.hpp"
#include "RasTerX/include/Vector3.hpp"

class VertexProcessor
{
private:
	rtx::Matrix4 objectToWorld;
	rtx::Matrix4 worldToView;
	rtx::Matrix4 viewToProjection;

public:
	static rtx::Matrix4 SetPerspective(const float fov, const float aspect, const float near, const float far);
	static rtx::Matrix4 SetLookAt(const rtx::Vector3& eye, const rtx::Vector3& center, const rtx::Vector3& up);
};