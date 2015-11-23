#include "stdafx.h"
#include "skyResourceLoader.h"
#include "Loaders\skyImageResourceLoader.h"
#include "Loaders\skyShaderResourceLoader.h"
#include "Loaders\skyMaterialResourceLoader.h"
#include "Loaders\skyGameObjectPrefabResourceLoader.h"
#include "skyResourceManagerInstance.h"


skyResult skyResourceManagerInstance::Initialize(skyUInt a_u32Size)
{
	skyResult hr;
	SKY_VR(m_System.Initialize(a_u32Size));

	// Register loaders!
	m_System.RegisterLoader(&m_ImageLoader);
	m_System.RegisterLoader(&m_ShaderLoader);
	m_System.RegisterLoader(&m_MeshLoader);
	m_System.RegisterLoader(&m_MaterialLoader);
	m_System.RegisterLoader(&m_EffectLoader);
	m_System.RegisterLoader(&m_GoPrefabLoader);

	return SKY_OK;
}

skyResult skyResourceManagerInstance::Shutdown()
{
	return m_System.Shutdown();
}

skyResult skyResourceManagerInstance::Load ( skyString a_strFile, skyIResource** a_pResource )
{
	return m_System.Load(a_strFile, a_pResource);
}

skyResult skyResourceManagerInstance::Request ( skyIResource* a_pResource, eResourceRequestMode a_eMode )
{
	return m_System.Request(a_pResource, a_eMode);
}

skyResult skyResourceManagerInstance::CacheOut ( skyIResource* a_pResource )
{
	return m_System.CacheOut(a_pResource);
}

skyResult skyResourceManagerInstance::Create ( sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource  )
{
	return m_System.Create(a_sDesc, a_pResource);
}