#include "stdafx.h"
#include "skyD3D11ResourceManager.h"

skyResult skyD3D11ResourceManager::Spawn ( skyD3D11ResourceManager** a_pManager)
{
	*a_pManager = SKY_NEW skyD3D11ResourceManager();

	return SKY_OK;
}

skyD3D11ResourceManager::skyD3D11ResourceManager()
{
	for(skyUInt i = 0; i < eGfxResourceType_Count; i++)
	{
		m_pHead[i] = nullptr;
	}
}

skyResult skyD3D11ResourceManager::RegisterResource ( skyIGfxResource* a_pResource )
{
	eGfxResourceType type = a_pResource->GetType();
	skyD3D11Resource* pHead = m_pHead[type];

	if(pHead)
	{
		skyD3D11Resource* pElement = static_cast<skyD3D11Resource*>(a_pResource);
		pElement->m_pNext = pHead->m_pNext;
		pHead->m_pNext = pElement->m_pNext;
		return SKY_OK;
	}

	pHead = static_cast<skyD3D11Resource*>(a_pResource);
	return SKY_OK;
}

skyResult skyD3D11ResourceManager::UnregisterResource ( skyIGfxResource* a_pResource )
{
	eGfxResourceType type = a_pResource->GetType();
	skyD3D11Resource* pHead = m_pHead[type];
	skyD3D11Resource* pNext = pHead;
	skyD3D11Resource* pElement = static_cast<skyD3D11Resource*>(a_pResource);

	while(pNext)
	{
		if(pNext == pElement)
		{
			pNext = pElement->m_pNext;
			break;
		}

		pNext = pNext->m_pNext;
	}
	
	return SKY_OK;
}