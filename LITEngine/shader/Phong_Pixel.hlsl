Texture2D tex;

SamplerState splr;

struct PointLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 position;
	float3 attenuation;
	float  range;
};

StructuredBuffer<PointLight> PointLights : register(t1);
	
cbuffer Material : register(b1)
{
	float4 m_ambient;
	float4 m_diffuse;
	float4 m_specular;
	float4 m_reflect;
};
cbuffer camPosition : register(b2)
{
	float3 cameraPosition;
}

struct PSInput
{
	float4 pos : SV_Position;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
	float3 worldPos : POSITION;
};

void ComputePointLight(
PointLight light,
float3 worldPosition,
float3 normal,
float3 toEye,
out float4 ambient,
out float4 diffuse,
out float4 spec)
{
	// Initialize outputs.
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
	// The vector from the surface to the light.
	float3 lightVec = light.position - worldPosition;
	// The distance from surface to light.
	float d = length(lightVec);
	// Range test.
	if (d > light.range)
		return;
	// Normalize the light vector.
	lightVec /= d;
	//lightVec = normalize(lightVec);
	// Ambient term.
	ambient = m_ambient * light.ambient;
	// Add diffuse and specular term, provided the surface is in
	// the line of site of the light.
	float diffuseFactor = dot(lightVec, normal);
	// Flatten to avoid dynamic branching.
	[flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), m_specular.w);
		diffuse = diffuseFactor * m_diffuse * light.diffuse;
		spec = specFactor * m_specular * light.specular;
	}
	// Attenuate
	float att = 1.0f / dot(light.attenuation, float3(1.0f, d, d * d));
	diffuse *= att;
	spec *= att;
}

float4 main(PSInput input) : SV_TARGET
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	
	uint numLights;
	uint stride;
	PointLights.GetDimensions(numLights, stride);
	float3 totalLight = float3(0, 0, 0);
	
	for (int i = 0; i < numLights; i++)
	{
		ComputePointLight(PointLights[i], input.worldPos, input.normal, normalize(cameraPosition - input.worldPos), ambient, diffuse, specular);
		totalLight += ambient + diffuse + specular;
	}
	
	//ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	//diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	//specular = float4(0.0f, 0.0f, 0.0f, 0.0f);
	
	float3 textureColor = (float3) tex.Sample(splr, input.tex);
	//float3 totalLight = (float3) (diffuse + ambient + specular);
	float3 saturatedLight = saturate(totalLight);
	float3 totalColor = saturatedLight * textureColor;
	return float4(totalColor, 1.0f);
}
