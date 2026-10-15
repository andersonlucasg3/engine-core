#pragma once

struct IDeleter
{
	inline virtual ~IDeleter() = default;

	inline virtual void Delete() = 0;
};

template<typename TPtr>
struct TDeleter : public IDeleter
{
	inline TDeleter(TPtr* InPtr) : _ptr(InPtr)
	{
		//
	}

	inline ~TDeleter() override = default;

	inline void Delete() override
	{
		if (_ptr == nullptr) return;

		delete _ptr;
	}

protected:
	TPtr* _ptr = nullptr;
};