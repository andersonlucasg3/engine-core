#pragma once

#include "SharedPointer.h"
#include "WeakPointer.h"

template<typename TPtr>
inline bool operator ==(const TSharedPtr<TPtr>& LHS, const TSharedPtr<TPtr>& RHS)
{
    return LHS.Raw() == RHS.Raw();
}

template<typename TPtr>
inline bool operator !=(const TSharedPtr<TPtr>& LHS, const TSharedPtr<TPtr>& RHS)
{
    return LHS.Raw() != RHS.Raw();
}

template<typename TPtr>
inline bool operator ==(const TWeakPtr<TPtr>& LHS, const TWeakPtr<TPtr>& RHS)
{
    return LHS.Raw() == RHS.Raw();
}

template<typename TPtr>
inline bool operator !=(const TWeakPtr<TPtr>& LHS, const TWeakPtr<TPtr>& RHS)
{
    return LHS.Raw() != RHS.Raw();
}

template<typename TPtr1, typename TPtr2>
inline bool operator ==(const TSharedPtr<TPtr1>& Shared, const TWeakPtr<TPtr2>& Weak)
{
    return Shared.Raw() == Weak.Raw();
}

template<typename TPtr1, typename TPtr2>
inline bool operator !=(const TSharedPtr<TPtr1>& Shared, const TWeakPtr<TPtr2>& Weak)
{
    return Shared.Raw() != Weak.Raw();
}

template<typename TPtr1, typename TPtr2>
inline bool operator ==(const TWeakPtr<TPtr1>& Shared, const TSharedPtr<TPtr2>& Weak)
{
    return Shared.Raw() == Weak.Raw();
}

template<typename TPtr1, typename TPtr2>
inline bool operator !=(const TWeakPtr<TPtr1>& Shared, const TSharedPtr<TPtr2>& Weak)
{
    return Shared.Raw() != Weak.Raw();
}

template<typename TPtr>
inline bool operator ==(const TSharedPtr<TPtr>& Shared, std::nullptr_t)
{
    return Shared.Raw() == nullptr;
}

template<typename TPtr>
inline bool operator !=(const TSharedPtr<TPtr>& Shared, std::nullptr_t)
{
    return Shared.Raw() != nullptr;
}

template<typename TPtr>
inline bool operator ==(const TWeakPtr<TPtr>& Weak, std::nullptr_t)
{
    return Weak.Raw() == nullptr;
}

template<typename TPtr>
inline bool operator !=(const TWeakPtr<TPtr>& Weak, std::nullptr_t)
{
    return Weak.Raw() != nullptr;
}