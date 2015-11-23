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

struct PSInput
{
	float4 position : SV_POSITION;
	float3 normal : TEXCOORD0;
	float2 uv : TEXCOORD1;
};


float4 main(PSInput input) : SV_TARGET0
{
	float3 lightDir = { 5.0f, 10.0f, -15.0f };
	lightDir = normalize(lightDir);
	float4 color;

	float intensity = saturate(dot(input.normal, lightDir));
	//float4 diffuseTextureColor = DiffuseTexture.Sample(DiffuseSampler, IN.uv.xy);
	float4 diffuseColor = saturate(diffuse  * intensity);
	
	float3 reflection = 2 * (dot(input.normal, lightDir)) * input.normal - lightDir; 
	//float intensitySpec = pow(dot(reflection, normalize(eye)), n);
	//float4 specularColor = saturate(specular * intensitySpec);
	
	
	return ca * ambient + cd * diffuseColor;
}