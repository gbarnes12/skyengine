#pragma once
//-----------------------------------------------------------------------------
// Enums
//-----------------------------------------------------------------------------

typedef enum eGfxPrimitiveType 
{
	eGfxPrimitiveType_Undefined = 0,
	eGfxPrimitiveType_PointList = 1,
	eGfxPrimitiveType_LineList = 2,
	eGfxPrimitiveType_LineStrip = 3,
	eGfxPrimitiveType_TriangleList = 4,
	eGfxPrimitiveType_TriangleStrip = 5,
	eGfxPrimitiveType_LineListAdj = 10,
	eGfxPrimitiveType_LineStripAdj = 11,
	eGfxPrimitiveType_TriangleListAdj = 12,
	eGfxPrimitiveType_TriangleStripAdj = 13
} eGfxPrimitiveType;

//-----------------------------------------------------------------------------
typedef enum eGfxFormat 
{
	eGfxTextureFormat_Unknown = 0,
	eGfxTextureFormat_R32G32B32A32_FLOAT = 2,
	eGfxTextureFormat_R32G32B32A32_UINT = 3,
	eGfxTextureFormat_R32G32B32A32_SINT = 4,
	eGfxTextureFormat_R32G32B32_FLOAT = 6,
	eGfxTextureFormat_R32G32B32_UINT = 7,
	eGfxTextureFormat_R32G32B32_SINT = 8,
	eGfxTextureFormat_R32G32_FLOAT = 16,
	eGfxTextureFormat_R32G32_UINT = 17,
	eGfxTextureFormat_R32G32_SINT = 18,
	eGfxTextureFormat_R16G16B16A16_FLOAT = 10,
	eGfxTextureFormat_R16G16B16A16_UNORM = 11,
	eGfxTextureFormat_R16G16B16A16_UINT = 12,
	eGfxTextureFormat_R16G16B16A16_SNORM = 13,
	eGfxTextureFormat_R16G16B16A16_SINT = 14,
	eGfxTextureFormat_R8G8B8A8_UNORM = 28,
	eGfxTextureFormat_R8G8B8A8_UNORM_SRGB = 29,
	eGfxTextureFormat_R8G8B8A8_UINT = 30,
	eGfxTextureFormat_R8G8B8A8_SNORM = 31,
	eGfxTextureFormat_R8G8B8A8_SINT = 32,
	eGfxDepthFormat_D24_UNORM_S8_UINT = 45,
} eGfxFormat;

//-----------------------------------------------------------------------------
typedef enum eGfxUsage
{
	eGfxUsage_Default = 0,
	eGfxUsage_Immutable = 1,
	eGfxUsage_Dynamic = 2,
	eGfxUsage_Staging = 3,
} eGfxUsage;

//-----------------------------------------------------------------------------
typedef enum eGfxBindFlags
{
	eGfxBindFlags_VertexBuffer      = 0x1L,
	eGfxBindFlags_IndexBuffer       = 0x2L,
	eGfxBindFlags_ConstantBuffer    = 0x4L,
	eGfxBindFlags_ShaderResource    = 0x8L,
	eGfxBindFlags_StreamOutput      = 0x10L,
	eGfxBindFlags_RenderTarget      = 0x20L,
	eGfxBindFlags_DepthStencil      = 0x40L,
	eGfxBindFlags_UnorderedAccess   = 0x80L 
} eGfxBindFlags;

//-----------------------------------------------------------------------------
typedef enum eGfxCpuAccessFlags
{
	eGfxCpuAccessFlags_Write = 0x10000L,
	eGfxCpuAccessFlags_Read  = 0x20000L
} eGfxCpuAccessFlags;

//-----------------------------------------------------------------------------
typedef enum eGfxDepthWriteMask { 
	eGfxDepthWriteMask_MaskZero  = 0,
	eGfxDepthWriteMask_MaskAll  = 1
} eGfxDepthWriteMask;

//-----------------------------------------------------------------------------
typedef enum eGfxComparisonFunc {
	eGfxTextureComparisonFunc_Never = 1,
	eGfxTextureComparisonFunc_Less = 2,
	eGfxTextureComparisonFunc_Equal = 3,
	eGfxTextureComparisonFunc_LessEqual = 4,
	eGfxTextureComparisonFunc_Greater = 5,
	eGfxTextureComparisonFunc_NotEqual = 6,
	eGfxTextureComparisonFunc_GreaterEqual = 7,
	eGfxTextureComparisonFunc_Always = 8 
} eGfxTextureComparisonFunc;

//-----------------------------------------------------------------------------
typedef enum eGfxStencilOp { 
	eGfxStencilOp_Keep = 1,
	eGfxStencilOp_Zero = 2,
	eGfxStencilOp_Replace = 3,
	eGfxStencilOp_IncrSat = 4,
	eGfxStencilOp_DecrSat = 5,
	eGfxStencilOp_Invert = 6,
	eGfxStencilOp_Incr = 7,
	eGfxStencilOp_Decr = 8
} eGfxStencilOp;

//-----------------------------------------------------------------------------
typedef enum eGfxFilter
{
	eGfxFilter_MinMagMipPoint = 0,
	eGfxFilter_MinMagPointMipLinear = 0x1,
	eGfxFilter_MinPointMagLinearMipPoint = 0x4,
	eGfxFilter_MinPointMagMipLinear = 0x5,
	eGfxFilter_MinLinearMagMipPoint = 0x10,
	eGfxFilter_MinLinearMagPointMipLinear = 0x11,
	eGfxFilter_MinMagLinearMipPoint = 0x14,
	eGfxFilter_MinMagMipLinear = 0x15,
	eGfxFilter_Anisotropic = 0x55,
	eGfxFilter_CompMinMagMipPoint = 0x80,
	eGfxFilter_CompMinMagPointMipLinear = 0x81,
	eGfxFilter_CompMinPointMagLinearMipPoint = 0x84,
	eGfxFilter_CompMinPointMagMipLinear = 0x85,
	eGfxFilter_CompMinLinearMagMipPoint = 0x90,
	eGfxFilter_CompMinLinearMagPointMipLinear = 0x91,
	eGfxFilter_CompMinMagLinearMipPoint = 0x94,
	eGfxFilter_CompMinMagMipLinear = 0x95,
	eGfxFilter_CompAnisotropic = 0xd5,
	eGfxFilter_Text1Bit = 0x80000000 
} eGfxFilter;

//-----------------------------------------------------------------------------
typedef enum eGfxTextureAddressMode {
  eGfxTextureAddressMode_Wrap = 1,
  eGfxTextureAddressMode_Mirror = 2,
  eGfxTextureAddressMode_Clamp = 3,
  eGfxTextureAddressMode_Border = 4,
  eGfxTextureAddressMode_MirrorOnce = 5 
} eGfxTextureAddressMode;

//-----------------------------------------------------------------------------
typedef enum eGfxFillMode 
{	eGfxFillMode_Wireframe	= 2,
	eGfxFillMode_Solid = 3,
	eGfxFillMode_Point = 4
} eGfxFillMode;


//-----------------------------------------------------------------------------
typedef enum eGfxCullMode
{	
	eGfxCullMode_None	= 1,
	eGfxCullMode_Front	= 2,
	eGfxCullMode_Back	= 3
} eGfxCullMode;

//-----------------------------------------------------------------------------
typedef enum eGfxShaderType
{
	eGfxShaderType_Vertex = 0,
	eGfxShaderType_Pixel = 1,
	eGfxShaderType_Compute = 2,
	eGfxShaderType_Hull = 3,
	eGfxShaderType_Geometry = 4
} eGfxShaderType;

//-----------------------------------------------------------------------------
typedef enum eGfxResourceType
{
	eGfxResourceType_Texture = 0,
	eGfxResourceType_VertexBuffer = 1,
	eGfxResourceType_IndexBuffer = 2,
	eGfxResourceType_ConstantBuffer = 3,
	eGfxResourceType_StructuredBuffer = 4,
	eGfxResourceType_DepthBuffer = 5,
	eGfxResourceType_BlendState = 6,
	eGfxResourceType_DepthStencilState = 7,
	eGfxResourceType_RenderTarget = 8,
	eGfxResourceType_Font = 9,
	eGfxResourceType_Sprite = 10,
	eGfxResourceType_Shader = 11,
	eGfxResourceType_Effect = 12,
	eGfxResourceType_Primitive = 13,
	eGfxResourceType_SamplerState = 14,
	eGfxResourceType_BaseResource = 15,
	eGfxResourceType_RasterizerState = 16,
	eGfxResourceType_Count = 17
} eGfxResourceType;

//-----------------------------------------------------------------------------
typedef enum eGfxMapTypes 
{
	eGfxMapType_Read	= 1,
	eGfxMapType_Write	= 2,
	eGfxMapType_ReadWrite = 3,
	eGfxMapType_WriteDiscard = 4,
	eGfxMapType_WriteNoOverwrite = 5
} eGfxMapTypes;

//-----------------------------------------------------------------------------
typedef enum eGfxMapFlags 
{
	eGfxMapFlag_None = 0x000000L,
	eGfxMapFlag_DoNotWait = 0x100000L
} eGfxMapFlags;

//-----------------------------------------------------------------------------
typedef enum eGfxSwapEffect { 
  eGfxSwapEffect_Discard = 0,
  eGfxSwapEffect_Sequential = 1,
  eGfxSwapEffect_Flip_Sequential = 3
} eGfxSwapEffect;

//-----------------------------------------------------------------------------
typedef enum eGfxStateGuids
{
	eGfxRasterizerGuid_Solid = 0x6f55b9a4,
	eGfxRasterizerGuid_Wireframe = 0x24eca061
} eGfxStateGuids;

//-----------------------------------------------------------------------------
typedef enum eGfxInputClassification {
  eGfxInputClassification_PerVertexData     = 0,
  eGfxInputClassification_PerInstanceData   = 1 
} eGfxInputClassification;

//-----------------------------------------------------------------------------
// Structs
//-----------------------------------------------------------------------------

typedef struct sGfxSampleDesc
{
	skyUInt m_uiCount;
	skyUInt m_uiQuality;
} sGfxSampleDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxTextureDesc 
{
	skyUInt m_uiWidth;
	skyUInt m_uiHeight;
	skyUInt m_uiMipLevels;
	skyUInt m_uiArraySize;
	eGfxFormat m_eFormat;
	eGfxUsage m_eUsage;
	skyUInt m_uiBindFlags;
	skyUInt m_uiCPUFlags;
	skyUInt m_uiMiscFlags;
	sGfxSampleDesc m_sSample;
	eLoadMode m_eMode;
	skyString m_sFileName;
	sIOMemBlob* m_sBlob;
} sGfxTextureDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxBlendDesc
{
}sGfxBlendDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxRasterizerDesc
{
	eGfxFillMode m_eFillMode;
	eGfxCullMode m_eCullMode;
	skyBool m_bFrontCounterClockwise;
	skyInt m_iDepthBias;
	skyFloat m_fDepthBiasClamp;
	skyFloat m_fSlopeScaledDepthBias;
	skyBool m_bDepthClipEnable;
	skyBool m_bScissorEnable;
	skyBool m_bMultisampleEnable;
	skyBool m_bAntialiasedLineEnable;
} sGfxRasterizerDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxSamplerDesc
{
	eGfxFilter m_eFilter;
	eGfxTextureAddressMode m_eAddressU;
	eGfxTextureAddressMode m_eAddressV;
	eGfxTextureAddressMode m_eAddressW;
	skyFloat m_fMipLODBias;
	skyUInt m_uiMaxAnisotropy;
	eGfxComparisonFunc m_eComparisonFunc;
	skyFloat m_aBorderColor[4];
	skyFloat m_fMinLOD;
	skyFloat m_fMaxLOD;
} sGfxSamplerDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxDrawDesc
{
//	skyIGfxIndexBuffer* m_pIndices;
//	skyIGfxVertexBuffer* m_pVertices;
	eGfxPrimitiveType m_ePrimitiveType;
	skyUInt m_uiVertexCount;
	skyUInt m_uiVertexLocation;
	skyUInt m_uiIndexCount;
	skyUInt m_uiIndexLocation;
	skyUInt m_uiInstanceCount;
	skyBool m_bInstanced;
} sGfxDrawDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxDrawPrimitiveDesc
{
	skyIGfxPrimitive* m_pPrimitive;
	skyUInt m_uiInstanceCount;
	skyBool m_bInstanced;
} sGfxDrawPrimitiveDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxVertexDesc
{
	eGfxUsage m_eUsage;
	eGfxBindFlags m_eBindFlags;
	eGfxCpuAccessFlags m_eCPUAccess;
	skyUInt m_uiSize;
	skyUInt m_uiCount;
} sGfxVertexDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxIndexDesc
{
	eGfxUsage m_eUsage;
	eGfxBindFlags m_eBindFlags;
	eGfxCpuAccessFlags m_eCPUAccess;
	skyUInt m_uiSize;
	skyUInt m_uiCount;
} sGfxIndexDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxConstantDesc
{
	eGfxUsage m_eUsage;
	eGfxBindFlags m_eBindFlags;
	eGfxCpuAccessFlags m_eCPUAccess;
	skyUInt m_uiSize;
	skyUInt m_uiCount;
} sGfxConstantDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxStructuredDesc
{
	eGfxUsage m_eUsage;
	eGfxBindFlags m_eBindFlags;
	eGfxCpuAccessFlags m_eCPUAccess;
	skyUInt m_uiSize;
	skyUInt m_uiCount;
	skyUInt m_uiArrayCount;
} sGfxStructuredDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxDepthStencilOpDesc
{
	eGfxStencilOp m_eStencilFailOp;
	eGfxStencilOp m_eStencilDepthFailOp;
	eGfxStencilOp m_eStencilPassOp;
	eGfxComparisonFunc m_eStencilFunc;
} sGfxDepthStencilOpDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxDepthStencilDesc
{
	skyBool m_bDepthEnable;
	eGfxDepthWriteMask m_eDepthWriteMask;
	eGfxComparisonFunc  m_eDepthFunc;
	skyBool m_bStencilEnable;
	skyUInt m_uiStencilReadMask;
	skyUInt m_uiStencilWriteMask;
	sGfxDepthStencilOpDesc m_sFrontFace;
	sGfxDepthStencilOpDesc m_sBackFace;
} sGfxDepthStencilDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxPresentDesc
{
	skyUInt m_uiSyncInterval;
	skyUInt m_uiFlags;
} sGfxPresentDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxLockedBuffer
{
	skyVoid* m_pData;
	skyUInt m_uiRowPitch;
	skyUInt m_uiDepthPitch;
	skyUInt m_uiSubresource;
} sGfxLockedBuffer;

//-----------------------------------------------------------------------------
typedef struct sGfxDeviceDesc
{
	HWND m_pHandle;
	skyUInt m_uiWidth;
	skyUInt m_uiHeight;
	skyBool m_bWindowed; 
	eGfxFormat m_eFormat;
} sGfxDeviceDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxDebugVertex 
{
	skyVector3 m_sPosition;
	skyVector4 m_sColor;
} sGfxDebugVertex;

//-----------------------------------------------------------------------------
typedef struct sGfxStaticVertex 
{
	skyVector3 m_sPosition;
	skyVector2 m_sUV;
	skyVector3 m_sNormal;
} sGfxStaticVertex;


//-----------------------------------------------------------------------------
typedef struct sGfxInputElementDesc 
{
	skyAnsiStr					m_strSemanticName;
	skyUInt						m_u32SemanticIndex;
	eGfxFormat					m_eFormat;
	skyUInt						m_u32InputSlot;
	skyUInt						m_u32AlignedByteOffset;
	eGfxInputClassification		m_eInputSlotClass;
	skyUInt						m_uiInstanceDataStepRate;
} sGfxInputElementDesc;

#define	skyGfxAppendAlignedElement	( 0xffffffff )

//-----------------------------------------------------------------------------
typedef struct sGfxShaderDesc
{
	eGfxShaderType m_eType;
	eLoadMode m_eMode;
	skyString m_sFileName;
	sIOMemBlob* m_sBlob;
	sGfxInputElementDesc* m_pLayout;
	skyUInt m_u32ElementCount;
} sGfxShaderDesc;

//-----------------------------------------------------------------------------
typedef struct sGfxViewport {
  skyFloat m_fTopLeftX;
  skyFloat m_fTopLeftY;
  skyFloat m_fWidth;
  skyFloat m_fHeight;
  skyFloat m_fMinDepth;
  skyFloat m_fMaxDepth;
} sGfxViewport;