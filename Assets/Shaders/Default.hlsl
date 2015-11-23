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

cbuffer CameraBuffer : register(b1)
{
	float3 eye;
	float padding;
};


cbuffer LightBuffer : register(b2)
{
	float directions[8];
	float4 colors[8];
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
	output.position = mul(View, output.position);
	output.position = mul(Projection, output.position);

	output.normal = normalize(mul((float3x3)World, IN.normal));
	output.color = IN.color;
	output.uv = IN.uv;
	
	return output;
}


float4 PSMain(PSInput IN) : SV_TARGET
{
	float3 lightDir = { 5.0f, 10.0f, -15.0f };
	lightDir = normalize(lightDir);
	float4 color;

	float intensity = saturate(dot(IN.normal, lightDir));
	float4 diffuseTextureColor = DiffuseTexture.Sample(DiffuseSampler, IN.uv.xy);
	float4 diffuseColor = saturate(diffuse * diffuseTextureColor * intensity);
	
	float3 reflection = 2 * (dot(IN.normal, lightDir)) * IN.normal - lightDir; 
	float intensitySpec = pow(dot(reflection, normalize(eye)), n);
	float4 specularColor = saturate(specular * intensitySpec);
	
	
	return ca * ambient + cd * diffuseColor + cs * specularColor;
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