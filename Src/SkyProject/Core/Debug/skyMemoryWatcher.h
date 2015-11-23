#pragma once

#if !defined(SKY_BUILD_MASTER)

#define SKY_WATCHER_DECLARATION() \
	public: \
		static long mNumOfAllocations; \
		static void* operator new(size_t size, const char* fileName = "unknown", int lineNumber = 0); \
		static void operator delete(void* pMemory, const char* fileName, int lineNumber); \
		static void* operator new[](size_t size, const char* fileName = "unknown", int lineNumber = 0); \
		static void operator delete[](void* pMemory, const char* fileName, int lineNumbe); \
	private:

#define SKY_WATCHER_DEFINITION(_className_, _classNameString_, _isLoggingEnabled_) \
	long _className_::mNumOfAllocations = 0;\
	void* _className_::operator new(size_t size, const char* fileName, int lineNumber) \
	{ \
		void* pMemory = malloc(size); \
		++_className_::mNumOfAllocations;\
		std::cout << "skyMemoryWatcher (Class: " << _classNameString_ << " ): allocated memory at address 0x" << reinterpret_cast<unsigned long>(pMemory) << " used " << size << " bytes (x" << mNumOfAllocations << ") at file " << fileName << ":" << lineNumber << std::endl;\
		if(_isLoggingEnabled_ == true)\
		{\
			SKY_MEMORY_ALLOCATION(skyToString("skyMemoryWatcher (Class: ") + skyToString(_classNameString_) + skyToString(" ): allocated memory at address 0x") + skyToString(pMemory) + skyToString(" used ") + skyToString(size) + skyToString(" bytes (x") + skyToString(mNumOfAllocations) + skyToString(") at file ") + skyToString(fileName) + skyToString(":") + skyToString(lineNumber));\
		}\
		return pMemory;\
	} \
	void _className_::operator delete(void* pMemory, const char* fileName, int lineNumber) \
	{ \
		free(pMemory); \
		--_className_::mNumOfAllocations;\
		std::cout << "skyMemoryWatcher  (Class: " << _classNameString_ << " ): freed memory at address 0x" << reinterpret_cast<unsigned long>(pMemory) << " (x" << mNumOfAllocations << ") " << std::endl;\
		if(_isLoggingEnabled_ == true)\
		{\
			SKY_MEMORY_DELETION(skyToString("skyMemoryWatcher (Class: ") + skyToString(_classNameString_) + skyToString(" ): freed memory at address 0x") + skyToString(pMemory) + skyToString(" (x") + skyToString(mNumOfAllocations) + skyToString(")"));\
		}\
	} \
	void* _className_::operator new[](size_t size, const char* fileName, int lineNumber) \
	{ \
		void* pMemory = malloc(size); \
		++_className_::mNumOfAllocations;\
		std::cout << "skyMemoryWatcher  (Class: " << _classNameString_ << " ): allocated memory at address 0x" << reinterpret_cast<unsigned long>(pMemory) << " used " << size << " bytes (x" << mNumOfAllocations + ") at file " << fileName << ":" << lineNumber << std::endl;\
		SKY_MEMORY_ALLOCATION(skyToString("skyMemoryWatcher (Class: ") + skyToString(_classNameString_) + skyToString(" ): allocated memory at address 0x") + skyToString(pMemory) + skyToString(" used ") + skyToString(size) + skyToString(" bytes (x") + skyToString(mNumOfAllocations) + skyToString(") at file ") + skyToString(fileName) + skyToString(":") + skyToString(lineNumber));\
		return pMemory;\
	} \
	void _className_::operator delete[](void* pMemory, const char* fileName, int lineNumber) \
	{ \
		free(pMemory); \
		--mNumOfAllocations;\
		std::cout << "New Memory Allocation  (Class: " << _classNameString_ << " ): freed memory at address 0x" << reinterpret_cast<unsigned long>(pMemory) << " (x" << mNumOfAllocations << ") " << std::endl;\
		if(_isLoggingEnabled_ == true)\
		{\
			SKY_MEMORY_DELETION(skyToString("skyMemoryWatcher (Class: ") + skyToString(_classNameString_) + skyToString(" ): freed memory at address 0x") + skyToString(pMemory) + skyToString(" (x") + skyToString(mNumOfAllocations) + skyToString(")"));\
		}\
	}
#else
	#define SKY_WATCHER_DECLARATION() (sizeof(void*))
    #define SKY_WATCHER_DEFINITION(_className_) (sizeof(_className_))
#endif
