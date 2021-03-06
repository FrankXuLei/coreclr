//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//

#include "ex.h"

inline SString& StringArrayList::operator[] (DWORD idx) const
{
    WRAPPER_NO_CONTRACT;
    return Get(idx);
} 

inline SString& StringArrayList::Get (DWORD idx) const
{
    WRAPPER_NO_CONTRACT;
    PTR_SString ppRet=(PTR_SString)m_Elements.Get(idx);
    return *ppRet;
} 

inline DWORD StringArrayList::GetCount() const
{
    WRAPPER_NO_CONTRACT;
    return m_Elements.GetCount();
}

#ifndef DACCESS_COMPILE
inline void StringArrayList::Append(const SString& string)
{
    CONTRACTL
    {
        THROWS;
        GC_NOTRIGGER;
    }
    CONTRACTL_END;    
    NewHolder<SString> pAdd=new SString(string);
    pAdd->Normalize();
    IfFailThrow(m_Elements.Append(pAdd));
    pAdd.SuppressRelease();
}

inline void StringArrayList::AppendIfNotThere(const SString& string)
{
    CONTRACTL
    {
        THROWS;
        GC_NOTRIGGER;
    }
    CONTRACTL_END;    
    for (DWORD i=0;i<GetCount();i++)
    {
        if(Get(i).Equals(string))
            return;
    }
    Append(string);
}

#endif


inline StringArrayList::~StringArrayList()
{
    CONTRACTL
    {
        DESTRUCTOR_CHECK;
        NOTHROW;
        GC_NOTRIGGER;
    }
    CONTRACTL_END;
#ifndef DACCESS_COMPILE    
    for (DWORD i=0;i< GetCount() ;i++)
    {
        delete (SString*)m_Elements.Get(i);
    }
#endif    
}

