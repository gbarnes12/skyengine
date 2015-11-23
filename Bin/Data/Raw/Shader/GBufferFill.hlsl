Texture2D<float4> DiffuseTexture : register(t0);
SamplerState DiffuseSampler : register(s0);

cbuffer MatrixBuffer
{
	matrix World;
	matrix View;
	matrix Projection;
};

cbuffer MaterialBuffer
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float  cd;
	float  ca;
	float  cs;
	int  n;
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
	float2 uv : TEXCOORD0;
	float2 depth : TEXCOORD1;
};

struct PSOutput
{
	float4 ColorBuffer : SV_TARGET0;
    float4 NormalBuffer : SV_TARGET1;
    float4 DepthBuffer : SV_TARGET2;
};


PSInput VSMain(VSInput IN)
{
	PSInput output;

	output.position = mul(World, IN.position);
	output.position = mul(View, output.position);
	output.position = mul(Projection, output.position);

	output.normal = normalize(mul((float3x3)World, IN.normal));
	output.color = IN.color;
	output.uv = IN.uv;
	
	output.depth.x = output.position.z;
    output.depth.y = output.position.w;

	return output;
}

PSOutput PSMain(PSInput input)
{
    PSOutput output;

    output.ColorBuffer = DiffuseTexture.Sample(DiffuseSampler, input.uv);            
    output.ColorBuffer.a = specular.x;                                             
    output.NormalBuffer.rgb = 0.5f * (normalize(input.normal) + 1.0f);   
    output.NormalBuffer.a = n;                                    
    output.DepthBuffer = input.depth.x / input.depth.y;  

    return output;

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