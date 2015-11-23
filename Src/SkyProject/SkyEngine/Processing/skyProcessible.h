#pragma once 


#define SKY_DECLARE_PROCESSIBLE(CLASS, _LEVEL) \
SKY_DECLARE_PROCESSIBLE_VAR(CLASS, _LEVEL, skyProcess, m_cProcess)

#define SKY_DECLARE_PROCESSIBLE_VAR(CLASS, _LEVEL, NAME, VAR)\
SKY_DECLARE_PROCESSIBLE_CLASS(CLASS, NAME, _LEVEL)\
NAME VAR;

#define SKY_DECLARE_PROCESSIBLE_CLASS(CLASS, NAME, _LEVEL) \
protected: \
class NAME : public skyIProcessible { \
public: \
	 static skyVoid SetEnabled ( const skyBool a_bValue ) { m_bEnabled = a_bValue; } \
	 static skyBool GetEnabled ( skyVoid ) { return m_bEnabled; } \
public: \
	 CLASS::NAME() { SetLevel(_LEVEL); } \
	 skyVoid Register ( CLASS* a_pInstance ); \
	 skyVoid Unregister ( ); \
public: \
	 virtual skyVoid OnProcess(); \
	 virtual skyInt GetLevel () const { return m_iLevel; }\
	 virtual skyVoid SetLevel ( const skyInt a_nLevel ) { m_iLevel = a_nLevel; } \
private: \
   CLASS* m_pInstance; \
   skyInt m_iLevel; \
private: \
   static skyBool m_bEnabled; \
}; 

#define SKY_DEFINE_PROCESSIBLE(CLASS) SKY_DEFINE_PROCESSIBLE_CLASS (CLASS, skyProcess, OnProcess)

#define SKY_DEFINE_PROCESSIBLE_CLASS(CLASS, NAME, FUNC) skyBool CLASS::NAME::m_bEnabled = SKY_TRUE; skyVoid CLASS::NAME::OnProcess () { if(m_pInstance && CLASS::NAME::GetEnabled()) { m_pInstance->FUNC(); } }  skyVoid CLASS::NAME::Register ( CLASS* a_pInstance ) { Unregister(); m_pInstance = a_pInstance; skyProcessManager::Instance().Register(this); } skyVoid CLASS::NAME::Unregister ( ) { m_pInstance = NULL; skyProcessManager::Instance().Unregister(this); }