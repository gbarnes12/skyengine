#pragma once

class skyD3D11Resource 
	: skyIGfxResource 
{
	friend class skyD3D11ResourceManager;

public:
	skyD3D11Resource::~skyD3D11Resource();
	virtual eGfxResourceType skyD3D11Resource::GetType ( skyVoid );

protected:
	skyD3D11Resource::skyD3D11Resource (skyD3D11GfxDevice* a_pDevice);

protected:
	skyD3D11GfxDevice* m_pDevice;
private:
	skyD3D11Resource* m_pNext;
}; 