cbuffer CameraBuf : register(b0)
{
	float4x4 view;
	float4x4 viewProjection;
};

cbuffer ObjBuf : register(b1)
{
	float4x4 objTransform;
};

struct VSOut
{
	float4 pos : SV_Position;
	float2 tex : TEXCOORD;
};

VSOut main(float3 pos : POSITION, float2 tex : TEXCOORD)
{
	VSOut vso;
	float4x4 mvp = mul(viewProjection, objTransform);
	vso.pos = mul(mvp, float4(pos, 1.0f));
	vso.tex = tex;
	return vso;
}