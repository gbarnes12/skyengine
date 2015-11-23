#include "stdafx.h"
#include "skyGfxDebugTypes.h"
#include "skyGfxDebugDrawManager.h"


skyResult skyGfxDebugDrawManager::Initialize()
{
	skyResult hr;
	sGfxShaderDesc sPixelShaderDesc;
	sGfxShaderDesc sVertexShaderDesc;

	SKY_ZERO_MEM(&sPixelShaderDesc, sizeof(sGfxShaderDesc));
	SKY_ZERO_MEM(&sVertexShaderDesc, sizeof(sGfxShaderDesc));

	sPixelShaderDesc.m_eMode = eLoadMode_FromMemory;
	sPixelShaderDesc.m_eType = eGfxShaderType_Pixel;
	sPixelShaderDesc.m_sFileName = "debug_ps.hlsl";

	sVertexShaderDesc.m_eMode = eLoadMode_FromMemory;
	sVertexShaderDesc.m_eType = eGfxShaderType_Vertex;
	sVertexShaderDesc.m_sFileName = "debug_vs.hlsl";

	sGfxInputElementDesc arrLayout[] = {
		{"POSITION", 0, eGfxTextureFormat_R32G32B32_FLOAT, 0, skyGfxAppendAlignedElement, eGfxInputClassification_PerVertexData, 0},
		{"COLOR", 0, eGfxTextureFormat_R32G32B32A32_FLOAT, 0, skyGfxAppendAlignedElement, eGfxInputClassification_PerVertexData, 0}
	};

	sVertexShaderDesc.m_pLayout = &arrLayout[0];
	sVertexShaderDesc.m_u32ElementCount = 2;

	// load the shader via resource system
	SKY_VR(skyShaderUtils::Load("debug_ps.hlsl", &m_pPixelShader, sPixelShaderDesc));
	SKY_VR(skyShaderUtils::Load("debug_vs.hlsl", &m_pVertexShader, sVertexShaderDesc));
	m_pPixelShader->AddRef();
	m_pVertexShader->AddRef();


	// request it immediately!
	SKY_VR(skyShaderUtils::Request(m_pPixelShader, eResourceRequestMode_Immediate));
	SKY_VR(skyShaderUtils::Request(m_pVertexShader, eResourceRequestMode_Immediate));

	return SKY_OK;
}

skyResult skyGfxDebugDrawManager::Shutdown()
{
	SKY_RELEASE(m_pPixelShader);
	SKY_RELEASE(m_pVertexShader);
	return SKY_OK;
}

skyVoid skyGfxDebugDrawManager::Prepare()
{
	if(m_pVertexShader && m_pPixelShader)
	{
		m_pVertexShader->Execute();
		m_pPixelShader->Execute();
	}
}


skyResult skyGfxDebugDrawManager::AddLine ( sGfxVector4& a_sStart, sGfxVector4& a_sEnd, sGfxColor& a_sColor)
{
	skyResult hr;
	skyGfxDebugLineObject* pObject = nullptr;
	SKY_VR(skyGfxDebugLineObject::Spawn(a_sStart, a_sEnd, a_sColor, m_pVertexShader->GetShader(), &pObject));

	if(!pObject)
		return SKY_ERROR;

	// push object back onto render queue!
	this->m_arrObjects.push_back(pObject);
	
	return SKY_OK;
}


skyResult skyGfxDebugDrawManager::AddTriangle ( sGfxVector4& a_sPosition, sGfxColor& a_sColor)
{
	skyResult hr;
	skyGfxDebugTriangleObject* pObject = nullptr;
	SKY_VR(skyGfxDebugTriangleObject::Spawn(a_sPosition, a_sColor, m_pVertexShader->GetShader(), &pObject));

	if(!pObject)
		return SKY_ERROR;

	// push object back onto render queue!
	this->m_arrObjects.push_back(pObject);
	
	return SKY_OK;
}

skyVoid skyGfxDebugDrawManager::ClearObjects()
{
	for(skyUInt i = 0; i < m_arrObjects.size(); i++)
		SKY_SAFE_DELETE(m_arrObjects[i]);

	m_arrObjects.clear();
}