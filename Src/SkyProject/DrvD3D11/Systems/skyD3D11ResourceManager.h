#pragma once

class skyD3D11ResourceManager : skyIGfxResourceManager
{
public:
	static skyResult skyD3D11ResourceManager::Spawn ( skyD3D11ResourceManager** a_pManager);

public:
	virtual skyResult skyIGfxResourceManager::RegisterResource ( skyIGfxResource* a_pResource );
	virtual skyResult skyIGfxResourceManager::UnregisterResource ( skyIGfxResource* a_pResource );
private:
	skyD3D11Resource* m_pHead[eGfxResourceType_Count];

	skyD3D11ResourceManager::skyD3D11ResourceManager();
};