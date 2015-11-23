#pragma once

typedef enum eApplicationState 
{
	eApplicationState_Started,
	eApplicationState_Initialized,
	eApplicationState_Loading,
	eApplicationState_Running,
	eApplicationState_Stopping,
	eApplicationState_Stopped
} eApplicationState;

typedef enum eModuleLevel
{
	eModuleLevel_Default = 0,
	eModuleLevel_GameObject = 12,
	eModuleLevel_Postprocess = 11,
	eModuleLevel_Graphics = 10,

} eModuleLevel;

typedef enum eProcessibleLevel 
{
	eProcessibleLevel_Default = 0,
	eProcessibleLevel_GameObject = 10,
	eProcessibleLevel_Postprocess = 899,
	eProcessibleLevel_Graphics = 900,
} eProcessibleLevel;

enum skyLightType 
{
	SKY_DIRECTIONAL_LIGHT,
	SKY_POINT_LIGHT,
	SKY_SPOT_LIGHT
};

typedef enum eApplicationMode
{
	eApplicationMode_Game = 1, 
	eApplicationMode_Editor = 2
} eApplicationMode;

typedef enum eGfxRenderSortId
{
	eGfxRenderSortId_Static = 0x00,
	eGfxRenderSortId_Dynamic = 0x01,
	eGfxRenderSortId_Sky = 0x02,
	eGfxRenderSortId_Debug = 0x03,
	eGfxRenderSortId_Gui = 0x04,
	eGfxRenderSortId_Count = 0x05
} eGfxRenderSortId;

enum skyRenderPath
{
	FORWARD,
	DEFERRED
};

struct sMatrixBuffer
{
	sGfxMatrix m_sProjection;
	sGfxMatrix m_sView;
};

enum skyDeviceButton 
{
	KEY_UNDEFINED = 0x00,
	MOUSE_LBUTTON = 0x01,
	MOUSE_RBUTTON = 0x02,
	MOUSE_MBUTTON = 0x04,

	KEY_BACK = 0x08,
	KEY_TAB = 0x09,
	KEY_RETURN = 0x0D,
	KEY_SHIFT = 0x10,
	KEY_CTRL = 0x11,
	KEY_LCTRL = 0xA2,
	KEY_RCTRL = 0xA3,
	KEY_ESCAPE = 0x1B,
	KEY_SPACE = 0x20,
	KEY_UP = 0x26,
	KEY_DOWN = 0x28,
	KEY_LEFT = 0x25,
	KEY_RIGHT = 0x27,

	KEY_0 = 0x30,
	KEY_1 = 0x31,
	KEY_2 = 0x32,
	KEY_3 = 0x33,
	KEY_4 = 0x34,
	KEY_5 = 0x35,
	KEY_6 = 0x36,
	KEY_7 = 0x37,
	KEY_8 = 0x38,
	KEY_9 = 0x39,

	KEY_A = 0x41,
	KEY_B = 0x42,
	KEY_C = 0x43,
	KEY_D = 0x44,
	KEY_E = 0x45,
	KEY_F = 0x46,
	KEY_G = 0x47,
	KEY_H = 0x48,
	KEY_I = 0x49,
	KEY_J = 0x4A,
	KEY_K = 0x4B,
	KEY_L = 0x4C,
	KEY_M = 0x4D,
	KEY_N = 0x4E,
	KEY_O = 0x4F,
	KEY_P = 0x50,
	KEY_Q = 0x51,
	KEY_R = 0x52,
	KEY_S = 0x53,
	KEY_T = 0x54,
	KEY_U = 0x55,
	KEY_V = 0x56,
	KEY_W = 0x57,
	KEY_X = 0x58,
	KEY_Y = 0x59,
	KEY_Z = 0x5A,

	KEY_F1 = 0x70,
	KEY_F2 = 0x71,
	KEY_F3 = 0x72,
	KEY_F4 = 0x73,
	KEY_F5 = 0x74,
	KEY_F6 = 0x75,
	KEY_F7 = 0x76,
	KEY_F8 = 0x77,
	KEY_F9 = 0x78,
	KEY_F10 = 0x79,
	KEY_F11 = 0x7A,
	KEY_F12 = 0x7B
};

//-----------------------------------------------------------------------------
// Typedefinition (Datatypes)
//-----------------------------------------------------------------------------
/*typedef shared_ptr<skyActor> skyStrongActorPtr;
typedef weak_ptr<skyActor> skyWeakActorPtr;
typedef skyString skyActorType;
typedef skyUInt skyActorID;
typedef shared_ptr<skyActorComponent> skyStrongActorComponentPtr;
typedef weak_ptr<skyActorComponent> skyWeakActorComponentPtr;
typedef skyUInt skyComponentID;
typedef shared_ptr<skyEventSink> skySharedEventSinkPtr;
typedef shared_ptr<skyIEvent> skyEventPtr;*/

typedef skyUInt skyGameObjectComponentId;
typedef skyUInt skyGameObjectId;
typedef skyString skyGameObjectType;

//-----------------------------------------------------------------------------
// Const Definitions
//-----------------------------------------------------------------------------
const skyGameObjectId INVALID_GAMEOBJECT_ID = 0;

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif