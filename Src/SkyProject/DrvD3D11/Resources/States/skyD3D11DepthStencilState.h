#pragma once


class skyD3D11DepthStencilState 
	: public skyIGfxDepthStencilState, public  skyD3D11Resource
{ 
public:
	static skyResult skyD3D11DepthStencilState::Spawn (  skyD3D11GfxDevice* a_pDevice, sGfxDepthStencilDesc a_sDesc, skyD3D11DepthStencilState** a_pState );

	skyD3D11DepthStencilState::~skyD3D11DepthStencilState();

public:
	virtual eGfxResourceType skyD3D11DepthStencilState::GetType ( skyVoid ) { return eGfxResourceType_DepthStencilState; }
	virtual sGfxDepthStencilDesc skyD3D11DepthStencilState::GetDesc ( skyVoid ) { return m_sDesc; }
public:
	ID3D11DepthStencilState* skyD3D11DepthStencilState::GetBaseState ( skyVoid ) { return m_pBaseState; }
private:
	ID3D11DepthStencilState* m_pBaseState;
	sGfxDepthStencilDesc m_sDesc;

	skyD3D11DepthStencilState::skyD3D11DepthStencilState(  skyD3D11GfxDevice* a_pDevice, sGfxDepthStencilDesc a_sDesc, 
													 ID3D11DepthStencilState* a_pBaseState);
};