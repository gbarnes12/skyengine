#pragma once


class skyIProcessible 
{
public:
	virtual skyVoid skyIProcessible::OnProcess		() = 0;
	virtual skyInt skyIProcessible::GetLevel		() const = 0;
	virtual skyVoid skyIProcessible::SetLevel ( const skyInt a_nLevel ) = 0;
};

class skyIModule
{
public:
	virtual skyResult skyIModule::Initialize		() = 0;
	virtual skyResult skyIModule::Shutdown			() = 0;
}; 