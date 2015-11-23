#pragma once


class skyD3D11SamplerState
	: public skyIGfxSamplerState, public  skyD3D11Resource
{ 
public:
	static skyResult skyD3D11SamplerState::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxSamplerDesc a_sDesc, skyD3D11SamplerState** a_pState );

	skyD3D11SamplerState::~skyD3D11SamplerState();

public:
	virtual eGfxResourceType skyD3D11SamplerState::GetType ( skyVoid ) { return eGfxResourceType_SamplerState; }
	virtual sGfxSamplerDesc skyD3D11SamplerState::GetDesc ( skyVoid ) { return m_sDesc; }
public:
	ID3D11SamplerState* skyD3D11SamplerState::GetBaseState ( skyVoid ) { return m_pBaseState; }
private:
	ID3D11SamplerState* m_pBaseState;
	sGfxSamplerDesc m_sDesc;

	skyD3D11SamplerState::skyD3D11SamplerState( skyD3D11GfxDevice* a_pDevice, sGfxSamplerDesc a_sDesc, 
													 ID3D11SamplerState* a_pBaseState);
};