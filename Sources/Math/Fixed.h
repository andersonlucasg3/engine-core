#pragma once

#include "String/String.h"

#define DECLARE_FIXED_OPERATOR(OP, T, V) \
constexpr TFixed operator OP(T Value) const { TFixed Copy = *this; Copy.Value OP##= V; return Copy; }

#define DECLARE_FIXED_OPERATOR_PRIMITIVES(OP, V) \
DECLARE_FIXED_OPERATOR(OP, Int32, V); \
DECLARE_FIXED_OPERATOR(OP, Int64, V); \
DECLARE_FIXED_OPERATOR(OP, Double, V);

#define DECLARE_FIXED_OPERATOR_REF(OP, T, V) \
constexpr TFixed& operator OP(T Value) { this->Value OP V; return *this; }

#define DECLARE_FIXED_OPERATOR_REF_PRIMITIVES(OP, V) \
DECLARE_FIXED_OPERATOR_REF(OP, Int32, V); \
DECLARE_FIXED_OPERATOR_REF(OP, Int64, V); \
DECLARE_FIXED_OPERATOR_REF(OP, Double, V);

#define DECLARE_FIXED_ARITHMETIC_OPERATOR(OP, T, V)	\
constexpr TFixed operator OP(T Value, const TFixed& Fixed) { return Fixed OP V; }

// don't need to scale here
#define DECLARE_FIXED_ARITHMETIC_OPERATOR_PRIMITIVES(OP) \
DECLARE_FIXED_ARITHMETIC_OPERATOR(OP, Int32, Value); \
DECLARE_FIXED_ARITHMETIC_OPERATOR(OP, Int64, Value); \
DECLARE_FIXED_ARITHMETIC_OPERATOR(OP, Double, Value);

#define DECLARE_FIXED_COMPARISON_OPERATOR(OP, T, V) \
constexpr bool operator OP(T Value) const { return this->Value OP V; }

#define DECLARE_FIXED_COMPARISON_OPERATORS(OP) \
DECLARE_FIXED_COMPARISON_OPERATOR(OP, const TFixed&, Value.Value); \
DECLARE_FIXED_COMPARISON_OPERATOR(OP, Int32, Scaled(Value)); \
DECLARE_FIXED_COMPARISON_OPERATOR(OP, Int64, Scaled(Value)); \
DECLARE_FIXED_COMPARISON_OPERATOR(OP, Double, Scaled(Value));

#define DECLARE_FIXED_SCALED_FUNC(T) \
static Int64 Scaled(T Value) { return static_cast<Int64>(Value * Precision); }

#define DECLARE_FIXED_DESCALE_FUNC(T, R) \
static R Descale(T Value) { return static_cast<R>(Value) / static_cast<R>(Precision); }

namespace Core::Maths
{
    using namespace Types;

	template<Int64 P>
    struct TFixed
	{
		constexpr static Int64 Precision = P;

		constexpr TFixed() = default;

		constexpr TFixed(Int32 Value) : Value(Scaled(Value))
		{
			//
		}
		
		constexpr TFixed(Int64 Value) : Value(Scaled(Value))
		{
			//
		}

		constexpr TFixed(Double Value) : Value(Scaled(Value))
		{
			//
		}

		constexpr Float AsFloat() const
		{
			return static_cast<Float>(Descale(Value));
		}

		constexpr operator Double() const
		{
			return Descale(Value);
		}

		constexpr Int64 operator *() const
		{
			return Value;
		}

		constexpr TFixed operator-() const
		{
			TFixed Negated;
			Negated.Value = -Value;
			return Negated;
		}

		constexpr TFixed& operator =(Int32 NewValue)
		{
			Value = Scaled(NewValue);
			return *this;
		}

		constexpr TFixed& operator =(Int64 NewValue)
		{
			Value = Scaled(NewValue);
			return *this;
		}

		constexpr TFixed& operator =(Double NewValue)
		{
			Value = Scaled(NewValue);
			return *this;
		}

		constexpr TFixed operator+(const TFixed &Value) const 
		{
			TFixed Copy = *this;
			Copy.Value += Value.Value;
			return Copy;
		}
		
		constexpr TFixed operator+(Int32 Value) const 
		{
			TFixed Copy = *this;
			Copy.Value += Scaled(Value);
			return Copy;
		}
		
		constexpr TFixed operator+(Int64 Value) const 
		{
			TFixed Copy = *this;
			Copy.Value += Scaled(Value);
			return Copy;
		}
		
		constexpr TFixed operator+(Double Value) const 
		{
			TFixed Copy = *this;
			Copy.Value += Scaled(Value);
			return Copy;
		}

		constexpr TFixed operator-(const TFixed &Value) const 
		{
			TFixed Copy = *this;
			Copy.Value -= Value.Value;
			return Copy;
		}

		constexpr TFixed operator-(Int32 Value) const 
		{
			TFixed Copy = *this;
			Copy.Value -= Scaled(Value);
			return Copy;
		}

		constexpr TFixed operator-(Int64 Value) const 
		{
			TFixed Copy = *this;
			Copy.Value -= Scaled(Value);
			return Copy;
		}

		constexpr TFixed operator-(Double Value) const 
		{
			TFixed Copy = *this;
			Copy.Value -= Scaled(Value);
			return Copy;
		}

		constexpr TFixed operator*(const TFixed &Other) const 
		{
			TFixed Copy = *this;
			Copy.Value = static_cast<Int64>(static_cast<Double>(Copy.Value) * Descale(Other.Value));
			return Copy;
		}

		constexpr TFixed operator*(Int32 Value) const
        {
			TFixed Copy = *this;
			Copy.Value *= Value;
			return Copy;
		}
		
		constexpr TFixed operator*(Int64 Value) const 
		{
			TFixed Copy = *this;
			Copy.Value *= Value;
			return Copy;
		}
		
		constexpr TFixed operator*(Double Value) const 
		{
			TFixed Copy = *this;
			Copy.Value = static_cast<Int64>(static_cast<Double>(Copy.Value) * Value);
			return Copy;
		}

		constexpr TFixed operator/(const TFixed& Other) const 
		{
			TFixed Copy = *this;
			Copy.Value = static_cast<Int64>(static_cast<Double>(Copy.Value) / Descale(Other.Value));
			return Copy;
		}

		constexpr TFixed operator/(Int32 Value) const 
		{
			TFixed Copy = *this;
			Copy.Value /= Value;
			return Copy;
		}

		constexpr TFixed operator/(Int64 Value) const 
		{
			TFixed Copy = *this;
			Copy.Value /= Value;
			return Copy;
		}

		constexpr TFixed operator/(Double Value) const 
		{
			TFixed Copy = *this;
			Copy.Value = static_cast<Int64>(static_cast<Double>(Copy.Value) / Value);
			return Copy;
		}

		constexpr TFixed &operator+=(const TFixed &Value) 
		{
			this->Value += Value.Value;
			return *this;
		}

		constexpr TFixed &operator+=(Int32 Value) 
		{
			this->Value += Scaled(Value);
			return *this;
		}
		
		constexpr TFixed &operator+=(Int64 Value) 
		{
			this->Value += Scaled(Value);
			return *this;
		}
		
		constexpr TFixed &operator+=(Double Value) 
		{
			this->Value += Scaled(Value);
			return *this;
		}

		constexpr TFixed &operator-=(const TFixed &Value)
        {
			this->Value -= Value.Value;
			return *this;
		}

		constexpr TFixed &operator-=(Int32 Value) 
		{
			this->Value -= Scaled(Value);
			return *this;
		}
		
		constexpr TFixed &operator-=(Int64 Value) 
		{
			this->Value -= Scaled(Value);
			return *this;
		}

		constexpr TFixed &operator-=(Double Value) 
		{
			this->Value -= Scaled(Value);
			return *this;
		}

		constexpr TFixed &operator*=(const TFixed &Value) 
		{
			this->Value *= Descale(Value.Value);
			return *this;
		}

		constexpr TFixed &operator*=(Int32 Value) 
		{
			this->Value *= Value;
			return *this;
		}

		constexpr TFixed &operator*=(Int64 Value) 
		{
			this->Value *= Value;
			return *this;
		}

		constexpr TFixed &operator*=(Double Value) 
		{
			this->Value *= Value;
			return *this;
		}

		constexpr TFixed &operator/=(const TFixed &Value) 
		{
			this->Value /= Descale(Value.Value);
			return *this;
		}

		constexpr TFixed &operator/=(Int32 Value) 
		{
			this->Value /= Value;
			return *this;
		}

		constexpr TFixed &operator/=(Int64 Value) 
		{
			this->Value /= Value;
			return *this;
		}

		constexpr TFixed &operator/=(Double Value) 
		{
			this->Value /= Value;
			return *this;
		}

		constexpr bool operator>(const TFixed &Value) const 
		{
			return this->Value > Value.Value;
		}

		constexpr bool operator>(Int32 Value) const 
		{
			return this->Value > Scaled(Value);
		}

		constexpr bool operator>(Int64 Value) const 
		{
			return this->Value > Scaled(Value);
		}

		constexpr bool operator>(Double Value) const 
		{
			return this->Value > Scaled(Value);
		}

		constexpr bool operator>=(const TFixed &Value) const 
		{
			return this->Value >= Value.Value;
		}

		constexpr bool operator>=(Int32 Value) const 
		{
			return this->Value >= Scaled(Value);
		}

		constexpr bool operator>=(Int64 Value) const 
		{
			return this->Value >= Scaled(Value);
		}

		constexpr bool operator>=(Double Value) const 
		{
			return this->Value >= Scaled(Value);
		}

		constexpr bool operator<(const TFixed &Value) const
        {
			return this->Value < Value.Value;
		}
		
		constexpr bool operator<(Int32 Value) const
        {
			return this->Value < Scaled(Value);
		}
		
		constexpr bool operator<(Int64 Value) const
        {
			return this->Value < Scaled(Value);
		}

		constexpr bool operator<(Double Value) const
        {
			return this->Value < Scaled(Value);
		}

		constexpr bool operator<=(const TFixed &Value) const
        {
			return this->Value <= Value.Value;
		}

		constexpr bool operator<=(Int32 Value) const
        {
			return this->Value <= Scaled(Value);
		}

		constexpr bool operator<=(Int64 Value) const
        {
			return this->Value <= Scaled(Value);
		}

		constexpr bool operator<=(Double Value) const
        {
			return this->Value <= Scaled(Value);
		}

		constexpr bool operator==(const TFixed &Value) const 
		{
			return this->Value == Value.Value;
		}

		constexpr bool operator==(Int32 Value) const 
		{
			return this->Value == Scaled(Value);
		}

		constexpr bool operator==(Int64 Value) const 
		{
			return this->Value == Scaled(Value);
		}

		constexpr bool operator==(Double Value) const 
		{
			return this->Value == Scaled(Value);
		}

		constexpr bool operator!=(const TFixed &Value) const
		{
			return this->Value != Value.Value;
		}

		constexpr bool operator!=(Int32 Value) const 
		{
			return this->Value != Scaled(Value);
		}

		constexpr bool operator!=(Int64 Value) const 
		{
			return this->Value != Scaled(Value);
		}

		constexpr bool operator!=(Double Value) const 
		{
			return this->Value != Scaled(Value);
		}

		static Int64 Scaled(Int32 Value) 
		{
			return static_cast<Int64>(Value * Precision);
		}

		static Int64 Scaled(Int64 Value) 
		{
			return static_cast<Int64>(Value * Precision);
		}

		static Int64 Scaled(Double Value) 
		{
			return static_cast<Int64>(Value * Precision);
		}

		static Double Descale(Int64 Value) 
		{
			return static_cast<Double>(Value) / static_cast<Double>(Precision);
		};

		CString ToString() const
		{
			return CString("(d:{}, f:{:.6f})", Value, Descale(Value));
		}

	private:
		Int64 Value = 0;
	};

	typedef TFixed<1000000000L> SFixed;

	constexpr SFixed operator+(Int32 Value, const SFixed &Fixed) 
	{
		return Fixed + Value;
	}

	constexpr SFixed operator+(Int64 Value, const SFixed &Fixed) 
	{
		return Fixed + Value;
	}
	
	constexpr SFixed operator+(Double Value, const SFixed &Fixed) 
	{
		return Fixed + Value;
	}

	constexpr SFixed operator-(Int32 Value, const SFixed &Fixed) 
	{
		return Fixed - Value;
	}

	constexpr SFixed operator-(Int64 Value, const SFixed &Fixed) 
	{
		return Fixed - Value;
	}

	constexpr SFixed operator-(Double Value, const SFixed &Fixed) 
	{
		return Fixed - Value;
	}

	constexpr SFixed operator*(Int32 Value, const SFixed &Fixed) 
	{
		return Fixed * Value;
	}

	constexpr SFixed operator*(Int64 Value, const SFixed &Fixed) 
	{
		return Fixed * Value;
	}
	
	constexpr SFixed operator*(Double Value, const SFixed &Fixed) 
	{
		return Fixed * Value;
	}

	constexpr SFixed operator/(Int32 Value, const SFixed &Fixed) 
	{
		return Fixed / Value;
	}

	constexpr SFixed operator/(Int64 Value, const SFixed &Fixed) 
	{
		return Fixed / Value;
	}

	constexpr SFixed operator/(Double Value, const SFixed &Fixed) 
	{
		return Fixed / Value;
	}
}
