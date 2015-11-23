#pragma once

class skyD3D11VertexShader
	:public skyIGfxShader, public skyD3D11Resource
{
public:
	static skyResult skyD3D11VertexShader::Spawn ( eLoadMode a_sLoadMode, skyD3D11GfxDevice* a_pDevice, sGfxInputElementDesc* a_sLayout
	, skyUInt a_u32ElementCount, sIOMemBlob* a_sBlob, std::string& a_strFileName, skyD3D11VertexShader** a_pShader);


	skyD3D11VertexShader::~skyD3D11VertexShader();
public:
	virtual eGfxResourceType skyD3D11VertexShader::GetType ( skyVoid ) { return eGfxResourceType_Shader; }
public:
	virtual eGfxShaderType skyD3D11VertexShader::GetShaderType ( skyVoid ) const { return eGfxShaderType_Vertex; }
public:
	virtual skyVoid skyD3D11VertexShader::Set ( skyVoid );
	virtual skyVoid skyD3D11VertexShader::Unset ( skyVoid );
	virtual skyVoid skyD3D11VertexShader::Compile ( skyVoid );
public:
	ID3D11VertexShader* skyD3D11VertexShader::GetBaseShader( skyVoid ) const { return m_pBaseShader; }
private:
	ID3D11VertexShader* m_pBaseShader;
	ID3D11InputLayout* m_pLayout;
	skyString a_cFileName;

	skyD3D11VertexShader::skyD3D11VertexShader( skyD3D11GfxDevice* a_pDevice, ID3D11VertexShader* a_pBaseShader, ID3D11InputLayout* a_pLayout);
};