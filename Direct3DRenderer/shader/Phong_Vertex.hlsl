cbuffer CameraBuf : register(b0)
{
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
	float3 normal : NORMAL;
	float3 worldPos : POSITION;
};

VSOut main(float3 pos : POSITION, float2 tex : TEXCOORD, float3 normal : NORMAL)
{
	VSOut vso;
	float4x4 mvp = mul(viewProjection, objTransform);
	vso.pos = mul(mvp, float4(pos, 1.0f)); // Convert the pos to mvp space
	vso.tex = tex;
	//vso.normal = mul((float3x3) objTransform, normal); // convert the normal vector to mvp space
	vso.normal = normalize(mul((float3x3) objTransform, normal)); // convert the normal vector to mvp space
	vso.worldPos = (float3) mul(objTransform, float4(pos, 1.0f)); // get the world position of the vertex
	return vso;
}