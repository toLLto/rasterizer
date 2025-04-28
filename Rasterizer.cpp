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

void Rasterizer::Render(std::vector<Renderable>& renderables, const std::vector<std::shared_ptr<Light>>& lights, unsigned int backgroundColor)
{
	buffer.SetBufferColorFill(backgroundColor);
	buffer.SetBufferDepthFill(FLT_MAX);

	for (int i = 0; i < renderables.size(); ++i)
	{
		RenderMesh(renderables[i], lights);
	}

	TGA::Save("miagk_9.tga", buffer.GetColorBuffer(), buffer.GetWidth(), buffer.GetHeight());
}

void Rasterizer::ClearBufferColor(unsigned int color)
{
	buffer.SetBufferColorFill(color);
}

void Rasterizer::ClearBufferDepth(float depth)
{
	buffer.SetBufferDepthFill(depth);
}

void Rasterizer::RenderMesh(Renderable renderable, const std::vector<std::shared_ptr<Light>>& lights)
{
	for (VTriangle& tr : renderable.mesh.GetTris())
	{
		VTriangle vTr = tr;

		if (renderable.enableVertexLighting)
		{
			VertexLightCalculation(vTr.GetVertexARef(), renderable.model, lights);
			VertexLightCalculation(vTr.GetVertexBRef(), renderable.model, lights);
			VertexLightCalculation(vTr.GetVertexCRef(), renderable.model, lights);
		}

		RenderTriangle(vTr, renderable.model, lights, WHITE, renderable.enableVertexLighting);
	}
}

void Rasterizer::RenderTriangle(VTriangle triangle, const rtx::Matrix4& model, const std::vector<std::shared_ptr<Light>>& lights, 
	unsigned int color, bool enableVertexLighting)
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

	rtx::Matrix4 normal = rtx::Matrix4::InvertedMatrix(model);
	normal.Transpose();

	rtx::Vector4 vertAWorldPosition = model * rtx::Vector4(triangle.GetVertexA().GetPosition(), 1.f);
	rtx::Vector4 vertAWorldNormal = normal * rtx::Vector4(triangle.GetVertexA().GetNormal(), 0.f);

	rtx::Vector4 vertBWorldPosition = model * rtx::Vector4(triangle.GetVertexB().GetPosition(), 1.f);
	rtx::Vector4 vertBWorldNormal = normal * rtx::Vector4(triangle.GetVertexB().GetNormal(), 0.f);

	rtx::Vector4 vertCWorldPosition = model * rtx::Vector4(triangle.GetVertexC().GetPosition(), 1.f);
	rtx::Vector4 vertCWorldNormal = normal * rtx::Vector4(triangle.GetVertexC().GetNormal(), 0.f);

	rtx::Vector3 worldNormals[3] = {
		rtx::Vector3(vertAWorldNormal.x, vertAWorldNormal.y, vertAWorldNormal.z).Normal(),
		rtx::Vector3(vertBWorldNormal.x, vertBWorldNormal.y, vertBWorldNormal.z).Normal(),
		rtx::Vector3(vertCWorldNormal.x, vertCWorldNormal.y, vertCWorldNormal.z).Normal()
	};

	rtx::Vector3 worldPositions[3] = {
		rtx::Vector3(vertAWorldPosition.x, vertAWorldPosition.y, vertAWorldPosition.z),
		rtx::Vector3(vertBWorldPosition.x, vertBWorldPosition.y, vertBWorldPosition.z),
		rtx::Vector3(vertCWorldPosition.x, vertCWorldPosition.y, vertCWorldPosition.z)
	};

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

					if (!enableVertexLighting)
					{
						Vector3 worldPosition = worldPositions[0] * u + worldPositions[1] * v + worldPositions[2] * w;
						Vector3 worldNormal = (worldNormals[0] * u + worldNormals[1] * v + worldNormals[2] * w).Normal();

						pColor = PixelLightCalculation(worldPosition, worldNormal, pColor, lights);
					}

					buffer.SetPixelColor(x, y, Color(pColor).ToHex());
					buffer.SetPixelDepth(x, y, pDepth);
				}
			}
		}
	}
}

void Rasterizer::VertexLightCalculation(Vertex& vert, const rtx::Matrix4& model, const std::vector<std::shared_ptr<Light>>& lights)
{
	Vector3 objColor = Color(vert.GetColor()).ToVector();
	Vector3 camPos = rtx::Vector3(0.f, 0.f, 1.f);
	Vector3 outColor = rtx::Vector3::Zero();

	Vector4 worldPos = model * rtx::Vector4(vert.GetPosition(), 1.0f);
	Vector3 worldPosition(worldPos.x, worldPos.y, worldPos.z);

	Matrix4 normalMatrix = rtx::Matrix4::InvertedMatrix(model);
	normalMatrix.Transpose();

	Vector4 worldNorm = normalMatrix * rtx::Vector4(vert.GetNormal(), 0.0f);
	Vector3 worldNormal(worldNorm.x, worldNorm.y, worldNorm.z);
	worldNormal = worldNormal.Normal();

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
			Vector3 vertLight = worldPosition - pointLight->GetPosition();
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
			Vector3 vertLight = worldPosition - spotLight->GetPosition();
			const float dist = vertLight.Length();
			lightDir = vertLight * (-1.f / dist);

			const float angle = lightDir.Dot(spotLight->GetDirection().Normal());
			const float cutOff = std::cos(spotLight->GetCutOff() * PI / 180.f);

			if (angle < cutOff)
				continue;

			const float spot = std::pow(std::max(angle, 0.f), 12.f);
			atten = spot / (1.f + 0.09f * dist + 0.032f * dist * dist);
		}

		amb = ambLight * objColor;

		const float d = std::max(worldNormal.Dot(lightDir), 0.f);
		diff = diffLight * objColor * d;

		Vector3 viewDir = (camPos - worldPosition).Normal();
		Vector3 reflectDir = worldNormal * (2.f * worldNormal.Dot(lightDir)) - lightDir;

		const float s = std::pow(std::max(viewDir.Dot(reflectDir), 0.f), shine);
		spec = specLight * s;

		outColor = outColor + (amb + diff + spec) * atten;
	}

	if (lights.empty())
	{
		outColor = objColor;
	}

	Color col = Color(
		MathUtils::Clamp(outColor.x, 0.f, 1.f),
		MathUtils::Clamp(outColor.y, 0.f, 1.f),
		MathUtils::Clamp(outColor.z, 0.f, 1.f)
	);

	vert.SetColor(col);
}

rtx::Vector3 Rasterizer::PixelLightCalculation(const rtx::Vector3& position, const rtx::Vector3& normal, const rtx::Vector3& color, 
	const std::vector<std::shared_ptr<Light>>& lights)
{
	Vector3 camPos = rtx::Vector3(0.f, 0.f, 1.f);
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
			Vector3 pixelLight = position - pointLight->GetPosition();
			const float dist = pixelLight.Length();
			lightDir = pixelLight * (-1.f / dist);
			atten = 1.f / (1.f + 0.09f * dist + 0.032f * dist * dist);
		}
		else if (auto dirLight = std::dynamic_pointer_cast<DirectionalLight>(light))
		{
			lightDir = -(dirLight->GetDirection()).Normal();
		}
		else if (auto spotLight = std::dynamic_pointer_cast<SpotLight>(light))
		{
			Vector3 pixelLight = position - spotLight->GetPosition();
			const float dist = pixelLight.Length();
			lightDir = pixelLight * (-1.f / dist);

			const float angle = lightDir.Dot(spotLight->GetDirection().Normal());
			const float cutOff = std::cos(spotLight->GetCutOff() * PI / 180.f);

			if (angle < cutOff)
				continue;

			const float spot = std::pow(std::max(angle, 0.f), 12.f);
			atten = spot / (1.f + 0.09f * dist + 0.032f * dist * dist);
		}

		amb = ambLight * color;

		const float d = std::max(normal.Dot(lightDir), 0.f);
		diff = diffLight * color * d;

		Vector3 viewDir = (camPos - position).Normal();
		Vector3 reflectDir = normal * (2.f * normal.Dot(lightDir)) - lightDir;

		const float s = std::pow(std::max(viewDir.Dot(reflectDir), 0.f), shine);
		spec = specLight * s;

		outColor = outColor + (amb + diff + spec) * atten;
	}

	if (lights.empty())
	{
		outColor = color;
	}

	Color col = Color(
		MathUtils::Clamp(outColor.x, 0.f, 1.f),
		MathUtils::Clamp(outColor.y, 0.f, 1.f),
		MathUtils::Clamp(outColor.z, 0.f, 1.f)
	);

	return col.ToVector();
}
