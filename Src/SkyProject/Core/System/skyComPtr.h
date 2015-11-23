#pragma once

// Template taken from http://www.codeproject.com/Articles/64111/Building-a-Quick-and-Handy-Reference-Counting-Clas
template < class Type >
class skyComPtr
{
public:
	skyComPtr ( Type* a_pObject = NULL )
		: m_pObject(a_pObject)
	{
		if(m_pObject != NULL) 
			m_pObject->AddRef();
	};

	skyComPtr ( const skyComPtr &a_ComPtr )
			: m_pObject(a_ComPtr.m_pObject)
	{
		if(m_pObject != NULL) 
			m_pObject->AddRef();
	};

	~skyComPtr()
	{
		if(m_pObject != NULL) 
			m_pObject->Release();
	};

public:
	//Assign a pointer
	//e.g. x = new T();
	skyComPtr &operator=(Type* a_pObject)
	{
		//The following grab and release operations have to be performed
		//in that order to handle the case where ptr == mPtr
		//(See comment below by David Garlisch)
		if(a_pObject != NULL) 
			a_pObject->AddRef(); 

		if(m_pObject != NULL) 
			m_pObject->Release();

		m_pObject = a_pObject;

		return (*this);
	}

	//Assign another RCPtr
	skyComPtr &operator= ( const skyComPtr &a_ComPtr )
	{
		return (*this) = a_ComPtr.m_pObject;
	}

	//Retrieve actual pointer
	Type* Get() const
	{
		return m_pObject;
	}

public:
	//Some overloaded operators to facilitate dealing with an RCPtr 
    //as a conventional C pointer.
	//Without these operators, one can still use the less transparent 
    //get() method to access the pointer.

	Type* operator->() const {return m_pObject;}
	Type &operator*() const {return *m_pObject;}
	operator Type*() const {return m_pObject;}	
	operator bool() const {return m_pObject != NULL;}
	bool operator==(const skyComPtr &a_ComPtr) {return m_pObject == a_ComPtr.m_pObject;}
	bool operator==(const Type* a_pObject) {return m_pObject == a_pObject;}

private:
	Type* m_pObject;
};