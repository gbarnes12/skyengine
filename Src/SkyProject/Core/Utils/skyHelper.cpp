//---------------------------------------------------------------------------//
//				___________     __   ___  ___      ___                       //
//				|  _______ \   |  | /  /  \  \    /  /                       //
//				|  |           |  |/  /    \  \  /  /                        //
//				|  |_______    |     /      \  \/  /                         //
//				\_________ \   |     |       \    /                          //
//				  _		 |  |  |  |\  \       |  |                           //
//				 | \_____|  |  |  | \  \      |  |                           //
//				 |__________/  |__|  \__\     |__|  Engine.                  //
//                                                                           //
//---------------------------------------------------------------------------//
//                                                                           //
// Name : skyHelper.cpp                                                      //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// You may find some helpful functions within this source file:             //
///	hardware identifikation, date time functions and so on.                  //
/// </summary>                                                               //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "skyHelper.h"


//-----------------------------------------------------------------------------
//  Name : skyRad2Deg (Function)
/// <summary>
/// Converts radians into degrees
/// </summary>
//-----------------------------------------------------------------------------
float skyRad2Deg(float radians)
{
	return radians * RAD2DEG;
};

//-----------------------------------------------------------------------------
//  Name : skyDeg2Rad (Function)
/// <summary>
/// Converts degrees into radians
/// </summary>
//-----------------------------------------------------------------------------
float skyDeg2Rad(float degree)
{
	return degree * DEG2RAD;
};

//-----------------------------------------------------------------------------
//  Name : skyString2WString (Function)
/// <summary>
/// Converts a string to a wstring
/// </summary>
//-----------------------------------------------------------------------------
std::wstring skyString2WString(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo( size_needed, 0 );
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

//-----------------------------------------------------------------------------
//  Name : skyWString2String (Function)
/// <summary>
/// Converts a wstring to a string
/// </summary>
//-----------------------------------------------------------------------------
std::string skyWString2String(const std::wstring& s)
{
    int slength = (int)s.length() + 1;
    int len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0)-1;
    std::string r(len, '\0');
    WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, &r[0], len, 0, 0);
    return r;
}

skyFloat skyClamp(skyFloat a, skyFloat min, skyFloat max)
{
	return (a > min) ? ((a > max) ? max: a) : min;
}

//-----------------------------------------------------------------------------
//  Name : skyWildcardMatch (Function)
/// <summary>
/// Checks whether or not a specific string matches the other!
/// </summary>
//-----------------------------------------------------------------------------
BOOL skyWildcardMatch(const char *pat, const char *str) 
{
   int i, star;

new_segment:

   star = 0;
   if (*pat == '*') {
      star = 1;
      do { pat++; } while (*pat == '*'); /* enddo */
   } /* endif */

test_match:

   for (i = 0; pat[i] && (pat[i] != '*'); i++) {
      //if (mapCaseTable[str[i]] != mapCaseTable[pat[i]]) {
	  if (str[i] != pat[i]) {
         if (!str[i]) return 0;
         if ((pat[i] == '?') && (str[i] != '.')) continue;
         if (!star) return 0;
         str++;
         goto test_match;
      }
   }
   if (pat[i] == '*') {
      str += i;
      pat += i;
      goto new_segment;
   }
   if (!str[i]) return 1;
   if (i && pat[i - 1] == '*') return 1;
   if (!star) return 0;
   str++;
   goto test_match;
}

//-----------------------------------------------------------------------------
//  Name : skyWildcardMatch (Function)
/// <summary>
/// Checks whether or not a specific string matches the other!
/// </summary>
//-----------------------------------------------------------------------------
BOOL skyWideWildcardMatch(skyWideStr pat, skyWideStr str) 
{
   int i, star;

new_segment:

   star = 0;
   if (*pat == '*') {
      star = 1;
      do { pat++; } while (*pat == '*'); /* enddo */
   } /* endif */

test_match:

   for (i = 0; pat[i] && (pat[i] != '*'); i++) {
      //if (mapCaseTable[str[i]] != mapCaseTable[pat[i]]) {
	  if (str[i] != pat[i]) {
         if (!str[i]) return 0;
         if ((pat[i] == '?') && (str[i] != '.')) continue;
         if (!star) return 0;
         str++;
         goto test_match;
      }
   }
   if (pat[i] == '*') {
      str += i;
      pat += i;
      goto new_segment;
   }
   if (!str[i]) return 1;
   if (i && pat[i - 1] == '*') return 1;
   if (!star) return 0;
   str++;
   goto test_match;
}


//-----------------------------------------------------------------------------
//  Name : SKY_PRINT_CONSOLE (Function)
/// <summary>
/// Prints a string to the console
/// </summary>
//-----------------------------------------------------------------------------
inline void skyPrintToConsole(std::string type, std::string msg, int classColor, std::string function, std::string file, int line)
{
	skyResult hr = skyPrintToNetwork(skyLogLevel::INFO, msg, function, file, line);
	if(hr != SKY_OK)
	{
		std::cout << "["; 
		skyPlatform::ColorConsole(classColor);
		std::cout << type;
		skyPlatform::ColorConsole(0x08);
		std::cout << "]: " << msg << std::endl;
	}
}

//-----------------------------------------------------------------------------
//  Name : SKY_PRINT_NET (Function)
/// <summary>
/// Prints a string to the console
/// </summary>
//-----------------------------------------------------------------------------
std::string skyExtractDirectory( const std::string& path )
{
	 return path.substr( 0, path.find_last_of( '\\' ) +1 );
}

//-----------------------------------------------------------------------------
//  Name : SKY_PRINT_NET (Function)
/// <summary>
/// Prints a string to the console
/// </summary>
//-----------------------------------------------------------------------------
std::string skyExtractFilename( const std::string& path )
{
	return path.substr( path.find_last_of( '\\' ) +1 );
}

//-----------------------------------------------------------------------------
//  Name : SKY_PRINT_NET (Function)
/// <summary>
/// Prints a string to the console
/// </summary>
//-----------------------------------------------------------------------------
std::string skyChangeExtension( const std::string& path, const std::string& ext )
{
	std::string filename = skyExtractFilename( path );
	return skyExtractDirectory( path ) +filename.substr( 0, filename.find_last_of( '.' ) ) +ext;
}

//-----------------------------------------------------------------------------
//  Name : skyPrintFromScript (Function)
/// <summary>
/// Prints message from script
/// </summary>
//-----------------------------------------------------------------------------
void skyPrintFromScript(std::string msg)
{
	SKY_PRINT_CONSOLE("skyScript", msg, 0x04);
}

//-----------------------------------------------------------------------------
//  Name : skyToBool (Function)
/// <summary>
/// Casts a string to a bool value. The string can either be 1 / 0 or true / false
/// </summary>
//-----------------------------------------------------------------------------
bool skyToBool( const std::string & s ) 
{
	
	if(s == "true" || s == "1")
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//  Name : skySplit (Function)
/// <summary>
/// Splits a string by the delimeter into a vector of strings.  For example, say you have the following string:
/// std::string test("one,two,three");
/// You could call Split() like this:
/// Split(test, outVec, ',');
/// outVec will have the following values:
/// "one", "two", "three"
/// </summary>
//-----------------------------------------------------------------------------
void skySplit(const std::string& str, skyStringVec& vec, char delimiter)
{
	vec.clear();
	size_t strLen = str.size();
	if (strLen == 0)
		return;

	size_t startIndex = 0;
	size_t indexOfDel = str.find_first_of(delimiter, startIndex);
	while (indexOfDel != std::string::npos)
	{
		vec.push_back(str.substr(startIndex, indexOfDel-startIndex));
		startIndex=indexOfDel + 1;
		if (startIndex >= strLen)
			break;
		indexOfDel = str.find_first_of(delimiter, startIndex);
	}
	if(startIndex < strLen)
		vec.push_back(str.substr(startIndex));
}

//-----------------------------------------------------------------------------
//  Name : skyPointInPlane (Function)
/// <summary>
/// Checks whether a vector is within a 2d plane or not!
/// </summary>
//-----------------------------------------------------------------------------
/*bool skyPointInPlane(skyVector2 mouse, skyVector4 plane)
{
	return (mouse.x >= plane.x && mouse.x <= (plane.x + plane.z) && mouse.y >= plane.y && mouse.y <= (plane.y + plane.w));
}*/

//-----------------------------------------------------------------------------
//  Name : skyTransformVector3 (Function)
/// <summary>
/// Transforms a vector by a given matrix!
/// </summary>
//-----------------------------------------------------------------------------
/*skyVector3 skyTransformVector3 ( skyVector3 pPosition, skyMatrix4 pMatrix)
{
	skyVector3 vector;

	vector.x = (pPosition.x * pMatrix[0][0]) + (pPosition.y * pMatrix[1][0]) + (pPosition.z * pMatrix[2][0]) + pMatrix[3][0];
    vector.y = (pPosition.x * pMatrix[0][1]) + (pPosition.y * pMatrix[1][1]) + (pPosition.z * pMatrix[2][1]) + pMatrix[3][1];
    vector.z = (pPosition.x * pMatrix[0][2]) + (pPosition.y * pMatrix[1][2]) + (pPosition.z * pMatrix[2][2]) + pMatrix[3][2];

	return vector;
}*/

//-----------------------------------------------------------------------------
//  Name : skyWCharToString (Function)
/// <summary>
/// Converts a wchar_t* to a string! Found at 
/// http://stackoverflow.com/questions/4339960/how-do-i-convert-wchar-t-to-stdstring
/// </summary>
//-----------------------------------------------------------------------------
std::string skyWCharToString( const wchar_t *s, char dfault = '?', 
                      const std::locale& loc = std::locale() )
{
  std::ostringstream stm;

  while( *s != L'\0' ) {
    stm << std::use_facet< std::ctype<wchar_t> >( loc ).narrow( *s++, dfault );
  }
  return stm.str();
}

//-----------------------------------------------------------------------------
//  Name : skyStringExplode (Function)
/// <summary>
/// Explodes a given string into pieces by separator. Stores the results in a 
/// vector. Found at:
/// http://www.infernodevelopment.com/perfect-c-string-explode-split
/// </summary>
//-----------------------------------------------------------------------------
void skyStringExplode(std::string str, std::string separator, std::vector<std::string>* results)
{
    int found;
    found = str.find_first_of(separator);

    while(found != std::string::npos)
	{
        if(found > 0)
		{
            results->push_back(str.substr(0,found));
        }

        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }

    if(str.length() > 0)
	{
        results->push_back(str);
    }
}

//-----------------------------------------------------------------------------
//  Name : skyHasFlag (Function)
/// <summary>
/// Has flag
/// </summary>
//-----------------------------------------------------------------------------
skyBool skyHasFlag( skyULong a_ulBitset, skyULong a_ulFlag )
{
    return (a_ulBitset & a_ulFlag) ? true : false;
}

/*
//-----------------------------------------------------------------------------
//  Name : skyCreateInputLayoutDescFromVertexShaderSignature (struct)
/// <summary>
///	Thanks to Bobby. http://takinginitiative.net/2011/12/11/directx-1011-basic-shader-reflection-automatic-input-layout-creation/
/// Taken from his blog. Very useful indeed! Creates the input layout 
/// dynamically by shader reflection!
/// </summary>
//-----------------------------------------------------------------------------
HRESULT skyCreateInputLayoutDescFromVertexShaderSignature( ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout )
{
    // Reflect shader info
    ID3D11ShaderReflection* pVertexShaderReflection = NULL;
    if ( FAILED( D3DReflect( pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &pVertexShaderReflection ) ) )
    {
        return S_FALSE;
    }
     
    // Get shader info
    D3D11_SHADER_DESC shaderDesc;
    pVertexShaderReflection->GetDesc( &shaderDesc );
     
    // Read input layout description from shader info
    UINT32 byteOffset = 0;
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
    for ( UINT32 i = 0; i < shaderDesc.InputParameters; i++ )
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;      
        pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc );
 
        // fill out input element desc
        D3D11_INPUT_ELEMENT_DESC elementDesc;  
        elementDesc.SemanticName = paramDesc.SemanticName;     
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;  
 
        // determine DXGI format
        if ( paramDesc.Mask == 1 )
        {
            if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
            byteOffset += 4;
        }
        else if ( paramDesc.Mask <= 3 )
        {
            if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
            byteOffset += 8;
        }
        else if ( paramDesc.Mask <= 7 )
        {
            if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
            byteOffset += 12;
        }
        else if ( paramDesc.Mask <= 15 )
        {
            if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            byteOffset += 16;
        }
             
        //save element desc
        inputLayoutDesc.push_back(elementDesc);
    }      
 
    // Try to create Input Layout
    HRESULT hr = pD3DDevice->CreateInputLayout( &inputLayoutDesc[0], inputLayoutDesc.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), pInputLayout );
 
    //Free allocation shader reflection memory
    pVertexShaderReflection->Release();
    return hr;
}*/


//-----------------------------------------------------------------------------
//  Name : SKY_PRINT_CONSOLE (Function)
/// <summary>
/// Prints a string to a attached network application if enabled, if not 
/// it will automatically use PrintToConsole. 
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyPrintToNetwork(skyLogLevel a_eLevel, std::string msg, std::string function, std::string file, int line)
{
	if(skyLog::g_NetworkLog.VIsEnabled())
	{
		skyLog::g_NetworkLog.VWrite(a_eLevel, msg, function, file + " at line " + skyToString(line));

		return SKY_OK;
	}
	
	return SKY_NOT_SUPPORTED;
}
