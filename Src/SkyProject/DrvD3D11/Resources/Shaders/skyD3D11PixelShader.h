#pragma once

class skyD3D11PixelShader
	: public skyIGfxShader, public skyD3D11Resource
{
public:
	static skyResult skyD3D11PixelShader::Spawn ( eLoadMode a_sLoadMode,  skyD3D11GfxDevice* a_pDevice, sIOMemBlob* a_sBlob, std::string& a_strFileName, skyD3D11PixelShader** a_pShader);

	skyD3D11PixelShader::~skyD3D11PixelShader();
public:
	virtual eGfxResourceType skyD3D11PixelShader::GetType ( skyVoid ) { return eGfxResourceType_Shader; }
public:
	virtual eGfxShaderType skyD3D11PixelShader::GetShaderType ( skyVoid ) const { return eGfxShaderType_Pixel; }
public:
	virtual skyVoid skyD3D11PixelShader::Set ( skyVoid );
	virtual skyVoid skyD3D11PixelShader::Unset ( skyVoid );
	virtual skyVoid skyD3D11PixelShader::Compile ( skyVoid );
public:
	ID3D11PixelShader* skyD3D11PixelShader::GetBaseShader( skyVoid ) const { return m_pBaseShader; }
private:
	ID3D11PixelShader* m_pBaseShader;
	skyString a_cFileName;

	skyD3D11PixelShader::skyD3D11PixelShader(  skyD3D11GfxDevice* a_pDevice, ID3D11PixelShader* a_pBaseShader);
};