#include "stdafx.h"
#include "skyD3D11GfxDevice.h"

//--------------------------------------------------------------------------------------------------------
skyResult skyD3D11GfxDevice::Spawn ( sGfxDeviceDesc a_sDesc, skyD3D11GfxDevice** a_pDevice)
{
	ID3D11DeviceContext* l_pContext = nullptr;
	ID3D11Device* l_pDevice = nullptr;
	IDXGISwapChain* l_pChain = nullptr;
	skyD3D11GfxSwapChain* l_pSwapChain = nullptr;
	skyD3D11ResourceManager* l_pResourceManager = nullptr;
	skyD3D11GfxStateManager* l_pStateManager = nullptr;
	skyD3D11DepthBuffer* l_pDepthBuffer = nullptr;
	skyD3D11RasterizerState* l_pRasterizerState = nullptr;
	skyD3D11DepthStencilState* l_pDepthState = nullptr;

	DXGI_SWAP_CHAIN_DESC l_desc; 
	sGfxDepthStencilDesc l_depthDesc;
	sGfxRasterizerDesc l_rasterizerDesc;
	skyResult hr;

	SKY_ZERO_MEM(&l_desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	l_desc.BufferCount = 1;
	l_desc.BufferDesc.Width = a_sDesc.m_uiWidth;
    l_desc.BufferDesc.Height = a_sDesc.m_uiHeight;
	l_desc.BufferDesc.Format =  static_cast<DXGI_FORMAT>(a_sDesc.m_eFormat);
    l_desc.BufferDesc.RefreshRate.Numerator = 60;
    l_desc.BufferDesc.RefreshRate.Denominator = 1;
    l_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	l_desc.OutputWindow = a_sDesc.m_pHandle;
	l_desc.Windowed = a_sDesc.m_bWindowed;
	l_desc.SampleDesc.Count = 1;


	D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE
    };

    skyUInt totalDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    skyUInt totalFeatureLevels = ARRAYSIZE( featureLevels );
	skyUInt creationFlags = 0;

#ifdef SKY_BUILD_DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HRESULT pResult;
    skyUInt uiDriver = 0;
	D3D_DRIVER_TYPE eType;
	D3D_FEATURE_LEVEL eFeatureLevel;

    for( uiDriver = 0; uiDriver < totalDriverTypes; ++uiDriver )
    {
        pResult = D3D11CreateDeviceAndSwapChain( 0, driverTypes[uiDriver], 0, creationFlags,
                                                featureLevels, totalFeatureLevels,
												D3D11_SDK_VERSION, &l_desc, &l_pChain,
												&l_pDevice, &eFeatureLevel, &l_pContext );

        if( SUCCEEDED( pResult ) )
        {
			eType = driverTypes[uiDriver];
            break;
        }
    }
	
	if( FAILED( pResult ) )
    {
        DXTRACE_MSG( L"Failed to create the Direct3D device!" );
        return SKY_ERROR;
    }

		// Create Objects, Swap Chain, Resource Manager and so on!
	hr = skyD3D11ResourceManager::Spawn(&l_pResourceManager);

	if(hr != SKY_OK)
	{
		SKY_RELEASE(l_pChain);
		SKY_RELEASE(l_pContext);
		SKY_RELEASE(l_pDevice);
		

		SKY_TODO("error message implementation!");
		return SKY_INVALID_POINTER;
	}


	hr = skyD3D11GfxStateManager::Spawn(l_pContext, &l_pStateManager);

	if(hr != SKY_OK)
	{
		SKY_SAFE_DELETE(l_pSwapChain);
		SKY_SAFE_DELETE(l_pResourceManager);
		SKY_RELEASE(l_pChain);
		SKY_RELEASE(l_pContext);
		SKY_RELEASE(l_pDevice);

		SKY_TODO("error message implementation!");
		return SKY_INVALID_POINTER;
	}

	// finally create the device
	*a_pDevice = SKY_NEW skyD3D11GfxDevice(l_pDevice, l_pContext, l_pResourceManager, l_pStateManager);

	// create the swap chain ;)
	hr = skyD3D11GfxSwapChain::Spawn(*a_pDevice, l_pChain, &l_pSwapChain);

	if(hr != SKY_OK)
	{
		SKY_SAFE_DELETE(l_pStateManager);
		SKY_SAFE_DELETE(l_pResourceManager);
		SKY_RELEASE(l_pChain);
		SKY_RELEASE(l_pContext);
		SKY_RELEASE(l_pDevice);
		
		SKY_TODO("error message implementation!");
		return SKY_INVALID_POINTER;
	}

	// set swap chain ;)
	(*a_pDevice)->SetSwapChain(l_pSwapChain);

	// Depth Stencil Buffer
	SKY_ZERO_MEM(&l_depthDesc, sizeof(sGfxDepthStencilDesc));
	l_depthDesc.m_bDepthEnable = true;
	l_depthDesc.m_eDepthWriteMask = eGfxDepthWriteMask_MaskAll;
	l_depthDesc.m_eDepthFunc = eGfxTextureComparisonFunc_Less;

	l_depthDesc.m_bStencilEnable = true;
	l_depthDesc.m_uiStencilReadMask = 0xFF;
	l_depthDesc.m_uiStencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	l_depthDesc.m_sFrontFace.m_eStencilFailOp = eGfxStencilOp_Keep;
	l_depthDesc.m_sFrontFace.m_eStencilDepthFailOp = eGfxStencilOp_Incr;
	l_depthDesc.m_sFrontFace.m_eStencilPassOp = eGfxStencilOp_Keep;
	l_depthDesc.m_sFrontFace.m_eStencilFunc = eGfxTextureComparisonFunc_Always;

	// Stencil operations if pixel is back-facing.
	l_depthDesc.m_sBackFace.m_eStencilFailOp = eGfxStencilOp_Keep;
	l_depthDesc.m_sBackFace.m_eStencilDepthFailOp = eGfxStencilOp_Decr;
	l_depthDesc.m_sBackFace.m_eStencilPassOp = eGfxStencilOp_Keep;
	l_depthDesc.m_sBackFace.m_eStencilFunc = eGfxTextureComparisonFunc_Always;

	hr = skyD3D11DepthBuffer::Spawn(*a_pDevice, l_depthDesc, &l_pDepthBuffer);
	
	if(hr != SKY_OK)
	{
		SKY_SAFE_DELETE(l_pStateManager);
		SKY_SAFE_DELETE(l_pSwapChain);
		SKY_SAFE_DELETE(l_pResourceManager);
		SKY_RELEASE(l_pChain);
		SKY_RELEASE(l_pContext);
		SKY_RELEASE(l_pDevice);

		SKY_TODO("error message implementation!");
		return SKY_INVALID_POINTER;
	}

	// bind the depth buffer!
	(*a_pDevice)->SetDepthBuffer(l_pDepthBuffer);

	// Depth Stencil State
	hr = skyD3D11DepthStencilState::Spawn(*a_pDevice, l_depthDesc, &l_pDepthState);

	if(hr != SKY_OK)
	{
		SKY_SAFE_DELETE(l_pDepthBuffer);
		SKY_SAFE_DELETE(l_pStateManager);
		SKY_SAFE_DELETE(l_pSwapChain);
		SKY_SAFE_DELETE(l_pResourceManager);
		
		SKY_RELEASE(l_pChain);
		SKY_RELEASE(l_pContext);
		SKY_RELEASE(l_pDevice);

		SKY_TODO("error message implementation!");
		return SKY_INVALID_POINTER;
	}

	// set state!
	l_pStateManager->SetDepthStencilState(l_pDepthState);


	// Rasterizer
	SKY_ZERO_MEM(&l_rasterizerDesc, sizeof(sGfxRasterizerDesc));
	l_rasterizerDesc.m_eFillMode = eGfxFillMode_Solid;
	l_rasterizerDesc.m_eCullMode = eGfxCullMode_None;
	l_rasterizerDesc.m_bAntialiasedLineEnable = true;
	l_rasterizerDesc.m_iDepthBias = 0;
	l_rasterizerDesc.m_fDepthBiasClamp = 0.0f;
	l_rasterizerDesc.m_bDepthClipEnable = true;
	l_rasterizerDesc.m_bFrontCounterClockwise = true;
	l_rasterizerDesc.m_bMultisampleEnable = false;
	l_rasterizerDesc.m_bScissorEnable = false;
	l_rasterizerDesc.m_fSlopeScaledDepthBias = 0.0f;

	hr = skyD3D11RasterizerState::Spawn(*a_pDevice, l_rasterizerDesc, &l_pRasterizerState);
	if(hr != SKY_OK)
	{
		SKY_SAFE_DELETE(l_pDepthState);
		SKY_SAFE_DELETE(l_pDepthBuffer);
		SKY_SAFE_DELETE(l_pStateManager);
		SKY_SAFE_DELETE(l_pSwapChain);
		SKY_SAFE_DELETE(l_pResourceManager);
		SKY_RELEASE(l_pChain);
		SKY_RELEASE(l_pContext);
		SKY_RELEASE(l_pDevice);

		SKY_TODO("error message implementation!");
		return SKY_INVALID_POINTER;
	}

	// set state!
	l_pStateManager->SetRasterizerState(l_pRasterizerState);

	
	return SKY_OK;
}
	
skyD3D11GfxDevice::skyD3D11GfxDevice(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pContext, 
									 skyD3D11ResourceManager* a_pResourceManager, skyD3D11GfxStateManager* a_pStateManager)
		: m_pDevice(a_pDevice)
		, m_pContext(a_pContext)
		, m_pDepthBuffer(NULL)
		, m_pSwapChain(NULL)
		, m_pResourceManager(a_pResourceManager)
		, m_pStateManager(a_pStateManager)
{
	for(skyUInt i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
	{
		m_pRenderTargets[i] = nullptr;
	}
}
		
skyD3D11GfxDevice::~skyD3D11GfxDevice()
{
	for(skyUInt i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
	{
		m_pRenderTargets[i] = nullptr;
	}

	SKY_SAFE_DELETE(m_pDepthBuffer);
	SKY_SAFE_DELETE(m_pStateManager);
	SKY_SAFE_DELETE(m_pSwapChain);
	SKY_SAFE_DELETE(m_pResourceManager);

	SKY_RELEASE(m_pContext);
	SKY_RELEASE(m_pDevice);
}

skyVoid skyD3D11GfxDevice::SetSwapChain ( skyIGfxSwapChain* a_pChain )
{
	SKY_SAFE_DELETE(m_pSwapChain);
	this->m_pSwapChain = static_cast<skyD3D11GfxSwapChain*>(a_pChain);
}

//--------------------------------------------------------------------------------------------------------
skyResult skyD3D11GfxDevice::CreateTexture ( skyIGfxTexture** a_pTexture, sGfxTextureDesc& a_sDesc )	
{
	skyD3D11Texture* l_pTexture = nullptr;
	skyResult hr;

	if(!a_sDesc.m_sBlob) 
	{
		hr = skyD3D11Texture::Spawn(this, &a_sDesc, &l_pTexture);
		if(hr != SKY_OK)
			return hr;
	}
	else 
	{
		hr = skyD3D11Texture::Spawn(a_sDesc.m_eMode, this, a_sDesc.m_sBlob, &l_pTexture);
		if(hr != SKY_OK)
			return hr;
	}

	*a_pTexture = l_pTexture;

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::CreateRenderTarget ( skyIGfxRenderTarget** a_pRT, sGfxTextureDesc& a_sDesc )
{
	skyD3D11RenderTarget* l_pRenderTarget = nullptr;
	skyResult hr;

	hr = skyD3D11RenderTarget::Spawn(this, a_sDesc, &l_pRenderTarget);
	if(hr != SKY_OK)
		return hr;

	*a_pRT = l_pRenderTarget;

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::CreateRenderTarget ( skyIGfxRenderTarget** a_pRT, skyIGfxTexture* a_pTexture )
{
	skyD3D11RenderTarget* l_pRenderTarget = nullptr;
	skyD3D11Texture* l_pTexture = nullptr;
	skyResult hr;

	l_pTexture = static_cast<skyD3D11Texture*>(a_pTexture);
	if(!l_pTexture)
		return SKY_INVALID_POINTER;

	hr = skyD3D11RenderTarget::Spawn( l_pTexture, this, &l_pRenderTarget);
	if(hr != SKY_OK)
		return hr;

	*a_pRT = l_pRenderTarget;

	return SKY_OK;
}



skyResult skyD3D11GfxDevice::CreateIndexBuffer ( skyIGfxIndexBuffer** a_pBuffer, sGfxIndexDesc& a_sDesc )
{
	skyD3D11IndexBuffer* l_pBuffer = nullptr;
	
	skyResult hr = skyD3D11IndexBuffer::Spawn(this, a_sDesc, &l_pBuffer);
	if(hr != SKY_OK)
		return hr;

	*a_pBuffer = l_pBuffer;

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::CreateVertexBuffer ( skyIGfxVertexBuffer** a_pBuffer, sGfxVertexDesc& a_sDesc )
{
	skyD3D11VertexBuffer* l_pBuffer = nullptr;
	a_sDesc.m_eBindFlags = eGfxBindFlags_VertexBuffer;

	skyResult hr = skyD3D11VertexBuffer::Spawn(this, a_sDesc, &l_pBuffer);
	if(hr != SKY_OK)
		return hr;

	*a_pBuffer = l_pBuffer;

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::CreateConstantBuffer ( skyIGfxConstantBuffer** a_pBuffer, sGfxConstantDesc& a_sDesc )
{
	skyD3D11ConstantBuffer* l_pBuffer = nullptr;

	skyResult hr = skyD3D11ConstantBuffer::Spawn(this, a_sDesc, &l_pBuffer);
	if(hr != SKY_OK)
		return hr;

	*a_pBuffer = l_pBuffer;

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::CreatePrimitive ( skyIGfxPrimitive** a_pPrimitive )
{
	skyResult hr;
	skyD3D11Primitive* pPrimitive = NULL;
	SKY_VR(skyD3D11Primitive::Spawn(this, &pPrimitive));
	*a_pPrimitive = pPrimitive;

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::CreateShader ( skyIGfxShader** a_pShader, sGfxShaderDesc& a_sDesc )
{
	if(a_sDesc.m_eType == eGfxShaderType_Pixel) { 
		skyResult hr;
		skyD3D11PixelShader* pShader = NULL;
		SKY_VR(skyD3D11PixelShader::Spawn ( a_sDesc.m_eMode, this, a_sDesc.m_sBlob, a_sDesc.m_sFileName, &pShader)); 
		*a_pShader = pShader;
	}
	else if(a_sDesc.m_eType == eGfxShaderType_Vertex) { 
		skyResult hr;
		skyD3D11VertexShader* pShader = NULL;
		SKY_VR(skyD3D11VertexShader::Spawn ( a_sDesc.m_eMode, this, a_sDesc.m_pLayout, a_sDesc.m_u32ElementCount, a_sDesc.m_sBlob, a_sDesc.m_sFileName, &pShader));
		*a_pShader = pShader;
	}


	return SKY_OK;
}

//--------------------------------------------------------------------------------------------------------
skyResult skyD3D11GfxDevice::SetRenderTarget ( skyUInt a_uiIndex, skyIGfxRenderTarget* a_pTarget, skyBool a_bUseDepthStencil = true )
{
	skyD3D11RenderTarget* l_pD3DTarget = nullptr;
	m_pRenderTargets[a_uiIndex] = a_pTarget;

	// cast to skyD3D11RenderTarget 
	l_pD3DTarget = static_cast<skyD3D11RenderTarget*>(a_pTarget);
	if(!l_pD3DTarget)
		return SKY_INVALID_POINTER;

	ID3D11RenderTargetView* pView = l_pD3DTarget->AsView();
	m_pContext->OMSetRenderTargets(1, &pView, (a_bUseDepthStencil) ? m_pDepthBuffer->AsView() : NULL);

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::GetRenderTarget ( skyUInt a_uiIndex, skyIGfxRenderTarget** a_pTarget )
{
	skyIGfxRenderTarget* pTarget = m_pRenderTargets[a_uiIndex];

	if(!pTarget)
		return SKY_INVALID_POINTER;

	*a_pTarget = pTarget;

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::ClearRenderTarget ( skyUInt a_uiIndex, sGfxColor& a_sColor )
{
	DX_START_SECTION(skyColor(1.0f, 0.0f, 0.0f, 1.0f), L"Clear Rendertarget");
	
	skyIGfxRenderTarget* l_pTarget = m_pRenderTargets[a_uiIndex];
	skyD3D11RenderTarget* l_pD3DTarget = nullptr;

	if(!l_pTarget)
		return SKY_INVALID_POINTER;

	// cast to skyD3D11RenderTarget 
	l_pD3DTarget = static_cast<skyD3D11RenderTarget*>(l_pTarget);
	if(!l_pD3DTarget)
		return SKY_INVALID_POINTER;

	m_pContext->ClearRenderTargetView(l_pD3DTarget->AsView(), a_sColor);
	
	ClearDepthBuffer();

	DX_END_SECTION();

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::ResetRenderTarget ( skyUInt a_uiIndex )
{
	SKY_UNTESTED_METHOD("not yet implemented");

	return SKY_NOT_SUPPORTED;
}

skyResult skyD3D11GfxDevice::ResetRenderTargets ( skyVoid )
{
	ID3D11RenderTargetView* l_pTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	m_pContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, l_pTargets, NULL);

	for(skyUInt i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
	{
		m_pRenderTargets[i] = nullptr;
	}

	return SKY_OK;
}

//--------------------------------------------------------------------------------------------------------
skyResult skyD3D11GfxDevice::SetBlendState ( skyIGfxBlendState* a_pState )
{
	return m_pStateManager->SetBlendState(a_pState);
}

skyResult skyD3D11GfxDevice::SetDepthState ( skyIGfxDepthStencilState* a_pState )
{
	return m_pStateManager->SetDepthStencilState(a_pState);
}

skyResult skyD3D11GfxDevice::SetRasterizerState ( skyIGfxRasterizerState* a_pState )
{
	return m_pStateManager->SetRasterizerState(a_pState);
}

skyResult skyD3D11GfxDevice::SetSamplerState ( eGfxShaderType a_eType, const skyUInt a_uiSlot, skyIGfxSamplerState* a_pState )
{
	return m_pStateManager->SetSamplerState(a_eType, a_uiSlot, a_pState);
}

skyResult skyD3D11GfxDevice::CreateBlendState ( sGfxBlendDesc a_sDesc, skyIGfxBlendState** a_pState )
{
	SKY_UNTESTED_METHOD("not yet implemented");

	return SKY_NOT_SUPPORTED;
}

skyResult skyD3D11GfxDevice::CreateDepthState ( sGfxDepthStencilDesc a_sDesc, skyIGfxDepthStencilState** a_pState )
{
	skyD3D11DepthStencilState* pState = nullptr;

	skyResult hr = skyD3D11DepthStencilState::Spawn(this, a_sDesc, &pState);
	if(hr != SKY_OK)
		return hr;
	
	*a_pState = pState;

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::CreateRasterizerState ( sGfxRasterizerDesc a_sDesc, skyIGfxRasterizerState** a_pState )
{
	skyD3D11RasterizerState* pState = nullptr;

	skyResult hr = skyD3D11RasterizerState::Spawn(this, a_sDesc, &pState);
	if(hr != SKY_OK)
		return hr;
	
	*a_pState = pState;

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::CreateSamplerState ( sGfxSamplerDesc a_sDesc, skyIGfxSamplerState** a_pState )
{
	skyD3D11SamplerState* pState = nullptr;

	skyResult hr = skyD3D11SamplerState::Spawn(this, a_sDesc, &pState);
	if(hr != SKY_OK)
		return hr;
	
	*a_pState = pState;

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::GetBackBuffer ( skyIGfxTexture** a_pTexture )
{
	return this->m_pSwapChain->GetBackBuffer(a_pTexture);
}

//--------------------------------------------------------------------------------------------------------
skyVoid skyD3D11GfxDevice::SetConstantbuffer ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxConstantBuffer* a_pBuffer )
{
	skyD3D11ConstantBuffer* pBuffer = static_cast<skyD3D11ConstantBuffer*>((skyIGfxConstantBuffer*)a_pBuffer);
	if(pBuffer)
	{
		ID3D11Buffer* pBaseBuffer = pBuffer->GetBaseBuffer();
		if(pBaseBuffer)
		{
			if(a_eType == eGfxShaderType_Pixel)
				this->m_pContext->PSSetConstantBuffers(a_uiSlot, 1, &pBaseBuffer);
			else if(a_eType == eGfxShaderType_Vertex)
				this->m_pContext->VSSetConstantBuffers(a_uiSlot, 1, &pBaseBuffer);
		}
	}
}

skyVoid skyD3D11GfxDevice::SetTexture ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxTexture* a_pTexture )
{
	skyD3D11Texture* pTexture = static_cast<skyD3D11Texture*>((skyIGfxTexture*)a_pTexture);
	if(pTexture)
	{
		ID3D11ShaderResourceView* pView = pTexture->AsResourceView();
		if(pView)
		{
			if(a_eType == eGfxShaderType_Pixel)
				this->m_pContext->PSSetShaderResources(a_uiSlot, 1, &pView);
			else if(a_eType == eGfxShaderType_Vertex)
				this->m_pContext->VSSetShaderResources(a_uiSlot, 1, &pView);
		}
	}
}


//--------------------------------------------------------------------------------------------------------
skyResult skyD3D11GfxDevice::SetIndexBuffer ( skyIGfxIndexBuffer* a_pBuffer )
{
	if(!a_pBuffer)
		return SKY_INVALID_POINTER;

	skyD3D11IndexBuffer* pBuffer = static_cast<skyD3D11IndexBuffer*>(a_pBuffer);
	if(!pBuffer)
		return SKY_INVALID_CAST;

	this->m_pContext->IASetIndexBuffer(pBuffer->GetBaseBuffer(), DXGI_FORMAT_R32_UINT, 0);

	return SKY_OK;
}

skyResult skyD3D11GfxDevice::SetVertexBuffer ( skyIGfxVertexBuffer* a_pBuffer, skyUInt a_u32Offset )
{
	if(!a_pBuffer)
		return SKY_INVALID_POINTER;

	skyD3D11VertexBuffer* pBuffer = static_cast<skyD3D11VertexBuffer*>(a_pBuffer);
	if(!pBuffer)
		return SKY_INVALID_CAST;

	sGfxVertexDesc sDesc = pBuffer->GetDesc();
	ID3D11Buffer* pBaseBuffer = pBuffer->GetBaseBuffer();
	skyUInt u32Stride = a_pBuffer->GetStride();

	this->m_pContext->IASetVertexBuffers(0, 1, &pBaseBuffer, &u32Stride, &a_u32Offset); 
	
	return SKY_OK;
}


//--------------------------------------------------------------------------------------------------------
skyResult skyD3D11GfxDevice::SetDepthBuffer ( skyIGfxDepthBuffer* a_pBuffer)
{
	if(!a_pBuffer)
		return SKY_INVALID_POINTER;

	SKY_SAFE_DELETE(m_pDepthBuffer);
	m_pDepthBuffer = static_cast<skyD3D11DepthBuffer*>(a_pBuffer);
	
	return SKY_OK;
}

skyIGfxDepthBuffer* skyD3D11GfxDevice::GetDepthBuffer ( ) const
{
	return this->m_pDepthBuffer;
}

skyVoid skyD3D11GfxDevice::ClearDepthBuffer ( ) 
{
	m_pContext->ClearDepthStencilView(m_pDepthBuffer->AsView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 0.0f, 0);
}

//--------------------------------------------------------------------------------------------------------
skyVoid skyD3D11GfxDevice::SetViewport ( const sGfxViewport& a_sViewport )
{
	D3D11_VIEWPORT sViewport;
	SKY_ZERO_MEM(&sViewport, sizeof(D3D11_VIEWPORT));
	sViewport.Width = a_sViewport.m_fWidth;
	sViewport.Height = a_sViewport.m_fHeight;
	sViewport.TopLeftX = a_sViewport.m_fTopLeftX;
	sViewport.TopLeftY = a_sViewport.m_fTopLeftY;
	sViewport.MinDepth = a_sViewport.m_fMinDepth;
	sViewport.MaxDepth = a_sViewport.m_fMaxDepth;

	this->m_pContext->RSSetViewports(1, &sViewport);
}

sGfxViewport skyD3D11GfxDevice::GetViewport ( skyVoid )
{
	sGfxViewport sOutViewport;
	SKY_ZERO_MEM(&sOutViewport, sizeof(sGfxViewport));

	D3D11_VIEWPORT sViewport[1];
	SKY_ZERO_MEM(&sViewport[0], sizeof(D3D11_VIEWPORT));
	
	skyUInt i = 1;
	this->m_pContext->RSGetViewports(&i, &sViewport[0]);

	return sOutViewport;
}


//--------------------------------------------------------------------------------------------------------
skyVoid skyD3D11GfxDevice::Draw ( skyIGfxPrimitive* a_pPrimitive )
{
	if(!a_pPrimitive)
		return;

	skyIGfxIndexBuffer* pIndexBuffer = a_pPrimitive->GetIndices();
	skyIGfxVertexBuffer* pVertexBuffer = a_pPrimitive->GetVertices();
	skyBool bHasIndices = SKY_FALSE;

	if(!pVertexBuffer)
		return;

	if(pIndexBuffer)
		bHasIndices = SKY_TRUE;

	sGfxVertexDesc sVDesc = pVertexBuffer->GetDesc();
	sGfxIndexDesc sIDesc = (bHasIndices) ? pIndexBuffer->GetDesc() : sGfxIndexDesc();

	sGfxDrawDesc sDesc; 
	sDesc.m_bInstanced = SKY_FALSE;
	sDesc.m_ePrimitiveType = eGfxPrimitiveType_TriangleList;
	sDesc.m_uiIndexCount = (!bHasIndices) ? 0 : sIDesc.m_uiCount;
	sDesc.m_uiIndexLocation = 0;
	sDesc.m_uiVertexLocation = 0;
	sDesc.m_uiVertexCount = pVertexBuffer->GetElementCount();
	sDesc.m_uiInstanceCount = 0;

	
	if(bHasIndices)
		this->SetIndexBuffer(pIndexBuffer);

	this->SetVertexBuffer(pVertexBuffer, 0);
	this->Draw(sDesc);
}

skyVoid skyD3D11GfxDevice::Draw ( sGfxDrawDesc& a_sDesc )
{
	this->m_pContext->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(a_sDesc.m_ePrimitiveType));
	// draw the vertex buffer to the back buffer
	if ( a_sDesc.m_uiIndexCount > 0 ) 
	{
		if(a_sDesc.m_bInstanced)
		{
			this->m_pContext->DrawIndexedInstanced(a_sDesc.m_uiIndexCount, a_sDesc.m_uiInstanceCount, a_sDesc.m_uiIndexLocation, 0, 0);
		}
		else 
		{
			this->m_pContext->DrawIndexed(a_sDesc.m_uiIndexCount, a_sDesc.m_uiIndexLocation, 0);
		}
	}
	else 
	{
		if(a_sDesc.m_bInstanced) 
		{
			this->m_pContext->DrawInstanced(a_sDesc.m_uiVertexCount, a_sDesc.m_uiInstanceCount, a_sDesc.m_uiVertexLocation, 0);
		} 
		else 
		{
			this->m_pContext->Draw(a_sDesc.m_uiVertexCount, a_sDesc.m_uiVertexLocation);
		}
	}
}

skyVoid skyD3D11GfxDevice::Present ( sGfxPresentDesc& a_sDesc )
{
	this->m_pSwapChain->Present(a_sDesc);
}

skyVoid skyD3D11GfxDevice::Resize ( skyVoid )
{
}

