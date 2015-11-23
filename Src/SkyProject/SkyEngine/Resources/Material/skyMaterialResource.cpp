#include "stdafx.h"
#include "skyMaterialUtils.h"
#include "skyMaterialResource.h"

skyResult skyMaterialResource::Spawn (sResourceInfo& a_sInfo, skyMaterialResource** a_pResource)
{
	skyMaterialResource* pResource = SKY_NEW skyMaterialResource();
	pResource->AttachResourceInfo(a_sInfo);
	*a_pResource = pResource;

	return SKY_OK;
}

skyResult skyMaterialResource::Spawn (skyMaterialResource** a_pResource)
{
	skyMaterialResource* pResource = SKY_NEW skyMaterialResource();
	*a_pResource = pResource;

	return SKY_OK;
}

skyMaterialResource::~skyMaterialResource()
{
}

skyVoid skyMaterialResource::SetDiffuseTexture(skyImageResource* a_pResource)
{
	SKY_RELEASE(m_pDiffuseTexture);
	m_pDiffuseTexture = a_pResource;

	if(m_pDiffuseTexture)
		m_pDiffuseTexture->AddRef();
}

skyResult skyMaterialResource::OnRequestRawData(sIOMemBlob& a_rMemBlob)
{
	OnCacheOut ();
	skyAnsiStr pContent = skyGetDataFromBlob<skyAnsiStr>(a_rMemBlob);
	if(!pContent)
		return SKY_ERROR;

	rapidjson::Document mDocument;
    mDocument.Parse<0>(pContent);

	if(mDocument.HasParseError())
	{
		SKY_PRINT_CONSOLE("skyMaterialResource", "Couldn't load material file [ " + this->m_strFileName + " ].", 0x0F);
		SKY_WARNING(0, "skyMaterialResource: Couldn't load material file [ " + this->m_strFileName + " ].");

		return SKY_ERROR;
	}

	if(!mDocument["Name"].IsString())
	{
		SKY_PRINT_CONSOLE("skyMaterialResource", "Material[ " + this->m_strFileName + " ] has no name tag.", 0x0F);
		SKY_WARNING(0, "skyMaterialResource: Material[ " + this->m_strFileName + " ] has no name tag.");

		return SKY_ERROR;
	}

	const rapidjson::Value& mParameter = mDocument["Parameters"];
	if(!mParameter.IsObject())
	{
		SKY_PRINT_CONSOLE("skyMaterialResource", "Material[ " + this->m_strFileName + " ] has no parameter tag.", 0x0F);
		SKY_WARNING(0, "skyMaterialResource: Material[ " + this->m_strFileName + " ] has no parameter tag.");

		return SKY_ERROR;
	}

	skyUInt i = 0;
	// ------------------------------------------------
	// Set Diffuse
	// ------------------------------------------------
	if(!mParameter["Diffuse"].IsObject())
	{
		SKY_PRINT_CONSOLE("skyMaterialResource", "Material[ " + this->m_strFileName + " ] has no diffuse tag.", 0x0F);
		SKY_WARNING(0, "skyMaterialResource: Material[ " + this->m_strFileName + " ] has no diffuse tag.");

		return SKY_ERROR;
	}

	
	// SET COLOR!
	if(!mParameter["Diffuse"]["Color"].IsArray()) 
	{
		SKY_PRINT_CONSOLE("skyMaterialResource", "Material[ " + this->m_strFileName + " ] has no diffuse color tag.", 0x0F);
		SKY_WARNING(0, "skyMaterialResource: Material[ " + this->m_strFileName + " ] has no diffuse  color tag.");
		return SKY_ERROR;
	}

	const rapidjson::Value& diffuseColorNode = mParameter["Diffuse"]["Color"];
	if(diffuseColorNode.Size() < 4)
		return SKY_ERROR;

	i = 0;
	this->m_sDiffuseColor = skyColor((float)diffuseColorNode[i].GetDouble(), (float)diffuseColorNode[++i].GetDouble(), 
										(float)diffuseColorNode[++i].GetDouble(), (float)diffuseColorNode[++i].GetDouble());

	// SET DIFFUSE MAP!
	if(!mParameter["Diffuse"]["Texture"].IsObject())
		return SKY_ERROR;

	if(!mParameter["Diffuse"]["Texture"]["File"].IsString())
		return SKY_ERROR;

	const rapidjson::Value& diffuseTextureNode = mParameter["Diffuse"]["Texture"]["File"];

	// Set Intensity
	if(!mParameter["Diffuse"]["Intensity"].IsDouble())
		return SKY_ERROR;

	this->m_fDiffuseIntensity = (float)mParameter["Diffuse"]["Intensity"].GetDouble();


	// ------------------------------------------------
	// Set Specular
	// ------------------------------------------------
	if(!mParameter["Specular"].IsObject())
		return SKY_ERROR;

	// SET COLOR!
	if(!mParameter["Specular"]["Color"].IsArray())
		return SKY_ERROR;

	const rapidjson::Value& specularColorNode = mParameter["Specular"]["Color"];
	if(specularColorNode.Size() < 4)
		return SKY_ERROR;

	i = 0;
	this->m_sSpecularColor = skyColor((float)specularColorNode[i].GetDouble(), (float)specularColorNode[++i].GetDouble(), 
							(float)specularColorNode[++i].GetDouble(), (float)specularColorNode[++i].GetDouble());

	// Set Intensity
	if(!mParameter["Specular"]["Intensity"].IsDouble())
		return SKY_ERROR;

	this->m_fSpecularIntensity = (float)mParameter["Specular"]["Intensity"].GetDouble();

	// ------------------------------------------------
	// Set Ambient
	// ------------------------------------------------
	if(!mParameter["Ambient"].IsObject())
		return SKY_ERROR;

	// Set Intensity
	if(!mParameter["Ambient"]["Intensity"].IsDouble())
		return SKY_ERROR;

	this->m_fAmbientIntensity = (float)mParameter["Ambient"]["Intensity"].GetDouble();

	// load constant buffer
	skyResult hr;
	sGfxConstantDesc sDesc;
	SKY_ZERO_MEM(&sDesc, sizeof(sGfxConstantDesc));
	sDesc.m_eUsage = eGfxUsage_Dynamic;
	sDesc.m_eBindFlags = eGfxBindFlags_ConstantBuffer;
	sDesc.m_eCPUAccess = eGfxCpuAccessFlags_Write;
	sDesc.m_uiCount = 1;
	sDesc.m_uiSize = sizeof(sGfxMaterialBuffer);

	SKY_VR(skyGfxManager::CreateConstantBuffer(&m_pPerObject, sDesc));

	sGfxLockedBuffer mLockedBuffer;
	SKY_ZERO_MEM(&mLockedBuffer, sizeof(sGfxLockedBuffer));
	SKY_VR_FAIL(m_pPerObject->Lock(eGfxMapType_WriteDiscard, eGfxMapFlag_None, &mLockedBuffer));

	sGfxMaterialBuffer* pMaterialBuffer = (sGfxMaterialBuffer*)mLockedBuffer.m_pData;
	pMaterialBuffer->m_fAmbientIntensity = m_fAmbientIntensity;
	pMaterialBuffer->m_fDiffuseIntensity = m_fDiffuseIntensity;
	pMaterialBuffer->m_fSpecularIntensity = m_fSpecularIntensity;
	pMaterialBuffer->m_sAmbientColor = m_sAmbientColor;
	pMaterialBuffer->m_sDiffuseColor = m_sDiffuseColor;
	pMaterialBuffer->m_sSpecularColor = m_sSpecularColor;
	pMaterialBuffer->m_u32Shinieness = m_u32Shinieness;

	m_pPerObject->Unlock(mLockedBuffer.m_uiSubresource);

	// load the texture
	SKY_VR_FAIL(skyImageUtils::Load(diffuseTextureNode.GetString(), &m_pDiffuseTexture));
	SKY_VR_FAIL(skyImageUtils::Request(m_pDiffuseTexture, eResourceRequestMode_Immediate));

	return SKY_OK;
FAILED:
	SKY_SAFE_DELETE(m_pPerObject);
	return SKY_ERROR;
}

skyResult skyMaterialResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob)
{
	return SKY_OK;
}

skyResult skyMaterialResource::OnCacheOut ()
{
	SKY_RELEASE(m_pDiffuseTexture);
	SKY_SAFE_DELETE(m_pPerObject);
	return SKY_OK;
}

skyVoid skyMaterialResource::Modify ( const rapidjson::Value& a_Data )
{
	const rapidjson::Value& data = a_Data;
	if(!data["Parameters"].IsObject())
		return;

	skyUInt i = 0;
	skyImageResource* pImageResource = nullptr;
	// ------------------------------------------------
	// Set Diffuse
	// ------------------------------------------------
	if(data["Parameters"]["Diffuse"].IsObject())
	{
		// SET COLOR!
		if(data["Parameters"]["Diffuse"]["Color"].IsArray())
		{
			i = 0;
			const rapidjson::Value& diffuseColorNode = data["Parameters"]["Diffuse"]["Color"];
			if(diffuseColorNode.Size() == 4) {
				this->m_sDiffuseColor = skyColor((float)diffuseColorNode[i].GetDouble(), (float)diffuseColorNode[++i].GetDouble(), 
									(float)diffuseColorNode[++i].GetDouble(), (float)diffuseColorNode[++i].GetDouble());
			}
		}
		
		// SET TEXTURE
		if(data["Parameters"]["Diffuse"]["Texture"].IsObject()) 
		{
			if(data["Parameters"]["Diffuse"]["Texture"]["File"].IsString())
			{
				const rapidjson::Value&  diffuseTextureNode = data["Parameters"]["Diffuse"]["Texture"]["File"];
				skyResult hr;

				SKY_VR_FAIL(skyImageUtils::Load(diffuseTextureNode.GetString(), &pImageResource));
				SKY_VR_FAIL(skyImageUtils::Request(pImageResource, eResourceRequestMode_Immediate));

				SKY_RELEASE(m_pDiffuseTexture);
				m_pDiffuseTexture = pImageResource;
			}
		}

		// Set Intensity
		if(data["Parameters"]["Diffuse"]["Intensity"].IsDouble())
		{
			this->m_fDiffuseIntensity = (float)data["Parameters"]["Diffuse"]["Intensity"].GetDouble();
		}
	}


	// ------------------------------------------------
	// Set Specular
	// ------------------------------------------------
	if(data["Parameters"]["Specular"].IsObject())
	{
		// SET COLOR!
		if(data["Parameters"]["Specular"]["Color"].IsArray())
		{
			i = 0;
			const rapidjson::Value&  specularColorNode = data["Parameters"]["Specular"]["Color"];
			if(specularColorNode.Size() == 4) {
				this->m_sSpecularColor = skyColor((float)specularColorNode[i].GetDouble(), (float)specularColorNode[++i].GetDouble(), 
									(float)specularColorNode[++i].GetDouble(), (float)specularColorNode[++i].GetDouble());
			}
		}

		// Set Intensity
		if(data["Parameters"]["Specular"]["Intensity"].IsDouble()) 
		{
			this->m_fSpecularIntensity = (float)data["Parameters"]["Specular"]["Intensity"].GetDouble();
		}
	}

	// ------------------------------------------------
	// Set Ambient
	// ------------------------------------------------
	if(data["Parameters"]["Ambient"].IsObject())
	{
		// Set Intensity
		if(data["Parameters"]["Ambient"]["Intensity"].IsDouble())
		{
			this->m_fAmbientIntensity = (float)data["Parameters"]["Ambient"]["Intensity"].GetDouble();
		}
	}

	skyResult hr;
	sGfxLockedBuffer mLockedBuffer;
	SKY_ZERO_MEM(&mLockedBuffer, sizeof(sGfxLockedBuffer));
	SKY_VR_FAIL(m_pPerObject->Lock(eGfxMapType_WriteDiscard, eGfxMapFlag_None, &mLockedBuffer));

	sGfxMaterialBuffer* pMaterialBuffer = (sGfxMaterialBuffer*)mLockedBuffer.m_pData;
	pMaterialBuffer->m_fAmbientIntensity = m_fAmbientIntensity;
	pMaterialBuffer->m_fDiffuseIntensity = m_fDiffuseIntensity;
	pMaterialBuffer->m_fSpecularIntensity = m_fSpecularIntensity;
	pMaterialBuffer->m_sAmbientColor = m_sAmbientColor;
	pMaterialBuffer->m_sDiffuseColor = m_sDiffuseColor;
	pMaterialBuffer->m_sSpecularColor = m_sSpecularColor;
	pMaterialBuffer->m_u32Shinieness = m_u32Shinieness;

	m_pPerObject->Unlock(mLockedBuffer.m_uiSubresource);

	return;
FAILED:
	SKY_SAFE_DELETE(m_pPerObject);
	SKY_RELEASE(pImageResource);
	return;
}

skyVoid skyMaterialResource::Apply ( skyEffectResource* a_pEffect )
{
	if(a_pEffect)
	{
		if(m_pPerObject)
			a_pEffect->SetConstantbuffer(eGfxShaderType_Pixel, 0, m_pPerObject);
		
		if(m_pDiffuseTexture)
			a_pEffect->SetTexture(eGfxShaderType_Pixel, 0, this->m_pDiffuseTexture->GetTexture());

		a_pEffect->Execute();	
	}
}