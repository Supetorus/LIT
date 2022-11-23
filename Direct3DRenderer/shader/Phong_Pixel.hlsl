Texture2D tex;

SamplerState splr;

cbuffer light
{
	float3 lightPos;
}

static const float3 ambient = { 0.05f, 0.05f, 0.05f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
static const float diffuseIntensity = 1.0f;
static const float attConst = 1.0f;
static const float attLin = 0.045f;
static const float attQuad = 0.0075f;

struct PSInput
{
	float4 pos : SV_Position;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
	float3 worldPos : POSITION; // fix this (where does it come from?)
};

float4 main(PSInput input) : SV_TARGET
{
	const float3 vToL = lightPos - input.worldPos;
	const float distToL = length(vToL);
	const float3 dirToL = vToL / distToL;
	
	const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
	const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, input.normal));
	//const float3 diffuse = tex.Sample(splr, input.tex) * diffuseIntensity * att * max(0.0f, dot(dirToL, input.normal));
	return float4(saturate(diffuse + ambient) * tex.Sample(splr, input.tex), 1.0f);
	
	
	
	//return tex.Sample(splr, input.tex);

}