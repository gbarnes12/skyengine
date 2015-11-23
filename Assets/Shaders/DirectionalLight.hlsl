Texture2D<float4> DiffuseTexture : register(t0);
SamplerState DiffuseSampler : register(s0);

Texture2D<float4> DepthTexture : register(t1);
SamplerState DepthSampler : register(s1);

Texture2D<float4> NormalTexture : register(t2);
SamplerState NormalSampler : register(s2);

cbuffer MatrixBuffer
{
	matrix World;
	matrix View;
	matrix Projection;
};


cbuffer LightBuffer
{
	matrix InvViewProjection;
	float4 ColorX;
	float3 LightPosition;
	float3 Direction;
	float3 CameraPosition;
	float2 HalfPixel;
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

BlendState EnableBlend
{
	BlendEnable[0] = TRUE;
	SrcBlend[0] = SRC_ALPHA;
	DestBlend[0] = INV_SRC_ALPHA;
	BlendOp[0] = ADD;
	SrcBlendAlpha[0] = ZERO;
	DestBlendAlpha[0] = ZERO;
	BlendOpAlpha[0] = ADD;
	RenderTargetWriteMask[0] = 0x0F;
};

PSInput VSMain(VSInput IN)
{
	PSInput output;

	output.position = mul(World, IN.position);
	output.position = mul(Projection, output.position);

	output.normal = normalize(mul((float3x3)World, IN.normal));
	output.color = IN.color;
	output.uv = IN.uv - HalfPixel;
	
	return output;
}


float4 PSMain(PSInput IN) : SV_TARGET0
{
	//get normal data from the normalMap
    float4 normalData = NormalTexture.Sample(NormalSampler, IN.uv);

    //tranform normal back into [-1,1] range
    float3 normalObject = 2.0f * normalData.xyz - 1.0f;

    //get specular power, and get it into [0,255] range]
    float specularPower = normalData.a * 255;

    //get specular intensity from the colorMap
    float specularIntensity = DiffuseTexture.Sample(DiffuseSampler, IN.uv).a;
	
	//read depth
	float depthVal = DepthTexture.Sample(DepthSampler, IN.uv).r;

	 //compute screen-space position
	 float4 positionScreenSpace;

	 positionScreenSpace.x = IN.uv.x * 2.0f - 1.0f;
	 positionScreenSpace.y = -(IN.uv.y * 2.0f - 1.0f);
	 positionScreenSpace.z = depthVal;
	 positionScreenSpace.w = 1.0f;

	 //transform to world space
	 positionScreenSpace = mul(positionScreenSpace, InvViewProjection);
	 positionScreenSpace /= positionScreenSpace.w;

	 //surface-to-light vector
    float3 lightVector = -normalize(Direction);

    //compute diffuse light
    float NdL = max(0,dot(normalObject,lightVector));
    float3 diffuseLight = NdL * ColorX.rgb;

    //reflexion vector
    float3 reflectionVector = normalize(reflect(lightVector, normalObject));

    //camera-to-surface vector
    float3 directionToCamera = normalize(CameraPosition - positionScreenSpace);

    //compute specular light
    float specularLight = specularIntensity * pow( saturate(dot(reflectionVector, directionToCamera)), specularPower);

    //output the two lights
    return float4(diffuseLight.rgb, specularLight) ;
}


technique11 ColorTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_5_0, VSMain() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_5_0, PSMain() ) );
	//	SetBlendState( EnableBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
	}
}