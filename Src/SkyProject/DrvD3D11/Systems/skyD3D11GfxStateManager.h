#pragma once 

class skyD3D11GfxStateManager 
	: skyIGfxStateManager
{
public:
	static skyResult skyD3D11GfxStateManager::Spawn ( ID3D11DeviceContext* a_pContext, skyD3D11GfxStateManager** a_pManager);
	skyD3D11GfxStateManager::~skyD3D11GfxStateManager();

public:
	skyResult skyD3D11GfxStateManager::SetBlendState ( skyIGfxBlendState* a_pNewState );
	skyResult skyD3D11GfxStateManager::SetDepthStencilState ( skyIGfxDepthStencilState* a_pNewState );
	skyResult skyD3D11GfxStateManager::SetSamplerState ( eGfxShaderType a_eType, const skyUInt a_uiSlot, skyIGfxSamplerState* a_pNewState );
	skyResult skyD3D11GfxStateManager::SetRasterizerState ( skyIGfxRasterizerState* a_pNewState );
private:
	ID3D11DeviceContext* m_pContext;

	skyD3D11GfxStateManager::skyD3D11GfxStateManager(ID3D11DeviceContext* a_pContext);

};