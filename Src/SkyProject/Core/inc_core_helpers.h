#pragma once
//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define SKY_ZERO_MEM(Destination, Length) ZeroMemory(Destination, Length)
#define SKY_VR(x) hr = x; if(skyFailed(hr)) { return hr; }
#define SKY_VR_FAIL(x) hr = x; if(skyFailed(hr)) { goto FAILED; }
#define SKY_V(x) hr = x;
#define SKY_RELEASE(x) if(x) { (x)->Release(); } (x) = 0;
#define _STR(x) #x
#define STR(x) _STR(x)
#define SKY_TODO(x) __pragma(message("==========> TODO: "_STR(x) " :: " __FILE__ "@"STR(__LINE__)))

#define SKY_PRINT_NET(level, msg) skyPrintToNetwork(level, msg, __FUNCTION__, __FILE__, __LINE__); 
#define SKY_PRINT_CONSOLE(type, msg, color) skyPrintToConsole(type, msg, color, __FUNCTION__, __FILE__, __LINE__);
#define SKY_UNTESTED_METHOD(x) SKY_PRINT_CONSOLE("untested method", x, 0x01); assert(false == true); 

#define SKY_HAS_FLAG(x,m) (x & m)

#define SKY_DECLARE_PROPERTY_SET(TYPE, INSTANCE, NAME) \
inline skyVoid Set##NAME ( const TYPE& value ) \
{ \
	this->INSTANCE = value;\
};

#define SKY_DECLARE_PROPERTY_GET(TYPE, INSTANCE, NAME) \
inline TYPE Get##NAME () const \
{ \
	return this->INSTANCE;\
};

#define SKY_PROPERTY_GET(TYPE, INSTANCE, NAME) \
public: \
SKY_DECLARE_PROPERTY_GET(TYPE, INSTANCE, NAME) 

#define SKY_PROPERTY_SET(TYPE, INSTANCE, NAME) \
public: \
SKY_DECLARE_PROPERTY_SET(TYPE, INSTANCE, NAME) 


#define SKY_PROPERTY_GETSET(TYPE, INSTANCE, NAME) public: SKY_DECLARE_PROPERTY_GET(TYPE, INSTANCE, NAME) SKY_DECLARE_PROPERTY_SET(TYPE, INSTANCE, NAME) 