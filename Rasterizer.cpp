#include "Rasterizer.hpp"
#include "RasTerX/include/MathUtils.hpp"
#include "TGA.hpp"
#include "Color.hpp"
#include "VertexProcessor.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"
#include "SpotLight.hpp"

Rasterizer::Rasterizer(unsigned int width, unsigned int height, float fov, float aspect, float near, float far)
	: buffer(width, height), fov(fov), aspect(aspect), near(near), far(far) 
{
}

void Rasterizer::Render(std::vector<Mesh>& meshes, const std::vector<rtx::Matrix4>& models, const std::vector<std::shared_ptr<Light>>& lights, unsigned int backgroundColor)
{
	buffer.SetBufferColorFill(backgroundColor);
	buffer.SetBufferDepthFill(FLT_MAX);

	for (int i = 0; i < meshes.size(); ++i)
	{
		RenderMesh(meshes[i], models[i], lights);
	}

	TGA::Save("miagk_8.tga", buffer.GetColorBuffer(), buffer.GetWidth(), buffer.GetHeight());
}

void Rasterizer::ClearBufferColor(unsigned int color)
{
	buffer.SetBufferColorFill(color);
}

void Rasterizer::ClearBufferDepth(float depth)
{
	buffer.SetBufferDepthFill(depth);
}

void Rasterizer::RenderMesh(Mesh mesh, const rtx::Matrix4& model, const std::vector<std::shared_ptr<Light>>& lights)
{
	for (VTriangle& tr : mesh.GetTris())
	{
		VTriangle vTr = tr;

		LightCalculation(vTr.GetVertexA(), lights);
		LightCalculation(vTr.GetVertexB(), lights);
		LightCalculation(vTr.GetVertexC(), lights);

		RenderTriangle(vTr, model, lights, RED);
	}
}

void Rasterizer::LightCalculation(Vertex& vert, const std::vector<std::shared_ptr<Light>>& lights)
{
	Vector3 objColor = Color(vert.GetColor()).ToVector();
	Vector3 camPos = rtx::Vector3::Zero();
	Vector3 outColor = rtx::Vector3::Zero();

	for (const auto& light : lights)
	{
		Vector3 amb;
		Vector3 diff;
		Vector3 spec;
		Vector3 lightDir;
		float atten = 1.f;

		Vector3 ambLight = Color(light->GetAmbient()).ToVector();
		Vector3 diffLight = Color(light->GetDiffuse()).ToVector();
		Vector3 specLight = Color(light->GetSpecular()).ToVector();
		const float shine = light->GetShine();

		if (auto pointLight = std::dynamic_pointer_cast<PointLight>(light))
		{
			Vector3 vertLight = vert.GetPosition() - pointLight->GetPosition();
			const float dist = vertLight.Length();
			lightDir = vertLight * (-1.f / dist);
			atten = 1.f / (1.f + 0.09f * dist + 0.032f * dist * dist);
		}
		else if (auto dirLight = std::dynamic_pointer_cast<DirectionalLight>(light))
		{
			lightDir = -(dirLight->GetDirection()).Normal();
		}
		else if (auto spotLight = std::dynamic_pointer_cast<SpotLight>(light))
		{
			Vector3 vertLight = vert.GetPosition() - spotLight->GetPosition();
			const float dist = vertLight.Length();
			lightDir = vertLight * (-1.f / dist);

			const float angle = lightDir.Dot(spotLight->GetDirection().Normal());
			const float cutOff = std::cos(spotLight->GetCutOff() * PI / 180.f);

			if (angle < cutOff)
				continue;

			const float spot = std::pow(std::max(angle, 0.f), 8.f);
			atten = spot / (1.f + 0.09f * dist + 0.032f * dist * dist);
		}

		amb = ambLight * objColor;

		const float d = std::max(vert.GetNormal().Dot(lightDir), 0.f);
		diff = diffLight * objColor * d;

		Vector3 viewDir = (camPos - vert.GetPosition()).Normal();
		Vector3 reflectDir = vert.GetNormal() * (2.f * vert.GetNormal().Dot(lightDir)) - lightDir;

		const float s = std::pow(std::max(viewDir.Dot(reflectDir), 0.f), shine);
		spec = specLight * s;

		outColor = outColor + (amb + diff + spec) * atten;
	}

	vert.SetColor(Color(MathUtils::Clamp(outColor.x, 0.f, 1.f), MathUtils::Clamp(outColor.y, 0.f, 1.f), MathUtils::Clamp(outColor.z, 0.f, 1.f)));
}

void Rasterizer::RenderTriangle(VTriangle triangle, const rtx::Matrix4& model, const std::vector<std::shared_ptr<Light>>& lights, unsigned int color)
{
	int width = buffer.GetWidth();
	int height = buffer.GetHeight();

	Matrix4 projection = VertexProcessor::SetPerspective(fov, aspect, near, far);
	Matrix4 view = VertexProcessor::SetLookAt(Vector3::Forward(), Vector3::Zero(), Vector3::Up());

	Matrix4 camera;
	camera.LoadIdentity();
	camera = camera * projection * view;

	Vector4 a = model * camera * Vector4(triangle.GetVertexA().GetPosition(), 1.f);
	int ax = (a.x + 1.f) * width * 0.5f;
	int ay = (a.y + 1.f) * height * 0.5f;
	float az = triangle.GetVertexA().GetPosition().z;

	Vector4 b = model * camera * Vector4(triangle.GetVertexB().GetPosition(), 1.f);
	int bx = (b.x + 1.f) * width * 0.5f;
	int by = (b.y + 1.f) * height * 0.5f;
	float bz = triangle.GetVertexB().GetPosition().z;

	Vector4 c = model * camera * Vector4(triangle.GetVertexC().GetPosition(), 1.f);
	int cx = (c.x + 1.f) * width * 0.5f;
	int cy = (c.y + 1.f) * height * 0.5f;
	float cz = triangle.GetVertexC().GetPosition().z;

	int xMin = std::max(MathUtils::Min3<int>(ax, bx, cx), 0);
	int yMin = std::max(MathUtils::Min3<int>(ay, by, cy), 0);

	int xMax = std::max(MathUtils::Max3<int>(ax, bx, cx), width);
	int yMax = std::max(MathUtils::Max3<int>(ay, by, cy), height);

	int abdx = ax - bx;
	int acdx = ax - cx;
	int badx = bx - ax;
	int bcdx = bx - cx;
	int cadx = cx - ax;
	int cbdx = cx - bx;

	int abdy = ay - by;
	int acdy = ay - cy;
	int bady = by - ay;
	int bcdy = by - cy;
	int cady = cy - ay;
	int cbdy = cy - by;

	bool topLeft1 = (abdy < 0 || (abdy == 0 && abdx > 0));
	bool topLeft2 = (bcdy < 0 || (bcdy == 0 && bcdx > 0));
	bool topLeft3 = (cady < 0 || (cady == 0 && cadx > 0));

	float uDenominator = 1.f / (bcdy * acdx + cbdx * acdy);
	float vDenominator = 1.f / (cady * bcdx + acdx * bcdy);

	for (int y = yMin; y < yMax; ++y)
	{
		for (int x = xMin; x < xMax; ++x)
		{
			int scdx = x - cx;
			int scdy = y - cy;

			float ab = abdx * (y - ay) - abdy * (x - ax);
			float bc = bcdx * (y - by) - bcdy * (x - bx);
			float ca = cadx * (y - cy) - cady * (x - cx);

			if ((ab > 0 || (ab >= 0 && topLeft1)) && (bc > 0 || (bc >= 0 && topLeft2)) && (ca > 0 || (ca >= 0 && topLeft3)))
			{
				float u = (bcdy * scdx + cbdx * scdy) * uDenominator;
				float v = (cady * scdx + acdx * scdy) * vDenominator;
				float w = 1.f - u - v;

				float sDepth = buffer.GetPixelDepth(x, y);
				float pDepth = u * az + v * bz + w * cz;

				if (pDepth < sDepth)
				{
					Vector3 pColor = triangle.GetVertexA().GetColor().ToVector() * u 
						+ triangle.GetVertexB().GetColor().ToVector() * v 
						+ triangle.GetVertexC().GetColor().ToVector() * w;

					buffer.SetPixelColor(x, y, Color(pColor).ToHex());
					buffer.SetPixelDepth(x, y, pDepth);
				}
			}
		}
	}
}
