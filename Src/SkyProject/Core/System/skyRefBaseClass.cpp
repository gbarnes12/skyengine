#include "stdafx.h"
#include "skyRefBaseClass.h"

skyRefBaseClass::skyRefBaseClass()
	: m_u32RefCount(0) 
{
	
}

skyRefBaseClass::~skyRefBaseClass()
{
	if(m_u32RefCount > 0)
		SKY_PRINT_CONSOLE("Ref Count", "ref count of class to high!", 0x0f);
}

skyVoid skyRefBaseClass::AddRef() const
{ 
	++m_u32RefCount; 
}

skyVoid skyRefBaseClass::Release() const
{
	assert(m_u32RefCount > 0);

	--m_u32RefCount;
	if(m_u32RefCount == 0) 
	{
		delete (skyRefBaseClass *)this;
	}
}

