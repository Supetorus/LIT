Texture2D tex;

SamplerState splr;

struct PSInput
{
	float4 pos : SV_Position;
	float2 tex : TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
	//return float4(.5, .5, 1, 1);
	//return float4(input.tex, 0, 1);
	return tex.Sample(splr, input.tex);

}