#pragma once

typedef skyResult (*skyStaticInitCallback)(skyVoid);  


class skyRuntimeClass 
{
public:
	static skyResult skyRuntimeClass::StaticInitialize();
	skyRuntimeClass::skyRuntimeClass() { };
	skyRuntimeClass::~skyRuntimeClass () { };
	skyRuntimeClass::skyRuntimeClass ( size_t a_uiId, skyString a_strName, skyStaticInitCallback a_pCallback );
private:
	skyString m_strName;
	size_t m_uiId;
	skyStaticInitCallback m_pCallback;
private:
	skyRuntimeClass* m_pNext;
private: 
	static skyRuntimeClass* g_pListHead;
};

#define SKY_DEFINE_RUNTIMEC(TYPE) \
	skyRuntimeClass TYPE::thisType( typeid( TYPE ).hash_code() ,  typeid( TYPE ).name(), &TYPE::StaticInitialize ); \
    skyResult TYPE::StaticInitialize() { \
		skySingleton<TYPE>::Instance(); \
		return SKY_OK;\
	}

#define SKY_DECLARE_RUNTIMEC(TYPE) \
	public: \
	static skyRuntimeClass thisType; \
	static skyResult TYPE::StaticInitialize(); 