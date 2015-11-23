cbuffer PerFrameBuffer
{
	matrix projection;
	matrix view;
};

struct VSInput
{
	float3 position : POSITION0;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float3 normal : TEXCOORD0;
	float2 uv : TEXCOORD1;
};

PSInput main(VSInput input)
{
	PSInput output;

	output.position = float4(input.position, 1.0f);
	output.position = mul(view, output.position);
	output.position = mul(projection, output.position);

	output.normal = normalize(input.normal);
	output.uv = input.uv;

	return output;
}