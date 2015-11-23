#pragma once 


class skyModule : public skyIModule
{

public:
	skyModule::~skyModule();

	skyInt skyModule::GetLevel () const;
	skyVoid skyModule::SetLevel ( const skyInt a_iLevel );

	virtual skyResult skyModule::Initialize(); 
	virtual skyResult skyModule::Shutdown(); 

protected:
	skyModule::skyModule();

protected:
	skyInt m_iLevel;
};

#define SKY_DECLARE_MODULE(_MODULE_, _LEVEL_) SKY_DECLARE_RUNTIMEC( _MODULE_ ); protected: friend class skySingleton< _MODULE_ >;_MODULE_() { this->SetLevel(_LEVEL_); skyModuleManager::Instance().Register(this);};  
#define SKY_DEFINE_MODULE(_MODULE_) SKY_DEFINE_RUNTIMEC(_MODULE_)
#define SKY_ENSURE_MODULE(_MODULE_) \
		skySingleton<_MODULE_>::Instance();