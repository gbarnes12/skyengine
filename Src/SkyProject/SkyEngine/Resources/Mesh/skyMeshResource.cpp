#include "stdafx.h"
#include "skyMeshUtils.h"
#include "skySubmeshResource.h"
#include "skyMeshResource.h"

skyResult skyMeshResource::Spawn (sResourceInfo& a_sInfo, skyMeshResource** a_pResource)
{
	skyMeshResource* pResource = SKY_NEW skyMeshResource();
	pResource->AttachResourceInfo(a_sInfo);
	*a_pResource = pResource;

	return SKY_OK;
}

skyResult skyMeshResource::Spawn (sIResourceCreateDesc* a_sDesc, skyMeshResource** a_pResource)
{
	skyMeshResource* pResource = SKY_NEW skyMeshResource();
	//sImageResourceCreateDesc* pDesc = static_cast<sImageResourceCreateDesc*>(a_sDesc);
	//pResource->m_sDesc = pDesc->m_sTextureDesc;
	*a_pResource = pResource;

	return SKY_OK;
}

skyMeshResource::~skyMeshResource()
{
}
 
SKY_TODO("Implement material handling");
skyResult skyMeshResource::OnRequestRawData(sIOMemBlob& a_rMemBlob)
{
	OnCacheOut();

	sGfxShaderDesc sPixelShaderDesc;
	sGfxShaderDesc sVertexShaderDesc;

	skyAnsiStr pContent = skyGetDataFromBlob<skyAnsiStr>(a_rMemBlob);
	rapidjson::Document mDocument;
    mDocument.Parse<0>(pContent);

	if(mDocument.HasParseError())
	{
		SKY_PRINT_CONSOLE("skyMesh", "Couldn't load mesh file.", 0x0F);
		SKY_WARNING(0, "skyMesh: Couldn't load mesh file. ");
		SKY_SAFE_DELETE_ARRAY(pContent);
		return SKY_ERROR;
	}

	if(!mDocument.IsObject())
	{
		SKY_PRINT_CONSOLE("skyMesh", "Couldn't load mesh file.", 0x0F);
		SKY_WARNING(0, "skyMesh: Couldn't load mesh file. ");
		SKY_SAFE_DELETE_ARRAY(pContent);
		return SKY_ERROR;
	}

	if(!mDocument["Name"].IsString())
	{
		SKY_PRINT_CONSOLE("skyMesh", "Couldn't load mesh file. Name is no string type.", 0x0F);
		SKY_WARNING(0, "skyMesh: Couldn't load mesh file. Name is no string type. ");
		SKY_SAFE_DELETE_ARRAY(pContent);
		return SKY_ERROR;
	}

	if(!mDocument["Material"].IsObject())
	{
		SKY_PRINT_CONSOLE("skyMesh", "Couldn't find any fallback material on mesh object thus it can't be loaded.", 0x0F);
		SKY_WARNING(0, "skyMesh: Couldn't find any fallback material on mesh object thus it can't be loaded. ");
		SKY_SAFE_DELETE_ARRAY(pContent);
		return SKY_ERROR;
	}

	this->m_strName = mDocument["Name"].GetString(); 

	// Load fallback material!
	skyString matName = mDocument["Material"]["File"].GetString();
	
	skyResult hr;
	skyMaterialResource* pMaterial = nullptr;
	SKY_VR(skyMaterialUtils::Load(matName, &pMaterial));
	SKY_VR_FAIL(skyMaterialUtils::Request(pMaterial, eResourceRequestMode_Immediate));
	pMaterial->AddRef();

	if(!mDocument["Meshes"].IsArray())
	{
		SKY_PRINT_CONSOLE("skyMesh", "Couldn't find any meshes thus the model is useless", 0x0F);
		SKY_WARNING(0, "skyMesh: Couldn't find any meshes thus the model is useless. ");
		SKY_RELEASE(pMaterial);
		return SKY_ERROR;
	}


	const rapidjson::Value& mMeshesNode = mDocument["Meshes"];

	for(skyUInt i = 0; i < mMeshesNode.Size(); i++)
	{
		const rapidjson::Value& node = mMeshesNode[i];

		if(!node["Name"].IsString())
		{
			SKY_PRINT_CONSOLE("skyMesh", "Couldn't find any name on mesh with index: " + i, 0x0F);
			SKY_WARNING(0, "skyMesh: Couldn't find any name on mesh with index: " + i);
			continue;
		}

		if(!node["Vertices"].IsInt())
		{
			SKY_PRINT_CONSOLE("skyMesh", "Couldn't find any name on mesh with index: " + i, 0x0F);
			SKY_WARNING(0, "skyMesh: Couldn't find any name on mesh with index: " + i);
			continue;
		}

		if(!node["Faces"].IsArray())
		{
			SKY_PRINT_CONSOLE("skyMesh", "Couldn't find any faces on mesh with index: " + i, 0x0F);
			SKY_WARNING(0, "skyMesh: Couldn't find any faces on mesh with index: " + i);
			continue;
		}


		skyUInt u32NumVertices = node["Vertices"].GetInt();
		const rapidjson::Value& vFacesNode =  node["Faces"];
		skyString meshName = node["Name"].GetString();
		skyUInt vertNum = 0;
		sGfxStaticVertex* arrVertices = SKY_NEW sGfxStaticVertex[u32NumVertices];

		for(skyUInt x = 0; x < vFacesNode.Size(); ++x)
		{
			const rapidjson::Value& face = vFacesNode[x];
			if(!face.IsArray())
				break;
			
			for(skyUInt y = 0; y < face.Size(); y++)
			{
				const rapidjson::Value&  mVertexNode = face[y];
				if(!mVertexNode["Position"].IsArray())	
					break;

				if(!mVertexNode["UV"].IsArray())	
					break;

				if(!mVertexNode["Normal"].IsArray())	
					break;

				const rapidjson::Value&  mPosition = mVertexNode["Position"];
				rapidjson::SizeType t = 0;
				arrVertices[vertNum].m_sPosition.x = (float)mPosition[t].GetDouble();
				arrVertices[vertNum].m_sPosition.y = (float)mPosition[++t].GetDouble();
				arrVertices[vertNum].m_sPosition.z = (float)mPosition[++t].GetDouble();

				t = 0;
				const rapidjson::Value&  mUV = mVertexNode["UV"];
				arrVertices[vertNum].m_sUV.x = (float)mUV[t].GetDouble();
				arrVertices[vertNum].m_sUV.y = (float)mUV[++t].GetDouble();

				t = 0;
				const rapidjson::Value& mNormal = mVertexNode["Normal"];
				arrVertices[vertNum].m_sNormal.x = (float)mNormal[t].GetDouble();
				arrVertices[vertNum].m_sNormal.y = (float)mNormal[++t].GetDouble();
				arrVertices[vertNum].m_sNormal.z = (float)mNormal[++t].GetDouble();
				vertNum++;
			}
		}

		skyMaterialResource* pMaterialSubmesh = nullptr;
		// load material!
		if(node["Material"].IsObject())
		{
			const rapidjson::Value&  mMaterial = node["Material"];
			if(mMaterial["File"].IsString())
			{
				if(skyMaterialUtils::Load(mMaterial["File"].GetString(), &pMaterialSubmesh) == SKY_OK)
				{
					pMaterialSubmesh->AddRef();
					skyResult hr = skyMaterialUtils::Request(pMaterialSubmesh, eResourceRequestMode_Immediate);

					if(hr == SKY_OK) {
						pMaterialSubmesh->Modify(mMaterial);
						
					} else {
						SKY_RELEASE(pMaterialSubmesh);
					}
				}
			}
		}

		skySubmeshResource* pSubmeshResource = nullptr;
		if(skySubmeshResource::Spawn(meshName, &pSubmeshResource) != SKY_OK)
		{
			SKY_SAFE_DELETE_ARRAY(arrVertices);
			SKY_RELEASE(pMaterialSubmesh)
			SKY_RELEASE(pSubmeshResource);
			continue;
		}

		if(pMaterialSubmesh)
			pSubmeshResource->SetMaterial(pMaterialSubmesh);
		else
			pSubmeshResource->SetMaterial(pMaterial);

		skyIGfxVertexBuffer* pVertexBuffer = nullptr;
		sGfxVertexDesc sVertexDesc;
		SKY_ZERO_MEM(&sVertexDesc, sizeof(sGfxVertexDesc));
		sVertexDesc.m_eUsage = eGfxUsage_Dynamic;
		sVertexDesc.m_eCPUAccess = eGfxCpuAccessFlags_Write;
		sVertexDesc.m_uiCount = u32NumVertices;
		sVertexDesc.m_uiSize = sizeof(sGfxStaticVertex);

		if(skyGfxManager::CreateVertexBuffer(&pVertexBuffer, sVertexDesc) != SKY_OK)
		{
			SKY_SAFE_DELETE_ARRAY(arrVertices);
			SKY_RELEASE(pSubmeshResource);
			continue;
		}

		// copy vertices to the vertex buffer!
		sGfxLockedBuffer sLockedBuffer;
		SKY_ZERO_MEM(&sLockedBuffer, sizeof(sGfxLockedBuffer));
		pVertexBuffer->Lock(eGfxMapType_WriteNoOverwrite, eGfxMapFlag_None, &sLockedBuffer);
		memcpy(sLockedBuffer.m_pData, arrVertices, sizeof(sGfxStaticVertex) * u32NumVertices); 
		pVertexBuffer->Unlock(sLockedBuffer.m_uiSubresource);
		pVertexBuffer->SetStride(sizeof(sGfxStaticVertex));
		pSubmeshResource->GetVisual()->SetVertices(pVertexBuffer);
		pSubmeshResource->SetParent(this);
		SKY_RELEASE(pMaterialSubmesh);
		pSubmeshResource->AddRef();
		this->m_arrMeshes.push_back(pSubmeshResource);
		SKY_SAFE_DELETE_ARRAY(arrVertices);
	}

	SKY_SAFE_DELETE_ARRAY(pContent);

	SKY_TODO("Refactor this into the create effect method!");


	SKY_ZERO_MEM(&sPixelShaderDesc, sizeof(sGfxShaderDesc));
	SKY_ZERO_MEM(&sVertexShaderDesc, sizeof(sGfxShaderDesc));

	sPixelShaderDesc.m_eMode = eLoadMode_FromMemory;
	sPixelShaderDesc.m_eType = eGfxShaderType_Pixel;
	sPixelShaderDesc.m_sFileName = "default_static_ps.hlsl";

	sVertexShaderDesc.m_eMode = eLoadMode_FromMemory;
	sVertexShaderDesc.m_eType = eGfxShaderType_Vertex;
	sVertexShaderDesc.m_sFileName = "default_static_vs.hlsl";

	sGfxInputElementDesc arrLayout[] = {
		{"POSITION", 0, eGfxTextureFormat_R32G32B32_FLOAT, 0, skyGfxAppendAlignedElement, eGfxInputClassification_PerVertexData, 0},
		{"NORMAL", 0, eGfxTextureFormat_R32G32B32_FLOAT, 0, skyGfxAppendAlignedElement, eGfxInputClassification_PerVertexData, 0},
		{"TEXCOORD", 0, eGfxTextureFormat_R32G32_FLOAT, 0, skyGfxAppendAlignedElement, eGfxInputClassification_PerVertexData, 0}
	};

	sVertexShaderDesc.m_pLayout = &arrLayout[0];
	sVertexShaderDesc.m_u32ElementCount = 3;

	SKY_RELEASE(pMaterial);
	
	// load the effect
	SKY_VR_FAIL(skyShaderUtils::CreateEffect(sVertexShaderDesc, sPixelShaderDesc, &m_pEffect));
	m_pEffect->AddRef();
	return SKY_OK;
FAILED:
	OnCacheOut();
	SKY_RELEASE(pMaterial);
	return SKY_ERROR;
}

skyResult skyMeshResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob)
{
	return SKY_OK;
}

skyResult skyMeshResource::OnCacheOut ()
{
	for(skyUInt i = 0; i < m_arrMeshes.size(); i++)
	{
		SKY_RELEASE(m_arrMeshes[i]);
	}

	m_arrMeshes.clear();

	SKY_RELEASE(m_pEffect);
	return SKY_OK;
}

skyVoid skyMeshResource::Draw ()
{
	for(skyUInt i = 0; i < m_arrMeshes.size(); i++)
	{
		skySubmeshResource* pMesh = this->m_arrMeshes[i];
		SKY_SUBMIT_RENDEROBJ(eGfxRenderSortId_Static, NULL, skySubmeshResource::RenderStatic, pMesh);
	}
}