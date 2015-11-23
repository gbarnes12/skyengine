#pragma once

using namespace System;
using namespace std;


#include "..\Utils\clr_scoped_ptr.h"

class skyGraphicsDevice;
class skyIRenderer;

namespace Sky { namespace NetEngine { namespace Components { namespace Rendering {

	using namespace Utils;

	public ref class D3D11Renderer
	{
	public:
		static skyBool D3D11Renderer::Spawn ( skyInt a_pWindow, skyUInt a_iClientWidth, skyUInt a_iClientHeight,  D3D11Renderer^% pRenderer );
		D3D11Renderer::~D3D11Renderer();
		
	private:
		clr_scoped_ptr<shared_ptr<skyIRenderer>> m_pRenderer;

		D3D11Renderer::D3D11Renderer ( shared_ptr<skyIRenderer>& a_pRenderer );
	};

}}}}
