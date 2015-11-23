#include "stdafx.h"
#include "skyD3D11DepthStencilState.h"


skyResult skyD3D11DepthStencilState::Spawn (  skyD3D11GfxDevice* a_pDevice, sGfxDepthStencilDesc a_sDesc, skyD3D11DepthStencilState** a_pState )
{
	ID3D11DepthStencilState* l_pBaseBuffer = nullptr;
	D3D11_DEPTH_STENCIL_DESC l_sDesc;
	SKY_ZERO_MEM(&l_sDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	l_sDesc.DepthEnable = a_sDesc.m_bDepthEnable;
	l_sDesc.DepthWriteMask = static_cast<D3D11_DEPTH_WRITE_MASK>(a_sDesc.m_eDepthWriteMask);
	l_sDesc.DepthFunc = static_cast<D3D11_COMPARISON_FUNC>(a_sDesc.m_eDepthFunc);

	l_sDesc.StencilEnable = a_sDesc.m_bStencilEnable;
	l_sDesc.StencilReadMask = a_sDesc.m_uiStencilReadMask;
	l_sDesc.StencilWriteMask = a_sDesc.m_uiStencilWriteMask;

	// Stencil operations if pixel is front-facing.
	l_sDesc.FrontFace.StencilFailOp = static_cast<D3D11_STENCIL_OP>(a_sDesc.m_sFrontFace.m_eStencilFailOp);
	l_sDesc.FrontFace.StencilDepthFailOp = static_cast<D3D11_STENCIL_OP>(a_sDesc.m_sFrontFace.m_eStencilDepthFailOp);
	l_sDesc.FrontFace.StencilPassOp = static_cast<D3D11_STENCIL_OP>(a_sDesc.m_sFrontFace.m_eStencilPassOp);
	l_sDesc.FrontFace.StencilFunc  = static_cast<D3D11_COMPARISON_FUNC>(a_sDesc.m_sFrontFace.m_eStencilFunc);

	// Stencil operations if pixel is back-facing.
	l_sDesc.BackFace.StencilFailOp  = static_cast<D3D11_STENCIL_OP>(a_sDesc.m_sBackFace.m_eStencilFailOp);
	l_sDesc.BackFace.StencilDepthFailOp = static_cast<D3D11_STENCIL_OP>(a_sDesc.m_sBackFace.m_eStencilDepthFailOp);
	l_sDesc.BackFace.StencilPassOp = static_cast<D3D11_STENCIL_OP>(a_sDesc.m_sBackFace.m_eStencilPassOp);
	l_sDesc.BackFace.StencilFunc = static_cast<D3D11_COMPARISON_FUNC>(a_sDesc.m_sBackFace.m_eStencilFunc);

	if( FAILED(a_pDevice->m_pDevice->CreateDepthStencilState(&l_sDesc, &l_pBaseBuffer)) )
		return SKY_ERROR;

	*a_pState = SKY_NEW skyD3D11DepthStencilState(a_pDevice, a_sDesc, l_pBaseBuffer);

	return SKY_OK;
}

skyD3D11DepthStencilState::~skyD3D11DepthStencilState()
{
	SKY_RELEASE(m_pBaseState);
}

skyD3D11DepthStencilState::skyD3D11DepthStencilState( skyD3D11GfxDevice* a_pDevice, sGfxDepthStencilDesc a_sDesc, 
													 ID3D11DepthStencilState* a_pBaseState)
	: skyD3D11Resource(a_pDevice)
	, m_sDesc ( a_sDesc )
	, m_pBaseState ( a_pBaseState )
{
}