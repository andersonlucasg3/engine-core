#pragma once

#include "Class.h"

template<typename ... TArgs>
CObjectPtr New(const CClassPtr& Class, TArgs ... Args)
{
    CObject* ConstructedObject = Class->CreateRaw<CObject>(std::forward<TArgs>(Args)...);
    return MakeShareable(ConstructedObject);
}

template<typename TObject = CObject, typename ... TArgs>
TSharedPtr<TObject> New(const CClassPtr& Class, TArgs ... Args)
{
    TObject* ConstructedObject = Class->CreateRaw<TObject>(std::forward<TArgs>(Args)...);
    return MakeShareable(ConstructedObject);
}

template<typename TObject = CObject, typename ... TArgs>
TSharedPtr<TObject> New(TArgs ... Args)
{
    TClass<TObject> ClassTemplate;
    // for some yet unknown reason, I need to do this 
    CClass* Class = &ClassTemplate;
    TObject* ConstructedObject = Class->CreateRaw<TObject>(std::forward<TArgs>(Args)...);
    return MakeShareable(ConstructedObject);
}