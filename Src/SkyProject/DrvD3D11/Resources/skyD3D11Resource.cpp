#include "stdafx.h"
#include "skyD3D11Resource.h"


skyD3D11Resource::~skyD3D11Resource()
{
	this->m_pDevice->m_pResourceManager->UnregisterResource(this);
}

skyD3D11Resource::skyD3D11Resource (skyD3D11GfxDevice* a_pDevice)
{
	this->m_pDevice = a_pDevice;
	this->m_pDevice->m_pResourceManager->RegisterResource(this);
	this->m_pNext = nullptr;
}

eGfxResourceType skyD3D11Resource::GetType ( skyVoid ) 
{ return eGfxResourceType_BaseResource; }