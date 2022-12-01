cbuffer CameraBuf : register(b0)
{
	float4x4 view;
	float4x4 viewProjection;
};

struct VSOut
{
	float3 worldPos : Position;
	float4 pos : SV_Position;
};

VSOut main(float3 pos : POSITION)
{
	VSOut vso;
	vso.worldPos = pos;
	vso.pos = mul(viewProjection, float4(pos, 0.0f));
	vso.pos.z = vso.pos.w;
	return vso;
}