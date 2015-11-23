#include "stdafx.h"
#include "skyD3D11RasterizerState.h"


skyResult skyD3D11RasterizerState::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxRasterizerDesc a_sDesc, skyD3D11RasterizerState** a_pState )
{
	ID3D11RasterizerState* l_pBaseBuffer = nullptr;
	D3D11_RASTERIZER_DESC l_sDesc;
	SKY_ZERO_MEM(&l_sDesc, sizeof(D3D11_RASTERIZER_DESC));

	l_sDesc.FillMode = static_cast<D3D11_FILL_MODE>(a_sDesc.m_eFillMode);
	l_sDesc.CullMode = static_cast<D3D11_CULL_MODE>(a_sDesc.m_eCullMode);
	l_sDesc.AntialiasedLineEnable = a_sDesc.m_bAntialiasedLineEnable;

	l_sDesc.DepthBias = a_sDesc.m_iDepthBias;
	l_sDesc.DepthBiasClamp = a_sDesc.m_fDepthBiasClamp;
	l_sDesc.DepthClipEnable = a_sDesc.m_bDepthClipEnable;
	l_sDesc.FrontCounterClockwise = a_sDesc.m_bFrontCounterClockwise;
	l_sDesc.MultisampleEnable = a_sDesc.m_bMultisampleEnable;
	l_sDesc.ScissorEnable = a_sDesc.m_bScissorEnable;
	l_sDesc.SlopeScaledDepthBias = a_sDesc.m_fSlopeScaledDepthBias;


	if( FAILED(a_pDevice->m_pDevice->CreateRasterizerState(&l_sDesc, &l_pBaseBuffer)) )
		return SKY_ERROR;

	*a_pState = SKY_NEW skyD3D11RasterizerState(a_pDevice, a_sDesc, l_pBaseBuffer);

	return SKY_OK;
}

skyD3D11RasterizerState::~skyD3D11RasterizerState()
{
	SKY_RELEASE(m_pBaseState);
}

skyD3D11RasterizerState::skyD3D11RasterizerState( skyD3D11GfxDevice* a_pDevice, sGfxRasterizerDesc a_sDesc, 
												 ID3D11RasterizerState* a_pBaseState)
   : skyD3D11Resource(a_pDevice)
	, m_sDesc ( a_sDesc )
	, m_pBaseState ( a_pBaseState )
{
}