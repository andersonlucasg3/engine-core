#pragma once

#include "RefCounter.h"
#include "Deleter.h"

#include "SharedFromThis.h"

#include <cstddef>
#include <type_traits>

using namespace Core::Types;

struct SSharedFromThis;

template<typename TPtr>
struct TWeakPtr;

template<typename TPtr>
struct TSharedPtr
{
	inline TSharedPtr() = default;

	inline TSharedPtr(const TSharedPtr& Other) : TSharedPtr()
	{
		if (!Other) return;

		_refCounter = Other._refCounter->RetainStrong();
		_object = Other._object;
		_deleter = Other._deleter;
	}

	template<typename TOtherPtr = TPtr>
	inline TSharedPtr(const TSharedPtr<TOtherPtr>& Shared) : TSharedPtr()
	{
		static_assert(std::is_base_of_v<TPtr, TOtherPtr> || std::is_same_v<TPtr, TOtherPtr>);

		if (!Shared) return;

		_refCounter = Shared._refCounter->RetainStrong();
		_object = Shared._object;
		_deleter = Shared._deleter;
	}

	template<typename TOtherPtr = TPtr>
	inline TSharedPtr(const TWeakPtr<TOtherPtr>& Weak) : TSharedPtr()
	{
		static_assert(std::is_base_of_v<TPtr, TOtherPtr> || std::is_same_v<TPtr, TOtherPtr>);

		if (!Weak) return;

		_refCounter = Weak._refCounter->RetainStrong();
		_deleter = Weak._deleter;
		_object = Weak._object;
	}

	inline TSharedPtr(std::nullptr_t) : TSharedPtr()
	{
		//
	}

	inline ~TSharedPtr()
	{
		Reset();
	}

	inline TPtr* Raw() const
	{
		if (_refCounter == nullptr) return nullptr;
		
		return _object;
	}

	inline UInt32 RefCount() const
	{
		return _refCounter ? _refCounter->RefCount() : 0;
	}

	inline bool IsValid() const
	{
		return _refCounter && _refCounter->IsValid() && !_refCounter->IsPendingDelete();
	}

	inline operator bool() const
	{
		return IsValid();
	}

	inline TPtr& operator*() const
	{
		return *_object;
	}

	inline TPtr* operator->() const
	{
		return _object;
	}

	inline explicit operator TPtr*() const
	{
		return _object;
	}

	inline TPtr& operator[](UInt32 Index) const
	{
		return _object[Index];
	}

	inline TPtr& operator[](UInt64 Index) const
	{
		return _object[Index];
	}

	inline TPtr* operator+(UInt32 Index) const
	{
		return (_object + Index);
	}

	inline TPtr* operator+(UInt64 Index) const
	{
		return (_object + Index);
	}

	inline bool operator ==(std::nullptr_t)
	{
		return _object == nullptr;
	}

	inline TSharedPtr& operator=(const TSharedPtr& Other)
	{
		Reset();

		if (!Other) return *this;

		_refCounter = Other._refCounter->RetainStrong();
		_deleter = Other._deleter;
		_object = Other._object;

		return *this;
	}

	template<typename TOtherPtr = TPtr>
	inline TSharedPtr& operator=(const TSharedPtr<TOtherPtr>& Other) 
	{
		static_assert(std::is_base_of_v<TPtr, TOtherPtr> || std::is_same_v<TPtr, TOtherPtr>);

		Reset();

		if (!Other) return *this;

		_refCounter = Other._refCounter->RetainStrong();
		_deleter = Other._deleter;
		_object = Other._object;

		return *this;
	}

	template<typename TOtherPtr = TPtr>
	inline TSharedPtr& operator=(const TWeakPtr<TOtherPtr>& Weak)
	{
		static_assert(std::is_base_of_v<TPtr, TOtherPtr> || std::is_same_v<TPtr, TOtherPtr>);

		Reset();

		if (!Weak) return *this;

		_refCounter = Weak._refCounter->RetainStrong();
		_deleter = Weak._deleter;
		_object = Weak._object;

		return *this;
	}

	template<typename TOtherPtr = TPtr>
	inline TSharedPtr& operator=(TOtherPtr* SFT)
	{
		static_assert(std::is_base_of_v<TPtr, TOtherPtr> || std::is_same_v<TPtr, TOtherPtr>);
		static_assert(std::is_base_of_v<SSharedFromThis, TOtherPtr>);

		Reset();

		if (!SFT) return *this;

		_refCounter = SFT->_weakRef->_refCounter->RetainStrong();
		_deleter = SFT->_deleter;
		_object = static_cast<TPtr*>(SFT);

		return *this;
	}

	inline TSharedPtr& operator=(std::nullptr_t)
	{
		Reset();

		return *this;
	}

private:
	TPtr* _object = nullptr;
	IDeleter* _deleter = nullptr;
	SRefCounter* _refCounter = nullptr;

	inline TSharedPtr(TPtr* InObject, IDeleter* InDeleter, SRefCounter* InRefCounter) : 
		_object(InObject),
		_deleter(InDeleter),
		_refCounter(InRefCounter)
	{
		//
	}

	inline void Reset()
	{
		if (_refCounter == nullptr) return;

		_refCounter->ReleaseStrong();

		if (!_refCounter->IsValid() && _deleter != nullptr)
		{
			_deleter->Delete();
			delete _deleter;
		}

		if (_refCounter->IsPendingDelete())
		{
			delete _refCounter;
		}

		_object = nullptr;
		_deleter = nullptr;
		_refCounter = nullptr;
	}

    friend struct TSharedPtr;

    template<typename TOtherPtr>
    friend struct TSharedPtr;

	template<typename TOtherPtr>
    friend struct TWeakPtr;

	template<typename TOtherPtr>
	friend struct TSharedFromThis;

    template<
        typename TPointer,
        typename ... TArgs
    >
    friend TSharedPtr<TPointer> MakeShared(TArgs...);

    template<typename TPointer, typename DeleterT>
    friend TSharedPtr<TPointer> MakeShareable(TPointer*);

    template<
        typename TCastTo,
        typename TCastFrom
    >
    friend TSharedPtr<TCastTo> StaticCastSharedPtr(const TSharedPtr<TCastFrom>&);
};