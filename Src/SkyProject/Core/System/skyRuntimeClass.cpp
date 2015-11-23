#include "stdafx.h"
#include "skyRuntimeClass.h"
#include <typeinfo>

//std::map<skyString, skyRuntimeClass*> skyRuntimeClass::g_pListHead;

skyRuntimeClass* skyRuntimeClass::g_pListHead;

skyResult skyRuntimeClass::StaticInitialize()
{
	// for (std::map<skyString, skyRuntimeClass*>::iterator it=g_pListHead.begin(); it!=g_pListHead.end(); ++it)
	//{
		skyRuntimeClass* pNode = g_pListHead;
		while(pNode)
		{
			pNode->m_pCallback();
			pNode = pNode->m_pNext;
		}
	//}

	return SKY_OK;
}


skyRuntimeClass::skyRuntimeClass ( size_t a_uiId, skyString a_strName, skyStaticInitCallback a_pCallback )
	: m_uiId(a_uiId)
	, m_strName(a_strName)
	, m_pCallback ( a_pCallback)
{
	
	skyRuntimeClass* pNode = g_pListHead;
	this->m_pNext = pNode;
	g_pListHead = this;
}