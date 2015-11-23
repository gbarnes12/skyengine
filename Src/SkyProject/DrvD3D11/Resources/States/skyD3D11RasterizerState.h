#pragma once


class skyD3D11RasterizerState
	: public skyIGfxRasterizerState, public  skyD3D11Resource
{ 
public:
	static skyResult skyD3D11RasterizerState::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxRasterizerDesc a_sDesc, skyD3D11RasterizerState** a_pState );

	skyD3D11RasterizerState::~skyD3D11RasterizerState();

public:
	virtual eGfxResourceType skyD3D11RasterizerState::GetType ( skyVoid ) { return eGfxResourceType_RasterizerState; }
	virtual sGfxRasterizerDesc skyD3D11RasterizerState::GetDesc ( skyVoid ) { return m_sDesc; }
public:
	ID3D11RasterizerState* skyD3D11RasterizerState::GetBaseState ( skyVoid ) { return m_pBaseState; }
private:
	ID3D11RasterizerState* m_pBaseState;
	sGfxRasterizerDesc m_sDesc;

	skyD3D11RasterizerState::skyD3D11RasterizerState( skyD3D11GfxDevice* a_pDevice, sGfxRasterizerDesc a_sDesc, 
													 ID3D11RasterizerState* a_pBaseState);
};