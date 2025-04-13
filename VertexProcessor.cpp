#include "VertexProcessor.hpp"
#include "RasTerX/include/MathUtils.hpp"

rtx::Matrix4 VertexProcessor::SetPerspective(float fov, float aspect, float near, float far)
{
	fov *= PI / 360.f;
	const float f = cos(fov) / sin(fov);

	return
	{
		rtx::Vector4(f / aspect, 0.f, 0.f, 0.f),
		rtx::Vector4(0.f, f, 0.f, 0.f),
		rtx::Vector4(0.f, 0.f, (far + near) / (near - far), -1.f),
		rtx::Vector4(0.f, 0.f, 2.f * far * near / (near - far), 0.f)
	};
}

rtx::Matrix4 VertexProcessor::SetLookAt(const rtx::Vector3& eye, const rtx::Vector3& center, const rtx::Vector3& up)
{
	rtx::Vector3 f = (center - eye).Normal();
	rtx::Vector3 s = rtx::Vector3::CrossProduct(f, up).Normal();
	rtx::Vector3 u = rtx::Vector3::CrossProduct(s, f).Normal();

	rtx::Matrix4 worldToView
	{
		rtx::Vector4(s.x, u.x, -f.x, 0.f),
		rtx::Vector4(s.y, u.y, -f.y, 0.f),
		rtx::Vector4(s.z, u.z, -f.z, 0.f),
		rtx::Vector4(0.f, 0.f, 0.f, 1.f)
	};

	return worldToView * Translate(rtx::Vector3(-eye.x, -eye.y, -eye.z));
}

rtx::Matrix4 VertexProcessor::Translate(const rtx::Vector3& vec)
{
	return 
	{
		rtx::Vector4(1.f, 0.f, 0.f, vec.x),
		rtx::Vector4(0.f, 1.f, 0.f, vec.y),
		rtx::Vector4(0.f, 0.f, 1.f, vec.z),
		rtx::Vector4(0.f, 0.f, 0.f, 1.f)
	};
}

rtx::Matrix4 VertexProcessor::Scale(const rtx::Vector3& vec)
{
	return
	{
		rtx::Vector4(vec.x, 0.f, 0.f, 0.f),
		rtx::Vector4(0.f, vec.y, 0.f, 0.f),
		rtx::Vector4(0.f, 0.f, vec.z, 0.f),
		rtx::Vector4(0.f, 0.f, 0.f, 1.f)
	};
}

rtx::Matrix4 VertexProcessor::Rotate(const float angle, const rtx::Vector3& vec)
{
	float sine = sin(angle * PI / 180.f);
	float cosine = cos(angle * PI / 180.f);
	rtx::Vector3 norm = vec.Normal();

	return
	{
		rtx::Vector4(norm.x * norm.x * (1.f - cosine) + cosine, norm.y * norm.x * (1.f - cosine) + norm.z * sine, norm.x * norm.z * (1.f - cosine) - norm.y * sine, 0.f),
		rtx::Vector4(norm.x * norm.y * (1.f - cosine) - norm.z * sine, norm.y * norm.y * (1.f - cosine) + cosine, norm.y * norm.z * (1.f - cosine) + norm.x * sine, 0.f),
		rtx::Vector4(norm.x * norm.z * (1.f - cosine) + norm.y * sine, norm.y * norm.z * (1.f - cosine) - norm.x * sine, norm.z * norm.z * (1 - cosine) + cosine, 0.f),
		rtx::Vector4(0.f, 0.f, 0.f, 1.f)
	};
}
