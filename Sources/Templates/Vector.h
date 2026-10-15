#pragma once

#include "String/String.h"
#include "Logger/Logger.h"
#include "Defines/Types.h"
#include "Math/Math.h"

#include <cmath>
#include <type_traits>

using namespace Core::Maths;

template<
    typename TElement,
    Int32 Size
>
struct TVector
{
    TVector() = default;

    explicit TVector(TElement Value)
    {
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Vector[Index] = Value;
        }
    }

    template<bool Condition = Size == 2, typename = std::enable_if_t<Condition>>
    TVector(TElement X, TElement Y)
    {
        Vector[0] = X;
        Vector[1] = Y;
    }

    template<bool Condition = Size == 3, typename = std::enable_if_t<Condition>>
    TVector(TElement X, TElement Y, TElement Z)
    {
        Vector[0] = X;
        Vector[1] = Y;
        Vector[2] = Z;
    }

    template<bool Condition = Size == 4, typename = std::enable_if_t<Condition>>
    TVector(TElement X, TElement Y, TElement Z, TElement W)
    {
        Vector[0] = X;
        Vector[1] = Y;
        Vector[2] = Z;
        Vector[3] = W;
    }

    TVector(const TElement(&InVector)[Size])
    {
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Vector[Index] = InVector[Index];
        }
    }

    TElement X() const
    {
        return Vector[0];
    }

    TElement& X()
    {
        return Vector[0];
    }

    TElement Y() const
    {
        return Vector[1];
    }

    TElement& Y()
    {
        return Vector[1];
    }

    template <bool Condition = Size >= 3>
    std::enable_if_t<Condition, TElement> Z() const
    {
        return Vector[2];
    }

    template<bool Condition = Size >= 3>
    std::enable_if_t<Condition, TElement&> Z()
    {
        return Vector[2];
    }

    template <bool Condition = Size >= 4>
    std::enable_if_t<Condition, TElement> W() const
    {
        return Vector[3];
    }

    template<bool Condition = Size >= 4>
    std::enable_if_t<Condition, TElement&> W()
    {
        return Vector[3];
    }

    CString ToString() const// override
    {
        CString VectorString = "{";
        for (UInt32 Index = 0; Index < Size; Index++)
        {
            VectorString += CString("{}", static_cast<Double>(Vector[Index]));

            if (Index < Size - 1)
            {
                VectorString += ",";
            }
        }
        return VectorString += "}";
    }

    static TElement Dot(const TVector& A, const TVector& B)
    {
        if constexpr (Size == 2)
        {
            return A.X() * B.X() + A.Y() * B.Y();
        }
        else if constexpr (Size == 3)
        {
            return A.X() * B.X() + A.Y() * B.Y() + A.Z() * B.Z();
        }
        else if constexpr (Size == 4)
        {
            return A.X() * B.X() + A.Y() * B.Y() + A.Z() * B.Z() + A.W() * B.W();
        }
        else
        {
            CLogger::Fatal("Dot product is not defined for vectors with size {}", Size);
        }
    }
    
    template<bool Condition = Size == 3>
    static std::enable_if_t<Condition, TVector> Cross(const TVector& A, const TVector& B)
    {
        return {
            A.Y() * B.Z() - B.Y() * A.Z(),
            A.Z() * B.X() - B.Z() * A.X(),
            A.X() * B.Y() - B.X() * A.Y()
        };
    }

    static TElement InverseSqrt(const TVector& Vector)
    {
        return 1.f / TMath<TElement>::Sqrt(Dot(Vector, Vector));
    }

    TElement Length() const
    {
        TElement Sum {};
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Sum += TMath<TElement>::Pow(Vector[Index], 2.0);
        }

        if (Sum == 0.0)
        {
            return 0.0;
        }

        return TMath<TElement>::Sqrt(Sum);
    }

    static void Normalize(TVector& Vector)
    {
        TElement Len = Vector.Length();
        if (Len != 0.0)
        {
            for (UInt32 Index = 0; Index < Size; Index++)
            {
                Vector[Index] = Vector[Index] / Len;
            }
        }
    }

    TVector Normalized()
    {
        TVector Vector = *this;
        Normalize(Vector);
        return Vector;
    }

    bool IsNearlyEqual(const TVector& Other, TElement Tolerance) const
    {
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            if (fabs(Vector[Index] - Other.Vector[Index]) > Tolerance) return false;
        }

        return true;
    }

    TVector operator +(const TVector& Other) const
    {
        TVector Result;
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Result[Index] = Vector[Index] + Other[Index];
        }
        return Result;
    }

    TVector operator +=(const TVector& Other)
    {
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Vector[Index] = Vector[Index] + Other[Index];
        }
        return *this;
    }

    TVector operator -(const TVector& Other) const
    {
        TVector Result;
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Result[Index] = Vector[Index] - Other[Index];
        }
        return Result;
    }

    TVector operator -=(const TVector& Other)
    {
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Vector[Index] = Vector[Index] - Other[Index];
        }
        return *this;
    }

    TVector operator-()
    {
        TVector Result{};
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Result[Index] = -Result[Index];
        }
        return Result;
    }

    TVector operator *(TElement Factor) const
    {
        TVector Result;
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Result[Index] = Vector[Index] * Factor;
        }
        return Result;
    }

    TVector& operator *=(TElement Factor)
    {
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Vector[Index] = Vector[Index] * Factor;
        }
        return *this;
    }

    TVector operator/(TElement Factor)
    {
        TVector Result;
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Result[Index] = Vector[Index] / Factor;
        }
        return Result;
    }

    TVector& operator/=(TElement Factor)
    {
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            Vector[Index] = Vector[Index] / Factor;
        }
        return *this;
    }

    bool operator ==(const TVector& Other) const
    {
        for (UInt64 Index = 0; Index < Size; Index++)
        {
            if (Vector[Index] != Other[Index])
            {
                return false;
            }
        }
        return true;
    }

    bool operator !=(const TVector& Other) const
    {
        return !this->operator==(Other);
    }

    TElement& operator[](UInt64 Index)
    {
        return Vector[Index];
    }

    const TElement& operator[](UInt64 Index) const
    {
        return Vector[Index];
    }

    static const TVector& Zero()
    {
        static TVector Zero{};
        return Zero;
    }

    static const TVector& One()
    {
        static TVector One{ 1 };
        return One;
    }

    template<bool Condition = Size >= 2 && Size < 4>
    static std::enable_if_t<Condition, const TVector&> Up()
    {
        static TVector Up = []{
            TVector Temp{};
            Temp.Y() = 1;
            return Temp;
        }();
        return Up;
    }

    template<bool Condition = Size >= 2 && Size < 4>
    static std::enable_if_t<Condition, const TVector&> Down()
    {
        static TVector Down = []{
            TVector Temp{};
            Temp.Y() = -1;
            return Temp;
        }();
        return Down;
    }

    template<bool Condition = Size >= 2 && Size < 4>
    static std::enable_if_t<Condition, const TVector&> Left()
    {
        static TVector Left = []{
            TVector Temp{};
            Temp.X() = -1;
            return Temp;
        }();
        return Left;
    }

    template<bool Condition = Size >= 2 && Size < 4>
    static std::enable_if_t<Condition, const TVector&> Right()
    {
        static TVector Right = []{
            TVector Temp{};
            Temp.X() = 1;
            return Temp;
        }();
        return Right;
    }

    template<bool Condition = Size >= 3 && Size < 4>
    static std::enable_if_t<Condition, const TVector&> Forward()
    {
        static TVector Forward = []{ 
            TVector Temp{};
            Temp.Z() = 1;
            return Temp;
        }();
        return Forward;
    }

    template<bool Condition = Size >= 3 && Size < 4>
    static std::enable_if_t<Condition, const TVector&> Backward()
    {
        static TVector Backward = []{
            TVector Temp{};
            Temp.Z() = -1;
            return Temp;
        }();
        return Backward;
    }

protected:
    TElement Vector[Size] {};

    static_assert(Size <= 4, "Size must be less than or equal to 4");
};

template<
    typename TElement,
    SizeT Size
>
TVector<TElement, Size> operator*(TElement Factor, const TVector<TElement, Size>& Vector)
{
    return Vector * Factor;
}
