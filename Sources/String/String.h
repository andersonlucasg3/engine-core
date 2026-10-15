#pragma once

#include "Defines/Types.h"

#include "Templates/Array.h"
#include "Templates/Hashable.h"

#include "SmartPointer/SharedPointer.h"

#include <format>

#if PLATFORM_WINDOWS
typedef TSharedPtr<wchar_t> CWString;
#endif // PLATFORM_WINDOWS

class CString : public CHashable
{
	CORE_API static TSharedPtr<char> _empty;

	SizeT _length;
	TSharedPtr<char> _bufferPtr;

	CORE_API void CopyStr(const char* CStr, SizeT Len);
	CORE_API SizeT StrLen(const char* CStr) const;

#if PLATFORM_WINDOWS
	CORE_API void CopyStr(const wchar_t* CWStr, SizeT Len);
	CORE_API SizeT StrLen(const wchar_t* CWStr) const;
#endif // PLATFORM_WINDOWS

	CORE_API bool Contains(const char* CStr, SizeT Len) const;

public:
	CORE_API static const char* Empty();

	CORE_API CString();
	CORE_API CString(const CString& Other);
	CORE_API CString(const char* CStr);
	CORE_API CString(const char* CStr, SizeT Len);
	
#if PLATFORM_WINDOWS
	CORE_API CString(const wchar_t* CWStr);
	CORE_API CString(const wchar_t* CWStr, SizeT Len);
#endif // PLATFORM_WINDOWS

	template<
		typename ... TArgs
	>
	explicit CString(const char* CStr, TArgs ... Args) : CString()
	{
		std::string Formatted = std::vformat(CStr, std::make_format_args(Args...));
		CopyStr(Formatted.c_str(), Formatted.size());
	}

	CORE_API ~CString() = default;

	CORE_API SizeT Len() const;
	CORE_API bool IsEmpty() const;

	CORE_API bool Contains(const char* CStr) const;
	CORE_API bool Contains(const CString& Other) const;

	CORE_API Int64 LastIndexOf(const char Char) const;

	CORE_API CString SubString(UInt64 Start) const;
	CORE_API CString SubString(UInt64 Start, UInt64 End) const;

	CORE_API CString Replace(const char OldChar, const char NewChar) const;
	CORE_API CString Replace(const char* OldCStr, const char* NewCStr) const;
	CORE_API CString Replace(const CString& OldStr, const CString& NewStr) const;

	CORE_API TArray<CString> Split(const char Separator) const;

	CORE_API bool StartsWith(const CString& Other) const;
	CORE_API bool EndsWith(const CString& Other) const;

	CORE_API char LastChar() const;

	CORE_API SizeT Hash() const;

#if PLATFORM_WINDOWS
	CORE_API CWString WStr() const;
#endif // PLATFORM_WINDOWS

	CORE_API CString& operator+=(const CString& Other);
	CORE_API CString& operator+=(const char* CStr);
	CORE_API CString& operator+=(char Char);
	
	CORE_API CString operator+(const CString& Other) const;
	CORE_API CString operator+(const char* CStr) const;
	CORE_API CString operator+(char Char) const;
	
	CORE_API bool operator >(const CString& Other) const;
	CORE_API bool operator <(const CString& Other) const;
	
	CORE_API CString& operator=(const CString& Other);
	CORE_API CString& operator=(char* CStr);
	CORE_API CString& operator=(const char* CStr);

#if PLATFORM_WINDOWS
	CORE_API CString& operator=(wchar_t* CWStr);
	CORE_API CString& operator=(const wchar_t* CWStr);
#endif // PLATFORM_WINDOWS

	CORE_API bool operator==(const CString& Other) const;
	CORE_API bool operator==(const char* InCStr) const;

	CORE_API char operator[](UInt64 Index) const;

	CORE_API char* operator*() const;
};

CORE_API CString operator+(const char* Lhs, const CString& Rhs);