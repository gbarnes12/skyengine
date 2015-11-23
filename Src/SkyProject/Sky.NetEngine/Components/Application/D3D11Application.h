#pragma once
//-----------------------------------------------------------------------------
// Include
//-----------------------------------------------------------------------------
#include "..\Utils\clr_scoped_ptr.h"
#include "..\Rendering\D3D11Renderer.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
using namespace System;
using namespace std;
using namespace Sky::NetEngine::Components::Rendering;

//-----------------------------------------------------------------------------
// Forward Declaration
//-----------------------------------------------------------------------------
class skyEditorApplication;


namespace Sky { namespace NetEngine { namespace Components { namespace Application {

	public ref class D3D11Application 
	{
	public:
		static skyBool D3D11Application::Spawn ( skyInt a_pWindow, skyUInt a_iClientWidth, skyUInt a_iClientHeight,  D3D11Application^% pApplication );
		D3D11Application::~D3D11Application();

		D3D11Renderer^ D3D11Application::GetRenderer ( skyVoid );
		skyVoid D3D11Application::Run ( skyVoid );
		skyVoid D3D11Application::Resize ( skyUInt a_iWidth, skyUInt a_iHeight );
	private:
		D3D11Renderer^ m_pManagedRenderer;
		skyInt m_iHWND;
		skyUInt m_uiWidth; 
		skyUInt m_uiHeight;

		D3D11Application::D3D11Application ( skyInt a_pWindow, skyUInt a_iClientWidth, skyUInt a_iClientHeight );
		skyBool D3D11Application::Initialize ( skyVoid );
	};


}}}}