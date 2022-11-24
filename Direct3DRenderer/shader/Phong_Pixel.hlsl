Texture2D tex;

SamplerState splr;

cbuffer light
{
	float3 lightPos;
	float diffuseIntensity;
	float attConst;
	float attLin;
	float attQuad;
}

static const float3 ambient = { 0.05f, 0.05f, 0.05f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };

struct PSInput
{
	float4 pos : SV_Position;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
	float3 worldPos : POSITION;
};

float4 main(PSInput input) : SV_TARGET
{
	const float3 vToL = lightPos - input.worldPos;
	const float distToL = length(vToL);
	const float3 dirToL = vToL / distToL;
	
	const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
	const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, input.normal));
	return float4(saturate(diffuse + ambient) * (float3)tex.Sample(splr, input.tex), 1.0f);
}