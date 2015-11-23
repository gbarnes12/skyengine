#pragma once

class skyGfxDebugObject;

class skyGfxDebugDrawManager : public skySingleton<skyGfxDebugDrawManager>
{
	friend class skyDoDebugObjectPass;
public:
	skyResult skyGfxDebugDrawManager::Initialize();
	skyResult skyGfxDebugDrawManager::Shutdown();

	skyVoid skyGfxDebugDrawManager::Prepare();

	// Add Methods
public:
	skyResult skyGfxDebugDrawManager::AddLine ( sGfxVector4& a_sStart, sGfxVector4& a_sEnd, sGfxColor& a_sColor);
	skyResult skyGfxDebugDrawManager::AddTriangle ( sGfxVector4& a_sPosition, sGfxColor& a_sColor);
private:
	std::vector<skyGfxDebugObject*> m_arrObjects;
	skyShaderResource* m_pVertexShader;
	skyShaderResource* m_pPixelShader;

	skyVoid skyGfxDebugDrawManager::ClearObjects();
};

#define SKY_ADD_LINE(_START_, _END_, _COLOR_) \
	skyGfxDebugDrawManager::Instance().AddLine(_START_, _END_, _COLOR_);

#define SKY_ADD_TRIANGLE(_POSITION_, _COLOR_) \
	skyGfxDebugDrawManager::Instance().AddTriangle(_POSITION_, _COLOR_);