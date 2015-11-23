#pragma once

//-----------------------------------------------------------------------------
// Internal Includes!
//-----------------------------------------------------------------------------
#include "inc_core_helpers.h"
#include "inc_core_types.h"
#include "inc_core_version.h"

//-----------------------------------------------------------------------------
// Include
//-----------------------------------------------------------------------------
// Platform definition! For which platform do we want to compile?
#if defined(WIN32) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <ctime>
#include <shlobj.h>
#include <mmsystem.h>
#endif

#include <strstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <memory>

//-----------------------------------------------------------------------------
// Lib Include
//-----------------------------------------------------------------------------
#pragma comment ( lib, "winmm.lib" )
#pragma comment ( lib, "User32.lib" )
#pragma comment ( lib, "Gdi32.lib" )

//-----------------------------------------------------------------------------
// Forward Declaration
//-----------------------------------------------------------------------------
namespace skyConfig {
	class IntType;
	class FloatType;
	class StringType;
	class Vector3Type;
	class BoolType;
};

class skyILog;
class skyLogDispatcher;
class skyHTMLLog;
class skyNetworkLog;
class skyFileLog;
class skyProfiler;
class skyProfilerSection;
class skyTimer;
class skyUDPSocket;
class skyHashedString;
class skyIWindow;
class skyICriticalSection;
class skyIFileDevice;
class skyIFile;
class skyFileSystem;
class skyAsyncFileOperation;
class skyZipFileDevice;
class skyDiskFileDevice;
class skyDiskFile;
class skyWindow;
class skyRuntimeClass;
class skyRefBaseClass;

template <class BaseClass, class IdType>
class skyGenericObjectFactory;
class optional_empty;
template <unsigned long size>
class optional_base;

template<class Type>
class skyComPtr;

template<class T, class P>
class skyIThread;

#if defined(WIN32)
template<class T, class P>
class skyWin32Thread;
class skyWin32CriticalSection;
#endif

//-----------------------------------------------------------------------------
// Usings
//-----------------------------------------------------------------------------
using namespace std::tr1;

//-----------------------------------------------------------------------------
// Internal includes
//-----------------------------------------------------------------------------
#include "inc_core_extern.h"
#include "Math\skyMath.h"
#include "Utils\skyHelper.h"
#include "Utils\skyTemplates.h"
#include "Utils\skyTimer.h"
#include "Utils\skyHashedString.h"
#include "System\skyRuntimeClass.h"
#include "System\skyComPtr.h"
#include "System\skyRefBaseClass.h"
#include "Config\skyConfigs.h"
#include "Config\skyConfigBoolType.h"
#include "Config\skyConfigIntType.h"
#include "Config\skyConfigFloatType.h"
#include "Config\skyConfigStringType.h"
#include "Debug\skyILog.h"
#include "Debug\skyLogDispatcher.h"
#include "Debug\skyLogs.h"
#include "Debug\Logs\skyFileLog.h"
#include "Debug\Logs\skyHTMLLog.h"
#include "Debug\Logs\skyNetworkLog.h"
#include "Debug\skyMemoryWatcher.h"
#include "Debug\Profiler\skyProfiler.h"
#include "Debug\Profiler\skyProfilerSection.h"
#include "Network\skyUDPSocket.h"
#include "Platform\skyIWindow.h"
#include "Platform\skyPlatform.h"
#include "Platform\skyPlatformFile.h"
#include "Platform\Threading\skyICriticalSection.h"
#include "Platform\Threading\skyIThread.h"
#include "FileSystem\skyIFileDevice.h"
#include "FileSystem\skyIFile.h"
#include "FileSystem\skyFileSystem.h"
#include "FileSystem\Devices\skyZipFileDevice.h"
#include "FileSystem\Devices\skyDiskFileDevice.h"
#include "FileSystem\Files\Sync\skyDiskFile.h"


#if defined(WIN32)
#include "Platform\Win32\skyWin32Platform.h"
#include "Platform\Win32\Threading\skyWin32Thread.h"
#include "Platform\Win32\Threading\skyWin32CriticalSection.h"
#include "Platform\Win32\skyWindow.h"
#endif