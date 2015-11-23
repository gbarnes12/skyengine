#include "stdafx.h"
#include "inc_core_extern.h"

bool skyFailed(skyResult hr)
{
	if(hr == skyResult::SKY_ERROR)
		return true;
	else if(hr == skyResult::SKY_CANCELED)
		return true;
	else if(hr == skyResult::SKY_OUT_OF_MEMORY)
		return true;
	else if(hr == skyResult::SKY_INVALID_CAST)
		return true;
	else if(hr == skyResult::SKY_INVALID_POINTER)
		return true;
	else if(hr == skyResult::SKY_NOT_IMPLEMENTED)
		return true;
	else if(hr == skyResult::SKY_NOT_SUPPORTED)
		return true;
	else if(hr == skyResult::SKY_TOO_LARGE)
		return true;

	return false;
}