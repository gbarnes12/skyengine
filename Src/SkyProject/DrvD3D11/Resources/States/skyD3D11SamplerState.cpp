#include "stdafx.h"
#include "skyD3D11SamplerState.h"


skyResult skyD3D11SamplerState::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxSamplerDesc a_sDesc, skyD3D11SamplerState** a_pState )
{
	ID3D11SamplerState* l_pBaseBuffer = nullptr;
	D3D11_SAMPLER_DESC l_sDesc;
	SKY_ZERO_MEM(&l_sDesc, sizeof(D3D11_SAMPLER_DESC));

	l_sDesc.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(a_sDesc.m_eAddressU);
	l_sDesc.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(a_sDesc.m_eAddressV);
	l_sDesc.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(a_sDesc.m_eAddressW);
	l_sDesc.BorderColor[0] = a_sDesc.m_aBorderColor[0];
	l_sDesc.BorderColor[1] = a_sDesc.m_aBorderColor[1];
	l_sDesc.BorderColor[2] = a_sDesc.m_aBorderColor[2];
	l_sDesc.BorderColor[3] = a_sDesc.m_aBorderColor[3];
	l_sDesc.ComparisonFunc = static_cast<D3D11_COMPARISON_FUNC>(a_sDesc.m_eComparisonFunc);
	l_sDesc.Filter = static_cast<D3D11_FILTER>(a_sDesc.m_eFilter);
	l_sDesc.MaxAnisotropy = a_sDesc.m_uiMaxAnisotropy;
	l_sDesc.MinLOD = a_sDesc.m_fMinLOD;
	l_sDesc.MaxLOD = a_sDesc.m_fMaxLOD;
	l_sDesc.MipLODBias = a_sDesc.m_fMipLODBias;

	if( FAILED(a_pDevice->m_pDevice->CreateSamplerState(&l_sDesc, &l_pBaseBuffer)) )
		return SKY_ERROR;

	*a_pState = SKY_NEW skyD3D11SamplerState(a_pDevice, a_sDesc, l_pBaseBuffer);

	return SKY_OK;
}

skyD3D11SamplerState::~skyD3D11SamplerState()
{
	SKY_RELEASE(m_pBaseState);
}

skyD3D11SamplerState::skyD3D11SamplerState( skyD3D11GfxDevice* a_pDevice, sGfxSamplerDesc a_sDesc, 
												ID3D11SamplerState* a_pBaseState)
   : skyD3D11Resource(a_pDevice)
	, m_sDesc ( a_sDesc )
	, m_pBaseState ( a_pBaseState )
{
}