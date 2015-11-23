#pragma once

class skyRefBaseClass 
{
public:
	skyRefBaseClass::skyRefBaseClass();
	virtual skyRefBaseClass::~skyRefBaseClass();

public:
	skyVoid skyRefBaseClass::AddRef() const;
	skyVoid skyRefBaseClass::Release() const;
	
private:
	mutable skyUInt m_u32RefCount;
}; 