#pragma once

class skyResource : public skyIResource 
{
public:
	skyResource::skyResource();
	virtual skyResource::~skyResource();

	virtual skyVoid skyResource::AttachResourceInfo(sResourceInfo a_sInfo);
	virtual sResourceInfo& skyResource::GetInfo();
	virtual eResourceState skyResource::GetResourceState() const;
	virtual skyVoid skyResource::SetResourceState(eResourceState a_eState);
protected:
	sResourceInfo m_sInfo;
	eResourceState m_eCurrentState;
};