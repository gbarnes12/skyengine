#include "stdafx.h"
#include "skyD3D11GfxStateManager.h"


skyResult skyD3D11GfxStateManager::Spawn ( ID3D11DeviceContext* a_pContext, skyD3D11GfxStateManager** a_pManager)
{
	skyD3D11GfxStateManager* l_pManager = nullptr;

	if(!a_pContext)
		return SKY_INVALID_POINTER;

	*a_pManager = SKY_NEW skyD3D11GfxStateManager(a_pContext);

	return SKY_OK;
}

skyD3D11GfxStateManager::skyD3D11GfxStateManager(ID3D11DeviceContext* a_pContext)
	: m_pContext(a_pContext)
{
}

skyD3D11GfxStateManager::~skyD3D11GfxStateManager()
{
}

skyResult skyD3D11GfxStateManager::SetBlendState ( skyIGfxBlendState* a_pNewState )
{
	if(!a_pNewState)
		return SKY_INVALID_POINTER;

	return SKY_NOT_IMPLEMENTED;
}

skyResult skyD3D11GfxStateManager::SetDepthStencilState ( skyIGfxDepthStencilState* a_pNewState )
{
	if(!a_pNewState)
		return SKY_INVALID_POINTER;

	skyD3D11DepthStencilState* l_pState = static_cast<skyD3D11DepthStencilState*>(a_pNewState);
	if(!l_pState)
		return SKY_INVALID_CAST;

	m_pContext->OMSetDepthStencilState(l_pState->GetBaseState(), 0);

	return SKY_OK;
}

skyResult skyD3D11GfxStateManager::SetSamplerState ( eGfxShaderType a_eType, const skyUInt a_uiSlot, skyIGfxSamplerState* a_pNewState )
{
	if(!a_pNewState)
		return SKY_INVALID_POINTER;

	skyD3D11SamplerState* pSampler = static_cast<skyD3D11SamplerState*>((skyIGfxSamplerState*)a_pNewState);
	if(pSampler)
	{
		ID3D11SamplerState* pBaseSampler = pSampler->GetBaseState();
		if(pBaseSampler)
		{
			if(a_eType == eGfxShaderType_Pixel)
				this->m_pContext->PSSetSamplers(a_uiSlot, 1, &pBaseSampler);
			else if(a_eType == eGfxShaderType_Vertex)
				this->m_pContext->VSSetSamplers(a_uiSlot, 1, &pBaseSampler);
		}
	}

	return SKY_OK;
}

skyResult skyD3D11GfxStateManager::SetRasterizerState ( skyIGfxRasterizerState* a_pNewState )
{
	if(!a_pNewState)
		return SKY_INVALID_POINTER;

	skyD3D11RasterizerState* l_pState = static_cast<skyD3D11RasterizerState*>(a_pNewState);
	if(!l_pState)
		return SKY_INVALID_CAST;

	m_pContext->RSSetState(l_pState->GetBaseState());

	return SKY_OK;
}

