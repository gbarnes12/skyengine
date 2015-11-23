#pragma once
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
// Name : skyTemplates.h                                                     //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// In this file there are common template classes, functions defined        //
/// in order to make life easier. Some of those templates have been          //
/// taken from different sources. Those are marked                           //
/// </summary>                                                               //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

#define SKY_SAFE_DELETE(x) if(x){ delete x; x = NULL; }
#define SKY_SAFE_DELETE_ARRAY(x) if(x) { delete[] x; x = NULL; }
//-----------------------------------------------------------------------------
//  Name : SKY_SAFE_DELETE (Template)
/// <summary>
/// Makes sure that a pointer gets deleted safely. Keep in mind that in certain
/// circumstances it may occur that the pointer won't get deleted successfully.
/// </summary>
//-----------------------------------------------------------------------------
/*template< class T > 
void SKY_SAFE_DELETE( T* pVal)
{
	if(pVal) {
		delete pVal;
		pVal = NULL;
	}
}
*/

//-----------------------------------------------------------------------------
//  Name : SKY_SAFE_DELETE_ARRAY (Template)
/// <summary>
/// Makes sure that a pointer to an array gets deleted safely. Keep in mind that in certain
/// circumstances it may occur that the pointer won't get deleted successfully.
/// </summary>
//-----------------------------------------------------------------------------
/*
template< class T > 
void SKY_SAFE_DELETE_ARRAY( T* pVal)
{
	if(pVal) {
		delete pVal;
		pVal = NULL;
	}
}
*/
//-----------------------------------------------------------------------------
//  Name : skyToString (Template)
/// <summary>
/// Converts nearly every datatype to a string of type std::string.
/// </summary>
//-----------------------------------------------------------------------------
template<class T> 
inline std::string skyToString(T& i)
{
	std::stringstream ss;
	std::string s;
	ss << i;
	s = ss.str();

	return s;
}

//-----------------------------------------------------------------------------
//  Name : skyToWString (Template)
/// <summary>
/// Converts nearly every datatype to a string of type std::string.
/// </summary>
//-----------------------------------------------------------------------------
template<class T> 
inline std::wstring skyToWString(T& f)
{
	std::wstringstream converter (std::wstringstream::in | std::wstringstream::out);
    converter << f;
	std::wstring ws = converter.str();
    return ws;
}
//-----------------------------------------------------------------------------
//  Name : skyToWString (Template)
/// <summary>
/// Converts nearly every datatype to a string of type std::string.
/// </summary>
//-----------------------------------------------------------------------------
template<class T> 
inline std::string skyToAString(T& f)
{
	std::stringstream converter (std::stringstream::in | std::stringstream::out);
    converter << f;
	std::string ws = converter.str();
    return ws;
}

//-----------------------------------------------------------------------------
//  Name : skyMakeSharedPtr (Template)
/// <summary>
/// Converts a weak pointer into a shared pointer. This methods checks before 
/// whether or not the weak pointer is already expired. If so it will return
/// a null pointer!
/// </summary>
//-----------------------------------------------------------------------------
template <class Type> 
shared_ptr<Type> skyMakeSharedPtr(weak_ptr<Type> pWeakPtr)
{
    if (!pWeakPtr.expired())
        return shared_ptr<Type>(pWeakPtr);
    else
        return shared_ptr<Type>();
}

//-----------------------------------------------------------------------------
//  Name : skySortBySharedPtrContent (Template)
/// <summary>
/// Used to sort the content of two shared pointers. Used to determine the 
/// z order of the screen elements. Taken from GameCoding Complete.
/// </summary>
//-----------------------------------------------------------------------------
template<class T>
struct skySortBySharedPtrContent
{
    bool operator()(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) const
    { 
		return *lhs < *rhs; 
	}
};

//-----------------------------------------------------------------------------
//  Name : skySingleton (Template)
/// <summary>
/// Use this template to specify a class as a singleton. This makes sure that 
/// a class has only one instance within the whole scope.
/// </summary>
//-----------------------------------------------------------------------------
template <class T_DERIVED>
class skySingleton
{
    public:
        static T_DERIVED& Instance()
        {
        static T_DERIVED oInstance ;
        return oInstance ;
        }
 
    protected:
		 skySingleton()
       {
      };
  
      //! Copy constructor.
    skySingleton(const skySingleton& source)
      {
     };
 
     //! Destructor.
     virtual ~skySingleton()
     {
      };
 
 
    private:
        skySingleton& operator=( const skySingleton& ) {return *this;}
} ;

struct skyFileSettings;
class skyResourceSystem;

//-----------------------------------------------------------------------------
//  Name : GenericObjectCreationFunction (Template)
/// <summary>
/// Creates a generic subtype and returns it base type. This is part of the 
/// GenericObjectFactory.
/// </summary>
//-----------------------------------------------------------------------------
template <class BaseType, class SubType>
BaseType* skyMaterialObjectCreationFunction(std::string name, char* pBuffer, unsigned int size, skyResourceSystem* pResourceSystem) { return SKY_NEW SubType(name, pBuffer, size, pResourceSystem); }

//-----------------------------------------------------------------------------
//  Name : GenericObjectFactory (Template)
/// <summary>
/// Creates a base class for a generic object factory which is able to 
/// store creation functions in order to create specific subtypes of a basetype.
/// This code has been taken from Game Coding Complete!
/// </summary>
//-----------------------------------------------------------------------------
template <class BaseClass, class IdType>
class skyMaterialObjectFactory
{
    typedef BaseClass* (*ObjectCreationFunction)(std::string name, char* pBuffer, unsigned int size, skyResourceSystem* pResourceSystem);
    std::map<IdType, ObjectCreationFunction> mCreationFunctions;

public:
    template <class SubClass>
    bool Register(IdType id)
    {
        auto findIt = mCreationFunctions.find(id);
        if (findIt == mCreationFunctions.end())
        {
            mCreationFunctions[id] = &skyMaterialObjectCreationFunction<BaseClass, SubClass>;  // insert() is giving me compiler errors
            return true;
        }

        return false;
    }

    BaseClass* Create(IdType id, std::string name, char* pBuffer, unsigned int size, skyResourceSystem* pResourceSystem)
    {
        auto findIt = mCreationFunctions.find(id);
        if (findIt != mCreationFunctions.end())
        {
            ObjectCreationFunction pFunc = findIt->second;
            return pFunc(name, pBuffer, size, pResourceSystem);
        }

        return NULL;
    }
};

//-----------------------------------------------------------------------------
//  Name : GetDataFromBlob (Template)
/// <summary>
/// Retrieves data from a blob!
/// </summary>
//-----------------------------------------------------------------------------
template <class T>
T skyGetDataFromBlob(sIOMemBlob& a_sBlob) 
{ 
	return reinterpret_cast<T>(a_sBlob.m_uiBufferPtr); 
}

//-----------------------------------------------------------------------------
//  Name : GenericObjectCreationFunction (Template)
/// <summary>
/// Creates a generic subtype and returns it base type. This is part of the 
/// GenericObjectFactory.
/// </summary>
//-----------------------------------------------------------------------------
template <class BaseType, class SubType>
BaseType* skyGenericObjectCreationFunction(void) { return SKY_NEW SubType; }

//-----------------------------------------------------------------------------
//  Name : GenericObjectFactory (Template)
/// <summary>
/// Creates a base class for a generic object factory which is able to 
/// store creation functions in order to create specific subtypes of a basetype.
/// This code has been taken from Game Coding Complete!
/// </summary>
//-----------------------------------------------------------------------------
template <class BaseClass, class IdType>
class skyGenericObjectFactory
{
    typedef BaseClass* (*ObjectCreationFunction)(void);
    std::map<IdType, ObjectCreationFunction> mCreationFunctions;

public:
    template <class SubClass>
    bool Register(IdType id)
    {
        auto findIt = mCreationFunctions.find(id);
        if (findIt == mCreationFunctions.end())
        {
            mCreationFunctions[id] = &skyGenericObjectCreationFunction<BaseClass, SubClass>;  // insert() is giving me compiler errors
            return true;
        }

        return false;
    }

    BaseClass* Create(IdType id)
    {
        auto findIt = mCreationFunctions.find(id);
        if (findIt != mCreationFunctions.end())
        {
            ObjectCreationFunction pFunc = findIt->second;
            return pFunc();
        }

        return NULL;
    }
};


#include <new>
class optional_empty { };

template <unsigned long size>
class optional_base
{
public:
    // Default - invalid.

    optional_base() : m_bValid(false) { }

    optional_base & operator = (optional_base const & t)
    {
                m_bValid = t.m_bValid;
                return * this;
    }

        //Copy constructor
    optional_base(optional_base const & other)
                : m_bValid(other.m_bValid)  { }

        //utility functions
        bool const valid() const                { return m_bValid; }
        bool const invalid() const              { return !m_bValid; }

protected:
    bool m_bValid;
    char m_data[size];  // storage space for T
};

template <class T>
class optional : public optional_base<sizeof(T)>
{
public:
    // Default - invalid.

    optional()   {    }
    optional(T const & t)  { construct(t); m_bValid = (true);  }
        optional(optional_empty const &) {      }

    optional & operator = (T const & t)
    {
        if (m_bValid)
        {
            * GetT() = t;
        }
        else
        {
            construct(t);
                        m_bValid = true;        // order important for exception safety.
        }

        return * this;
    }

        //Copy constructor
    optional(optional const & other)
    {
                if (other.m_bValid)
                {
                        construct(* other);
            m_bValid = true;    // order important for exception safety.
                }
    }

    optional & operator = (optional const & other)
    {
                assert(! (this == & other));        // don't copy over self!
                if (m_bValid)
                {                                               // first, have to destroy our original.
                        m_bValid = false;       // for exception safety if destroy() throws.
                                                                // (big trouble if destroy() throws, though)
                        destroy();
                }

                if (other.m_bValid)
                {
                        construct(* other);
                        m_bValid = true;        // order vital.

                }
                return * this;
    }


        bool const operator == (optional const & other) const
        {
                if ((! valid()) && (! other.valid())) { return true; }
                if (valid() ^ other.valid()) { return false; }
                return ((* * this) == (* other));
        }

        bool const operator < (optional const & other) const
        {
                // equally invalid - not smaller.
                if ((! valid()) && (! other.valid()))   { return false; }

                // I'm not valid, other must be, smaller.
                if (! valid())  { return true; }

                // I'm valid, other is not valid, I'm larger
                if (! other.valid()) { return false; }

                return ((* * this) < (* other));
        }

    ~optional() { if (m_bValid) destroy(); }

        // Accessors.

        T const & operator * () const { assert(m_bValid); return * GetT(); }
        T & operator * ()  { assert(m_bValid); return * GetT(); }
        T const * const operator -> () const { assert(m_bValid); return GetT(); }
        T               * const operator -> () { assert(m_bValid); return GetT(); }

        //This clears the value of this optional variable and makes it invalid once again.
        void clear()
        {
                if (m_bValid)
                {
                        m_bValid = false;
                        destroy();
                }
        }

        //utility functions
        bool const valid() const                { return m_bValid; }
        bool const invalid() const              { return !m_bValid; }

private:


    T const * const GetT() const { return reinterpret_cast<T const * const>(m_data); }
    T * const GetT()                     { return reinterpret_cast<T * const>(m_data);}
        void construct(T const & t)  { SKY_NEW (GetT()) T(t); }
    void destroy() { GetT()->~T(); }
};


