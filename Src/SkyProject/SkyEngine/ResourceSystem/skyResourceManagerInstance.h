#pragma once 

#include "inc_resource.h"
#include "Loaders\skyImageResourceLoader.h"
#include "Loaders\skyShaderResourceLoader.h"
#include "Loaders\skyMeshResourceLoader.h"
#include "Loaders\skyMaterialResourceLoader.h"
#include "Loaders\skyEffectResourceLoader.h"
#include "Loaders\skyGameObjectPrefabResourceLoader.h"

class skyResourceManagerInstance
{
public:
	skyResult skyResourceManagerInstance::Initialize(skyUInt a_u32Size);
	skyResult skyResourceManagerInstance::Shutdown();
public:
	skyResult skyResourceManagerInstance::Load ( skyString a_strFile, skyIResource** a_pResource );
	skyResult skyResourceManagerInstance::Request ( skyIResource* a_pResource, eResourceRequestMode a_eMode );
	skyResult skyResourceManagerInstance::CacheOut ( skyIResource* a_pResource );
	skyResult skyResourceManagerInstance::Create ( sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource  );
private:
	skyResourceSystem m_System;
	skyImageResourceLoader m_ImageLoader;
	skyShaderResourceLoader m_ShaderLoader;
	skyMeshResourceLoader m_MeshLoader;
	skyMaterialResourceLoader m_MaterialLoader;
	skyEffectResourceLoader m_EffectLoader;
	skyGameObjectPrefabResourceLoader m_GoPrefabLoader;
};