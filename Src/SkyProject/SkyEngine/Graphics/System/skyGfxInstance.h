#pragma once

class skyGfxInstance 
{
public:
	skyGfxInstance::skyGfxInstance();
public:
	skyResult skyGfxInstance::Initialize ( skyVoid );
	skyResult skyGfxInstance::Shutdown ( skyVoid );
public:
	skyIGfxDevice* skyGfxInstance::Device( skyVoid ) const
	{
		return this->m_pDevice;
	}

	skyIWindow* skyGfxInstance::Window ( skyVoid ) const 
	{
		return this->m_pWindow; 
	}

	skyIGfxRenderTarget* skyGfxInstance::BackBufferRT ( skyVoid ) const 
	{
		return this->m_pBackBufferRT;
	}

	skyIGfxTexture* skyGfxInstance::BackBuffer ( skyVoid ) const 
	{
		return this->m_pBackBufferTexture;
	}

	skyIGfxConstantBuffer* skyGfxInstance::ConstantMatrixBuffer ( skyVoid ) const 
	{
		return this->m_pMatrixBuffer;
	}
private:
	skyComPtr<skyIWindow>	m_pWindow;
	skyIGfxSystem*			m_pSystem;
	skyIGfxDevice*			m_pDevice;
	skyIGfxRenderTarget*	m_pBackBufferRT;
	skyIGfxTexture*			m_pBackBufferTexture;
	skyIGfxConstantBuffer*	m_pMatrixBuffer;
};