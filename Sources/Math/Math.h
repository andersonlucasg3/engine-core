#pragma once

#include "Defines/Types.h"

#include "Fixed.h"

#include <cmath>

#if PLATFORM_WINDOWS
#include "corecrt_math_defines.h"
#endif // PLATFORM_WINDOWS

namespace Core::Maths
{
    using namespace Types;

    template<typename TElement>
    struct TMath
    {
        inline static const TElement HalfHalfPI = static_cast<TElement>(M_PI_4);
        inline static const TElement HalfPI = static_cast<TElement>(M_PI_2);
        inline static const TElement PI = static_cast<TElement>(M_PI);
        inline static const TElement ThreeHalfPI = static_cast<TElement>(3.0 * M_PI_2);
        inline static const TElement TwoPI = static_cast<TElement>(2 * M_PI);
        
        static TElement Rad2Deg(TElement Radians)
        {
            return Radians * RAD2DEG;
        }

        static TElement Deg2Rad(TElement Degrees)
        {
            return Degrees * DEG2RAD;
        }

        static TElement Cos(TElement Rad)
        {
            return std::cos(Rad);
        }
        
        static TElement CosDeg(TElement Degrees)
        {
            return Cos(Deg2Rad(Degrees));
        }
        
        static TElement Sin(TElement Rad)
        {
            return std::sin(Rad);
        }

        static TElement SinDeg(TElement Degrees)
        {
            return Sin(Deg2Rad(Degrees));
        }

        static TElement Tan(TElement Rad)
        {
            return std::tan(Rad);
        }
        
        static TElement TanDeg(TElement Degrees)
        {
            return Tan(Deg2Rad(Degrees));
        }

        static TElement CopySign(TElement Number, TElement Sign)
        {
            return std::copysign(Number, Sign);
        }
        
        static TElement Atan2(TElement Num1, TElement Num2)
        {
            return std::atan2(Num1, Num2);
        }
        
        static TElement Abs(TElement Num)
        {
            return std::abs(Num);
        }
        
        static TElement Asin(TElement Num)
        {
            return std::asin(Num);
        }

        static TElement Pow(TElement Num, TElement Power)
        {
            return std::pow(Num, Power);
        }
        
        static TElement Sqrt(TElement Num)
        {
            return std::sqrt(Num);
        }

    private:
        inline static const TElement DEG2RAD = static_cast<TElement>(M_PI / 180.0);
        inline static const TElement RAD2DEG = static_cast<TElement>(180.0 / M_PI);

        TMath() = delete;
    };

    typedef TMath<SFixed> SFMath;
    typedef TMath<Float> SMathF;
}
