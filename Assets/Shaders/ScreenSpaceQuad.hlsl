Texture2D<float4> DiffuseTexture : register(t0);
SamplerState DiffuseSampler : register(s0);

cbuffer MatrixBuffer
{
	matrix World;
	matrix View;
	matrix Projection;
};

struct VSInput
{
	float4 position : POSITION0;
	float4 color : COLOR0;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};



PSInput VSMain(VSInput IN)
{
	PSInput output;

	output.position = mul(World, IN.position);
	output.position = mul(Projection, output.position);

	output.normal = normalize(mul((float3x3)World, IN.normal));
	output.color = IN.color;
	output.uv = IN.uv;
	
	return output;
}


float4 PSMain(PSInput IN) : SV_TARGET
{
	return DiffuseTexture.Sample(DiffuseSampler, IN.uv); 
}


technique11 ColorTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_5_0, VSMain() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_5_0, PSMain() ) );
	}
}