cbuffer CameraBuf : register(b0)
{
	float4x4 view;
	float4x4 viewProjection;
};

cbuffer ObjBuf : register(b1)
{
	float4x4 model;
};

struct VSOut
{
	float4 pos : SV_Position;
	float2 tex : TEXCOORD;
};

VSOut main(float3 pos : POSITION, float2 tex : TEXCOORD)
{
	VSOut vso;									// Create a structure to hold data
	float4x4 mvp = mul(viewProjection, model);	// Create a matrix to translate, rotate, and scale the vertex
	vso.pos = mul(mvp, float4(pos, 1.0f));		// Apply the matrix to the vertex
	vso.tex = tex;								// Just passing data through
	return vso;									// Give the structure to the next step in the pipeline.
}