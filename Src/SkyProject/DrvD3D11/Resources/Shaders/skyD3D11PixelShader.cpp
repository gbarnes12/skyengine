#include "stdafx.h"
#include "skyD3D11PixelShader.h"


skyResult skyD3D11PixelShader::Spawn ( eLoadMode a_sLoadMode,  skyD3D11GfxDevice* a_pDevice, sIOMemBlob* a_sBlob, std::string& a_strFileName, skyD3D11PixelShader** a_pShader)
{
	skyD3D11PixelShader* l_pShader = nullptr;
	ID3D11PixelShader* l_pBaseShader = nullptr;

	ID3DBlob* pBlob = nullptr; 
	ID3DBlob* pErrorBlob = nullptr; 

	/*D3DCreateBlob(a_sBlob.m_uiBufferSize, &pBlob);
	skyAnsiStr pContent = skyGetDataFromBlob<skyAnsiStr>(a_sBlob);
	memcpy(pBlob->GetBufferPointer(), pContent, a_sBlob.m_uiBufferSize);*/
	
	skyAnsiStr pContent = skyGetDataFromBlob<skyAnsiStr>(*a_sBlob);
	if ( FAILED(D3DX11CompileFromMemory((char*)pContent, a_sBlob->m_uiBufferSize, a_strFileName.c_str()
		, NULL, NULL, "main", "ps_5_0", NULL, NULL, NULL, &pBlob, &pErrorBlob, NULL)) ) 
	{
			std::cout << (char*)pErrorBlob->GetBufferPointer();
		return SKY_ERROR;
	}

	if ( FAILED(a_pDevice->m_pDevice->CreatePixelShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), 0, &l_pBaseShader)) )
		return SKY_ERROR;

	SKY_RELEASE(pBlob);

	*a_pShader = SKY_NEW skyD3D11PixelShader(a_pDevice, l_pBaseShader);


	return SKY_OK;
}

skyD3D11PixelShader::~skyD3D11PixelShader() 
 {
	 SKY_RELEASE(m_pBaseShader);
 }

 skyVoid skyD3D11PixelShader::Set ( skyVoid ) 
 {
	 m_pDevice->m_pContext->PSSetShader(this->m_pBaseShader, 0, 0);
 }

 skyVoid skyD3D11PixelShader::Unset ( skyVoid ) 
 {

 }

 skyVoid skyD3D11PixelShader::Compile ( skyVoid ) 
 {
	 	 SKY_UNTESTED_METHOD("not implemented!");
 }

skyD3D11PixelShader::skyD3D11PixelShader( skyD3D11GfxDevice* a_pDevice, ID3D11PixelShader* a_pBaseShader) 
	: m_pBaseShader(a_pBaseShader)
	, skyD3D11Resource(a_pDevice)
 {
 }