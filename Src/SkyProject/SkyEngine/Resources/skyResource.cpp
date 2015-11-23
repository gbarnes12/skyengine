#include "stdafx.h"
#include "skyResource.h"

skyResource::skyResource()
	: m_eCurrentState(eResourceState_Created)
{
}

skyResource::~skyResource()
{
	if(m_eCurrentState != eResourceState_CachedOut)
		SKY_PRINT_CONSOLE("memory leak","resource with name " + m_sInfo.m_strFileName + " hasn't been cached out!", 0x01);
}

skyVoid skyResource::AttachResourceInfo(sResourceInfo a_sInfo)
{
	this->m_sInfo = a_sInfo;
}

sResourceInfo& skyResource::GetInfo()
{
	return this->m_sInfo;
}

eResourceState skyResource::GetResourceState() const
{
	return this->m_eCurrentState;
}

skyVoid skyResource::SetResourceState(eResourceState a_eState) 
{
	this->m_eCurrentState = a_eState;
}