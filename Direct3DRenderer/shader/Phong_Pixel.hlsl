Texture2D tex;

SamplerState splr;

cbuffer light : register(b0)
{
	float3 lightPos;	// relative to the camera / in view space.
	float diffuseIntensity;
	float attConst;
	float attLin;
	float attQuad;
}

cbuffer object : register(b1)
{
	float specularIntensity = 0;
	float specularPower = 0;
};

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
	float3 vToL = lightPos - input.worldPos;
	float distToL = length(vToL);
	float3 dirToL = vToL / distToL;
	
	float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
	float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, input.normal));
	
	float3 w = input.normal * dot(vToL, input.normal);
	float3 r = w * 2.0f - vToL;
	float3 specular = att * (diffuseColor * diffuseIntensity) * specularIntensity * pow(max(0.0f, dot(normalize(-r), normalize(input.worldPos))),			specularPower);
	
	float3 textureColor = (float3) tex.Sample(splr, input.tex);
	float3 totalLight = diffuse + ambient + specular;
	float3 saturatedLight = saturate(totalLight);
	float3 totalColor = totalLight * textureColor;
	return float4(totalColor, 1.0f);
}