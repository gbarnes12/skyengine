#include "stdafx.h"
#include "skyD3D11VertexShader.h"


skyResult skyD3D11VertexShader::Spawn ( eLoadMode a_sLoadMode,  skyD3D11GfxDevice* a_pDevice, sGfxInputElementDesc a_sLayout[], skyUInt a_u32ElementCount, sIOMemBlob* a_sBlob, std::string& a_strFileName, skyD3D11VertexShader** a_pShader)
{
	ID3D11VertexShader* l_pBaseShader = nullptr;

	
		
	SKY_TODO("Fix the resource stuff we can't load binary shader files... :/");
		
	ID3DBlob* pBlob = nullptr; 
	ID3DBlob* pErrorBlob = nullptr; 
	skyAnsiStr pContent = skyGetDataFromBlob<skyAnsiStr>(*a_sBlob);
	if ( FAILED(D3DX11CompileFromMemory((char*)pContent, a_sBlob->m_uiBufferSize, a_strFileName.c_str()
		, NULL, NULL, "main", "vs_5_0", NULL, NULL, NULL, &pBlob, &pErrorBlob, NULL)) ) 
	{
		std::cout << (char*)pErrorBlob->GetBufferPointer();
		return SKY_ERROR;
	}

	if ( FAILED(a_pDevice->m_pDevice->CreateVertexShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), 0, &l_pBaseShader)) )
		return SKY_ERROR;

	//create input layout
	ID3D11InputLayout* pLayout = nullptr;
	D3D11_INPUT_ELEMENT_DESC* pLayoutDesc = SKY_NEW D3D11_INPUT_ELEMENT_DESC[a_u32ElementCount];

	for(skyUInt i = 0; i < a_u32ElementCount; i++) {
		pLayoutDesc[i].AlignedByteOffset = a_sLayout[i].m_u32AlignedByteOffset;
		pLayoutDesc[i].SemanticIndex = a_sLayout[i].m_u32SemanticIndex;
		pLayoutDesc[i].SemanticName = a_sLayout[i].m_strSemanticName;
		pLayoutDesc[i].InputSlotClass = static_cast<D3D11_INPUT_CLASSIFICATION>(a_sLayout[i].m_eInputSlotClass);
		pLayoutDesc[i].Format = static_cast<DXGI_FORMAT>(a_sLayout[i].m_eFormat);
		pLayoutDesc[i].InputSlot = a_sLayout[i].m_u32InputSlot;
		pLayoutDesc[i].InstanceDataStepRate = a_sLayout[i].m_uiInstanceDataStepRate;
	}

	SKY_TODO("if anything fails clean up the valid instances.. in every class respectively!");
	if ( FAILED(a_pDevice->m_pDevice->CreateInputLayout(pLayoutDesc, a_u32ElementCount, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pLayout)) )
		return SKY_ERROR;

	SKY_SAFE_DELETE_ARRAY(pLayoutDesc);
	SKY_RELEASE(pBlob);

	*a_pShader = SKY_NEW skyD3D11VertexShader(a_pDevice, l_pBaseShader, pLayout);

	return SKY_OK;
}


skyD3D11VertexShader::~skyD3D11VertexShader() 
 {
	 SKY_RELEASE(m_pLayout);
	 SKY_RELEASE(m_pBaseShader);
 }

 skyVoid skyD3D11VertexShader::Set ( skyVoid ) 
 {
	 m_pDevice->m_pContext->VSSetShader(this->m_pBaseShader, 0, 0);
	 m_pDevice->m_pContext->IASetInputLayout(this->m_pLayout);
 }

 skyVoid skyD3D11VertexShader::Unset ( skyVoid ) 
 {
 }

 skyVoid skyD3D11VertexShader::Compile ( skyVoid ) 
 {
	 SKY_UNTESTED_METHOD("not implemented!");
 }


skyD3D11VertexShader::skyD3D11VertexShader( skyD3D11GfxDevice* a_pDevice, ID3D11VertexShader* a_pBaseShader, ID3D11InputLayout* a_pLayout ) 
	: m_pBaseShader(a_pBaseShader)
	, m_pLayout(a_pLayout)
	, skyD3D11Resource(a_pDevice)
 {
 }