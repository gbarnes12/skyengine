#include "stdafx.h"
#include "skyImageUtils.h"
#include "skyImageResource.h"

skyResult skyImageResource::Spawn (sResourceInfo& a_sInfo, skyImageResource** a_pResource)
{
	skyImageResource* pResource = SKY_NEW skyImageResource();
	pResource->AttachResourceInfo(a_sInfo);
	*a_pResource = pResource;

	return SKY_OK;
}

skyResult skyImageResource::Spawn (sIResourceCreateDesc* a_sDesc, skyImageResource** a_pResource)
{
	skyImageResource* pResource = SKY_NEW skyImageResource();
	sImageResourceCreateDesc* pDesc = static_cast<sImageResourceCreateDesc*>(a_sDesc);
	pResource->m_sDesc = pDesc->m_sTextureDesc;
	*a_pResource = pResource;

	return SKY_OK;
}

skyImageResource::~skyImageResource()
{
}

skyResult skyImageResource::CreateTexture()
{
	skyResult hr;
	SKY_VR(skyGfxManager::CreateTexture(&m_pInstance, m_sDesc));
	return SKY_OK;
}
 
skyResult skyImageResource::OnRequestRawData(sIOMemBlob& a_rMemBlob)
{
	OnCacheOut ();

	skyResult hr;
	skyAnsiStr pBuffer = skyGetDataFromBlob<skyAnsiStr>(a_rMemBlob);
	skyString m_sFileName = ""; 

	m_sDesc.m_sBlob = &a_rMemBlob;
	SKY_VR_FAIL(skyGfxManager::CreateTexture(&m_pInstance, m_sDesc));
	m_sFileName = m_sDesc.m_sFileName;
	m_sDesc = m_pInstance->GetDesc();
	m_sDesc.m_sFileName = m_sFileName;

	this->m_u32Width = m_sDesc.m_uiWidth;
	this->m_u32Height = m_sDesc.m_uiHeight;

	return SKY_OK;
FAILED:	
	SKY_SAFE_DELETE_ARRAY(pBuffer);
	return SKY_ERROR;
}

skyResult skyImageResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob)
{
	return SKY_OK;
}

skyResult skyImageResource::OnCacheOut ()
{
	SKY_SAFE_DELETE(m_pInstance);
	return SKY_OK;
}