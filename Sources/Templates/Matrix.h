#pragma once

#include "Vector.h"
#include "String/String.h"
#include "Environment/Environment.h"

#include <initializer_list>

template<
    typename TElement,
    SizeT Size
>
struct TMatrix
{
private:
    using TVector = TVector<TElement, Size>;

public:
    TMatrix() = default;

    TMatrix(TElement Value)
    {
        for (UInt64 Row = 0; Row < Size; Row++)
        {
            for (UInt64 Col = 0; Col < Size; Col++)
            {
                Matrix[Row][Col] = Value;
            }
        }
    }

    TMatrix(const TElement(&InMatrix)[Size][Size])
    {
        for (UInt64 Row = 0; Row < Size; Row++)
        {
            for (UInt64 Col = 0; Col < Size; Col++)
            {
                Matrix[Row][Col] = InMatrix[Row][Col];
            }
        }
    }

    TMatrix(std::initializer_list<std::initializer_list<TElement>> InitList)
    {
        UInt64 Row = 0;
        for (const auto& RowList : InitList)
        {
            UInt64 Col = 0;
            for (const auto& Element : RowList)
            {
                Matrix[Row][Col] = Element;
                Col++;
            }
            Row++;
        }
    }

    static TMatrix Multiply(const TMatrix& A, TElement B)
    {
        TMatrix Result {};
        for (UInt64 Row = 0; Row < Size; Row++)
        {
            for (UInt64 Col = 0; Col < Size; Col++)
            {
                Result[Row][Col] = A[Row][Col] * B;
            }
        }
        return Result;
    }

    static TMatrix Multiply(const TMatrix& A, const TVector& B)
    {
        TMatrix Result {};
        for (UInt64 Row = 0; Row < Size; Row++)
        {
            for (UInt64 Col = 0; Col < Size; Col++)
            {
                for (UInt64 K = 0; K < Size; K++)
                {
                    Result[Row][Col] += A[Row][K] * B[K];
                }
            }
        }
        return Result;
    }

    static TMatrix Multiply(const TMatrix& A, const TMatrix& B)
    {
        TMatrix Result {};
        for (UInt64 Row = 0; Row < Size; Row++)
        {
            for (UInt64 Col = 0; Col < Size; Col++)
            {
                for (UInt64 K = 0; K < Size; K++)
                {
                    TElement Elem1 = A[Row][K];
                    TElement Elem2 = B[K][Col];
                    Result[Row][Col] += Elem1 * Elem2;
                }
            }
        }
        return Result;
    }

    static TMatrix Sum(const TMatrix& A, const TMatrix& B)
    {
        TMatrix Result {};
        for (UInt64 Row = 0; Row < Size; Row++)
        {
            for (UInt64 Col = 0; Col < Size; Col++)
            {
                Result[Row][Col] = A[Row][Col] + B[Row][Col];
            }
        }
        return Result;
    }

    static TMatrix Sub(const TMatrix& A, const TMatrix& B)
    {
        TMatrix Result {};
        for (UInt64 Row = 0; Row < Size; Row++)
        {
            for (UInt64 Col = 0; Col < Size; Col++)
            {
                Result[Row][Col] = A[Row][Col] - B[Row][Col];
            }
        }
        return Result;
    }

    // TODO: strip this code in case of non-debug build
    CString ToString() const
    {
        CString MatrixString = CEnvironment::NewLine();
        MatrixString += "{";
        for (UInt32 VectorIndex = 0; VectorIndex < Size; VectorIndex++)
        {
            const TVector& Vector = Matrix[VectorIndex];

            MatrixString += CEnvironment::NewLine();
            MatrixString += "\t{";
            for (UInt32 Index = 0; Index < Size; Index++)
            {
                MatrixString += CString(" {}", Vector[Index]);

                if (Index < Size - 1)
                {
                    MatrixString += ",";
                }
            }
            MatrixString += " }";

            if (VectorIndex < Size - 1)
            {
                MatrixString += ",";
            }
        }
        MatrixString += CEnvironment::NewLine();
        return MatrixString += "}";
    }

    TMatrix operator*(TElement Factor) const
    {
        return Multiply(*this, Factor);
    }

    TMatrix& operator*=(TElement Factor)
    {
        TMatrix Result = Multiply(*this, Factor);
        this->Matrix = Result.Matrix;
        return *this;
    }

    TMatrix operator*(const TVector& Vector) const
    {
        return Multiply(*this, Vector);
    }

    TMatrix& operator*=(const TVector& Vector)
    {
        TMatrix Result = Multiply(*this, Vector);
        this->Matrix = Result.Matrix;
        return *this;
    }

    TMatrix operator*(const TMatrix& Other) const
    {
        return Multiply(*this, Other);
    }

    TMatrix& operator*=(const TMatrix& Other)
    {
        return (*this = Multiply(*this, Other));
    }

    TMatrix operator+(const TMatrix& Other)
    {
        return Sum(*this, Other);
    }

    TMatrix& operator+=(const TMatrix& Other)
    {
        return (*this = Sum(*this, Other));
    }

    TMatrix operator-(const TMatrix& Other)
    {
        return Sub(*this, Other);
    }

    TMatrix& operator-=(const TMatrix& Other)
    {
        return (*this = Sub(*this, Other));
    }

    TVector& operator[](UInt64 Index)
    {
        return Matrix[Index];
    }

    const TVector& operator[](UInt64 Index) const
    {
        return Matrix[Index];
    }

    static const TMatrix& Identity()
    {
        static TMatrix Identity = []{
            TMatrix Temp{};
            for (UInt64 Index = 0; Index < Size; Index++)
            {
                Temp[Index][Index] = 1;
            }
            return Temp;
        }();
        return Identity;
    }

private:
    TVector Matrix[Size] {};
};
