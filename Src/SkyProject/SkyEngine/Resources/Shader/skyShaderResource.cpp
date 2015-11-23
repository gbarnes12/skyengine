#include "stdafx.h"
#include "..\skyResource.h"
#include "skyShaderResource.h"

skyResult skyShaderResource::Spawn (sResourceInfo& a_sInfo, skyShaderResource** a_pResource)
{
	skyShaderResource* pResource = SKY_NEW skyShaderResource();
	pResource->AttachResourceInfo(a_sInfo);
	*a_pResource = pResource;

	return SKY_OK;
}

skyResult skyShaderResource::Spawn (sIResourceCreateDesc* a_sDesc, skyShaderResource** a_pResource)
{
	skyShaderResource* pResource = SKY_NEW skyShaderResource();
	*a_pResource = pResource;

	return SKY_OK;
}

skyShaderResource::~skyShaderResource()
{
}
 
skyResult skyShaderResource::OnRequestRawData(sIOMemBlob& a_rMemBlob)
{
	skyAnsiStr pBuffer = skyGetDataFromBlob<skyAnsiStr>(a_rMemBlob);
	OnCacheOut ();

	if(m_sDesc.m_sFileName == "")
		return SKY_ERROR;

	// set memory blob!
	m_sDesc.m_sBlob = &a_rMemBlob;
	
	skyResult hr;
	SKY_VR(skyGfxManager::CreateShader(&m_pInstance, m_sDesc));

	return SKY_OK;
}

skyResult skyShaderResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob)
{
	return SKY_OK;
}

skyResult skyShaderResource::OnCacheOut ()
{
	SKY_SAFE_DELETE(m_pInstance);
	return SKY_OK;
}

skyVoid skyShaderResource::SetDesc(sGfxShaderDesc& a_sDesc)
{
	m_sDesc = a_sDesc;
}

sGfxShaderDesc* skyShaderResource::GetDesc()
{
	return &m_sDesc;
}

skyVoid skyShaderResource::Execute()
{
	this->m_pInstance->Set();
}