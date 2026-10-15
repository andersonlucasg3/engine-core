#pragma once

#include "SharedPointer.h"
#include "SharedFromThis.h"
#include "Deleter.h"
#include "WeakPointer.h"

#include <type_traits>

template<
	typename TPtr,
	typename ... TArgs
>
inline TSharedPtr<TPtr> MakeShared(TArgs ... Args)
{
	TPtr* Ptr = new TPtr(std::forward<TArgs>(Args)...);
	
	TDeleter<TPtr>* Deleter = new TDeleter<TPtr>(Ptr);
	SRefCounter* RefCounter = new SRefCounter();
	RefCounter->RetainStrong();

	if constexpr (std::is_base_of_v<SSharedFromThis, TPtr>)
	{
		Ptr->UpdateWeakPtr(Deleter, RefCounter);
	}
	
	return TSharedPtr<TPtr>(Ptr, Deleter, RefCounter);
}

template<typename TPtr, typename DeleterT = TDeleter<TPtr>>
inline TSharedPtr<TPtr> MakeShareable(TPtr* InPtr)
{
	IDeleter* Deleter = new DeleterT(InPtr);
	SRefCounter* RefCounter = new SRefCounter();
	RefCounter->RetainStrong();

	if constexpr (std::is_base_of_v<SSharedFromThis, TPtr>)
	{
		InPtr->UpdateWeakPtr(Deleter, RefCounter);
	}

	return TSharedPtr<TPtr>(InPtr, Deleter, RefCounter);
}

template<
	typename TCastTo, 
	typename TCastFrom
>
inline TSharedPtr<TCastTo> StaticCastSharedPtr(const TSharedPtr<TCastFrom>& Cast)
{
	static_assert(std::is_convertible_v<TCastTo*, TCastFrom*>);

	Cast._refCounter->RetainStrong();

	return TSharedPtr<TCastTo>(static_cast<TCastTo*>(Cast._object), Cast._deleter, Cast._refCounter);
}

template<
	typename TCastTo,
	typename TCastFrom
>
inline TWeakPtr<TCastTo> StaticCastWeakPtr(const TWeakPtr<TCastFrom>& Cast)
{
	static_assert(std::is_convertible_v<TCastTo*, TCastFrom*>);

	Cast._refCounter->RetainWeak();
	
	return TWeakPtr<TCastTo>(static_cast<TCastTo*>(Cast._object), Cast._deleter, Cast._refCounter);
}
