// Created by amoylel on 14/02/2019.
// Copyright (c) 2019 amoylel All rights reserved.

#ifndef JSON_JSON_18852008_BC51_457D_91D6_9A25CCA25F7C_HPP__
#define JSON_JSON_18852008_BC51_457D_91D6_9A25CCA25F7C_HPP__

#include <assert.h>
#include <math.h>
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <type_traits>
#include <cstring>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <array>
#include <bitset>
#include <iostream>
#include <cmath>


//////////////////////////////////////////////////////////////////////////
#ifndef IMPORTS_70AAA82F_44D5_45BD_93FC_D6DFFA1B711C
#define IMPORTS_70AAA82F_44D5_45BD_93FC_D6DFFA1B711C
///!@import begin
///!@import segment_macro_namespaces
///!@import segment_logger_defines_mcro
///!@import segment_is_int_xx_t
///!@import segment_is_uint_xx_t
///!@import segment_to_string
///!@import segment_from_string
///!@import segment_memory_writer
///!@import segment_json_memory_allocator
///!@import segment_json_enum
///!@import segment_json_string_parser
///!@import segment_json_number_parser
///!@import segment_json_string_reader
///!@import segment_json_stream_reader
///!@import segment_json_array_container
///!@import segment_json_object_container
///!@import segment_json_data_types
///!@import segment_json_key_string
///!@import segment_single_json_object_helper
///!@import segment_json_value_proxy
///!@import segment_json_data_object
///!@import segment_json_parser
///!@import segment_basic_json
///!@import segment_json_object_helper
///!@import segment_json_object





#ifndef segment_macro_namespaces
#define segment_macro_namespaces

#ifndef _AMO_NAMESPACE_BEGIN
#define _AMO_NAMESPACE_BEGIN namespace amo {
#endif

#ifndef _AMO_NAMESPACE_END
#define _AMO_NAMESPACE_END }
#endif

#ifndef _AMO
#define _AMO ::amo::
#endif

///!@segment update timestamp 20200216211257
#endif //segment_macro_namespaces


#ifndef segment_logger_defines_mcro
#define segment_logger_defines_mcro

#include <ctime>
#include <mutex>
#include <string>
static std::mutex& logger_mutex() { static std::mutex mutex;  return mutex; }
template<typename ... Args>
static void logger_defines_mcro_print_log(const char* level_, const char* function_name_, int line_, const char* fmt_,
        Args&& ... args) {
    std::mutex& mutex = logger_mutex();
    mutex.lock();
    std::time_t t = std::time(NULL);
    char mbstr[100] = { 0 };
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#endif
    std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
#ifdef _MS_VER
#pragma warning(pop)
#endif
    std::string fmt = "[%s][%s] [%s:%d] ";
    fmt += fmt_;
    fmt += "\n";
    printf(fmt.c_str(), mbstr, level_, function_name_, line_, args...);
    mutex.unlock();
}

#ifndef $cdevel
#define $cdevel(fmt, ...) logger_defines_mcro_print_log("trace", __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#endif
#ifndef $cdebug
#define $cdebug(fmt, ...) logger_defines_mcro_print_log("debug", __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#endif
#ifndef $cinfo
#define $cinfo(fmt, ...) logger_defines_mcro_print_log("info", __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#endif
#ifndef $cwarn
#define $cwarn(fmt, ...) logger_defines_mcro_print_log("warnning", __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#endif
#ifndef $cerr
#define $cerr(fmt, ...) logger_defines_mcro_print_log("error", __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#endif
#ifndef $cfatal
#define $cfatal(fmt, ...) logger_defines_mcro_print_log("fatal", __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#endif

///!@segment update timestamp 20200216211257
#endif //segment_logger_defines_mcro


#ifndef segment_is_int_xx_t
#define segment_is_int_xx_t

_AMO_NAMESPACE_BEGIN
template<typename T> struct is_int_xx_t {
    const static int value = std::is_same<T, int8_t>::value || std::is_same<T, int16_t>::value
                             || std::is_same<T, int32_t>::value || std::is_same<T, int64_t>::value;
};
_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_is_int_xx_t


#ifndef segment_is_uint_xx_t
#define segment_is_uint_xx_t

_AMO_NAMESPACE_BEGIN
template<typename T> struct is_uint_xx_t {
    const static int value = std::is_same<T, uint8_t>::value || std::is_same<T, uint16_t>::value
                             || std::is_same<T, uint32_t>::value || std::is_same<T, uint64_t>::value;
};
_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_is_uint_xx_t


#ifndef segment_int_to_string
#define segment_int_to_string

#define P(T) T, '0',  T, '1', T, '2', T, '3', T, '4', T, '5', T, '6', T, '7', T, '8', T, '9'

_AMO_NAMESPACE_BEGIN
struct Pair {
    char t, o;
};
static const Pair s_pairs[] = { P('0'), P('1'), P('2'), P('3'), P('4'), P('5'), P('6'), P('7'), P('8'), P('9') };
_AMO_NAMESPACE_END


#define ITOA_W(N, I) *(Pair*)&b[N] = s_pairs[I]
#define ITOA_A(N) t = (uint64_t(1) << (32 + N / 5 * N * 53 / 16)) / uint32_t(1e##N) + 1 + N/6 - N/8, t *= u, t >>= N / 5 * N * 53 / 16, t += N / 6 * 4, ITOA_W(0, t >> 32)
#define ITOA_S(N) b[N] = char(uint64_t(10) * uint32_t(t) >> 32) + '0'
#define ITOA_D(N) t = uint64_t(100) * uint32_t(t), ITOA_W(N, t >> 32)

#define ITOA_C0 b[0] = char(u) + '0'
#define ITOA_C1 ITOA_W(0, u)
#define ITOA_C2 ITOA_A(1), ITOA_S(2)
#define ITOA_C3 ITOA_A(2), ITOA_D(2)
#define ITOA_C4 ITOA_A(3), ITOA_D(2), ITOA_S(4)
#define ITOA_C5 ITOA_A(4), ITOA_D(2), ITOA_D(4)
#define ITOA_C6 ITOA_A(5), ITOA_D(2), ITOA_D(4), ITOA_S(6)
#define ITOA_C7 ITOA_A(6), ITOA_D(2), ITOA_D(4), ITOA_D(6)
#define ITOA_C8 ITOA_A(7), ITOA_D(2), ITOA_D(4), ITOA_D(6), ITOA_S(8)
#define ITOA_C9 ITOA_A(8), ITOA_D(2), ITOA_D(4), ITOA_D(6), ITOA_D(8)

#define L09(F) u < 100        ? L01(F) : L29(F)
#define L29(F) u < 1000000    ? L25(F) : L69(F)
#define L25(F) u < 10000      ? L23(F) : L45(F)
#define L69(F) u < 100000000  ? L67(F) : L89(F)
#define L03(F) u < 100        ? L01(F) : L23(F)

#define L01(F) u < 10         ? F(0) : F(1)
#define L23(F) u < 1000       ? F(2) : F(3)
#define L45(F) u < 100000     ? F(4) : F(5)
#define L67(F) u < 10000000   ? F(6) : F(7)
#define L89(F) u < 1000000000 ? F(8) : F(9)

#define PART(N) (ITOA_C##N, b += N + 1)
#define LAST(N) (ITOA_C##N, terminate<RESULT>(b + N + 1))


_AMO_NAMESPACE_BEGIN


template<class T> inline T terminate(char* b) {
    return b;
}
template<> inline void terminate<void>(char* b) {
    *b = 0;
}


template < class RESULT = char*, class T>
inline typename std::enable_if < (sizeof(T) <= sizeof(uint32_t)), size_t >::type integer_to_chars(T i, char* b) {
    char* addr = b;
    uint64_t t;
    uint32_t u = i < 0 ? *b++ = '-', 0u - uint32_t(int32_t(i)) : uint32_t(i);
    return (char*)(L09(LAST)) - b;
}

template<class RESULT = char*, class T>
inline typename std::enable_if<(sizeof(T) == sizeof(uint64_t)), size_t>::type integer_to_chars(T i, char* b) {
    char* addr = b;
    uint64_t t;
    uint64_t n = i < 0 ? *b++ = '-', 0u - uint64_t(i) : uint64_t(i);
    uint32_t u = uint32_t(n);
    
    if (u == n) {
        return (char*)(L09(LAST)) - addr;
    }
    
    uint64_t a = n / 100000000u;
    u = uint32_t(a);
    
    if (u == a) {
        L09(PART);
    } else {
        u = uint32_t(a / 100000000u);
        L03(PART);
        u = a % 100000000u;
        PART(7);
    }
    
    u = n % 100000000u;
    return (char*)(LAST(7)) - addr;
}
_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_int_to_string


#ifndef segment_double_to_string
#define segment_double_to_string

#define UINT64_C2(h, l) ((static_cast<uint64_t>(h) << 32) | static_cast<uint64_t>(l))

struct DiyFp {
    DiyFp() {}
    
    DiyFp(uint64_t f, int e) : f(f), e(e) {}
    
    DiyFp(double d) {
        union {
            double d;
            uint64_t u64;
        } u = { d };
        
        int biased_e = (u.u64 & kDpExponentMask) >> kDpSignificandSize;
        uint64_t significand = (u.u64 & kDpSignificandMask);
        
        if (biased_e != 0) {
            f = significand + kDpHiddenBit;
            e = biased_e - kDpExponentBias;
        } else {
            f = significand;
            e = kDpMinExponent + 1;
        }
    }
    
    DiyFp operator-(const DiyFp& rhs) const {
        assert(e == rhs.e);
        assert(f >= rhs.f);
        return DiyFp(f - rhs.f, e);
    }
    
    DiyFp operator*(const DiyFp& rhs) const {
#if defined(_MSC_VER) && defined(_M_AMD64)
        uint64_t h;
        uint64_t l = _umul128(f, rhs.f, &h);
        
        if (l & (uint64_t(1) << 63)) { // rounding
            h++;
        }
        
        return DiyFp(h, e + rhs.e + 64);
#elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__x86_64__)
        unsigned __int128 p = static_cast<unsigned __int128>(f) * static_cast<unsigned __int128>(rhs.f);
        uint64_t h = p >> 64;
        uint64_t l = static_cast<uint64_t>(p);
        
        if (l & (uint64_t(1) << 63)) { // rounding
            h++;
        }
        
        return DiyFp(h, e + rhs.e + 64);
#else
        const uint64_t M32 = 0xFFFFFFFF;
        const uint64_t a = f >> 32;
        const uint64_t b = f & M32;
        const uint64_t c = rhs.f >> 32;
        const uint64_t d = rhs.f & M32;
        const uint64_t ac = a * c;
        const uint64_t bc = b * c;
        const uint64_t ad = a * d;
        const uint64_t bd = b * d;
        uint64_t tmp = (bd >> 32) + (ad & M32) + (bc & M32);
        tmp += 1U << 31;  /// mult_round
        return DiyFp(ac + (ad >> 32) + (bc >> 32) + (tmp >> 32), e + rhs.e + 64);
#endif
    }
    
    DiyFp Normalize() const {
#if defined(_MSC_VER) && defined(_M_AMD64)
        unsigned long index;
        _BitScanReverse64(&index, f);
        return DiyFp(f << (63 - index), e - (63 - index));
#elif defined(__GNUC__)
        int s = __builtin_clzll(f);
        return DiyFp(f << s, e - s);
#else
        DiyFp res = *this;
        
        while (!(res.f & kDpHiddenBit)) {
            res.f <<= 1;
            res.e--;
        }
        
        res.f <<= (kDiySignificandSize - kDpSignificandSize - 1);
        res.e = res.e - (kDiySignificandSize - kDpSignificandSize - 1);
        return res;
#endif
    }
    
    DiyFp NormalizeBoundary() const {
#if defined(_MSC_VER) && defined(_M_AMD64)
        unsigned long index;
        _BitScanReverse64(&index, f);
        return DiyFp(f << (63 - index), e - (63 - index));
#else
        DiyFp res = *this;
        
        while (!(res.f & (kDpHiddenBit << 1))) {
            res.f <<= 1;
            res.e--;
        }
        
        res.f <<= (kDiySignificandSize - kDpSignificandSize - 2);
        res.e = res.e - (kDiySignificandSize - kDpSignificandSize - 2);
        return res;
#endif
    }
    
    void NormalizedBoundaries(DiyFp* minus, DiyFp* plus) const {
        DiyFp pl = DiyFp((f << 1) + 1, e - 1).NormalizeBoundary();
        DiyFp mi = (f == kDpHiddenBit) ? DiyFp((f << 2) - 1, e - 2) : DiyFp((f << 1) - 1, e - 1);
        mi.f <<= mi.e - pl.e;
        mi.e = pl.e;
        *plus = pl;
        *minus = mi;
    }
    
    static const int kDiySignificandSize = 64;
    static const int kDpSignificandSize = 52;
    static const int kDpExponentBias = 0x3FF + kDpSignificandSize;
    static const int kDpMinExponent = -kDpExponentBias;
    static const uint64_t kDpExponentMask = UINT64_C2(0x7FF00000, 0x00000000);
    static const uint64_t kDpSignificandMask = UINT64_C2(0x000FFFFF, 0xFFFFFFFF);
    static const uint64_t kDpHiddenBit = UINT64_C2(0x00100000, 0x00000000);
    
    uint64_t f;
    int e;
};

inline DiyFp GetCachedPower(int e, int* K) {
    // 10^-348, 10^-340, ..., 10^340
    static const uint64_t kCachedPowers_F[] = {
        UINT64_C2(0xfa8fd5a0, 0x081c0288), UINT64_C2(0xbaaee17f, 0xa23ebf76),
        UINT64_C2(0x8b16fb20, 0x3055ac76), UINT64_C2(0xcf42894a, 0x5dce35ea),
        UINT64_C2(0x9a6bb0aa, 0x55653b2d), UINT64_C2(0xe61acf03, 0x3d1a45df),
        UINT64_C2(0xab70fe17, 0xc79ac6ca), UINT64_C2(0xff77b1fc, 0xbebcdc4f),
        UINT64_C2(0xbe5691ef, 0x416bd60c), UINT64_C2(0x8dd01fad, 0x907ffc3c),
        UINT64_C2(0xd3515c28, 0x31559a83), UINT64_C2(0x9d71ac8f, 0xada6c9b5),
        UINT64_C2(0xea9c2277, 0x23ee8bcb), UINT64_C2(0xaecc4991, 0x4078536d),
        UINT64_C2(0x823c1279, 0x5db6ce57), UINT64_C2(0xc2109436, 0x4dfb5637),
        UINT64_C2(0x9096ea6f, 0x3848984f), UINT64_C2(0xd77485cb, 0x25823ac7),
        UINT64_C2(0xa086cfcd, 0x97bf97f4), UINT64_C2(0xef340a98, 0x172aace5),
        UINT64_C2(0xb23867fb, 0x2a35b28e), UINT64_C2(0x84c8d4df, 0xd2c63f3b),
        UINT64_C2(0xc5dd4427, 0x1ad3cdba), UINT64_C2(0x936b9fce, 0xbb25c996),
        UINT64_C2(0xdbac6c24, 0x7d62a584), UINT64_C2(0xa3ab6658, 0x0d5fdaf6),
        UINT64_C2(0xf3e2f893, 0xdec3f126), UINT64_C2(0xb5b5ada8, 0xaaff80b8),
        UINT64_C2(0x87625f05, 0x6c7c4a8b), UINT64_C2(0xc9bcff60, 0x34c13053),
        UINT64_C2(0x964e858c, 0x91ba2655), UINT64_C2(0xdff97724, 0x70297ebd),
        UINT64_C2(0xa6dfbd9f, 0xb8e5b88f), UINT64_C2(0xf8a95fcf, 0x88747d94),
        UINT64_C2(0xb9447093, 0x8fa89bcf), UINT64_C2(0x8a08f0f8, 0xbf0f156b),
        UINT64_C2(0xcdb02555, 0x653131b6), UINT64_C2(0x993fe2c6, 0xd07b7fac),
        UINT64_C2(0xe45c10c4, 0x2a2b3b06), UINT64_C2(0xaa242499, 0x697392d3),
        UINT64_C2(0xfd87b5f2, 0x8300ca0e), UINT64_C2(0xbce50864, 0x92111aeb),
        UINT64_C2(0x8cbccc09, 0x6f5088cc), UINT64_C2(0xd1b71758, 0xe219652c),
        UINT64_C2(0x9c400000, 0x00000000), UINT64_C2(0xe8d4a510, 0x00000000),
        UINT64_C2(0xad78ebc5, 0xac620000), UINT64_C2(0x813f3978, 0xf8940984),
        UINT64_C2(0xc097ce7b, 0xc90715b3), UINT64_C2(0x8f7e32ce, 0x7bea5c70),
        UINT64_C2(0xd5d238a4, 0xabe98068), UINT64_C2(0x9f4f2726, 0x179a2245),
        UINT64_C2(0xed63a231, 0xd4c4fb27), UINT64_C2(0xb0de6538, 0x8cc8ada8),
        UINT64_C2(0x83c7088e, 0x1aab65db), UINT64_C2(0xc45d1df9, 0x42711d9a),
        UINT64_C2(0x924d692c, 0xa61be758), UINT64_C2(0xda01ee64, 0x1a708dea),
        UINT64_C2(0xa26da399, 0x9aef774a), UINT64_C2(0xf209787b, 0xb47d6b85),
        UINT64_C2(0xb454e4a1, 0x79dd1877), UINT64_C2(0x865b8692, 0x5b9bc5c2),
        UINT64_C2(0xc83553c5, 0xc8965d3d), UINT64_C2(0x952ab45c, 0xfa97a0b3),
        UINT64_C2(0xde469fbd, 0x99a05fe3), UINT64_C2(0xa59bc234, 0xdb398c25),
        UINT64_C2(0xf6c69a72, 0xa3989f5c), UINT64_C2(0xb7dcbf53, 0x54e9bece),
        UINT64_C2(0x88fcf317, 0xf22241e2), UINT64_C2(0xcc20ce9b, 0xd35c78a5),
        UINT64_C2(0x98165af3, 0x7b2153df), UINT64_C2(0xe2a0b5dc, 0x971f303a),
        UINT64_C2(0xa8d9d153, 0x5ce3b396), UINT64_C2(0xfb9b7cd9, 0xa4a7443c),
        UINT64_C2(0xbb764c4c, 0xa7a44410), UINT64_C2(0x8bab8eef, 0xb6409c1a),
        UINT64_C2(0xd01fef10, 0xa657842c), UINT64_C2(0x9b10a4e5, 0xe9913129),
        UINT64_C2(0xe7109bfb, 0xa19c0c9d), UINT64_C2(0xac2820d9, 0x623bf429),
        UINT64_C2(0x80444b5e, 0x7aa7cf85), UINT64_C2(0xbf21e440, 0x03acdd2d),
        UINT64_C2(0x8e679c2f, 0x5e44ff8f), UINT64_C2(0xd433179d, 0x9c8cb841),
        UINT64_C2(0x9e19db92, 0xb4e31ba9), UINT64_C2(0xeb96bf6e, 0xbadf77d9),
        UINT64_C2(0xaf87023b, 0x9bf0ee6b)
    };
    static const int16_t kCachedPowers_E[] = {
        -1220, -1193, -1166, -1140, -1113, -1087, -1060, -1034, -1007,  -980,
            -954,  -927,  -901,  -874,  -847,  -821,  -794,  -768,  -741,  -715,
            -688,  -661,  -635,  -608,  -582,  -555,  -529,  -502,  -475,  -449,
            -422,  -396,  -369,  -343,  -316,  -289,  -263,  -236,  -210,  -183,
            -157,  -130,  -103,   -77,   -50,   -24,     3,    30,    56,    83,
            109,   136,   162,   189,   216,   242,   269,   295,   322,   348,
            375,   402,   428,   455,   481,   508,   534,   561,   588,   614,
            641,   667,   694,   720,   747,   774,   800,   827,   853,   880,
            907,   933,   960,   986,  1013,  1039,  1066
        };
        
    //int k = static_cast<int>(ceil((-61 - e) * 0.30102999566398114)) + 374;
    double dk = (-61 - e) * 0.30102999566398114 + 347;	// dk must be positive, so can do ceiling in positive
    int k = static_cast<int>(dk);
    
    if (k != dk) {
        k++;
    }
    
    unsigned index = static_cast<unsigned>((k >> 3) + 1);
    *K = -(-348 + static_cast<int>(index << 3));	// decimal exponent no need lookup table
    
    assert(index < sizeof(kCachedPowers_F) / sizeof(kCachedPowers_F[0]));
    return DiyFp(kCachedPowers_F[index], kCachedPowers_E[index]);
}

inline void GrisuRound(char* buffer, int len, uint64_t delta, uint64_t rest, uint64_t ten_kappa, uint64_t wp_w) {
    while (rest < wp_w && delta - rest >= ten_kappa &&
            (rest + ten_kappa < wp_w ||  /// closer
             wp_w - rest > rest + ten_kappa - wp_w)) {
        buffer[len - 1]--;
        rest += ten_kappa;
    }
}

inline unsigned CountDecimalDigit32(uint32_t n) {
    // Simple pure C++ implementation was faster than __builtin_clz version in this situation.
    if (n < 10) {
        return 1;
    }
    
    if (n < 100) {
        return 2;
    }
    
    if (n < 1000) {
        return 3;
    }
    
    if (n < 10000) {
        return 4;
    }
    
    if (n < 100000) {
        return 5;
    }
    
    if (n < 1000000) {
        return 6;
    }
    
    if (n < 10000000) {
        return 7;
    }
    
    if (n < 100000000) {
        return 8;
    }
    
    if (n < 1000000000) {
        return 9;
    }
    
    return 10;
}

inline void DigitGen(const DiyFp& W, const DiyFp& Mp, uint64_t delta, char* buffer, int* len, int* K) {
    static const uint32_t kPow10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
    const DiyFp one(uint64_t(1) << -Mp.e, Mp.e);
    const DiyFp wp_w = Mp - W;
    uint32_t p1 = static_cast<uint32_t>(Mp.f >> -one.e);
    uint64_t p2 = Mp.f & (one.f - 1);
    int kappa = static_cast<int>(CountDecimalDigit32(p1));
    int max_buffer_size = *len;
    *len = 0;
    
    while (kappa > 0) {
        uint32_t d;
        
        switch (kappa) {
            case 10:
                d = p1 / 1000000000;
                p1 %= 1000000000;
                break;
                
            case  9:
                d = p1 / 100000000;
                p1 %= 100000000;
                break;
                
            case  8:
                d = p1 / 10000000;
                p1 %= 10000000;
                break;
                
            case  7:
                d = p1 / 1000000;
                p1 %= 1000000;
                break;
                
            case  6:
                d = p1 / 100000;
                p1 %= 100000;
                break;
                
            case  5:
                d = p1 / 10000;
                p1 %= 10000;
                break;
                
            case  4:
                d = p1 / 1000;
                p1 %= 1000;
                break;
                
            case  3:
                d = p1 / 100;
                p1 %= 100;
                break;
                
            case  2:
                d = p1 / 10;
                p1 %= 10;
                break;
                
            case  1:
                d = p1;
                p1 = 0;
                break;
                
            default:
#if defined(_MSC_VER)
                __assume(0);
#elif __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
                __builtin_unreachable();
#else
                d = 0;
#endif
        }
        
        if (d || *len) {
            buffer[(*len)++] = '0' + static_cast<char>(d);
            
            if (*len >= max_buffer_size) {
                *len = -1;
                return;
            }
        }
        
        kappa--;
        uint64_t tmp = (static_cast<uint64_t>(p1) << -one.e) + p2;
        
        if (tmp <= delta) {
            *K += kappa;
            GrisuRound(buffer, *len, delta, tmp, static_cast<uint64_t>(kPow10[kappa]) << -one.e, wp_w.f);
            return;
        }
    }
    
    // kappa = 0
    for (;;) {
        p2 *= 10;
        delta *= 10;
        char d = static_cast<char>(p2 >> -one.e);
        
        if (d || *len) {
            buffer[(*len)++] = '0' + d;
            
            if (*len >= max_buffer_size) {
                *len = -1;
                return;
            }
        }
        
        p2 &= one.f - 1;
        kappa--;
        
        if (p2 < delta) {
            *K += kappa;
            GrisuRound(buffer, *len, delta, p2, one.f, wp_w.f * kPow10[-kappa]);
            return;
        }
    }
}

inline void Grisu2(double value, char* buffer, int* length, int* K) {
    const DiyFp v(value);
    DiyFp w_m, w_p;
    v.NormalizedBoundaries(&w_m, &w_p);
    
    const DiyFp c_mk = GetCachedPower(w_p.e, K);
    const DiyFp W = v.Normalize() * c_mk;
    DiyFp Wp = w_p * c_mk;
    DiyFp Wm = w_m * c_mk;
    Wm.f++;
    Wp.f--;
    DigitGen(W, Wp, Wp.f - Wm.f, buffer, length, K);
}

inline const char* GetDigitsLut() {
    static const char cDigitsLut[200] = {
        '0', '0', '0', '1', '0', '2', '0', '3', '0', '4', '0', '5', '0', '6', '0', '7', '0', '8', '0', '9',
        '1', '0', '1', '1', '1', '2', '1', '3', '1', '4', '1', '5', '1', '6', '1', '7', '1', '8', '1', '9',
        '2', '0', '2', '1', '2', '2', '2', '3', '2', '4', '2', '5', '2', '6', '2', '7', '2', '8', '2', '9',
        '3', '0', '3', '1', '3', '2', '3', '3', '3', '4', '3', '5', '3', '6', '3', '7', '3', '8', '3', '9',
        '4', '0', '4', '1', '4', '2', '4', '3', '4', '4', '4', '5', '4', '6', '4', '7', '4', '8', '4', '9',
        '5', '0', '5', '1', '5', '2', '5', '3', '5', '4', '5', '5', '5', '6', '5', '7', '5', '8', '5', '9',
        '6', '0', '6', '1', '6', '2', '6', '3', '6', '4', '6', '5', '6', '6', '6', '7', '6', '8', '6', '9',
        '7', '0', '7', '1', '7', '2', '7', '3', '7', '4', '7', '5', '7', '6', '7', '7', '7', '8', '7', '9',
        '8', '0', '8', '1', '8', '2', '8', '3', '8', '4', '8', '5', '8', '6', '8', '7', '8', '8', '8', '9',
        '9', '0', '9', '1', '9', '2', '9', '3', '9', '4', '9', '5', '9', '6', '9', '7', '9', '8', '9', '9'
    };
    return cDigitsLut;
}

inline char* WriteExponent(int K, char* buffer) {
    if (K < 0) {
        *buffer++ = '-';
        K = -K;
    }
    
    if (K >= 100) {
        *buffer++ = '0' + static_cast<char>(K / 100);
        K %= 100;
        const char* d = GetDigitsLut() + K * 2;
        *buffer++ = d[0];
        *buffer++ = d[1];
    } else if (K >= 10) {
        const char* d = GetDigitsLut() + K * 2;
        *buffer++ = d[0];
        *buffer++ = d[1];
    } else {
        *buffer++ = '0' + static_cast<char>(K);
    }
    
    *buffer = '\0';
    return buffer;
}

inline int Prettify(char* buffer, int length, int k) {
    const int kk = length + k;	// 10^(kk-1) <= v < 10^kk
    
    if (length <= kk && kk <= 21) {
        // 1234e7 -> 12340000000
        for (int i = length; i < kk; i++) {
            buffer[i] = '0';
        }
        
        buffer[kk] = '.';
        buffer[kk + 1] = '0';
        buffer[kk + 2] = '\0';
        return kk + 2;
    } else if (0 < kk && kk <= 21) {
        // 1234e-2 -> 12.34
        std::memmove(&buffer[kk + 1], &buffer[kk], length - kk);
        buffer[kk] = '.';
        buffer[length + 1] = '\0';
        return length + 1;
    } else if (-6 < kk && kk <= 0) {
        // 1234e-6 -> 0.001234
        const int offset = 2 - kk;
        std::memmove(&buffer[offset], &buffer[0], length);
        buffer[0] = '0';
        buffer[1] = '.';
        
        for (int i = 2; i < offset; i++) {
            buffer[i] = '0';
        }
        
        buffer[length + offset] = '\0';
        return length + offset;
    } else if (length == 1) {
        // 1e30
        buffer[1] = 'e';
        return static_cast<int>((kk - 1, &buffer[2]) - buffer);
    } else {
        // 1234e30 -> 1.234e33
        std::memmove(&buffer[2], &buffer[1], length - 1);
        buffer[1] = '.';
        buffer[length + 1] = 'e';
        return static_cast<int>(WriteExponent(kk - 1, &buffer[0 + length + 2]) - buffer);
    }
    
    return length;
}

inline int dtoa_milo(double value, char* buffer, int max_buffer_size) {
    // Not handling NaN and inf
    assert(!std::isnan(value));
    assert(!std::isinf(value));
    
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = '0';
        buffer[3] = '\0';
        return 3;
    } else {
        if (value < 0) {
            *buffer++ = '-';
            value = -value;
        }
        
        int length = max_buffer_size, K;
        Grisu2(value, buffer, &length, &K);
        
        // 如果缓冲区长度不够则返回-1
        if (length == -1) {
            return -1;
        }
        
        int len = Prettify(buffer, length, K);
        
        if (len > max_buffer_size) {
            // throw ex
            return -1;
        }
        
        if (strlen(buffer) != len) {
            std::cout << buffer << ": " << len << std::endl;
        }
        
        return len;
        
    }
}

///!@segment update timestamp 20200216211257
#endif //segment_double_to_string


#ifndef segment_memory_buffer
#define segment_memory_buffer
_AMO_NAMESPACE_BEGIN

// basic_buffer 用于关联指针，向缓存区写入数据，写入的数据全部为char*
template<typename ValueType> class basic_buffer {
public:
    basic_buffer() : m_data(nullptr), m_current_pos(0) { }
    basic_buffer(const ValueType& data_) : m_data((ValueType*) & data_), m_current_pos(0) {}
    virtual ~basic_buffer() {}
    basic_buffer& append(const ValueType* val) {  size_t len = strlen(val);  return this->append(val, len); }
    inline basic_buffer& append(const ValueType val) {  return this->append(&val, 1); }
    inline basic_buffer& append(const ValueType* val, size_t len) {
        this->adjust_buffer_size(len);
        std::memcpy(m_data + m_current_pos, val, len);
        m_current_pos += len;
        return *this;
    }
    // 获取缓冲区指针
    inline const ValueType* data() const { return m_data;  }
    // 关联缓冲区指针
    inline void data(const ValueType* val) { m_data = (ValueType*)val; }
    // 获取当前指针位置
    inline const ValueType* current() const { return m_data + m_current_pos;  }
    // 调整缓冲区大小，适用于动态扩容缓冲区
    virtual inline bool adjust_buffer_size(size_t len) { return true; }
    // 强制刷新
    virtual inline void flush() {}
    // 获取已使用的缓冲区长度
    inline size_t size() const { return m_current_pos; }
    // 设置已使用的缓冲区长度
    inline void size(size_t val) { m_current_pos = val; }
    // 探险从start_pos开始,offset 长度的数据
    inline void erase(size_t start_pos, size_t offset = 0xffffffff) {
        size_t length = (std::min<size_t>)(offset, size() - start_pos);
        std::memset(m_data + start_pos, 0, length);
        m_current_pos = start_pos;
    }
    // 重置缓存区数据
    inline void reset() {
        std::memset(m_data, 0, size());
        m_current_pos = 0;
    }
    // 获取string对象
    inline std::string to_string() const { return std::move(std::string(m_data, m_current_pos)); }
    
    ValueType* m_data;
    size_t m_current_pos;
};

//template<typename Type>
//using memory_buffer = basic_buffer<Type>;

// memory_buffer 类，主要用来给to_string分配，没什么用啊
template<typename Type> class memory_buffer : public  basic_buffer<typename Type::value_type> {
public:
    memory_buffer(Type& data_, int32_t start_pos_ = 0)
        : basic_buffer<typename Type::value_type>(*(data_.data() + start_pos_)), m_buffer(data_) {}
    memory_buffer& write(const char val) { basic_buffer<typename Type::value_type>::append(val); return *this; }
    memory_buffer& write(const char* val) { basic_buffer<typename Type::value_type>::append(val); return *this; }
    memory_buffer& write(const char* val, size_t len) { basic_buffer<typename Type::value_type>::append(val, len); return *this; }
    // 调整缓存区大小
    virtual inline bool adjust_buffer_size(size_t len) override {
        if (len + this->size() > m_buffer.size()) {
            m_buffer.resize(len + this->size());
            this->data(&*m_buffer.data());
        }
        return true;
    }
    
protected:
    Type& m_buffer;
};

// 只用了这个类
template<> class memory_buffer <char> : public basic_buffer<char> {
public:
    memory_buffer() {}
    memory_buffer(char& data_) : basic_buffer<char>(data_) {}
    memory_buffer& write(const char* val) { basic_buffer<char>::append(val); return *this; }
    virtual inline bool adjust_buffer_size(size_t len) override { return true; }
};

_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_memory_buffer


#ifndef segment_to_string
#define segment_to_string
_AMO_NAMESPACE_BEGIN
template<typename T>  struct fast_to_string {
    const static bool value = false;
};

struct fast_mode {};
struct slow_mode {};

namespace details {

    // 普通 to_string 方法
    // 整数不使用标准库提供的方法，太慢 int to string
    template<typename T> inline typename std::enable_if < std::is_enum<T>::value
    || std::is_integral<T>::value, std::string >::type to_string_details(const T& val) {
        char retval[20] = { 0 }; // 整数最多19位
        return std::string(retval, _AMO integer_to_chars<char*>(val, retval));
    }
    // float to string
    template<typename T> inline typename std::enable_if < std::is_floating_point<T>::value,
    std::string >::type to_string_details(const T& val) {
        char retval[325] = { 0 }; // 浮点数最多324位
        ::dtoa_milo(val, retval, 325);
        return retval;
    }
    // other type to string
    template<typename T> inline typename std::enable_if < !std::is_arithmetic<T>::value,
    std::string >::type to_string_details(const T& val) {
        return val.to_string(); // 要求自带 to_string 函数
    }
    
    template<> inline std::string to_string_details(const bool& val) { return  val ? "true" : "false";  } // bool to string
    template<> inline std::string to_string_details(const std::nullptr_t& val) { return "null"; } // nullptr to string
    inline std::string to_string_details(const std::string& val) { return val; } // string to string
    inline std::string to_string_details(const char* val) { return val; } // const char* to string
    inline std::string to_string_details(char* val) { return val; } // char* to string
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 判断是否存在成员函数 to_string
    template<typename T, typename... Args> struct __ck_mfunc_to_string {
    private:
        struct nil2 {};
        template<typename U> static auto check(int) -> typename
        std::decay<decltype(std::declval<U>().to_string(std::declval<Args>()...))>::type;
        template<typename U> static std::false_type check(...);
    public:
        using type = typename std::conditional<std::is_void<decltype(check<T>(0))>::value, nil2, decltype(check<T>(0))>::type;
        enum { value = !std::is_same<decltype(check<T>(0)), std::false_type>::value };
    };
    
    // int to string
    template<typename R = std::string, typename T> inline typename std::enable_if < std::is_integral<T>::value,
    std::size_t >::type to_string_details(memory_buffer<R>& retval, const T& val) {
        retval.adjust_buffer_size(20);  // 要求20个字节的空间
        std::size_t len = _AMO integer_to_chars<char*>(val, (char*)retval.current()); // 返回
        retval.size(retval.size() + len);
        return len;
    }
    
    // float to string
    template<typename R = std::string, typename T> inline typename std::enable_if < std::is_floating_point<T>::value,
    std::size_t >::type to_string_details(memory_buffer<R>& retval, const T& val) {
        int32_t buffer_size = 32;
        while (true) {
            // buffer_size = 32 64 128 256 , float 最多到324，超过512还没成功，throw
            if (buffer_size > 512) { throw std::runtime_error("dtoa_milo error"); }
            retval.adjust_buffer_size(buffer_size);
            int32_t len = ::dtoa_milo(val, (char*)retval.current(), buffer_size);
            if (len == -1) {
                buffer_size *= 2;
                continue;
            }
            
            retval.size(retval.size() + len);
            return len;
        }
        return 0;
    }
    
    template<typename R = std::string, typename T>
    inline typename std::enable_if < !std::is_arithmetic<T>::value,
    int32_t >::type to_string_details_with_mode(memory_buffer<R>& retval, const T& val, fast_mode) {
        return val.to_string(retval);
    }
    
    template<typename R = std::string, typename T>
    inline typename std::enable_if < !std::is_arithmetic<T>::value,
    int32_t >::type to_string_details_with_mode(memory_buffer<R>& retval, const T& val, slow_mode) {
        std::string str = val.to_string();
        retval.append(str.c_str(), str.size());
        return str.size();
    }
    
    template<typename R = std::string, typename T>
    inline typename std::enable_if < !std::is_arithmetic<T>::value,
    int32_t >::type to_string_details(memory_buffer<R>& retval, const T& val) {
        typedef typename std::conditional<__ck_mfunc_to_string<T, memory_buffer<R> >::value, fast_mode, slow_mode>::type type;
        return to_string_details_with_mode(retval, val, type());
    }
    
    template<typename R = std::string> inline int32_t to_string_details(memory_buffer<R>& retval, const std::string& val) {
        retval.append(val.c_str(), val.size());
        return val.size();
    }
    
    template<typename R = std::string> inline int32_t to_string_details(memory_buffer<R>& retval, char* val) {
        std::size_t length = strlen(val);
        retval.append(val, length);
        return length;
    }
    
    template<typename R = std::string> inline int32_t to_string_details(memory_buffer<R>& retval, const char* val) {
        std::size_t length = strlen(val);
        retval.append(val, length);
        return length;
    }
    
    template<typename R = std::string>
    inline int32_t to_string_details(memory_buffer<R>& retval, const char* val, std::size_t length) {
        if (length == 0) { return 0; }
        retval.append(val, length);
        return length;
    }
    
    template<typename R = std::string> inline int32_t to_string_details(memory_buffer<R>& retval, const bool& val) {
        if (val) {
            retval.append("true", 4);
            return 4;
        } else {
            retval.append("false", 5);
            return 5;
        }
    }
    
    template<typename R = std::string>
    inline int32_t to_string_details(memory_buffer<R>& retval, const std::nullptr_t& val) {
        retval.append("null", 4);
        return 4;
    }
}


template<typename T> std::string to_string(const T& val) { return details::to_string_details(val); }
template<typename R = std::string, typename T> inline int32_t to_string(R& retval, const T& val) {
    memory_buffer<R> buffer(retval);
    return  details::to_string_details(buffer, val);
}

template<typename R = std::string, typename T> inline typename std::enable_if < std::is_same<T, char>::value,
int32_t >::type  to_string(char& retval, const T& val) {
    memory_buffer<char> buffer(retval);
    return details::to_string_details(buffer, val);
    
}
_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_to_string


#ifndef segment_from_string
#define segment_from_string

_AMO_NAMESPACE_BEGIN
template<typename T, typename Enable = void> struct FromStringHelper {
    inline T from_string(const std::string& val) { return T::from_string(val); }
};

template<typename T> struct FromStringHelper < T, typename std::enable_if < std::is_integral<T>::value  >::type > {
    struct HelperInt64 {};
    struct HelperInt32 {};
    struct HelperUint {};
    struct HelperInt {};
    inline T from_string(const std::string& val) {
        typedef typename std::conditional < sizeof(T) == 8, HelperInt64, HelperInt32 > ::type type;
        return from_string_impl(val, type());
    }
    
    inline T from_string_impl(const std::string& val, HelperInt64) {
        typedef typename std::conditional < std::is_unsigned<T>::value, HelperUint, HelperInt > ::type type;
        return from_string_impl64(val, type());
    }
    
    inline T from_string_impl(const std::string& val, HelperInt32) {
        typedef typename std::conditional < std::is_unsigned<T>::value, HelperUint, HelperInt > ::type type;
        return from_string_impl32(val, type());
    }
    
    inline T from_string_impl64(const std::string& val, HelperInt) { return std::stoll(val); }
    inline T from_string_impl64(const std::string& val, HelperUint) { return std::stoull(val); }
    inline T from_string_impl32(const std::string& val, HelperInt) { return std::stoi(val); }
    inline T from_string_impl32(const std::string& val, HelperUint) { return std::stoul(val); }
};
template<typename T> struct FromStringHelper<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
    inline T from_string(const std::string& val) { return std::stod(val); }
};

template<typename T> struct FromStringHelper<T, typename std::enable_if<std::is_same<T, std::string>::value>::type> {
    inline T from_string(const std::string& val) { return val; }
};

template<typename T> struct FromStringHelper<T, typename std::enable_if<std::is_same<T, std::nullptr_t>::value>::type> {
    inline T from_string(const std::string& val) { return nullptr; }
};

template<typename T> inline  T  from_string(const std::string& val) { return FromStringHelper<T>().from_string(val); }

_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_from_string


#ifndef segment_memory_writer
#define segment_memory_writer

_AMO_NAMESPACE_BEGIN

// 固定长度memory_writer ,无法进行括容，适用短字符串格式化
template<int MAX_SIZE = 256> class memory_writer : public memory_buffer<char> {
public:
    memory_writer() : memory_buffer<char>() { data(&m_buffer[0]);  }
    template<typename T> inline memory_writer& operator << (const T& val) { return write(val); }
    inline memory_writer& write(const std::string& val) { return this->write(val.c_str(), val.size()); }
    inline memory_writer& write(const char* val) {  return this->write(val, strlen(val));  }
    inline memory_writer& write(const char* val, size_t length) {  if (length != 0) { append(val, length); } return *this; }
    inline memory_writer& write(char val) { basic_buffer<char>::append(val); return *this; }
    inline memory_writer& put(char ch) { return write(ch); }
    template<typename T> inline memory_writer& write(const T& val) { _AMO details::to_string_details(*this, val); return *this; }
    inline size_t capacity() const { return MAX_SIZE; }
    inline size_t usable_size() const { return capacity() - m_current_pos; }
    virtual inline bool adjust_buffer_size(size_t len) override {
        if (m_current_pos + len > MAX_SIZE) { throw std::runtime_error("out of range."); } //写入数据超长 throw
        return true;
    }
public:
    char m_buffer[MAX_SIZE];		// 定长数组
};

// 使用vector<char> 特化memory_writer,可以动态扩容
template<> class memory_writer<0> : public memory_buffer<char> {
public:
    memory_writer(int32_t size_ = 256) : memory_buffer<char>(), m_buffer(size_, 0) { data(m_buffer.data()); }
    template<typename T> inline memory_writer& operator << (const T& val) { return write(val); }
    inline memory_writer& write(char ch) { this->append(ch); return *this; }
    inline memory_writer& put(char ch) { return write(ch); }
    inline memory_writer& write(const char* val) { return this->write(val, strlen(val)); }
    inline memory_writer& write(const char* val, size_t length) { if (length > 0) { append(val, length); } return *this; }
    template<typename T> inline memory_writer& write(const T& val) { _AMO details::to_string_details(*this, val); return *this; }
    inline memory_writer& write(const std::string& val) { return write(val.c_str(), val.size()); }
    inline size_t capacity() const { return m_buffer.size(); }
    inline size_t usable_size() const { return m_buffer.size() - size(); }
    virtual inline bool adjust_buffer_size(size_t len) override {
        if (size() + len > m_buffer.size()) {
            m_buffer.resize(m_buffer.size() * 2 + len);
            data(m_buffer.data());
        }
        return true;
    }
public:
    std::vector<char> m_buffer;
};

// 使用std::string  特化memory_writer, 可以动态扩容
template<> class memory_writer < -1 > : public memory_buffer<char> {
public:
    memory_writer(int32_t size_ = 256) : memory_buffer<char>(), m_buffer(size_, 0) { data(m_buffer.data()); }
    template<typename T> inline memory_writer& operator << (const T& val) { return write(val); }
    inline memory_writer& write(char ch) { this->append(ch); return *this; }
    inline memory_writer& put(char ch) { return write(ch); }
    inline memory_writer& write(const char* val, size_t length) { if (length > 0) { this->append(val, length); } return *this; }
    inline memory_writer& write(const char* val) { return this->write(val, strlen(val)); }
    template<typename T> inline memory_writer& write(const T& val) { _AMO details::to_string_details(*this, val); return *this; }
    inline memory_writer& write(const std::string& val) { return write(val.c_str(), val.size()); }
    inline size_t capacity() const { return m_buffer.size(); }
    inline size_t usable_size() const { return m_buffer.size() - size(); }
    virtual inline bool adjust_buffer_size(size_t len) override {
        if (size() + len > m_buffer.size()) {
            m_buffer.resize(m_buffer.size() * 2 + len);
            data(m_buffer.data());
        }
        return true;
    }
public:
    std::string m_buffer;
};
// 使用stream 保存数据，可以用来保存文件
template<> class memory_writer < -2 > : public memory_writer<0> {
public:
    memory_writer(std::ostream& stream) : memory_writer<0>(1024 * 4), m_buffer(stream) {}
    template<typename T> inline memory_writer& operator << (const T& val) { return this->write<T>(val); }
    virtual ~memory_writer() { flush(); }
    inline memory_writer& write(const std::string& val) { return this->write(val.c_str(), val.size()); }
    inline memory_writer& write(char ch) {
        memory_writer<0>::write(ch);
        flush_if_necessary();
        return *this;
    }
    inline memory_writer& put(char ch) { return this->write(ch); }
    inline memory_writer& write(const char* val) { return this->write(val, strlen(val)); }
    inline memory_writer& write(const char* val, size_t length) {
        memory_writer<0>::write(val, length);
        flush_if_necessary();
        return *this;
    }
    template<typename T> inline memory_writer& write(const T& val) {
        memory_writer<0>::write(val);
        flush_if_necessary();
        return *this;
    }
    
    inline size_t capacity() const { return (std::numeric_limits<size_t>::max)(); }
    inline size_t usable_size() const { return (std::numeric_limits<size_t>::max)(); }
    virtual inline void flush() {
        if (memory_writer<0>::size() > 0) {
            m_buffer.write(memory_writer<0>::data(), memory_writer<0>::size());
            memory_writer<0>::reset();
        }
    }
private:
    // 判断是否需要刷新流，如果缓冲区超过 48*1024 个字节，则将缓存区的数据写入到buffer中
    void flush_if_necessary() {
        if (memory_writer<0>::size() > 49152) { flush(); }
    }
public:
    std::ostream& m_buffer;
};
_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_memory_writer


#ifndef segment_json_memory_allocator
#define segment_json_memory_allocator

_AMO_NAMESPACE_BEGIN

/**
 * @class json_memory_allocator
 *
 * @brief 默认的JSON内存分配器.
 */
template<typename ObjectType, uint32_t BlockSize = 256, uint32_t AlignSize = 8>
class json_memory_allocator {
public:
    typedef json_memory_allocator<ObjectType, BlockSize, AlignSize> allocator_type;
    typedef void value_type;
    typedef char* pointer;
    typedef const char* const_pointer;
    typedef pointer void_pointer;
    typedef const_pointer const_void_pointer;
    typedef size_t size_type;
    typedef int32_t difference_type;
    
public:
    json_memory_allocator() : total_size(BlockSize / 2), used_size(BlockSize / 2), data_ptr(nullptr), blocks(8, nullptr) {
        blocks.resize(0);
    }
    
    ~json_memory_allocator() {
        for (auto& p : blocks) {
            if (p != nullptr) { std::free(p); }
        }
    }
    
    static inline size_type align_size(size_type sz, int n) { return (sz + n - 1) & -n; }
    
    /**
     * @fn ObjectType& json_memory_allocator::root()
     *
     * @brief 返回JSON对象的根节点，每个内存分配器对应一个JSON根节点，方便程序开发，也可以减少basic_json的内存占用.
     *
     * @return  一个json_data_object的引用.
     */
    
    ObjectType& root() { return object; }
    
    /**
     * @fn pointer memory_allocator::allocate(size_type size_)
     *
     * @brief 获取指定数量的内存，按照AlignSize对齐，默认为8字节对齐（比如要求7字节，会返回一个8字节的内存空间）.
     *
     * @param size_ 要求分配的内存长度.
     *
     * @return 分配的内存地址.
     */
    pointer allocate(size_type size_) {
        // 对齐，默认是按8字节对齐
        size_type tmp = align_size(size_, AlignSize);
        used_size += tmp;
        //如果需要的内存空间大于当前可用的内存空间，那么重新分配新的内存
        if (used_size > total_size) { reallocate(tmp); }
        // 返回指针
        return data_ptr + used_size - tmp;
    }
    
    /**
     * @fn void json_memory_allocator::reallocate(size_type required_size)
     *
     * @brief 该函数在当前剩余的内存空间不够时，用于增加内存池长度.
     *
     * @param required_size 最低要求的内存空间.
     */
    
    void reallocate(size_type required_size) {
        const static size_type max_bock_size = 1024 * 1024 * 10;		// 最大块内存为10M
        if (required_size > max_bock_size) { // 如果要求的空间大于10M，则直接分配10M的空间出来
            total_size = required_size;
        } else {
            // 找到一个合适的空间
            while (true) {
                // 实际是最多分配20M空间
                total_size = (std::min<size_type>)(max_bock_size, total_size * 2); // 翻倍
                if (total_size > required_size) {
                    break;
                }
            }
        }
        
        // 重新分配内存
        data_ptr = (char*)std::malloc(total_size);
        
        if (data_ptr == nullptr) {
            $cerr("allocate memory failed : %llu, need : %llu", (uint64_t)total_size, (uint64_t)required_size);
            //std::cout << "allocate memory failed: " << total_size << " need: " << required_size << std::endl;
            total_size = 0;
        }
        
        // 重置used指针
        used_size = required_size;
        blocks.push_back(data_ptr);
    }
    
    /**
     * @fn inline void json_memory_allocator::deallocate(pointer p, size_type n)
     *
     * @brief 释放资源，实际上为了提升程序性能，没有释放任务资源.
     *
     * @param p 内存地址.
     * @param n 内存长度.
     */
    
    inline void deallocate(pointer p, size_type n) { }
    
    /**
     * @fn inline void json_memory_allocator::add_allocator(std::shared_ptr <json_memory_allocator> allocator_)
     *
     * @brief 关联一个分配器到当前内存分配器，这个函数的主要目的是将其他JSON对象的分配器保存到当前JSON对象的分配器中，
     * 		  防止关联的内存空间被自动销毁.例如:
     * 		  amo::json a;
     * 		  {
     * 			amo::json b = "abc";
     * 			a["b"] = std::move(b);  // 使用移动语义可以避免不必要的内存拷贝
     * 		  } // b 的生命周期结束后，因为调用该函数增加了引用计数，使得b的内存分配器不分释放内存空间，a可以继续关联b的内容
     *
     * @param allocator_ 需要关联的内存分配器.
     */
    
    inline void add_allocator(const std::shared_ptr <json_memory_allocator>& allocator_) {
        // 不添加自己
        if (allocator_.get() == this) { return; }
        if (!vecs) { vecs.reset(new std::vector<std::shared_ptr <json_memory_allocator> >()); }
        for (auto& p : *vecs) {
            if (p.get() == allocator_.get()) { return; }
        }
        vecs->push_back(allocator_);
    }
    
private:
    size_type total_size;	                                                       // 预分配的内存长度
    size_type used_size;		                                                   // 当前已使用的大小
    pointer data_ptr;			                                                   // 预分配的内存
    std::vector<void* > blocks;                                                    // 已分配的内存块
    ObjectType object;                                                             // 默认的json root 对象
    std::shared_ptr<std::vector<std::shared_ptr <json_memory_allocator> > >  vecs; // 关联的其他内存分配器
};

// JsonArray/JsonObject 的内存分配器
template<class T, class Alloc> class json_container_allocator {
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Alloc::size_type size_type;
    typedef typename Alloc::difference_type difference_type;
    
    // 必须要重新定义，否则容器如 list, set, map 无法正常工作
    template<class Other> struct rebind { typedef json_container_allocator<Other, Alloc> other; };
    
    // 构造函数必须实现
    json_container_allocator() { m_allocator = nullptr; }
    json_container_allocator(const std::shared_ptr<Alloc>& allocator_) : m_allocator(allocator_.get()) {}
    json_container_allocator(const Alloc* allocator_) : m_allocator((Alloc*)allocator_) {}
    json_container_allocator(json_container_allocator<T, Alloc> const& rhs) : m_allocator(rhs.m_allocator) {}
    json_container_allocator<T, Alloc>& operator=(json_container_allocator<T, Alloc> const& rhs) {
        m_allocator = rhs.m_allocator;
        return (*this);
    }
    template<class Other> json_container_allocator(json_container_allocator<Other, Alloc> const& rhs) {
        m_allocator = rhs.m_allocator;
    }
    template<class Other> json_container_allocator<T, Alloc>& operator=(json_container_allocator<Other, Alloc> const& rhs) {
        m_allocator = rhs.m_allocator;
        return (*this);
    }
    ~json_container_allocator() {}
    pointer address(reference x) const { return &x; }
    const_pointer address(const_reference x) const { return x; }
    // 内存的分配与释放可以实现为自定义的算法，替换函数体即可
    pointer allocate(size_type n, const_pointer = 0) { return reinterpret_cast<pointer>(m_allocator->allocate(n * sizeof(T))); }
    // 不释放内存
    void deallocate(pointer ptr, size_type count = 1) { return; /* 暂不释放 */ }
    size_type max_size() const { return static_cast<size_type>((std::numeric_limits<size_type>::max)() / sizeof(T)); }
    
    template <typename... Types> void construct(pointer p, Types&& ... t) { ::new (static_cast<void*>(p)) value_type(std::forward<Types>(t)...); }
    void  destroy(pointer p) { p->~value_type(); }
    Alloc* m_allocator;
};

_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_json_memory_allocator


#ifndef segment_json_enum
#define segment_json_enum

_AMO_NAMESPACE_BEGIN

#pragma region 枚举定义

enum token_t {
    // 对象开始{   对象结束 }  数组开始[  数组结束]  空null 数字 字符串 布尔 true/false 冒号: 逗号, 结束标志 JSON对象 JSON数组
    token_invalid = 0,					        // 无效
    token_begin_object = 1,		                // 对象开始{
    token_end_object = 2,		                // 对象结束 }
    token_begin_array = 4,		                // 数组开始[
    token_end_array = 8,		                // 数组结束]
    token_json_null = 16,		                // 空null
    token_json_string = 32,		                // 字符串
    token_json_boolean = 64,	                // 布尔 true/false
    token_json_number = 128,	                // 数字
    token_sep_colon = 256,		                // 冒号:
    token_sep_comma = 512,		                // 逗号,
    token_end_document = 1024,	                // 结束标志
    token_json_object = 2048,	                // JSON对象
    token_json_array = 4096,	                // JSON数组
    token_json_true = 8192,		                // true
    token_json_false = 16384,	                // false
    token_json_negative_number = 32768,			// 负数
};

enum value_t {
    json_value_empty = 0,				        // 空类型,可以转换为任意类型
    json_value_null = 1,				        // null
    json_value_string = 2,			            // 字符串
    json_value_boolean = 3,			            // 布尔
    json_value_unsigned = 4,			        // 无符号整型
    json_value_integer = 8,                     // 有符号整型
    json_value_float = 16,				        // 浮点
    json_value_number = 4 + 8 + 16,             // =28 数值类型，包含json_value_integer,json_value_unsigned,json_value_float，28
    __json_value_unknown__ = 63,                // 为json_object预留的类型
    json_value_invalid = 64,			        // 无效JSON,用于字符串解析失败时对JSON对象的标记
    json_value_object = 126,			        // JSON对象
    json_value_array = 127,			            // JSON数组
    // 128 开始为自定义的数据类型，目前保存数据类型的为uin16_t,最大到65535
};
#pragma endregion

_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_json_enum


#ifndef segment_json_string_parser
#define segment_json_string_parser

_AMO_NAMESPACE_BEGIN

/**
 * @class lite_json_string_parser
 *
 * @brief 精简版的 JSON string parser.
 *
 * @tparam ObjectType json_data_object.
 */

template<typename ObjectType> class lite_json_string_parser {
public:
    typedef ObjectType object_type;
    typedef typename object_type::CharReaderType CharReaderType;
    
    /**
     * @fn inline void lite_json_string_parser::unescape(CharReaderType& reader, object_type& object)
     *
     * @brief 精简版的string解析，直接找到"就算完.
     *
     * @param [in]  reader char reader.
     * @param [out] object 需要填充的object.
     */
    
    inline void unescape(CharReaderType& reader, object_type& object) {
        for (; reader.good(); reader.forward()) {
            if (reader.peek() == '\"') {
                reader.stop_refstring(object.d.s.elements, object.d.s.length);
                reader.forward();
                return;
            }
        }
    }
    
    /**
     * @fn template<typename T> inline void lite_json_string_parser::escape(const object_type& object, T& stream, int32_t indent = 0) const
     *
     * @brief  将object中的内存输出到 stream 中去，不做任何转义
     *
     * @param 		   object The object.
     * @param [out]	   stream 输出缓存.
     * @param 		   indent (Optional) 使用几个空格缩进,默认为0,不缩进.
     */
    
    template<typename T> inline void escape(const object_type& object, T& stream, int32_t indent = 0) const {
        stream.write(object.d.s.elements, object.d.s.length);
    }
};

template<typename ObjectType> class json_string_parser {
public:
    typedef ObjectType object_type;
    typedef typename object_type::JsonAllocType JsonAllocType;
    typedef typename object_type::CharReaderType CharReaderType;
    
    inline char is_hex(char ch) {
        return ((ch >= '0' && ch <= '9') || ('a' <= ch && ch <= 'f') || ('A' <= ch && ch <= 'F')) ? ch : '\0';
    }
    
    inline int8_t hex(char ch) {
        return ((('0' <= (ch) && (ch) <= '9')) ? (ch) - '0' : (('a' <= (ch) &&
                (ch) <= 'f')) ? (ch) - 'a' + 10 : (('A' <= (ch) && (ch) <= 'F')) ? (ch) - 'A' + 10 : (-1));
                
    }
    
    /**
     * @fn inline void json_string_parser::unescape(CharReaderType& reader, object_type& object)
     *
     * @brief 读取转义字符.
     *
     * @param [in,out] reader The reader.
     * @param [in,out] object 需要填充的object.
     */
    
    inline void unescape(CharReaderType& reader, object_type& object) {
        bool esc = false;  // 是否为转义字符
        size_t j = 0;
        uint16_t W1 = 0;
        uint16_t  W2 = 0;
        uint32_t U = 0;
        
        typename CharReaderType::StringBufferType output = reader.string_buffer();// (char*)reader.address(0);
        
        for (; reader.good(); reader.forward()) {
            char ch = reader.peek();
            
            if (!esc) {
                switch (ch) {
                    case '\\':
                        esc = true;   // 转义字符
                        break;
                        
                    case '\"':
                        output[j++] = ch;
                        reader.stop_refstring(object.d.s.elements, object.d.s.length);
                        object.d.s.length = static_cast<uint32_t>(j - 1);
                        reader.forward();
                        return;
                        
                    default:
                        output[j++] = ch;
                        break;
                }
            } else {
                esc = false;
                
                switch (ch) {
                    default:
                        set_invalid_object(reader, object);
                        
                    case '"':
                    case '\\':
                    case '/': {
                        output[j++] = ch;
                        break;
                    }
                    case 'b': {
                        output[j++] = 0x08;
                        break;
                    }
                    case 'f': {
                        output[j++] = 0x0c;
                        break;
                    }
                    
                    case 'n': {
                        output[j++] = 0x0a;
                        break;
                    }
                    
                    case 'r': {
                        output[j++] = 0x0d;
                        break;
                    }
                    
                    case 't': {
                        output[j++] = 0x09;
                        break;
                    }
                    
                    case 'u':
                    
                        /*
                         * RFC 2781, 2.2 Decoding UTF-16
                         */
                        
                        if (reader.eof(4)
                                || !is_hex(reader.peek(1))
                                || !is_hex(reader.peek(2))
                                || !is_hex(reader.peek(3))
                                || !is_hex(reader.peek(4))) {
                            set_invalid_object(reader, object);
                        }
                        
                        W1 = (hex(reader.peek(1)) << 12) | (hex(reader.peek(2)) << 8) | (hex(reader.peek(3)) << 4) | hex(reader.peek(4));
                        reader.forward(5);
                        
                        
                        if (W1 < 0xD800 || 0xDFFF < W1) {
                            U = W1;
                        } else if (!(0xD800 <= W1 && W1 <= 0xDBFF)) {
                            set_invalid_object(reader, object);
                        } else {
                            if (reader.eof(5)
                                    || reader.peek() != '\\'
                                    || reader.peek(1) != 'u'
                                    || !is_hex(reader.peek(2))
                                    || !is_hex(reader.peek(3))
                                    || !is_hex(reader.peek(4))
                                    || !is_hex(reader.peek(5))) {
                                return set_invalid_object(reader, object);
                            }
                            
                            W2 = (hex(reader.peek(2)) << 12)
                                 | (hex(reader.peek(3)) << 8)
                                 | (hex(reader.peek(4)) << 4)
                                 | hex(reader.peek(5));
                                 
                            reader.forward(6);
                            
                            if (!(0xDC00 <= W2 && W2 <= 0xDFFF)) {
                                return set_invalid_object(reader, object);
                            }
                            
                            U = ((W1 & 0x3FF) << 10) | (W2 & 0x3FF);
                            U += 0x10000;
                        }
                        
                        /*
                         * RFC 3629, 3. UTF-8 definition
                         */
                        if (U <= 0x0000007F) {
                            output[j++] = U & 0x7F;
                        } else if (U <= 0x000007FF) {
                            if (reader.eof(1)) {
                                set_invalid_object(reader, object);
                            }
                            
                            output[j++] = 0xC0 | ((U >> 6) & 0x1F);
                            output[j++] = 0x80 | (U & 0x3F);
                        } else if (U <= 0x0000FFFF) {
                            if (reader.eof(2)) {
                                set_invalid_object(reader, object);
                            }
                            
                            output[j++] = 0xE0 | ((U >> 12) & 0x0F);
                            output[j++] = 0x80 | ((U >> 6) & 0x3F);
                            output[j++] = 0x80 | (U & 0x3F);
                        } else if (0x00010000 <= U && U <= 0x0010FFFF) {
                            if (reader.eof(3)) {
                                set_invalid_object(reader, object);
                            }
                            
                            output[j++] = 0xF0 | ((U >> 18) & 0x07);
                            output[j++] = 0x80 | ((U >> 12) & 0x3F);
                            output[j++] = 0x80 | ((U >> 6) & 0x3F);
                            output[j++] = 0x80 | (U & 0x3F);
                        } else {
                            set_invalid_object(reader, object);
                        }
                        //TODO: 字符串解析过程中不应该出现回退操作--current_index;
                        reader.back_forward();/* prepare for ++ at the for loop */
                }
            }
        }
        set_invalid_object(reader, object);
    }
    
    void __throw_error_message(CharReaderType& reader) {
        _AMO memory_writer<0> stream;
        stream << "json parse error, unexpected token at position [" << reader.processed_size() << "], error buffers: ";
        stream << reader.error_buffers();
        throw std::runtime_error(stream.to_string());
    }
    inline void set_invalid_object(CharReaderType& reader, object_type& object) {  __throw_error_message(reader); }
    
    /**
     * @fn template<typename T> inline void json_string_parser::escape(const object_type& object, T& stream, int32_t indent = 0) const
     *
     * @brief 将object中的内存输出到 stream 中去，只做简单转义，防止\" \\之类影响JSON字符串解析的转义.
     *
     * @tparam T Generic type parameter.
     * @param 	    object The object.
     * @param [out] stream 输出缓存.
     * @param 	    indent (Optional) 使用几个空格缩进,默认为0,不缩进.
     */
    
    template<typename T> inline void escape(const object_type& object, T& stream, uint32_t indent = 0) const {
        for (uint32_t i = 0; i < object.d.s.length; ++i) {
            char ch = object.d.s.elements[i];
            
            switch (ch) {
                case '\"':
                    stream.write("\\\"", 2);
                    break;
                    
                case '\\':
                    stream.write("\\\\", 2);
                    break;
                    
                /*case '\b':
                    stream.write("\\b", 2);
                    break;
                
                case '\f':
                    stream.write("\\f", 2);
                    break;
                
                case '\n':
                    stream.write("\\n", 2);
                    break;
                
                case '\r':
                    stream.write("\\r", 2);
                    break;
                
                case '\t':
                    stream.write("\\t", 2);
                    break;*/
                
                default:
                    // 其他的编译不处理 \x01之类的
                    stream.write(object.d.s.elements[i]);
                    break;
            }
        }
    }
};

_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_json_string_parser


#ifndef segment_json_number_parser
#define segment_json_number_parser

_AMO_NAMESPACE_BEGIN

/**
 * @class json_number_parser
 *
 * @brief A JSON 数值解析类.
 *
 * @tparam ObjectType json_data_object.
 */

template<typename ObjectType> class json_number_parser {
public:
    typedef ObjectType object_type;
    typedef typename object_type::JsonAllocType JsonAllocType;
    typedef typename object_type::CharReaderType CharReaderType;
    
    void __throw_error_message(CharReaderType& reader) {
        _AMO memory_writer<0> stream;
        stream << "json parse error, unexpected token at position [" << reader.processed_size() << "], error buffers: ";
        stream << reader.error_buffers();
        throw std::runtime_error(stream.to_string());
    }
    
    // 解析失败，抛出异常
    inline void set_invalid_object(CharReaderType& reader) { __throw_error_message(reader); }
    
    inline bool is_char_0_9(char ch) const { return ch >= '0' && ch <= '9'; }
    
    /**
     * @fn template<typename T> static inline bool json_number_parser::is_number_overflow(CharReaderType& reader, T& retval, unsigned char ch)
     *
     * @brief 检测当前值*10 + ch 后是否会越界.
     *
     * @tparam T Generic type parameter.
     * @param [in,out] reader The reader.
     * @param [in,out] retval 需要检查的数值.
     * @param 		   ch	  char.
     *
     * @return True if number overflow, false if not.
     */
    
    template<typename T> static inline bool is_number_overflow(CharReaderType& reader, T& retval, unsigned char ch) {
        static const T max_t = (std::numeric_limits<T>::max)() / 10;
        static const T limits[256] = {
            //0-47
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            // 48-55
            max_t - 0, max_t - 1, max_t - 2, max_t - 3, max_t - 4, max_t - 5, max_t - 6, max_t - 7,
            //56-63
            max_t - 8, max_t - 9, max_t, max_t, max_t, max_t, max_t, max_t,
            
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            
            //128-255
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
            max_t, max_t, max_t, max_t, max_t, max_t, max_t, max_t,
        };
        
        return (retval > limits[ch]);
    }
    
    /**
     * @fn template<typename T> inline void json_number_parser::check_and_calc_number(CharReaderType& reader, T& retval, unsigned char ch)
     *
     * @brief / 检测当前值*10 + ch后是否会越界.
     *
     * @tparam T Generic type parameter.
     * @param [in,out] reader The reader.
     * @param [in,out] retval 需要检测的数值.
     * @param 		   ch	  需要加上的值.
     */
    
    template<typename T> inline void check_and_calc_number(CharReaderType& reader, T& retval, unsigned char ch) {
        if (is_number_overflow(reader, retval, ch)) { set_invalid_object(reader); }
        retval = retval * 10 + ch - '0';
    }
    
    /**
     * @fn inline char json_number_parser::calc_exp_value(CharReaderType& reader, int32_t& retval)
     *
     * @brief 计算科学计数法中的指数值e10 e-10 e+10 中的10.
     *
     * @param [in,out] reader The reader.
     * @param [in,out] retval 需要计算的值.
     *
     * @return JSON字符串中最新解析到的的字符.
     */
    
    inline char calc_exp_value(CharReaderType& reader, int32_t& retval) {
        char ch = '\0';
        for (; reader.good(); reader.forward()) {
            ch = reader.peek();
            if (!is_char_0_9(ch)) { return ch; }
            check_and_calc_number(reader, retval, ch);
        }
        return ch;
    }
    
    // 跳过所有的数字字符
    inline char skip_digit_char(CharReaderType& reader) {
        char ch = '\0';
        for (; reader.good(); reader.forward()) {
            ch = reader.peek();
            if (!is_char_0_9(ch)) { return ch; }
        }
        return ch;
    }
    
    /**
     * @fn inline double json_number_parser::pow_n(int32_t f)
     *
     * @brief 通过查表计算10的n次方，用来替换pow函数.
     *
     * @param f 10的几次方.
     *
     * @return 返回10的f次方.
     */
    
    inline double pow_n(int32_t f) {
        static const double pows[309] = {
            1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11, 1e12, 1e13, 1e14, 1e15,
            1e16, 1e17, 1e18, 1e19, 1e20, 1e21, 1e22, 1e23, 1e24, 1e25, 1e26, 1e27, 1e28, 1e29, 1e30, 1e31,
            1e32, 1e33, 1e34, 1e35, 1e36, 1e37, 1e38, 1e39, 1e40, 1e41, 1e42, 1e43, 1e44, 1e45, 1e46, 1e47,
            1e48, 1e49, 1e50, 1e51, 1e52, 1e53, 1e54, 1e55, 1e56, 1e57, 1e58, 1e59, 1e60, 1e61, 1e62, 1e63,
            1e64, 1e65, 1e66, 1e67, 1e68, 1e69, 1e70, 1e71, 1e72, 1e73, 1e74, 1e75, 1e76, 1e77, 1e78, 1e79,
            1e80, 1e81, 1e82, 1e83, 1e84, 1e85, 1e86, 1e87, 1e88, 1e89, 1e90, 1e91, 1e92, 1e93, 1e94, 1e95,
            1e96, 1e97, 1e98, 1e99, 1e100, 1e101, 1e102, 1e103, 1e104, 1e105, 1e106, 1e107, 1e108, 1e109, 1e110, 1e111,
            1e112, 1e113, 1e114, 1e115, 1e116, 1e117, 1e118, 1e119, 1e120, 1e121, 1e122, 1e123, 1e124, 1e125, 1e126, 1e127,
            1e128, 1e129, 1e130, 1e131, 1e132, 1e133, 1e134, 1e135, 1e136, 1e137, 1e138, 1e139, 1e140, 1e141, 1e142, 1e143,
            1e144, 1e145, 1e146, 1e147, 1e148, 1e149, 1e150, 1e151, 1e152, 1e153, 1e154, 1e155, 1e156, 1e157, 1e158, 1e159,
            1e160, 1e161, 1e162, 1e163, 1e164, 1e165, 1e166, 1e167, 1e168, 1e169, 1e170, 1e171, 1e172, 1e173, 1e174, 1e175,
            1e176, 1e177, 1e178, 1e179, 1e180, 1e181, 1e182, 1e183, 1e184, 1e185, 1e186, 1e187, 1e188, 1e189, 1e190, 1e191,
            1e192, 1e193, 1e194, 1e195, 1e196, 1e197, 1e198, 1e199, 1e200, 1e201, 1e202, 1e203, 1e204, 1e205, 1e206, 1e207,
            1e208, 1e209, 1e210, 1e211, 1e212, 1e213, 1e214, 1e215, 1e216, 1e217, 1e218, 1e219, 1e220, 1e221, 1e222, 1e223,
            1e224, 1e225, 1e226, 1e227, 1e228, 1e229, 1e230, 1e231, 1e232, 1e233, 1e234, 1e235, 1e236, 1e237, 1e238, 1e239,
            1e240, 1e241, 1e242, 1e243, 1e244, 1e245, 1e246, 1e247, 1e248, 1e249, 1e250, 1e251, 1e252, 1e253, 1e254, 1e255,
            1e256, 1e257, 1e258, 1e259, 1e260, 1e261, 1e262, 1e263, 1e264, 1e265, 1e266, 1e267, 1e268, 1e269, 1e270, 1e271,
            1e272, 1e273, 1e274, 1e275, 1e276, 1e277, 1e278, 1e279, 1e280, 1e281, 1e282, 1e283, 1e284, 1e285, 1e286, 1e287,
            1e288, 1e289, 1e290, 1e291, 1e292, 1e293, 1e294, 1e295, 1e296, 1e297, 1e298, 1e299, 1e300, 1e301, 1e302, 1e303,
            1e304, 1e305, 1e306, 1e307, 1e308
        };
        return pows[f];
    }
    
    /**
     * @fn inline void json_number_parser::parse_exp_part(CharReaderType& reader, object_type& object, uint32_t used_exp)
     *
     * @brief 解析科学计数部分.
     *
     * @param [in,out] reader   The reader.
     * @param [in,out] object   The object.
     * @param 		   used_exp The used exponent.
     */
    
    inline void parse_exp_part(CharReaderType& reader, object_type& object, uint32_t used_exp) {
        reader.forward();
        //eE后面是否为-+号
        char ch = reader.next();
        int32_t max_allowd_exp = 308 - used_exp; //最大还允许的幂
        bool small_exp = false;
        
        // 如果是+-号，那么后面必需跟一个数字
        if (ch == '+' || ch == '-') {
            if (ch == '-') { small_exp = true; }
            ch = reader.next();
        }
        
        // E e + - 后面必需跟一个数字
        if (!is_char_0_9(ch)) { set_invalid_object(reader); }
        
        int32_t exp = ch - '0';
        calc_exp_value(reader, exp);
        // 超大浮点数
        if (!small_exp) {
            if (exp < max_allowd_exp) { // 小于极限值，怎么乘都不会溢出
                object.d.d *= pow_n(exp);
            } else if (exp == max_allowd_exp) { // 等于极限值，可能会溢出，不能直接*pow_n(exp)
                object.d.d *= pow_n(exp - 1);   // 先乘一下安全的数，再判断是否会溢出
                check_and_calc_number(reader, object.d.d, '0'); // 检测乘10后是否会溢出，如果溢出throw
            } else { // 大于极限值，直接就溢出了
                set_invalid_object(reader);
            }
        } else { // 小数
            (exp <= max_allowd_exp) ? (object.d.d /= pow_n(exp)) : (object.d.d = 0);
        }
        
        if (object.d.ss.flag == json_value_integer) { object.d.d = -object.d.d; }
        object.d.ss.flag = json_value_float;
    }
    
    /**
     * @fn inline void json_number_parser::parse_frac_part(CharReaderType& reader, object_type& object, uint32_t used_exp)
     *
     * @brief 解析浮点数.
     *
     * @param [in,out] reader   The reader.
     * @param [in,out] object   The object.
     * @param 		   used_exp The used exponent.
     */
    
    inline void parse_frac_part(CharReaderType& reader, object_type& object, uint32_t used_exp) {
        object.d.d = (double)object.d.u;
        reader.forward();
        // 获取小数点后的字符，小数点后面可接受的值为0-9
        char ch = reader.next();
        if (!is_char_0_9(ch)) { return set_invalid_object(reader); }
        uint64_t frac_part = ch - '0';
        
        uint32_t exp = 1;
        
        for (; reader.good(); reader.forward()) {
            ch = reader.peek();
            if (!is_char_0_9(ch)) { break; }
            
            // 判断是否已溢出
            if ((exp + used_exp) > 18 && is_number_overflow(reader, frac_part, ch)) {
                ch = skip_digit_char(reader);
                break;
            }
            frac_part = frac_part * 10 + ch - '0';
            ++exp;
        }
        
        object.d.d += frac_part / pow_n(exp);
        
        if (ch == 'e' || ch == 'E') { return parse_exp_part(reader, object, used_exp); }
        if (object.d.ss.flag == json_value_integer) {
            object.d.d = -object.d.d;
        }
        object.d.ss.flag = json_value_float;
    }
    
    /**
    * @fn inline void json_number_parser::parse_integer_low_part(CharReaderType& reader, object_type& object, uint32_t used_exp)
    *
    * @brief 解析大整数后面的低精度部分，超过最大精度，后面的值直接忽略.
    *
    * @param [in,out] reader   The reader.
    * @param [in,out] object   The object.
    * @param 		   used_exp The used exponent.
    */
    
    inline void parse_integer_low_part(CharReaderType& reader, object_type& object, uint32_t used_exp) {
        char ch = '\0';
        uint32_t exp = 0;
        for (; reader.good(); reader.forward()) {
            ch = reader.peek();
            if (!is_char_0_9(ch)) { break; }
            ++exp;
        }
        
        used_exp += exp;
        
        if (used_exp < 308) {
            object.d.d = object.d.u * pow_n(exp);
        } else if (used_exp == 308) { // 检测乘10后是否会溢出，如果溢出抛出异常
            object.d.d = object.d.u * pow_n(exp - 1);
            check_and_calc_number(reader, object.d.d, '0');
        } else {
            set_invalid_object(reader);
        }
        
        // 已经溢出，小数点后面的不要了
        if (ch == '.') { reader.forward(); ch = skip_digit_char(reader); }
        // 解析为科学计数
        if (ch == 'e' || ch == 'E') { return parse_exp_part(reader, object, used_exp); }
        
        // 其他字符均视为数字的结束标志
        if (object.d.ss.flag == json_value_integer) { object.d.d = -object.d.d; }
        object.d.ss.flag = json_value_float;
    }
    
    /**
     * @fn inline void json_number_parser::parse_number(CharReaderType& reader, object_type& object)
     *
     * @brief Parse number.
     *
     * @param [in,out] reader The reader.
     * @param [in,out] object The object.
     */
    
    inline void parse_number(CharReaderType& reader, object_type& object) {
        char signbit = reader.rpeek(1);  // 查看第一个字符是否为负号
        char char0 = signbit;
        char char1 = reader.peek();;
        // 拿4个字符来判断字符串是否为合法数字
        if (signbit == '-') {
            char0 = reader.peek(0);
            char1 = reader.peek(1);
            object.d.ss.flag = json_value_integer;
            // 负号后面必须跟一个数字
            if (!is_char_0_9(char0)) { set_invalid_object(reader); }
            object.d.u = char0 - '0';
            reader.next(); //移动到下一个字符
        } else {
            object.d.u = signbit - '0';
            object.d.ss.flag = json_value_unsigned;
        }
        
        uint32_t used_exp = 0;
        // 当前函数判断数字是否合法的流程
        // 1. 找到第一个不是0-9之间的char
        char ch = '\0';
        
        for (; reader.good(); reader.forward()) {
            ch = reader.peek();
            if (!is_char_0_9(ch)) { break; }
            
            // 整型溢出，使用double来保存数据
            if (used_exp > 17 && is_number_overflow(reader, object.d.u, ch)) {
                object.d.ss.placeholder2 = -1;
                return parse_integer_low_part(reader, object, used_exp);
            }
            
            ++used_exp;
            object.d.u = object.d.u * 10 + (ch - '0');
        }
        
        // 解析为浮点数
        if (ch == '.') { return parse_frac_part(reader, object, used_exp); }
        if (ch == 'e' || ch == 'E') { object.d.d = (double)object.d.u; return parse_exp_part(reader, object, used_exp); }
        
        // 其他字符均视为数字的结束标志
        if (signbit != '-') {
            if (signbit == '0' && used_exp != 0) { set_invalid_object(reader); }
        } else {
            // 判断当前数字是否大于最小负整数
            if (object.d.u <= (uint64_t)(std::numeric_limits<int64_t>::max)() + 1) {
                if (char0 == '0' && used_exp != 0) { set_invalid_object(reader); }
                object.d.i = -static_cast<int64_t>(object.d.u);
            } else {
                set_invalid_object(reader);
            }
        }
    }
};

_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_number_parser


#ifndef segment_json_string_reader
#define segment_json_string_reader

_AMO_NAMESPACE_BEGIN
template<typename JsonAllocType> class json_string_reader {
public:
    typedef char* StringBufferType;
    typedef int32_t reader_type;
public:
    const char* reader;		   // 字符串指针
    size_t length;			   // 数据种长度
    size_t current_index;	   // 当前读取到的位置
    size_t start_pos;		   // 索引开始位置
    JsonAllocType m_allocator; // JSON类型分配器
public:

    // 从字符串中构造对象
    json_string_reader(JsonAllocType& allocator_, const char* str, size_t len)
        : m_allocator(allocator_)
        , reader(allocator_->allocate(len + 2)) // 向内存分配器申请一块内存，保存需要解析的字符串
        , length(len + 2)
        , current_index(0)
        , start_pos(0) {
        memcpy((char*)reader, str, len);
        ((char*)reader)[len] = '\0';
        ((char*)reader)[len + 1] = '\0';
    }
    
    // 从一个流中构造对象
    json_string_reader(JsonAllocType& allocator_, std::istream* stream_) : m_allocator(allocator_), start_pos(0) {
        const static size_t L_DEFAULT_BUFFER_SIZE = 1024 * 60;
        char buffer[L_DEFAULT_BUFFER_SIZE ] = { 0 };  // 临时缓存
        std::string str;
        // 读取stream_中的所有数据到str中
        while (stream_->good()) {
            stream_->read(buffer, L_DEFAULT_BUFFER_SIZE);
            str.append(buffer, (size_t)stream_->gcount());
        }
        
        str += '\0';
        char* ptr = this->m_allocator->allocate(str.size() + 1); // 申请内存
        memcpy(ptr, str.c_str(), str.size());
        ptr[str.size()] = '\0';
        
        this->reader = ptr;
        this->length = str.size() + 1;
        this->current_index = 0;
        
    }
    // 返回已处理的字符数
    inline size_t processed_size() const { return current_index; }
    // JSON字符串错误时返回错误位置附近的一些字符串
    inline const std::string error_buffers() const {
        size_t sub_start_pos = 0;
        if (current_index > 20) {
            sub_start_pos = current_index - 20;
        }
        size_t offset_len = 60;
        if (sub_start_pos + offset_len > length) { offset_len = length - sub_start_pos; }
        
        return std::string(reader + sub_start_pos, offset_len);
    }
    // 读取当前字符，将指针移向后一个字符
    inline char next() { return reader[current_index++]; }
    // 读取前一个字符
    inline char back() { return reader[--current_index]; }
    // 读取当前字符
    inline char peek() const { return reader[current_index]; }
    // 读取指定偏移量的字符
    inline char peek(size_t offset) const { return reader[current_index + offset]; }
    // 读取当前字符
    inline char rpeek() const { return reader[current_index]; }
    // 读取向后指定偏移量的字符
    inline char rpeek(size_t offset) const { return reader[current_index - offset]; }
    
    // 获取当前位置的指针
    inline const char* current_address() const { return reader + current_index; }
    // 获取string_reader Buffer对象
    inline StringBufferType string_buffer() { return (char*)reader + current_index; }
    // 开始记录读取的字符串，主要用于解析json_value_string
    inline void start_refstring() { start_pos = current_index; }
    inline void start_refstring(size_t pos) { start_pos = pos; }
    // 返回从start_refstring调用后所缓存的字符串
    inline void stop_refstring(char*& first, uint32_t& second) {
        first = (char*)(reader + start_pos);
        second = static_cast<uint32_t>(current_index - start_pos);
        start_pos = current_index;
    }
    // 向后移动指针
    inline void back_forward() { --current_index; }
    inline void back_forward(int32_t offset) { current_index -= offset; }
    // 向前移动指针
    inline void forward() { ++current_index; }
    inline void forward(int32_t offset) { current_index += offset; }
    // 判断当前流是否无效
    inline bool eof() const { return current_index >= length; }
    inline bool eof(int32_t offset) const { return current_index + offset >= length; }
    // 判断是否已经到流的末尾,当前流是否有效
    inline bool good() const { return current_index < length; }
    inline bool good(size_t offset) const { return current_index + offset < length; }
    // 判断当前位置是否安全，某些情况下，总是安全的，可以用来替换good函数来提升效率
    inline bool safe() const { return true; }
    // 返回当前流的索引
    inline size_t index() const { return current_index; }
};
_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_json_string_reader


#ifndef segment_json_string_buffer
#define segment_json_string_buffer

_AMO_NAMESPACE_BEGIN

// 字符串缓存类，用来缓存token_reader中读取的字符，用于拷贝类型的token_reader
class json_string_buffer {
public:
    json_string_buffer() : m_buffer(16384, 0), pos(0) {}
    // 追加一个char
    inline json_string_buffer& append(char ch) {
        if (pos + 1 >= m_buffer.size()) { m_buffer.resize(m_buffer.size() * 2);  }
        m_buffer[pos++] = ch;
        return *this;
    }
    // 追加指定长度的char*
    inline json_string_buffer& append(const char* str, size_t len) {
        if (pos + len >= m_buffer.size()) { m_buffer.resize(m_buffer.size() * 2);  }
        memcpy(m_buffer.data() + pos, str, len);
        pos += len;
        return *this;
    }
    
    // 置空
    inline void reset() { pos = 0; }
    // 返回缓存字符串的开始位置
    inline const char* address() const { return m_buffer.data(); }
    // 返回当前缓存字符串的长度
    inline size_t length() const { return pos; }
    // 返回缓冲区容量
    inline size_t capacity() const { return m_buffer.size(); }
    // 重新设置缓冲区大小
    inline void resize(size_t new_size) { return m_buffer.resize(new_size); }
private:
    size_t pos;                     // 已使用的长度
    std::vector<char> m_buffer;     // 缓冲区
};
_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_json_string_buffer


#ifndef segment_json_stream_reader_buffer
#define segment_json_stream_reader_buffer

_AMO_NAMESPACE_BEGIN
class json_stream_reader_buffer {
public:
    inline bool need_copy_data() const { return buffers.length() > 0; }
    inline char& operator[](size_t index) { return start[len++]; } // 兼容unescape
    
    inline void reset(const char* ptr_) {
        buffers.reset();
        start = (char*)ptr_;
        len = 0;
    }
    
    // 当buffer指针所指的原始数据将要发生变化时，缓存数据到vetor中去
    inline void cache_data(const char* end_pos) {
        if (len == 0) { len = static_cast<uint32_t>(end_pos - start); }
        buffers.append(start, len);
        start = nullptr;
        len = 0;
    }
    
    // 获取总的缓存区长度
    inline size_t size() const { return len + buffers.length(); }
    inline size_t buffers_size() { return buffers.length(); }
    
    // 将缓存的数据复制到指定指针上，len暂时不用
    inline void copy_data(char* dst_, size_t len_) {
        memcpy(dst_, buffers.address(), buffers.length());
        memcpy(dst_ + buffers.length(), start, len);
    }
    
public:
    char* start;					// 需要缓存的字符串的开始地址
    uint32_t len;					// 长度
    json_string_buffer buffers;		// 缓存新数据时将上一次缓存的数据保存到buffers中去
};
_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_stream_reader_buffer


#ifndef segment_json_stream_reader
#define segment_json_stream_reader
_AMO_NAMESPACE_BEGIN
// 读流
template<typename JsonAllocType>
class json_stream_reader {
public:
    typedef json_stream_reader_buffer& StringBufferType;
    typedef uint32_t reader_type;
public:
    json_stream_reader_buffer m_string_buffer;		// 缓存token内容
    std::istream* stream;					        // stream
    char* buffer;							        // 缓存stream的字符串
    size_t current_index;
    size_t length;
    // 预留8个字节，用来防止读取 true,false,null 之类的固定字节时越界,还有string也是这样的。
    size_t reserved = 8;
    bool m_b_refstring;						        // 是否处于refstring状态
    size_t start_pos;						        // 索引开始位置
    size_t processed_count = 0;                     // 已处理的字符数
    char ch;
    const static size_t MAX_BUFFER_LEN = 65535;
    JsonAllocType m_allocator;
public:
    json_stream_reader(JsonAllocType& allocator_, const std::istream* stream_)
        : m_allocator(allocator_)
        , stream((std::istream*)stream_)
        , current_index(0)
        , ch('\0')
        , start_pos(0) {
        
        buffer = m_allocator->allocate(MAX_BUFFER_LEN);
        m_b_refstring = false;
        stream->read(buffer, MAX_BUFFER_LEN);
        length = (int32_t)stream->gcount();
        
        if (length < MAX_BUFFER_LEN) {
            stream = nullptr;
            buffer[length] = '\0';
            ++length;
        }
    }
    
    json_stream_reader(JsonAllocType& allocator_, const char* str, size_t len)
        : m_allocator(allocator_)
        , stream(nullptr)
        , current_index(0)
        , ch('\0')
        , start_pos(0) {
        buffer = m_allocator->allocate(len + 1);
        memcpy(buffer, str, len);
        buffer[len] = '\0';
        length = len + 1;
        m_b_refstring = false;
    }
    //
    inline bool has_more() {
        if (length > 0 && (current_index < length - reserved)) { return true; }
        this->fill_buffer();
        return length > 0 && (current_index < length);
    }
    
    // 重新填充缓冲区
    inline void fill_buffer() {
        if (!stream || stream->eof()) { return;}
        
        if (m_b_refstring) {
            //TODO: back_forward BUG
            // 将当前缓存中的剩余部分复制到stringbuffer中
            m_string_buffer.cache_data(buffer + current_index);
            m_string_buffer.reset(buffer);
            start_pos = 0;
        }
        
        
        // 将未使用的部分移动到前面去（包括current_index）
        size_t unused = length - current_index;
        memcpy(buffer, buffer + current_index, unused);
        // 计算被占用的空间
        size_t used = unused;
        
        stream->read(buffer + used, MAX_BUFFER_LEN - used);
        processed_count += current_index;
        current_index = 0;
        int32_t readcount = (int32_t)stream->gcount();
        length = readcount + used;
        
        if (readcount == MAX_BUFFER_LEN - used) {
            reserved = (std::min<size_t>)(length, 8);
        } else {
            reserved = 0;
        }
    }
    // 返回已处理的字节数
    inline size_t processed_size() const { return processed_count + current_index; }
    // JSON字符串错误时返回错误位置附近的一些字符串
    inline const std::string error_buffers() const {
        size_t sub_start_pos = 0;
        if (current_index > 20) { sub_start_pos = current_index - 20;}
        size_t offset_len = 40;
        if (sub_start_pos + offset_len > length) { offset_len = length - sub_start_pos; }
        return std::string(buffer + sub_start_pos, offset_len);
    }
    // 读取后一个字符
    inline char next() { return buffer[current_index++]; }
    // 读取前一个字符
    inline char back() { return buffer[--current_index]; }
    // 读取当前字符
    inline char peek() const { return buffer[current_index]; }
    // 读取指定偏移量的字符
    inline char peek(size_t offset) const { return buffer[current_index + offset]; }
    // 读取当前字符
    inline char rpeek() const { return buffer[current_index]; }
    // 读取指定偏移量的字符
    inline char rpeek(size_t offset) const { return buffer[current_index - offset]; }
    // 获取当前位置的指针
    inline const char* current_address() const { return buffer + current_index; }
    // 获取stringreaderBuffer对象
    inline StringBufferType string_buffer() { return m_string_buffer; }
    // 记录当前函数调用后所读取的字符串
    inline void start_refstring() {
        m_string_buffer.reset(buffer + current_index);
        start_pos = current_index;
        m_b_refstring = true; // 标记状态为true
    }
    inline void start_refstring(int32_t pos) {
        m_string_buffer.reset(buffer + pos);
        start_pos = pos;
        m_b_refstring = true; // 标记状态为true
    }
    // 获取从start_refstring调用后所缓存的字符串
    inline void stop_refstring(char*& first, uint32_t& second) {
        // 1. stream == nullptr,说明操作和StringReader一样，不需要进行复制
        // 2. 如果m_bbb.size() == 0; 那么说明重来没有调用过append操作，这时应该直接使用current_pos - start_pos;
        // 如果是一次读入缓存区的，那么直接返回地址
        if (stream == nullptr) {
            // 不能直接拿到字符串的真实长度 ，参考unescape
            first = buffer + start_pos;
            second = static_cast<uint32_t>(current_index - start_pos);
        } else {
            // 如果m_bbbb.len == 0，那么使用当前缓存长度，那么更新一下实际的缓存长度
            if (m_string_buffer.len == 0) { m_string_buffer.len = static_cast<uint32_t>(current_index - start_pos); }
            second = static_cast<uint32_t>(m_string_buffer.size());
            first = m_allocator->allocate(second + 1);
            m_string_buffer.copy_data(first, second);
        }
        
        m_b_refstring = false;
    }
    
    inline void back_forward() { --current_index; }
    inline void back_forward(size_t offset) { current_index -= offset; }
    inline void forward() { ++current_index; }
    inline void forward(size_t offset) { current_index += offset; }
    // 判断当前流是否无效
    inline bool eof() { return !has_more(); }
    inline bool eof(size_t offset) const { return current_index + offset >= length; }
    // 判断是否已经到流的末尾,当前流是否有效
    inline bool good() { return !this->eof(); }
    inline bool good(size_t offset) const { return !this->eof(offset); }
    // 判断当前位置是否安全
    inline bool safe() { return this->good(); }
    // 返回当前流的索引
    inline size_t index() const { return current_index; }
};

_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_stream_reader


#ifndef segment_json_array_container
#define segment_json_array_container

_AMO_NAMESPACE_BEGIN

// JSON数组封装,能比std::vector快一点点，并不明显
// BLOCK_SIZE为数组扩容时的长度
template<typename ObjectType, typename Alloc, int BLOCK_SIZE = 4> class json_array_container {
public:
    typedef typename ObjectType::size_type size_type;
    typedef ObjectType* iterator;
    typedef const iterator const_iterator;
public:
    json_array_container() : m_json_array(nullptr), total(0), current_pos(0) {}
    json_array_container(const Alloc& allocator_) : allocator(allocator_), total(BLOCK_SIZE), current_pos(0) {
        __init_json_array_buffer();
    }
    json_array_container(size_t count_, const ObjectType& value_, const Alloc& allocator_)
        : allocator(allocator_)
        , total(count_)
        , current_pos(0) {
        __init_json_array_buffer();
    }
    inline ObjectType& push_back_object() {
        __resize_if_necessary();
        return m_json_array[current_pos++];
    }
    iterator erase(const_iterator first, const_iterator last) {
        if (last > this->end()) { return this->end(); }
        size_t erase_size = last - first; // 计算要移除的元素个数
        size_t right_size = this->end() - last;
        std::memcpy((char*)first, (char*)last, (right_size) * sizeof(ObjectType));
        current_pos -= erase_size;
        return first;
    }
    inline iterator erase(const_iterator first) { return this->erase(first, first + 1); }
    inline size_t size() const { return current_pos; }
    inline ObjectType& at(size_t index) { return m_json_array[index]; }
    inline ObjectType& operator[](size_t index) { return m_json_array[index]; }
    inline bool empty() const { return current_pos == 0; }
    inline void clear() { current_pos = 0; }
    inline iterator begin() { return m_json_array; }
    inline const_iterator begin() const { return m_json_array; }
    inline iterator end() { return m_json_array + current_pos; }
    inline const_iterator end() const { return m_json_array + current_pos; }
private:
    inline void __resize_if_necessary() {
        if (current_pos < total) { return; }
        total *= 2;
        ObjectType* ptr = allocator.allocate(total);
        size_t left_len_ = (current_pos) * sizeof(ObjectType);
        size_t right_len_ = total * sizeof(ObjectType) - left_len_;
        memcpy((char*)ptr, (char*)m_json_array, (current_pos) * sizeof(ObjectType));
        memset((char*)ptr + left_len_, 0, right_len_);
        m_json_array = (ObjectType*)ptr;
        
    }
    inline void __init_json_array_buffer() {
        ObjectType* ptr = allocator.allocate(total);
        memset(ptr, 0, total * sizeof(ObjectType));
        m_json_array = (ObjectType*)ptr;
    }
private:
    Alloc allocator;            // 内存分配器
    ObjectType* m_json_array;   // 数组内存空间
    size_t total;             // 数组容量
    size_t current_pos;       // 已使用的空间
};


_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_array_container


#ifndef segment_json_object_container
#define segment_json_object_container

_AMO_NAMESPACE_BEGIN
template<typename KeyType, typename ValueType, typename Comp, typename Alloc, int32_t MAX_SIZE = 16>
class json_object_container {
public:
    using ContainerType = std::array<std::pair<const KeyType, ValueType>, MAX_SIZE>;
    
    typedef typename std::map<KeyType, ValueType, Comp, Alloc > MapType;
    typedef typename MapType::key_compare key_compare;
    
    using value_type = std::pair<const KeyType, ValueType>;
    typedef typename ValueType::JsonAllocType JsonAllocType;
    typedef typename ValueType::MemoryAllocType MemoryAllocType;
    template<int IterType = 1>
    class iterator_base : public std::iterator<std::forward_iterator_tag, value_type> {
        friend class json_object_container;
    protected:
        json_object_container* m_ptr;								// 容器的指针
        typename MapType::iterator m_iter;							// map的iterator
        size_t m_index;												// 数组的index
        bool m_has_map;												// 是否存在map
        iterator_base(json_object_container* ptr, size_t index_) : m_ptr(ptr), m_index(index_), m_has_map(false) {}
        iterator_base(json_object_container* ptr, size_t index_, const typename MapType::iterator& iter)
            : m_ptr(ptr), m_index(index_), m_iter(iter), m_has_map(true) {}
    public:
        iterator_base() : m_ptr(0), m_index(0), m_has_map(false) {}
        iterator_base operator++() {
            if (m_index >= m_ptr->current_pos && m_has_map) {
                ++m_iter;
                return *this;
            }
            
            m_index++;
            return *this;
        }
        inline bool operator<(const iterator_base& other) const { return m_index > other.m_index; }
        inline bool operator==(const iterator_base& other) const { return !this->operator !=(other); }
        inline bool operator!=(const iterator_base& other) const {
            if (m_index != other.m_index) { return true; }
            if (m_index >= m_ptr->current_pos && m_has_map) {  return this->m_iter != other.m_iter;  }
            return false;
        }
        inline const std::pair<const KeyType, ValueType>& operator*() const { return get_value(); }
        inline const std::pair<const KeyType, ValueType>* operator->() const { return &get_value(); }
        inline typename std::enable_if<IterType == 1, std::pair<const KeyType, ValueType>&>::type operator*() {
            return this->get_value();
        }
        inline typename std::enable_if<IterType == 1, std::pair<const KeyType, ValueType>*>::type operator->() {
            return &this->get_value();
        }
        inline std::pair<const KeyType, ValueType>& get_value() {
            if (is_fast_mode()) {
                return m_ptr->m_object_array[m_index];
            } else if (m_has_map) {
                return *m_iter;
            }
            
            // 返回一个越界值
            return m_ptr->m_object_array[m_ptr->current_pos];
        }
        inline const std::pair<const KeyType, ValueType>& get_value() const {
            if (is_fast_mode()) {
                return m_ptr->m_object_array[m_index];
            } else if (m_has_map) {
                return *m_iter;
            }
            
            // 返回一个越界值
            return m_ptr->m_object_array[m_ptr->current_pos];
        }
        inline bool is_fast_mode() const { return m_index < m_ptr->current_pos; }
    };
    
    typedef iterator_base<1> iterator;
    typedef iterator_base<0> const_iterator;
    using pair_boolean = std::pair<iterator, bool>;
public:
    json_object_container(const key_compare& __comp, const JsonAllocType& allocator_) : m_allocator(allocator_.get()) {}
    json_object_container(const JsonAllocType& allocator_) : m_allocator(allocator_.get()) {}
    ~json_object_container() { if (this->m_object_map) { this->m_object_map->~MapType(); } }
    
    inline size_t size() const {
        if (this->m_object_map != nullptr) { return current_pos + this->m_object_map->size(); }
        return current_pos;
    }
    
    inline iterator begin() {
        if (this->m_object_map != nullptr) {
            return iterator(this, 0, this->m_object_map->begin());
        } else {
            return iterator(this, 0);
        }
    }
    
    inline iterator end() {
        if (this->m_object_map != nullptr) {
            return iterator(this, current_pos, this->m_object_map->end());
        } else {
            return iterator(this, current_pos);
        }
    }
    
    inline const_iterator begin() const {
        if (this->m_object_map != nullptr) {
            return const_iterator(this, 0, this->m_object_map->begin());
        } else {
            return const_iterator(this, 0);
        }
    }
    
    inline const_iterator end() const {
        if (this->m_object_map != nullptr) {
            return const_iterator(this, current_pos, this->m_object_map->end());
        } else {
            return const_iterator(this, current_pos);
        }
    }
    
    inline MemoryAllocType* get_allocator() { return m_allocator; }
    
    template<typename T> typename
    std::enable_if<std::is_same<std::string, T>::value, ValueType&>::type find_or_insert_object_with_copy(const T& key) {
        return find_or_insert_object_with_move(key);
    }
    
    template<typename T> typename std::enable_if < std::is_same<T, KeyType>::value&& !std::is_same<std::string, T>::value,
    ValueType& >::type find_or_insert_object_with_copy(const T& key) {
        for (size_t i = 0; i < current_pos; ++i) {
            if (m_object_array[i].first == key) {
                return m_object_array[i].second;
            }
        }
        
        if (current_pos < MAX_SIZE) {
            char* ptr = this->get_allocator()->allocate(key.size() + 1);
            ptr[key.size()] = '\0';
            memcpy(ptr, key.data(), key.size());
            ((KeyType&)m_object_array[current_pos].first) = KeyType(ptr, key.size());
            //m_object_array[current_pos].second.d.ss.flag = 0;  // 将类型置0
            return m_object_array[current_pos++].second;
        }
        
        // 保证map不为空
        __create_std_map();
        auto iter = this->m_object_map->find(key);
        if (iter == this->m_object_map->end()) {
            char* ptr = this->get_allocator()->allocate(key.size() + 1);
            ptr[key.size()] = '\0';
            memcpy(ptr, key.data(), key.size());
            iter = this->m_object_map->insert({ KeyType(ptr, key.size()), ValueType() }).first;
        }
        return iter->second;
    }
    // 快速插入模式，不进行key值比较，可以提高解析速度
    template<int mode> inline typename std::enable_if < mode != 0,
    ValueType& >::type find_or_insert_object_with_move(const KeyType& key) {
        if (current_pos < MAX_SIZE) {
            ((KeyType&)m_object_array[current_pos].first) = key;
            return m_object_array[current_pos++].second;
        }
        
        // 保证map不为空
        __create_std_map();
        auto iter = this->m_object_map->find(key);
        if (iter == this->m_object_map->end()) {
            iter = this->m_object_map->insert({ key, ValueType() }).first;
        }
        return iter->second;
    }
    // 进行KEY值比较
    template<int mode> inline typename std::enable_if < mode == 0, ValueType& >::type find_or_insert_object_with_move(
        const KeyType& key) {
        for (size_t i = 0; i < current_pos; ++i) {
            if (m_object_array[i].first == key) {
                return m_object_array[i].second;
            }
        }
        
        return find_or_insert_object_with_move<1>(key);
    }
    
    inline iterator find(const KeyType& key) {
        for (auto iter = this->begin(); iter != this->end(); ++iter) {
            if (iter->first == key) { return iter; }
        }
        return end();
    }
    
    inline const_iterator find(const KeyType& key) const {
        for (auto iter = this->begin(); iter != this->end(); ++iter) {
            if (iter->first == key) { return iter; }
        }
        
        return end();
    }
    
    inline iterator erase(const KeyType& key) {
        for (size_t i = 0; i < current_pos; ++i) {
            if (m_object_array[i].first == key) {
                // 释放资源
                m_object_array[i].second.release(this->get_allocator());
                //TODO: 释放KEY
                //m_object_array[i].first.release();
                ((KeyType&)m_object_array[i].first) = std::move(m_object_array[current_pos - 1].first);
                // 将列表中的最后一个元素放到当前位置
                m_object_array[i].second = std::move(m_object_array[current_pos - 1].second);
                m_object_array[current_pos - 1].second.d.ss.flag = 0; //将类型置0
                --current_pos;
                // 不管map的iter, 被移除的iterator不会再去做其他操作
                return { this, current_pos };
            }
        }
        
        if (m_object_map != nullptr) {
            auto iter = m_object_map->find(key);
            if (iter != m_object_map->end()) {
                //TODO: 释放KeyString
                iter->second.release(this->get_allocator());
                m_object_map->erase(iter);
            }
            
            return { this, current_pos };
        }
        
        return end();
    }
    
    inline ValueType& operator[](const KeyType& key) { return find(key)->second; }
    inline const ValueType& operator[](const KeyType& key) const { return this->find(key)->second; }
private:
    inline void __create_std_map() {
        if (this->m_object_map == nullptr) {
            char* ptr = this->get_allocator()->allocate(sizeof(MapType));
            m_object_map = new (ptr)  MapType(typename MapType::key_compare(), this->get_allocator());
        }
    }
private:
    ContainerType m_object_array;       // 连续空间，优先使用
    MapType* m_object_map = nullptr;    // MAP容器
    MemoryAllocType* m_allocator;
    size_t current_pos = 0;             // m_object_array 已使用的空间
};
_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_object_container


#ifndef segment_json_data_types
#define segment_json_data_types

_AMO_NAMESPACE_BEGIN
// 长字符串
struct String {
    using value_type = char;
    typedef uint32_t size_type;
    value_type* elements;			// 起始地址
    size_type length;					// 当前数据长度
};

// 短字符串,只用的Flag功能
struct ShortString {
    uint64_t placeholder1;       // 占位符，没什么用
    int16_t placeholder2;        // 占位符，没什么用
    int16_t placeholder3;        // 占位符，没什么用
    int16_t placeholder4;        // 占位符，没什么用
    uint16_t flag;               // 类型标识符
};

// 键值类型
template<typename ObjectTypeTraits>
struct ObjectData {
    using value_type = ObjectTypeTraits;
    value_type* elements;
};

// 数组类型
template<typename ArrayTypeTraits>
struct ArrayData {
    using value_type = ArrayTypeTraits;
    value_type* elements;
};

_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_data_types


#ifndef segment_json_key_string
#define segment_json_key_string
_AMO_NAMESPACE_BEGIN

// 引用键值Key
class json_key_string {
public:
    union StringData { String s; };
    typedef StringData KeyDataType;
    typedef uint32_t size_type;
public:
    StringData d;
public:
    json_key_string() {
        // 如果要释放内存，需要将初始化当前内存块
        //d.ss.flag = EMPTYSTRING;
        //d.s.elements = nullptr;
    }
    
    // 传进来的为字符串地址，在JsonKeyString的生命周期内，该指针不会被释放
    json_key_string(const char* val, size_type len) {
        d.s.elements = (char*)val;
        d.s.length = len;
    }
    
    ~json_key_string() { /*不释放内存*/ }
    
    json_key_string(const char* val) : json_key_string(val, (size_type)strlen(val)) { }
    json_key_string(const std::string& val) : json_key_string(val.c_str(), (size_type)val.size()) { }
    json_key_string(const std::string&& val) : json_key_string(val.c_str(), (size_type)val.size()) { }
    json_key_string(const json_key_string& rhs) : json_key_string(std::move(rhs.d)) { }
    json_key_string(const json_key_string&& rhs) : json_key_string(std::move(rhs.d)) { }
    json_key_string& operator=(const json_key_string& rhs) { d = std::move(rhs.d);  return *this; }
    json_key_string& operator=(const json_key_string&& rhs) { d = std::move(rhs.d);  return *this; }
    json_key_string(const KeyDataType& d_) { copy_data(this->d, d_); }
    json_key_string(const KeyDataType&& d_) {  d = d_; }
    
    
    inline json_key_string clone() const {
        json_key_string retval;
        retval.copy_data(retval.d, this->d);
        return retval;
    }
    inline void copy_data(KeyDataType& dst, const KeyDataType& src) const {
        dst.s.elements = src.s.elements;
        dst.s.length = src.s.length;
    }
    
    inline const char* c_str() const { return d.s.elements; }
    inline const char* data() const { return d.s.elements; }
    inline const std::pair<const char*, uint32_t> buffer() const { return { d.s.elements, (uint32_t)d.s.length }; }
    
    inline int32_t size() const { return d.s.length; }
    operator std::string() const { return { d.s.elements, (uint32_t)d.s.length }; }
    std::string to_string() const { return this->operator std::string(); }
    
    inline int traits_compare(const char* left, const uint32_t left_size,
                              const char* right, const uint32_t right_size) const {
        const int ans = compare(left, right, (right_size < left_size ? right_size : left_size));
        if (ans != 0) { return ans; }
        if (left_size < right_size) { return -1; }
        if (left_size > right_size) { return 1; }
        return 0;
    }
    
    
    inline bool traits_equal(const std::pair<const char*, uint32_t>&& a,
                             const std::pair<const char*, uint32_t>&& b) const {
        return a.second == b.second && compare(a.first, b.first, a.second) == 0;
    }
    inline int compare(const char* left, const char* right, uint32_t _Count) const {
        for (; 0 < _Count; --_Count, ++left, ++right) {
            if (*left != *right) {
                return *left < *right ? -1 : +1;
            }
        }
        return 0;
    }
    
    inline int compare(const int* left, const int* right, uint32_t _Count) const {
        for (; 0 < _Count; --_Count, ++left, ++right) {
            if (*left != *right) {
                return *left < *right ? -1 : +1;
            }
        }
        return 0;
    }
    
    inline bool operator<(const json_key_string& rhs) const {
        return traits_compare(this->data(), this->size(), rhs.data(), rhs.size()) < 0;
    }
    inline bool operator>(const json_key_string& rhs) const {
        return traits_compare(this->data(), this->size(), rhs.data(), rhs.size()) > 0;
    }
    inline bool operator==(const json_key_string& _Right) const {
        return traits_equal(this->buffer(), _Right.buffer());
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const json_key_string& str) {
        stream.write(str.data(), str.size());
        return stream;
    }
};

_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_key_string


#ifndef segment_nil
#define segment_nil

_AMO_NAMESPACE_BEGIN
struct nil {};
_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_nil


#ifndef segment_type_traits
#define segment_type_traits
#include <type_traits>
#include <memory>
#include <utility>
#include <list>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <forward_list>
#include <unordered_map>
#include <unordered_set>

#ifndef AMO_CLASS_HAS_MEMBER_VARIABLE
#define AMO_CLASS_HAS_MEMBER_VARIBALE(var) \
    _AMO_NAMESPACE_BEGIN\
    template<typename T>\
    struct has_member_variable_##var{\
        template <typename U>static auto check(U)->typename std::decay<decltype(U::var)>::type;\
        static std::false_type check(...);\
        using type =  decltype(check(std::declval<T>()));\
        enum{value=!std::is_same<type, std::false_type>::value};\
    };\
    _AMO_NAMESPACE_END
#endif


#ifndef AMO_CLASS_HAS_MEMBER_FUNCTION2
#define AMO_CLASS_HAS_MEMBER_FUNCTION2(name, func)\
    _AMO_NAMESPACE_BEGIN\
    template<typename T, typename... Args>struct has_member_function_##name\
    {\
    private:\
        template<typename U> static auto check(int) -> typename std::decay<decltype(std::declval<U>(). func(std::declval<Args>()...))>::type;\
        template<typename U> static std::false_type check(...);\
    public:\
        using type = typename std::conditional<std::is_void<decltype(check<T>(0))>::value, nil, decltype(check<T>(0))>::type;\
        enum { value = !std::is_same<decltype(check<T>(0)), std::false_type>::value };\
    };\
    _AMO_NAMESPACE_END
#endif // !AMO_CLASS_HAS_MEMBER_FUNCTION2

#ifndef AMO_CLASS_HAS_MEMBER_FUNCTION
#define AMO_CLASS_HAS_MEMBER_FUNCTION(member) AMO_CLASS_HAS_MEMBER_FUNCTION2(member, member)
#endif // !AMO_CLASS_HAS_MEMBER_FUNCTION


#ifndef AMO_CLASS_HAS_DECLARE_TYPE
#define AMO_CLASS_HAS_DECLARE_TYPE(name)\
    _AMO_NAMESPACE_BEGIN\
    template<typename T> struct has_declare_##name {\
        template<typename U> static auto check(std::vector<typename U:: name>*)->typename U:: name;\
        template<typename U> static std::false_type check(...);\
        typedef decltype(check<T>(0)) type;\
        enum { value = !std::is_same<type, std::false_type>::value };\
    };\
    _AMO_NAMESPACE_END
#endif



#ifndef AMO_CLASS_HAS_STATIC_FUNCTION
#define AMO_CLASS_HAS_STATIC_FUNCTION(name)\
    _AMO_NAMESPACE_BEGIN\
    template<typename T> struct has_static_function_##name {\
        template<typename U> static auto check( std::vector<decltype(&U:: name)> *)-> decltype((&U:: name)) ;\
        template<typename U> static std::false_type check(...);\
        typedef decltype(check<T>(0)) type;\
        enum { value = !std::is_same<type, std::false_type>::value };\
    };\
    _AMO_NAMESPACE_END
#endif

// 判断是否为智能指针
#ifndef AMO_MAKE_SMART_PTR_TRAITS
#define AMO_MAKE_SMART_PTR_TRAITS(smart_ptr_type)\
    _AMO_NAMESPACE_BEGIN\
    template<typename T> struct is_##smart_ptr_type{\
        const static int value = std::is_class<T>::value && has_member_function_get<T>::value\
                                 && std::is_same< std:: smart_ptr_type <typename std::remove_pointer<typename has_member_function_get<T>::type>::type> , T>::value;\
    };\
    _AMO_NAMESPACE_END
#endif

// 所有的函数或变量都必须是public访问权限
AMO_CLASS_HAS_MEMBER_FUNCTION2(operator_square_brackets, operator[]) // 是否有函数 operator[]
AMO_CLASS_HAS_MEMBER_FUNCTION2(operator_asterisk, operator*)         // 是否有函数 operator*
AMO_CLASS_HAS_MEMBER_FUNCTION(begin)                                 // 是否有函数 begin
AMO_CLASS_HAS_MEMBER_FUNCTION(end)                                   // 是否有函数 end
AMO_CLASS_HAS_MEMBER_FUNCTION(at)                                    // 是否有函数 at
AMO_CLASS_HAS_MEMBER_FUNCTION(data)                                  // 是否有函数 data
AMO_CLASS_HAS_MEMBER_FUNCTION(capacity)                              // 是否有函数 data
AMO_CLASS_HAS_MEMBER_FUNCTION(push)                                  // 是否有函数 push
AMO_CLASS_HAS_MEMBER_FUNCTION(push_back)                             // 是否有函数 push_back
AMO_CLASS_HAS_MEMBER_FUNCTION(top)                                   // 是否有函数 top
AMO_CLASS_HAS_MEMBER_FUNCTION(pop)                                   // 是否有函数 pop
AMO_CLASS_HAS_MEMBER_FUNCTION(pop_back)                              // 是否有函数 pop_back
AMO_CLASS_HAS_MEMBER_FUNCTION(pop_front)                             // 是否有函数 pop_front
AMO_CLASS_HAS_MEMBER_FUNCTION(insert)                                // 是否有函数 insert
AMO_CLASS_HAS_MEMBER_FUNCTION(insert_after)                          // 是否有函数 insert_after
AMO_CLASS_HAS_MEMBER_FUNCTION(reserve)                               // 是否有函数 reserve
AMO_CLASS_HAS_MEMBER_FUNCTION(clear)                                 // 是否有函数 clear
AMO_CLASS_HAS_MEMBER_FUNCTION(empty)                                 // 是否有函数 empty
AMO_CLASS_HAS_MEMBER_FUNCTION(front)                                 // 是否有函数 front
AMO_CLASS_HAS_MEMBER_FUNCTION(swap)                                  // 是否有函数 swap
AMO_CLASS_HAS_MEMBER_FUNCTION(shrink_to_fit)                         // 是否有函数 shrink_to_fit
AMO_CLASS_HAS_MEMBER_FUNCTION(c_str)                                 // 是否有函数 c_str
AMO_CLASS_HAS_MEMBER_FUNCTION(length)                                // 是否有函数 length
AMO_CLASS_HAS_MEMBER_FUNCTION(emplace)                               // 是否有函数 emplace

AMO_CLASS_HAS_MEMBER_FUNCTION(count)                                 // 是否有函数 count
AMO_CLASS_HAS_MEMBER_FUNCTION(find)                                  // 是否有函数 find
AMO_CLASS_HAS_MEMBER_FUNCTION(use_count)                             // 是否有函数 use_count
AMO_CLASS_HAS_MEMBER_FUNCTION(bucket_count)                          // 是否有函数 bucket_count

AMO_CLASS_HAS_MEMBER_FUNCTION(get)                                   // 是否有函数 get
AMO_CLASS_HAS_MEMBER_FUNCTION(to_string)                             // 是否有函数 to_string
AMO_CLASS_HAS_MEMBER_FUNCTION(to_json)                               // 是否有函数 to_json
AMO_CLASS_HAS_MEMBER_VARIBALE(first)                                 // 是否有成员变量 first
AMO_CLASS_HAS_MEMBER_VARIBALE(second)                                // 是否有成员变量 second
AMO_CLASS_HAS_MEMBER_VARIBALE(__json_type_value__)                        // 是否有成员变量 __json_type_value__

AMO_CLASS_HAS_DECLARE_TYPE(type)                                     // 是否有typedef some_type type
AMO_CLASS_HAS_DECLARE_TYPE(value_type)                               // 是否有typedef some_type value_type
AMO_CLASS_HAS_DECLARE_TYPE(iterator)                                 // 是否有typedef iterator
AMO_CLASS_HAS_DECLARE_TYPE(const_iterator)                           // 是否有typedef const_iterator
AMO_CLASS_HAS_DECLARE_TYPE(iterator_category)                        // 是否有typedef iterator_category
AMO_CLASS_HAS_DECLARE_TYPE(key_type)                                 // 是否有typedef key_type
AMO_CLASS_HAS_DECLARE_TYPE(size_type)                                // 是否有typedef size_type
AMO_CLASS_HAS_DECLARE_TYPE(difference_type)                          // 是否有typedef difference_type
AMO_CLASS_HAS_DECLARE_TYPE(key_compare)                              // 是否有typedef key_compare
AMO_CLASS_HAS_DECLARE_TYPE(value_compare)                            // 是否有typedef value_compare
AMO_CLASS_HAS_DECLARE_TYPE(mapped_type)                              // 是否有typedef mapped_type
AMO_CLASS_HAS_DECLARE_TYPE(hasher)                                   // 是否有typedef hasher
AMO_CLASS_HAS_DECLARE_TYPE(key_equal)                                // 是否有typedef key_equal

AMO_CLASS_HAS_STATIC_FUNCTION(from_json)                             // 是否有静态函数 from_json
AMO_CLASS_HAS_STATIC_FUNCTION(from_string)                           // 是否有静态函数 from_string
AMO_CLASS_HAS_STATIC_FUNCTION(test)                                  // 是否有静态函数 test

AMO_MAKE_SMART_PTR_TRAITS(shared_ptr)   // std::shared_ptr
AMO_MAKE_SMART_PTR_TRAITS(unique_ptr)   // std::unique_ptr


_AMO_NAMESPACE_BEGIN
template<typename T> struct is_pair {
    typedef typename has_member_variable_first<T>::type first_type;
    typedef typename has_member_variable_second<T>::type second_type;
    const static bool value = std::is_class<T>::value && has_member_variable_first<T>::value
                              && has_member_variable_second<T>::value
                              && (std::is_same< std::pair<typename std::remove_cv< first_type>::type, typename std::remove_cv< second_type>::type>, T> ::value
                                  || std::is_same< std::pair<const typename std::remove_cv< first_type>::type, typename std::remove_cv<  second_type>::type>, T> ::value
                                  || std::is_same< std::pair< typename std::remove_cv< first_type>::type, const typename  std::remove_cv<   second_type>::type>, T> ::value
                                  || std::is_same< std::pair<const typename std::remove_cv< first_type>::type, const typename  std::remove_cv<   second_type>::type>, T> ::value);
};

template<typename T> struct is_maybe_sequence_container {
    typedef typename _AMO has_declare_iterator<T>::type iterator;
    typedef typename _AMO has_declare_iterator_category<iterator>::type iterator_category;
    const static int value = std::is_class<T>::value
                             && _AMO has_member_function_begin<T>::value
                             && _AMO has_member_function_end<T>::value
                             && _AMO has_declare_iterator<T >::value;
};
// std::array<T, N>
template<typename T> struct is_array {
    const static int value = _AMO is_maybe_sequence_container<T>::value && _AMO has_member_function_data<T>::value
                             && !_AMO has_member_function_capacity<T>::value;
};
// std::vector
template<typename T> struct is_vector {
    typedef typename _AMO has_declare_value_type<T>::type value_type;
    const static int value = _AMO is_maybe_sequence_container<T>::value && _AMO has_member_function_data<T>::value
                             && _AMO has_member_function_capacity<T>::value && !_AMO has_member_function_c_str<T>::value
                             && _AMO has_member_function_push_back<T, value_type>::value;
};
// std::deque
template<typename T> struct is_deque {
    typedef typename _AMO has_declare_value_type<T>::type value_type;
    const static int value = _AMO is_maybe_sequence_container<T>::value && !_AMO has_member_function_data<T>::value
                             && !_AMO has_member_function_capacity<T>::value && _AMO has_member_function_at<T, size_t>::value
                             && _AMO has_member_function_pop_front<T>::value && _AMO has_member_function_push_back<T, value_type>::value;
};

// std::forword_list
template<typename T> struct is_forward_list {
    typedef typename _AMO has_declare_iterator<T>::type iterator;
    typedef typename _AMO has_declare_value_type<T>::type value_type;
    const static int value = _AMO is_maybe_sequence_container<T>::value
                             && _AMO has_member_function_insert_after<T, iterator, value_type>::value;
};
// std::list
template<typename T> struct is_list {
    typedef typename _AMO has_declare_value_type<T>::type value_type;
    const static int value = _AMO is_maybe_sequence_container<T>::value && !_AMO has_member_function_insert_after<T>::value
                             && !_AMO has_member_function_at<T, size_t>::value && _AMO has_member_function_push_back<T, value_type>::value
                             && _AMO has_member_function_pop_front<T>::value && _AMO has_declare_value_type<T>::value
                             && !_AMO has_member_function_operator_square_brackets<T, size_t>::value;
};

// std::set std::multiset std::unordered_set std::unordered_multiset
template<typename T> struct is_set {
    typedef typename _AMO has_declare_key_type<T>::type key_type;
    const static int value = _AMO is_maybe_sequence_container<T>::value && _AMO has_member_function_find<T, key_type>::value
                             && _AMO has_member_function_count<T, key_type>::value && !_AMO has_member_function_front<T>::value
                             && !_AMO has_declare_mapped_type<T>::value;
};

// std::map std::multimap std::unordered_map std::unordered_multimap
template<typename T> struct is_map {
    typedef typename _AMO has_declare_key_type<T>::type key_type;
    const static int value = _AMO is_maybe_sequence_container<T>::value && _AMO has_member_function_find<T, key_type>::value
                             && _AMO has_member_function_count<T, key_type>::value && !_AMO has_member_function_front<T>::value
                             && _AMO has_declare_mapped_type<T>::value;
};

_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_type_traits


#ifndef segment_is_json_value
#define segment_is_json_value
_AMO_NAMESPACE_BEGIN
template<typename T, typename Enable = void> struct is_json_value {
    static const int32_t value = 0;
};

template<typename T> struct is_json_value < T,
             typename std::enable_if < std::is_same<T, bool>::value
             || std::is_same<T, std::nullptr_t>::value
             || std::is_arithmetic<T>::value
             || std::is_same <typename std::decay<T>::type, std::string>::value
             || std::is_same <typename std::decay<T>::type, char*>::value
             || _AMO has_member_variable___json_type_value__<T>::value >::type > {
    static const int32_t value = 1;
};
_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_is_json_value


#ifndef segment_json_type_traits
#define segment_json_type_traits
#include <type_traits>
#include <cstdint>

_AMO_NAMESPACE_BEGIN
template<typename T> struct is_smart_pointer {
    const static int32_t value = is_shared_ptr<T>::value || is_unique_ptr<T>::value;
};
// 容器赋值类，普通容器使用push_back
template<typename T, typename Enable = void> struct json_container_inserter {
    json_container_inserter(T& val_) : m_val(val_) {}
    template<typename P>
    void push_back(const P& val_) { m_val.push_back(val_); }
    T& m_val;
};
// set 特化 使用insert插入数据
template<typename T> struct json_container_inserter<T, typename std::enable_if<is_set<T>::value, void>::type> {
    json_container_inserter(T& val_) : m_val(val_) {}
    template<typename P>
    void push_back(const P& val_) { m_val.insert(val_); }
    T& m_val;
};

template<typename T> struct is_container {
    const static int32_t value = is_vector<T>::value || is_set<T>::value || is_deque<T>::value
                                 || is_list<T>::value || is_forward_list<T>::value || _AMO is_array<T>::value;
};
_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_json_type_traits


#ifndef segment_json_type_upgrader
#define segment_json_type_upgrader
#include <type_traits>
#include <string.h>
#include <vector>

_AMO_NAMESPACE_BEGIN
// 类型升级，
template<typename T, typename  Enable = void> struct json_type_upgrader {
    typedef T raw_type;															    // 原始数据类型
    typedef typename std::decay<T>::type downgrade_type;						    // 降级后的类型
    typedef typename std::remove_pointer<downgrade_type>::type raw_value_type;	    // 去掉指针后的类型
    typedef downgrade_type  upgrade_type;                                           // 升级后的数据类型
    const static size_t raw_type_size = sizeof(raw_value_type);					    // 类型大小
    
    inline const upgrade_type& upgrade(const upgrade_type& val, size_t size) { return  val; }
    inline void copy_from_container(raw_type& r, const upgrade_type& t) {}
};

// unique_ptr
template<typename T> struct json_type_upgrader < T, typename std::enable_if<amo::is_unique_ptr<T>::value, void>::type> {
    typedef T raw_type;															    // 原始数据类型
    typedef typename std::decay<T>::type downgrade_type;						    // 降级后的类型
    typedef typename std::remove_pointer<downgrade_type>::type raw_value_type;	    // 去掉指针后的类型
    typedef downgrade_type upgrade_type;                                            // 升级后的数据类型
    
    inline const upgrade_type& upgrade(const upgrade_type& val, size_t size) { return val; }
    inline void copy_from_container(raw_type& r, upgrade_type& t) { r.swap(t); }
};

// 指针特化，如果指针为空，那么new一个出来
template<typename T> struct json_type_upgrader< T, typename  std::enable_if <std::is_pointer<T>::value, void >::type > {
    typedef T raw_type;															// 原始数据类型
    typedef typename std::decay<T>::type downgrade_type;						// 降级后的类型
    typedef typename std::remove_pointer<downgrade_type>::type raw_value_type;	// 去掉指针后的类型
    typedef downgrade_type  upgrade_type;                                       // 升级后的数据类型
    const static size_t raw_type_size = sizeof(raw_value_type);					// 类型大小
    
    inline const upgrade_type& upgrade(downgrade_type& val, size_t size) {
        if (val == nullptr) { val = new raw_value_type(); }
        return val;
    }
    // 进来的和出去的相同，不用操作//*r = t;
    inline void copy_from_container(raw_type& r, const upgrade_type& t) {}
};

// 类型升级，将数组升级为vector, 降级为指针
template<typename T> struct json_type_upgrader<T, typename  std::enable_if < std::is_array<T>::value, void >::type > {
    typedef T raw_type;															// 原始数据类型
    typedef typename std::decay<T>::type downgrade_type;						// 降级后的类型
    typedef typename std::remove_pointer<downgrade_type>::type raw_value_type;	// 去掉指针后的类型
    typedef std::vector<raw_value_type>  upgrade_type;                          // 升级后的数据类型
    const static size_t raw_type_size = sizeof(raw_value_type);					// 类型大小
    
    inline const upgrade_type  upgrade(const downgrade_type& val, size_t size) {
        return { (downgrade_type)val, val + size / raw_type_size };
    }
    inline void copy_from_container(raw_type& r, const upgrade_type& t) {
        memcpy((char*)r, (char*)t.data(), t.size() * raw_type_size);
    }
};

_AMO_NAMESPACE_END


///!@segment update timestamp 20200216211257
#endif //segment_json_type_upgrader


#ifndef segment_single_json_object_helper
#define segment_single_json_object_helper
_AMO_NAMESPACE_BEGIN

struct ObjectUnknown {};         // 当前类型未知 vector deque list 等
struct ObjectPod {};             // POD  JSON 可以支持的原生类型,与C语言的POD不一样  如:int double bool nullptr  std::string
struct ObjectClass {};           // class
struct ObjectContainer {};       // container
struct ObjectSmart {};           // share_ptr unique_ptr
struct ObjectPointer {};         // 指针类型  如：int*
struct ObjectMap {};             // map 如： std::map std::unordered_map

struct with_push_back {};                   // 使用push_back 插入数据
struct with_insert {};                      // 使用insert 插入数据
struct with_square_brackets {};    // 使用operrator [] 插入数据
struct with_insert_after {};                // 使用insert_after 插入数据
struct with_empty_func {};                  // 没有操作符


template<typename JsonType, typename T> struct ObjectClassHelper {
    inline void json_to_value(const JsonType& json, T* retval) { T::from_json(json, retval); }
    inline JsonType value_to_json(const T& val) { return val.to_json(); }
};

template<typename T> struct json_object_helper_traits {
    typedef typename std::conditional < amo::is_container<T>::value, ObjectContainer,   // T 是一个容器
            typename std::conditional < amo::is_map<T>::value, ObjectMap,               // T 是一个键值对MAP
            typename std::conditional < amo::is_smart_pointer<T>::value, ObjectSmart,   // T 是一个智能指针
            typename std::conditional < std::is_pointer<T>::value, ObjectPointer,       // T 是一个指针
            typename std::conditional < amo::is_json_value<T>::value, ObjectPod,        // T 是一个POD类型
            ObjectClass                                                                 // T Class
            >::type>::type>::type>::type>::type value_type;
};

// 未知类型和JSON互转, 先计算出T的具体的类型，再调用对应的特化版本来取值或赋值
template<typename JsonType, typename T, typename P> class single_json_object_helper {
public:
    typedef typename json_object_helper_traits<T>::value_type value_type;  // 计算T的具体类型
public:
    static inline void get_value_from_json(T& retval, const JsonType& json, const T& default_) {
        return single_json_object_helper<JsonType, T, value_type>::get_value_from_json(retval, json, default_);
    }
    
    static inline void set_json_from_value(JsonType& json, const T& val) {
        return single_json_object_helper<JsonType, T, value_type>::set_json_from_value(json, val);
    }
};

// 将一个POD类型与JSON类型之间进行转换
template<typename JsonType, typename T> class single_json_object_helper<JsonType, T, ObjectPod> {
public:
    static inline void get_value_from_json(T& retval, const JsonType& json, const T& default_) {
        retval = json.template get<T>(); // POD类型可以直接取值
    }
    static inline void set_json_from_value(JsonType& json, const T& val) { json = val;/* POD类型可以直接赋值 */}
};

// 将一个Class 与JSON类型进行转换
template<typename JsonType_, typename T_> class single_json_object_helper<JsonType_, T_, ObjectClass> {
public:
    static inline void get_value_from_json(T_& retval, const JsonType_& json, const T_& default_) {
        make_object_from_json<JsonType_, T_>(json, &retval);
    }
    
    static inline void set_json_from_value(JsonType_& json, const T_& val) {
        json = make_json_from_object<JsonType_, T_>(val);
    }
    
    // 将JSON转换为一个对象
    template<typename JsonType, typename T> static inline typename
    std::enable_if < !std::is_same<typename std::decay<JsonType>::type, typename std::decay<T>::type>::value,
    void >::type make_object_from_json(const JsonType& json, T* retval) {
        T::from_json(json, retval);
    }
    
    // 特化，将JSON转换为JSON
    template<typename JsonType, typename T> static inline typename
    std::enable_if< std::is_same<typename std::decay<JsonType>::type, typename std::decay<T>::type>::value, void>::type
    make_object_from_json(
        const JsonType& json, T* retval) {
        *retval = json;
    }
    
    template<typename JsonType, typename T> static inline typename std::enable_if <
    !std::is_same<typename std::decay<JsonType>::type, typename std::decay<T>::type>::value,
    JsonType >::type make_json_from_object(const T& val) {
        return val.to_json();
    }
    
    template<typename JsonType, typename T> static inline typename
    std::enable_if< std::is_same<typename std::decay<JsonType>::type, typename std::decay<T>::type>::value, JsonType>::type
    make_json_from_object(
        const T& val) {
        return val;
    }
};

// 将一个指针与JSON相互转换
template<typename JsonType, typename T> class single_json_object_helper<JsonType, T, ObjectPointer> {
public:
    typedef typename std::remove_pointer<T>::type P1;  // 拿到真实类型
    typedef typename json_object_helper_traits<P1>::value_type value_type;
    static inline void get_value_from_json(T& retval, const JsonType& json, const T& default_) {
        if (json.is_empty()) { return; } // 如果json不存在，那么指针也应该为空指针?
        if (retval == nullptr) { retval = new P1(); }  // 指针应该不为空
        single_json_object_helper<JsonType, P1, value_type>::get_value_from_json(*retval, json, default_ ? *default_ : P1());
    }
    
    static inline void set_json_from_value(JsonType& json, const T& val) {
        if (!val) { return; }
        return single_json_object_helper<JsonType, P1, value_type>::set_json_from_value(json, val ? *val : P1());
    }
};

// 智能指针与JSON互转
template<typename JsonType, typename T> class single_json_object_helper<JsonType, T, ObjectSmart> {
public:
    typedef typename T::element_type P1;    // 拿到真实类型
    typedef typename json_object_helper_traits<P1>::value_type value_type;
    static inline void get_value_from_json(T& retval, const JsonType& json, const T& default_) {
        if (json.is_empty()) { return; } // 如果json不存在，不再new
        if (!retval) { retval.reset(new P1()); }
        single_json_object_helper<JsonType, P1, value_type>::get_value_from_json(*retval, json, default_ ? *default_ : P1());
    }
    
    static inline void set_json_from_value(JsonType& json, const T& val) {
        if (!val) { return; }
        return single_json_object_helper<JsonType, P1, value_type>::set_json_from_value(json, val ? *val : P1());
    }
};

// 数组容器与JSON互转
template<typename JsonType, typename T> class single_json_object_helper <JsonType, T, ObjectContainer> {
public:
    typedef typename T::value_type P1;
    typedef typename json_object_helper_traits<P1>::value_type value_type;
    typedef typename std::conditional <_AMO has_member_function_push_back<T, P1>::value, with_push_back,
            typename std::conditional<_AMO has_member_function_insert<T, P1>::value, with_insert,
            typename std::conditional<_AMO has_member_function_insert_after<T, typename _AMO has_declare_const_iterator<T>::type, P1>::value, with_insert_after,
            typename std::conditional<_AMO has_member_function_operator_square_brackets<T, size_t>::value, with_square_brackets, with_empty_func
            >::type >::type >::type>::type insert_type;
    static inline void get_value_from_json(T& retval, const JsonType& json, const T& default_) {
        if (!json.is_array()) { retval = default_; return; }
        size_t index = 0;
        
        for (auto& p : json) {
            P1 tmp;
            single_json_object_helper<JsonType, P1, value_type>::get_value_from_json(tmp, p, tmp);
            set_value_from_json_by_member_func(retval, tmp, index++, insert_type());
        }
    }
    
    static inline void set_value_from_json_by_member_func(T& retval, const P1& val, size_t index, with_push_back) {
        retval.push_back(val);
    }
    static inline void set_value_from_json_by_member_func(T& retval, const P1& val, size_t index, with_insert) {
        retval.insert(val);
    }
    static inline void set_value_from_json_by_member_func(T& retval, const P1& val, size_t index, with_insert_after) {
        retval.push_front(val);  // insert after 只有 forward_list 里面有，直接使用push_front 来插入数据
    }
    static inline void set_value_from_json_by_member_func(T& retval, const P1& val, size_t index, with_square_brackets) {
        if (index >= retval.size()) {// 必须要求一下size函数
            $cwarn("index out of range: capcity[%u], index[%u]", retval.size(), index);
            return;
        }
        retval[index] = val;
    }
    // 未知类型，不知道用什么方式来插入数据
    static inline void set_value_from_json_by_member_func(T& retval, const P1& val, size_t index, with_empty_func) {
        $cerr("%s is not support.", typeid(T).name());
    }
    
    static inline void set_json_from_value(JsonType& json, const T& val) {
        if (json.is_empty()) { json.set_array(); }  // 允许将空的JSON设置为JsonArray
        if (!json.is_array()) { return; }           // 检测类型是否为数组
        
        for (auto& p : val) {
            JsonType tmp = json[-1];
            single_json_object_helper<JsonType, P1, value_type>::set_json_from_value(tmp, p);
        }
    }
};

// MAP容器与JSON互转
template<typename JsonType, typename T> class single_json_object_helper <JsonType, T, ObjectMap> {
public:
    typedef typename T::key_type key_type;
    typedef typename T::mapped_type P1;
    typedef typename json_object_helper_traits<P1>::value_type value_type;
    typedef typename json_object_helper_traits<key_type>::value_type first_type;
    
    typedef typename std::conditional < _AMO has_member_function_push_back<T, P1>::value, with_push_back,
            typename std::conditional<_AMO has_member_function_insert<T, P1>::value, with_insert,
            typename std::conditional< _AMO has_member_function_insert_after<T, typename _AMO has_declare_const_iterator<T>::type, P1>::value, with_insert_after,
            typename std::conditional<_AMO has_member_function_operator_square_brackets<T, size_t>::value, with_square_brackets, with_empty_func
            >::type >::type >::type>::type insert_type;
    //
    template<typename P> static inline typename
    std::enable_if<std::is_same<std::string, typename std::decay<typename P::key_type>::type >::value, void>::type
    set_json_from_value_impl(
        JsonType& json, const P& val) {
        if (json.is_empty()) { json.set_object(); } // 允许将空的JSON设置为JsonObject
        for (auto& p : val) {
            JsonType tmp = json[p.first];
            single_json_object_helper<JsonType, P1, value_type>::set_json_from_value(tmp, p.second);
        }
    }
    
    //
    template<typename P>  static inline typename
    std::enable_if < !std::is_same<std::string, typename std::decay<typename P::key_type>::type >::value,
    void >::type set_json_from_value_impl(JsonType& json, const P& val) {
        if (json.is_empty()) { json.set_array(); }  // 允许将空的JSON设置为JsonArray
        for (auto& p : val) {
            JsonType arr = json[-1];
            arr.set_array();
            JsonType a1 = arr[-1];
            JsonType a2 = arr[-1];
            single_json_object_helper<JsonType, key_type, first_type>::set_json_from_value(a1, p.first);
            single_json_object_helper<JsonType, P1, value_type>::set_json_from_value(a2, p.second);
        }
    }
    
    static inline void get_value_from_json(T& retval, const JsonType& json, const T& default_) {
        // 如果是array，那么支持以下情况
        if (json.is_array()) {
            if (json.size() == 2 && json[0].template is<key_type>()) { // 这种形式 ["a":1]
                typename T::mapped_type val{};
                _AMO single_json_object_helper<JsonType, P1, value_type>::get_value_from_json(val, json[1], val);
                retval.insert({json[0].template get<key_type>(), val });
            } else { // 这种形式[{"a":1},{"b":2}]
                json.template transfer<size_t>([&](const size_t& key, JsonType & p)->void {
                    /* typename T::mapped_type val{};
                     _AMO single_json_object_helper<JsonType, P1, value_type>::get_value_from_json(val, p, val);
                     retval.insert({ key, val });*/
                    // p一定要是一个pair<key_type, P1>;
                    get_value_from_json(retval, p, default_); // 递归
                    
                    /*if (p.is_array() && p.size() == 2 && p[0].is<key_type>()) {
                        typename T::mapped_type val{};
                        _AMO single_json_object_helper<JsonType, P1, value_type>::get_value_from_json(val, p, val);
                        retval.insert({ p[0].get<key_type>(), val });
                    }*/
                    
                });
                
                
                
            }
            return;
        }
        
        if (!json.is_object()) {
            retval = default_;
            return;
        }
        
        json.template transfer<key_type>([&](const key_type & key, JsonType & p)->void {
            typename T::mapped_type val{};
            _AMO single_json_object_helper<JsonType, P1, value_type>::get_value_from_json(val, p, val);
            retval.insert({ key, val });
        });
    }
    
    static inline void set_json_from_value(JsonType& json, const T& val) {
        set_json_from_value_impl<T>(json, val);
    }
    
    
};
// 返回值管理
template<typename TypeTraits, typename JsonType> struct single_object_get_set_helper {
    typedef typename TypeTraits::upgrade_type upgrade_type;
    typedef typename TypeTraits::raw_type raw_type;
    typedef typename TypeTraits::downgrade_type downgrade_type;
    typedef typename TypeTraits::raw_value_type raw_value_type;
    struct array_type_traits {};   // 数组类数据 char a[12], int a[10]; std::is_array<T>::value == 1
    struct other_type_traits {};   // 其他类型数据
    // 从JSON取一个值
    inline void get(const JsonType& json, raw_type& ptr) {
        typedef typename std::conditional<std::is_array<raw_type>::value, array_type_traits, other_type_traits>::type type;
        return __get_impl(json, ptr, type());
    }
    // 将值赋值给JSON
    inline void set(JsonType& json, const raw_type* ptr) {
        typedef typename std::conditional<std::is_array<raw_type>::value, array_type_traits, other_type_traits>::type type;
        return __set_impl(json, ptr, type());
    }
private:
    inline void __get_impl(const JsonType& json, raw_type& ptr, array_type_traits) {
        auto p = TypeTraits().upgrade(ptr, sizeof(ptr));
        auto default_value = p;
        p.clear();
        amo::single_json_object_helper<JsonType, upgrade_type, amo::ObjectUnknown>::get_value_from_json(p, json, default_value);
        TypeTraits().copy_from_container(ptr, p);
    }
    
    inline void __get_impl(const JsonType& json, raw_type& ptr, other_type_traits) {
        raw_type& p = (raw_type&)TypeTraits().upgrade(ptr, sizeof(ptr));
        amo::single_json_object_helper<JsonType, upgrade_type, amo::ObjectUnknown>::get_value_from_json(p, json, p);
        TypeTraits().copy_from_container(ptr, p);
    }
    
    inline void __set_impl(JsonType& json, const raw_type* ptr, array_type_traits) {
        amo::single_json_object_helper<JsonType, upgrade_type, amo::ObjectUnknown>::set_json_from_value(json,
                TypeTraits().upgrade((downgrade_type)*ptr, sizeof(*ptr)));
    }
    
    inline void __set_impl(JsonType& json, const raw_type* ptr, other_type_traits) {
        amo::single_json_object_helper<JsonType, upgrade_type, amo::ObjectUnknown>::set_json_from_value(json, *ptr);
    }
};
_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_single_json_object_helper


#ifndef segment_json_value_proxy
#define segment_json_value_proxy
_AMO_NAMESPACE_BEGIN

template<typename DataType, typename T> inline typename std::enable_if<0, T&>::type
json_number_helper(const DataType& d) {
    return (T&)d.d;
}
template<typename DataType, typename T> inline typename std::enable_if < std::is_integral<T>::value&&
std::is_signed<T>::value&& !std::is_same<T, bool>::value,
decltype(DataType().i)& >::type json_number_helper(const DataType& d) {
    return ((DataType&)d).i;
}
template<typename DataType, typename T> inline typename std::enable_if < std::is_integral<T>::value&&
std::is_unsigned<T>::value&& !std::is_same<T, bool>::value,
decltype(DataType().u)& >::type json_number_helper(const DataType& d) {
    return ((DataType&)d).u;
}
template<typename DataType, typename T> inline typename
std::enable_if<std::is_floating_point<typename std::remove_cv<T>::type>::value, decltype(DataType().d)&>::type
json_number_helper(
    const DataType& d) {
    return ((DataType&)d).d;
}
template<typename DataType, typename T>
inline typename
std::enable_if<std::is_same<typename std::remove_cv<T>::type, bool>::value, bool&>::type json_number_helper(
    const DataType& d) {
    return ((DataType&)d).b;
}

// POD类型操作
template<typename ObjectType, typename type, int f> struct json_value_proxy_for_pod {
    static const int32_t value = f;		   // 数据类型
    typedef typename ObjectType::DataType DataType;
    typedef typename ObjectType::JsonAllocType JsonAllocType;
    
    inline type get_value(const DataType& d, const JsonAllocType& allocator)  const {
        switch (d.ss.flag) {
            case json_value_integer:
                return  static_cast<type>(json_number_helper<DataType, int64_t>(d));
            case json_value_unsigned:
                return  static_cast<type>(json_number_helper<DataType, uint64_t>(d));
            case json_value_float:
                return  static_cast<type>(json_number_helper<DataType, double>(d));
            default:
                break;
        }
        return type();
    }
    
    inline void set_value(DataType& d, const type& val, const JsonAllocType& allocator) {
        json_number_helper<DataType, type>(d) = val;
        d.ss.flag = (int8_t)value;
    }
    
    template<typename T> inline void to_string(const DataType& d, T& stream) const {
        switch (d.ss.flag) {
            case json_value_integer:
                stream << json_number_helper<DataType, int64_t>(d);
                break;
            case json_value_unsigned:
                stream << json_number_helper<DataType, uint64_t>(d);
                break;
            case json_value_float:
                stream << json_number_helper<DataType, double>(d);
                break;
            default:
                break;
        }
    }
};


template<typename ObjectType, typename T, typename Enable = void> struct json_value_proxy {
    static const int32_t value = __json_value_unknown__;		  // 数据类型
};

template<typename U> struct type_value_helper { const static int value = U::__json_type_value__; };
template<> struct type_value_helper<int> { const static int value = json_value_string; };

// 特化自定义类型中如果是 trival类型（兼容C语言结构休） 且不存在成员函数 to_string 不存在静态成员函数 from_string,那么可以从这里进行转换
template<typename ObjectType, typename T>
struct json_value_proxy < ObjectType, T,
           typename std::enable_if < std::is_class<T>::value&& std::is_trivial<T>::value
           && !has_member_function_to_string<T>::value
           && !has_static_function_from_string<T>::value&& !is_container<T>::value >::type > {
    static const int32_t value =
        type_value_helper<typename std::conditional <has_member_variable___json_type_value__<T>::value, T, int>::type>::value;	 // 数据类型
    static const int32_t compatible = json_value_string;  // 兼容类型为string
    typedef typename ObjectType::DataType DataType;
    typedef typename ObjectType::JsonAllocType JsonAllocType;
    json_value_proxy() {}
    
    inline T& get_value(const DataType& d, const JsonAllocType& allocator) const { return *(T*)d.s.elements; }
    inline void set_value(DataType& d, const T& val, const JsonAllocType& allocator) {
        d.ss.flag = value;
        return set_token_value(d, (char*)&val, sizeof(T), allocator);
    }
    template<typename P> inline void to_string(const DataType& d, P& stream) const { stream.write(d.s.elements, d.s.length); }
    inline void set_token_value(DataType& d, const char* val, size_t len, const JsonAllocType& allocator) {
        d.s.elements = allocator->allocate(len);
        memcpy(d.s.elements, val, len);
        d.s.length = len;
    }
};

// 特化自定义类型中如果存在, 静态变量 __json_type_value__ 成员函数 to_string 静态成员函数 from_string,那么可以从这里进行转换
// 最简单的类型示例
//class AAAA {
//public:
//    AAAA(){}
//    const static int __type_value = 5555;
//    const std::string to_string() const { return "123"; }
//    AAAA from_string(const std::string& str) { return AAAA(); }
//};
template<typename ObjectType, typename T>
struct json_value_proxy < ObjectType, T,
           typename std::enable_if < has_member_variable___json_type_value__<T>::value
           && has_member_function_to_string<T>::value
           && has_static_function_from_string<T>::value >::type > {
    static const int32_t value = T::__json_type_value__;		  // 数据类型
    typedef typename ObjectType::DataType DataType;
    typedef typename ObjectType::JsonAllocType JsonAllocType;
    
    inline T get_value(const DataType& d, const JsonAllocType& allocator) const {
        return T::from_string(std::string(d.s.elements, d.s.length));
    }
    
    inline void set_value(DataType& d, const T& val, const JsonAllocType& allocator) {
        d.ss.flag = value;
        const std::string&& str = val.to_string();
        return set_token_value(d, str.c_str(), str.size(), allocator);
    }
    
    inline void set_value(DataType& d, const char* val, size_t len, const JsonAllocType& allocator) {
        d.ss.flag = value;
        return set_token_value(d, val, len, allocator);
    }
    
    template<typename P> inline void to_string(const DataType& d, P& stream) const {
        stream.write(d.s.elements, d.s.length);
    }
    
    inline void set_token_value(DataType& d, const char* val, size_t len, const JsonAllocType& allocator) {
        d.s.elements = allocator->allocate(len);
        memcpy(d.s.elements, val, len);
        d.s.length = len;
    }
};

// string 特化
template<typename ObjectType, typename T> struct
    json_value_proxy<ObjectType, T, typename std::enable_if<std::is_same<typename std::decay<T>::type, std::string>::value>::type> {
    static const int32_t value = json_value_string;		  // 数据类型
    typedef typename ObjectType::DataType DataType;
    typedef typename ObjectType::JsonAllocType JsonAllocType;
    json_value_proxy() {}
    inline T get_value(const DataType& d, const JsonAllocType& allocator) const {
        return _AMO from_string<T>(std::string(d.s.elements, d.s.length));
    }
    
    inline void set_value(DataType& d, const T& val, const JsonAllocType& allocator) {
        d.ss.flag = value;
        std::string&& str = _AMO to_string(val);
        return set_token_value(d, str.c_str(), str.size(), allocator);
    }
    
    inline void set_value(DataType& d, const char* val, size_t len, const JsonAllocType& allocator) {
        if (d.ss.flag == json_value_string && d.s.length >= (int32_t)len) {
            memcpy(d.s.elements, val, len);
            d.s.length = (uint32_t)len;
        } else {
            d.ss.flag = value;
            return set_token_value(d, val, len, allocator);
        }
    }
    // 没有调用过，直接写没有转义
    template<typename P> inline void to_string(const DataType& d, P& stream) const {
        stream.write(d.s.elements, d.s.length);
    }
    
    inline void set_token_value(DataType& d, const char* val, size_t len, const JsonAllocType& allocator) {
        d.s.elements = allocator->allocate(len);
        memcpy(d.s.elements, val, len);
        d.s.length = static_cast<uint32_t>(len);
    }
};

// null 特化
template<typename ObjectType, typename T>
struct json_value_proxy<ObjectType, T, typename std::enable_if<std::is_same<T, std::nullptr_t>::value>::type> {
    static const int32_t value = json_value_null;
    typedef typename ObjectType::DataType DataType;
    typedef typename ObjectType::JsonAllocType JsonAllocType;
    
    std::nullptr_t get_value(const DataType& d, const JsonAllocType& allocator) const { return std::nullptr_t(); }
    inline void set_value(DataType& d, const std::nullptr_t& val, const JsonAllocType& allocator) { d.ss.flag = value; }
    template<typename P> inline void to_string(const DataType& d, P& stream) const { stream.write("null", 4); }
};

// bool 特化
template<typename ObjectType, typename T>
struct json_value_proxy<ObjectType, T, typename std::enable_if<std::is_same<T, bool>::value>::type> {
    static const int32_t value = json_value_boolean;
    typedef typename ObjectType::DataType DataType;
    typedef typename ObjectType::JsonAllocType JsonAllocType;
    
    bool get_value(const DataType& d, const JsonAllocType& allocator) const {
        switch (d.ss.flag) {
            case json_value_boolean:
                return d.b;
            case json_value_integer:
                return d.i != 0;
            case json_value_unsigned:
                return d.u != 0;
            case json_value_float:
                return d.d != 0;
            default:
                return false;
        }
    }
    
    inline void set_value(DataType& d, const bool& val, const JsonAllocType& allocator) { d.b = val;  d.ss.flag = value; }
    template<typename P> inline void to_string(const DataType& d, P& stream) const { d.b ? stream.write("true", 4) : stream.write("false", 5); }
};

// int 特化
template<typename ObjectType, typename T>
struct json_value_proxy < ObjectType, T, typename
    std::enable_if < std::is_integral<T>::value&& !std::is_unsigned<T>::value&& !std::is_same<T, bool>::value >::type >
    : public json_value_proxy_for_pod<ObjectType, T, json_value_integer> {
    using json_value_proxy_for_pod<ObjectType, T, json_value_integer>::json_value_proxy_for_pod;
};

// unsigned int 特化
template<typename ObjectType, typename T>
struct json_value_proxy < ObjectType, T, typename
    std::enable_if < std::is_integral<T>::value&& std::is_unsigned<T>::value&& !std::is_same<T, bool>::value >::type >
    : public json_value_proxy_for_pod<ObjectType, T, json_value_unsigned> {
    using json_value_proxy_for_pod<ObjectType, T, json_value_unsigned>::json_value_proxy_for_pod;
};

// float 特化
template<typename ObjectType, typename T>
struct json_value_proxy < ObjectType, T, typename
    std::enable_if < std::is_floating_point<T>::value&& !std::is_same<T, bool>::value >::type >
    : public json_value_proxy_for_pod<ObjectType, T, json_value_float> {
    using json_value_proxy_for_pod<ObjectType, T, json_value_float>::json_value_proxy_for_pod;
};

_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_value_proxy


#ifndef segment_json_data_object
#define segment_json_data_object
_AMO_NAMESPACE_BEGIN
template<typename TypeTraits> struct json_data_object {
public:
    typedef typename TypeTraits::size_type size_type;
    typedef typename TypeTraits::release_resources_type release_resources_type;
    typedef typename TypeTraits::CharReaderType CharReaderType;
    typedef typename TypeTraits::JsonStringParserType JsonStringParserType;
    typedef typename TypeTraits::JsonKeyParserType JsonKeyParserType;
    typedef typename TypeTraits::KeyType KeyType;
    typedef typename TypeTraits::MapType MapType;
    typedef typename TypeTraits::ArrayType ArrayType;
    typedef typename TypeTraits::MemoryAllocType MemoryAllocType;
    typedef typename TypeTraits::JsonAllocType JsonAllocType;
    typedef typename TypeTraits::MapAllocType MapAllocType;
    typedef typename TypeTraits::ArrAllocType ArrAllocType;
    typedef typename TypeTraits::DataType DataType;
    typedef typename TypeTraits::JsonParserType JsonParserType;
    typedef typename TypeTraits::JsonNumberParserType JsonNumberParserType;
public:
    DataType d;
public:
    // 默认构造函数，将内存空间置0
    json_data_object() { std::memset(&d, 0, sizeof(DataType)); }
    
    // 赋值构造函数
    template<typename T>  json_data_object(const T& value_) : json_data_object() {
        set_type(json_value_proxy<json_data_object, T>::value);
        set_value(value_, {});
    }
    json_data_object(const std::string&& value_) : json_data_object() {
        set_type(json_value_proxy<json_data_object, std::string>::value);
        d.s.elements = (char*)value_.c_str();
        d.s.length = value_.size();
    }
    // 只能做临时对象，没有使用内存池分配内存，不能使用json进行管理
    json_data_object(const std::string& value_) : json_data_object() {
        set_type(json_value_proxy<json_data_object, std::string>::value);
        d.s.elements = (char*)value_.c_str();
        d.s.length = value_.size();
    }
    // 只能做临时对象，没有使用内存池分配内存，不能使用json进行管理
    json_data_object(const char* value_) : json_data_object() {
        set_type(json_value_proxy<json_data_object, std::string>::value);
        d.s.elements = (char*)value_;
        d.s.length = strlen(value_);
    }
    // 移动
    json_data_object(const DataType&& d_, const JsonAllocType& allocator) : json_data_object() { d = d_; }
    // 复制
    json_data_object(const DataType& d_, const JsonAllocType& allocator) : json_data_object() { __copy_data(d_, allocator); }
    // 将对象设置为JsonObject
    inline void set_object(const JsonAllocType& allocator) {
        this->release(allocator.get());
        set_type(json_value_object);
        void* ptr = allocator->allocate(sizeof(MapType));
        d.o.elements = new (ptr)  MapType(typename MapType::key_compare(), allocator);
    }
    
    // 将对象设置为JsonArray,
    inline void set_array(const JsonAllocType& allocator) {
        this->release(allocator.get());
        set_type(json_value_array);
        void* ptr = allocator->allocate(sizeof(ArrayType));
        d.a.elements = new (ptr)ArrayType(allocator);
    }
    inline void set_array(size_t capcity, const JsonAllocType& allocator) {
        this->release(allocator.get());
        set_type(json_value_array);
        void* ptr = allocator->allocate(sizeof(ArrayType));
        d.a.elements = new (ptr)ArrayType(capcity, {}, allocator);
    }
    // 设置对象类型 参考value_t
    inline void set_type(uint32_t type_) { d.ss.flag = type_; }
    // 获取对象类型 参考value_t
    inline uint32_t get_type() const { return d.ss.flag; }
    
    // 释放资源，Object对象默认不在析构函数中释放资源，以方便Object中的内容在不同JSON对象中现象浅层拷贝
    // 资源释放需要手动进行
    void release(const MemoryAllocType* allocator) {
        d.ss.flag = 0;
        return;  // 暂不释放资源，提升程序速度
        /////////////////////////////////////////////////////////////////////////////////////////
        auto type = get_type();
        
        switch (type) {
            case json_value_array: {
                for (auto& p : * (d.a.elements)) {
                    p.release(allocator);
                }
                d.a.elements->~ArrayType();
                break;
            }
            
            case json_value_object: {
                for (auto& p : * (d.o.elements)) {
                    TypeTraits().release_key_string((KeyType&)p.first, allocator);
                    p.second.release(allocator);
                }
                d.o.elements->~MapType();
                break;
            }
            
            case json_value_string:
                break;
                
            default:
                break;
        }
        
        // 将对象标记为空
        d.ss.flag = 0;
    }
    
    // 字符串对齐
    /*  inline const std::string align_string(int32_t indent) const {
          int32_t high = ((indent & 0xffff0000) >> 16);
          return std::string(high, ' ');
      }*/
    // 字符串对齐
    inline const int32_t align_string(int32_t indent) const {
        return ((indent & 0xffff0000) >> 16);
    }
    // 字符串缩进
    inline int32_t add_indent(int32_t indent) const {
        int32_t low = (indent & 0xffff);
        int32_t high = ((indent & 0xffff0000) >> 16) + low;
        return (high << 16) + low;
    }
    // 转换为string
    const std::string to_string(int32_t indent = 0) const {
        _AMO memory_writer < -1 > writer;
        this->to_string(writer, indent);
        return writer.to_string();
    }
    // 转换为string
    template<typename T> void to_string(T& stream, int32_t indent = 0) const {
        const static std::vector<char> blanks(1024, ' ');
        const char* algin_string = blanks.data();
        auto type = get_type();
        switch (type) {
            case json_value_null:
                stream.write("null", 4);
                break;
                
            case json_value_boolean:
                d.b ? stream.write("true", 4) : stream.write("false", 5);
                break;
                
            case json_value_integer:
            case json_value_unsigned:
                stream.adjust_buffer_size(21);
                stream.size(stream.size() + _AMO integer_to_chars<char*>(d.u, (char*)stream.current()));
                break;
                
            case json_value_float:
                stream.adjust_buffer_size(308);
                stream.size(stream.size() + ::dtoa_milo(d.d, (char*)stream.current(), 308));
                break;
                
            case json_value_string:
                stream.write("\"", 1);
                JsonStringParserType().escape(*this, stream, indent);
                stream.write("\"", 1);
                break;
                
            case json_value_object: {
                int32_t algin_str1 = align_string(indent);
                stream .write("{", 1);
                if (indent > 0) { stream .write("\n", 1); }
                indent = this->add_indent(indent);
                int32_t algin_str = this->align_string(indent);
                
                const static char* tail_str = ",\n";
                size_t len = 0;
                
                if (d.o.elements != nullptr) {
                    for (auto& p : * (d.o.elements)) {
                        if (p.second.get_type() == json_value_empty) { continue; }
                        stream.write(tail_str, len);
                        stream.write(algin_string, algin_str).write("\"", 1);
                        stream.write(p.first.c_str(), p.first.size());
                        stream.write("\":", 2);
                        p.second.to_string(stream, indent);
                        len = (indent > 0) ? 2 : 1;
                    }
                    
                    if (indent > 0) { stream .write("\n", 1); }
                }
                
                stream .write(algin_string, algin_str1).write("}", 1);
            }
            break;
            
            case json_value_array: {
                stream .write("[", 1);
                const static char* tail_str = ",";
                size_t len = 0;
                
                if (d.a.elements != nullptr) {
                    for (size_t i = 0; i < d.a.elements->size(); ++i) {
                        if (d.a.elements->at(i).get_type() == json_value_empty) { continue; }
                        stream.write(tail_str, len);  // 写入,
                        d.a.elements->at(i).to_string(stream, indent);
                        len = 1;
                    }
                }
                
                stream.write("]", 1);
            }
            break;
            
            case json_value_empty:
                break;
                
            default: {                              // 自定义类型
                stream.write("\"", 1);
                stream.write("\b\t", 2);            // 写入自定义标志
                char type_flag[2];
                type_flag[0] = (char)(d.ss.flag & 0xff);
                type_flag[1] = (char)((d.ss.flag >> 8) & 0xff);
                char length_flag[4];
                length_flag[0] = (char)(d.s.length & 0xff);
                length_flag[1] = (char)((d.s.length >> 8) & 0xff);
                length_flag[2] = (char)((d.s.length >> 16) & 0xff);
                length_flag[3] = (char)((d.s.length >> 24) & 0xff);
                stream.write(type_flag, 2);         // 写入类型标志
                stream.write(length_flag, 4);         // 写入长度标志
                stream.write(d.s.elements, d.s.length); // 写入数据
                stream.write("\"", 1);
            }
            break;
        }
    }
    
    // 克隆当前对象到一个新的对象，深层复制对象，调用深层复制构造函数
    inline json_data_object clone(const JsonAllocType& allocator) const { return json_data_object(d, allocator); }
    // 深层复制到当前对象
    inline json_data_object& copy(const json_data_object& rhs, const JsonAllocType& allocator) {
        __copy_data(rhs.d, allocator);
        return *this;
    }
    
    // 通过key查找对象，如果key对应的value不存在，那么返回一个空对象
    // 该方法默认当前对象为JsonObject，即d.o是存在的，该方法由JSON解析器调用
    inline json_data_object& find_or_insert_object_with_move(const KeyType& key) {
        return TypeTraits().find_or_insert_object_with_move(d.o.elements, key);
    }
    
    // 从JsonArray中获取一个空Object
    // 该方法默认当前对象为JsonArray，即d.a是存在的
    inline json_data_object& push_back_object() { return TypeTraits().push_back_object(d.a.elements); }
    
    // 判断是否存在key
    inline bool contains_key(const KeyType& key) const {
        return d.o.elements->find(key) != d.o.elements->end();
    }
    // 在JsonObject查找值
    inline json_data_object& find(const KeyType& key, const JsonAllocType& allocator) const {
        return TypeTraits().find_or_insert_object_with_copy(d.o.elements, key);
    }
    // 在JsonArray查找值
    inline json_data_object& find(const int32_t& key, const JsonAllocType& allocator)  const {
        if (key == -1) { return TypeTraits().push_back_object(d.a.elements); }
        return d.a.elements->at(key);
    }
    
    // 从JsonObject中移除值
    inline void erase(const KeyType& key, const JsonAllocType& allocator) { TypeTraits().erase(d.o.elements, key, allocator); }
    // 从JsonArray中移除值
    void erase(const uint32_t start_pos, const uint32_t offset, const JsonAllocType& allocator) {
        if (start_pos + offset > d.a.elements->size()) {
            $cerr("erase size out of range");
            return;
        }
        
        size_t end_pos = start_pos + offset;
        for (size_t i = start_pos; i < end_pos; ++i) {
            d.a.elements->at(i).release(allocator.get());
        }
        d.a.elements->erase(d.a.elements->begin() + start_pos, d.a.elements->begin() + end_pos);
    }
    
    // 遍历一个JsonObject
    void transfer(std::function<void(const KeyType&, const json_data_object&) > fn) {
        if (get_type() == json_value_object) {
            for (auto& p : * (d.o.elements)) {
                fn(p.first, p.second);
            }
        } else {
            throw std::runtime_error("invalid json type, need json object");
        }
    }
    
    // 遍历一个JsonArray
    void transfer(std::function<void(const size_t&, const json_data_object&) > fn) {
        if (get_type() == json_value_array) {
            for (size_t i = 0; i < d.a.elements->size(); ++i) {
                fn(i, d.a.elements->at(i));
            }
        } else {
            throw std::runtime_error("invalid json type, need json array");
        }
    }
    // 获取JsonObject或JsonArray的长度，该函数会因为存在json_value_empty这种类型导致结果不准
    inline size_t size() const {
        auto type = get_type();
        if (type == json_value_object) {
            return (d.o.elements)->size();
        } else if (type == json_value_array) {
            return (d.a.elements)->size();
        } else {
            return 0;
        }
    }
    
    // 将当前对象设置为指定值
    template <typename T> inline void set_value(const T& val, const JsonAllocType& allocator) {
        release(allocator.get());
        return json_value_proxy<json_data_object, T>().set_value(d, val, allocator);
    }
    
    // 特化
    inline void set_value(const json_data_object& val, const JsonAllocType& allocator) {
        release(allocator.get());
        this->copy(val, allocator);
    }
    // 特化
    inline void set_value(const char* val, const JsonAllocType& allocator) {
        release(allocator.get());
        set_value(val, strlen(val), allocator);
    }
    // 特化
    inline void set_value(const std::string& val, const JsonAllocType& allocator) {
        release(allocator.get());
        set_value(val.c_str(), val.size(), allocator);
    }
    // 特化
    inline void set_value(const char* val, size_t len, const JsonAllocType& allocator) {
        release(allocator.get());
        json_value_proxy<json_data_object, std::string>().set_value(d, val, len, allocator);
    }
    // 获取当前对象的具体值
    template<typename T> inline T get_value(const JsonAllocType& allocator) const {
        return json_value_proxy<json_data_object, T>().get_value(d, allocator);
    }
    
private:
    inline void __copy_data(const DataType& d_, const JsonAllocType& allocator) {
        d.ss.flag = d_.ss.flag;
        
        switch (d.ss.flag) {
            case json_value_empty:			            // 空类型,可以转换为任意类型
            case json_value_null:				        // null
            case json_value_boolean:			        // 布尔
            case json_value_integer:			        // 数值
            case json_value_unsigned:                   // 数值
            case json_value_float:			            // 数值
                std::memcpy(&d, &d_, sizeof(DataType));
                break;
                
            case json_value_array: {
                set_array(allocator);
                for (const auto& p : * (d_.a.elements)) {
                    push_back_object() = (p.clone(allocator));
                }
                return;
            }
            
            case json_value_object: {
                set_object(allocator);
                for (const auto& p : * (d_.o.elements)) {
                    TypeTraits().find_or_insert_object_with_copy(d.o.elements, p.first) = p.second.clone(allocator);
                }
                return;
            }
            
            case json_value_string: {
                json_value_proxy<json_data_object, std::string>().set_value(d, d_.s.elements, d_.s.length, allocator);
                return;
            }
            
            case json_value_invalid: {
                json_value_proxy<json_data_object, std::string>().set_token_value(d, d_.s.elements, d_.s.length, allocator);
                return;
            }
            
            default:
                // 自定义数据类型
                std::memcpy(&d, &d_, sizeof(DataType));
                json_value_proxy<json_data_object, std::string>().set_value(d, d_.s.elements, d_.s.length, allocator);
                return;
        }
    }
};

_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_data_object


#ifndef segment_json_parser
#define segment_json_parser

_AMO_NAMESPACE_BEGIN

// JsonPaser 基类，用来将json字符串按不同类型分割成单独的token,只保存字符串的指针
template<typename ObjectType> class json_parser {
public:
    typedef ObjectType object_type;
    typedef typename object_type::JsonAllocType JsonAllocType;
    typedef typename object_type::CharReaderType CharReaderType;
    typedef typename object_type::JsonStringParserType JsonStringParserType;
    typedef typename object_type::JsonKeyParserType JsonKeyParserType;
    typedef typename object_type::JsonNumberParserType JsonNumberParserType;
    CharReaderType reader;
    JsonAllocType m_allocator;
    const static int32_t AllExpect = _AMO token_t::token_json_null
                                     | _AMO token_t::token_json_number
                                     | _AMO token_t::token_json_negative_number
                                     | _AMO token_t::token_json_true
                                     | _AMO token_t::token_json_false
                                     | _AMO token_t::token_json_string
                                     | _AMO token_t::token_begin_object
                                     | _AMO token_t::token_begin_array;
                                     
public:
    json_parser() {}
    json_parser(JsonAllocType& allocator_, const std::istream* rhs_)
        : m_allocator(allocator_), reader(allocator_, (std::istream*)rhs_) {}
    json_parser(JsonAllocType& allocator_, const char* str, size_t len)
        : m_allocator(allocator_), reader(allocator_, str, len) {}
    // 解析Json字符串，这个函数是解析函数的入口
    void parse(ObjectType& object, int32_t expect = AllExpect | token_end_document) {
        __parse(object, expect);
        if (__skip_left_blank_char() != '\0') { __throw_error_message(); }
    }
private:
    // 解析键值对中的key
    template<typename KeyType>
    inline typename std::enable_if < !std::is_same<std::string, KeyType>::value, void >::type __parse_key(KeyType& key) {
        reader.start_refstring();
        JsonKeyParserType().unescape(reader, (ObjectType&)key);
    }
    // 解析键值对中的key
    inline void __parse_key(std::string& key) {
        object_type object;
        reader.start_refstring();
        JsonKeyParserType().unescape(reader, object);
        key = { object.d.s.elements, (size_t)object.d.s.length };
    }
    // 解析null
    inline void __parse_null(object_type& object) {
        if (reader.good(3) && reader.next() == 'u' && reader.next() == 'l' && reader.next() == 'l') {
            object.set_value(nullptr, m_allocator);
            return;
        }
        __throw_error_message();
        
    }
    // 解析true
    inline void __parse_true(object_type& object) {
        if (reader.good(3) && reader.next() == 'r' && reader.next() == 'u' && reader.next() == 'e') {
            object.set_value(true, m_allocator);
            return;
        }
        __throw_error_message();
    }
    // 解析false
    inline void __parse_false(object_type& object) {
        if (reader.good(4) && reader.next() == 'a' && reader.next() == 'l' && reader.next() == 's' && reader.next() == 'e') {
            object.set_value(false, m_allocator);
            return;
        }
        __throw_error_message();
    }
    // 解析数字
    inline void __parse_number(object_type& object) { return JsonNumberParserType().parse_number(reader, object); }
    // 解析字符串
    inline void __parse_string(object_type& object) {
        reader.start_refstring();
        object.d.ss.flag = json_value_string;
        
        // 看看是不是自定义类型
        if (reader.peek() == '\b' && reader.peek(1) == '\t' /*&& reader.peek(2) == '\t' && reader.peek(3) == '\t'*/) {
            reader.forward(2);
            return this->__parse_custom_object(object);
        }
        
        // 解析为正常字符串
        JsonStringParserType().unescape(reader, object);
        
    }
    
    // 解析自定义类型
    inline void __parse_custom_object(object_type& object) {
        // buffer最多可以缓存8个字节，所以这里还可以直接访问6个字节，不用担心越界
        // type为自定义类型ID
        uint32_t type = reader.peek() + (reader.peek(1) << 8) /*+ (reader.peek(2) << 16) + (reader.peek(3) << 24)*/;
        uint32_t length = reader.peek(2) + (reader.peek(3) << 8) + (reader.peek(4) << 16) + (reader.peek(5) << 24);
        reader.forward(2 + 4); //前移2+4个字符
        for (uint32_t i = 0; i < length; ++i) {
            if (reader.good()) {
                reader.forward();
            } else {
                __throw_error_message();// 长度不匹配，错误的JSON数据
            }
        }
        if (reader.peek() == '\"') {
            reader.stop_refstring(object.d.s.elements, object.d.s.length);
            // 将类型标记为自定义类型
            object.d.ss.flag = type;
            object.d.s.elements += 8;  // 开始位置+2+2+4 =8
            object.d.s.length -= 8;
            // 读出来的长度要与要求的长度一致
            if (object.d.s.length != length) {
                __throw_error_message();
            }
            reader.forward();
            return;
        } else {
            __throw_error_message();// 必须是\"，否则为错误的JSON数据
        }
        //for (int i = 0; reader.good(); reader.forward()) {
        //    if (reader.peek() == '\"') {
        //        reader.stop_refstring(object.d.s.elements, object.d.s.length);
        //        // 将类型标记为自定义类型
        //        object.d.ss.flag = type;
        //        object.d.s.elements += 8;  // 开始位置+8
        //        object.d.s.length -= 8;
        //
        //        reader.forward();
        //        return;
        //    }
        //}
    }
    
    // 解析JsonValue
    void __parse_json_value(ObjectType& object, token_t token_type_ch, char ch) {
        switch (token_type_ch) {
            case token_begin_object:
                return this->__parse_json_object(object);
                
            case token_begin_array:
                return this->__parse_json_array(object);
                
            case token_json_negative_number:
            case token_json_number:
                return this->__parse_number(object);
                
            case token_json_string:
                return __parse_string(object);
                
            case token_json_null:
                return __parse_null(object);
                
            case token_json_true:
                return __parse_true(object);
                
            case  token_json_false:
                return __parse_false(object);
                
            case token_sep_colon:
                return;
                
            case token_end_document:
                return;
                
            default:
                __throw_error_message();
                break;
        }
    }
    //解析JsonObject
    void __parse_json_object(ObjectType& jsonObject) {
        jsonObject.set_object(m_allocator);
        int32_t expectToken = token_json_string | token_end_object;
        typename ObjectType::KeyType key;
        
        while (reader.good()) {
            char ch = __skip_left_blank_char();
            auto token_type_ch = (token_t)(((int32_t)__char_to_token_type(ch)) & expectToken);
            
            switch (token_type_ch) {
                case  _AMO token_t::token_json_string: {
                    __parse_key(key);
                    auto& object = jsonObject.find_or_insert_object_with_move(key);
                    // 期望双引号后面是冒号
                    __parse(object, token_sep_colon);
                    // 冒号后面是具体的值
                    __parse(object, token_json_null | token_json_number | token_json_negative_number | token_json_true
                            | token_json_false | token_json_string | token_begin_object | token_begin_array);
                    // 值后面只能是,或者}
                    expectToken = token_sep_comma | token_end_object;
                    break;
                }
                
                case _AMO token_t::token_sep_comma:
                    // 逗号后面必须是 Key "
                    expectToken = token_json_string;
                    break;
                    
                case _AMO token_t::token_end_object:
                    return;
                    
                case  _AMO token_t::token_end_document:
                    return;
                    
                default:
                    __throw_error_message();
            }
        }
    }
    // 解析JsonArray
    void __parse_json_array(ObjectType& jsonArray) {
        int32_t expectToken = token_begin_array | token_end_array | token_begin_object | token_json_null | token_json_number |
                              token_json_negative_number | token_json_true | token_json_false | token_json_string;
        jsonArray.set_array(m_allocator);
        
        while (reader.good()) {
            char ch = __skip_left_blank_char();
            auto token_type_ch = (token_t)(((int32_t)__char_to_token_type(ch)) & expectToken);
            expectToken = token_sep_comma | token_end_array;
            
            switch (token_type_ch) {
                case _AMO token_t::token_begin_object: {
                    auto& object = jsonArray.push_back_object();
                    __parse_json_object(object);
                    break;
                }
                
                case _AMO token_t::token_begin_array: {
                    auto& object = jsonArray.push_back_object();
                    __parse_json_array(object);
                    break;
                }
                
                case _AMO token_t::token_json_null: {
                    auto& object = jsonArray.push_back_object();
                    __parse_null(object);
                    break;
                }
                case _AMO token_t::token_json_negative_number:
                case _AMO token_t::token_json_number: {
                    auto& object = jsonArray.push_back_object();
                    __parse_number(object);
                    break;
                }
                
                case _AMO token_t::token_json_true: {
                    auto& object = jsonArray.push_back_object();
                    __parse_true(object);
                    break;
                }
                
                case _AMO token_t::token_json_false: {
                    auto& object = jsonArray.push_back_object();
                    __parse_false(object);
                    break;
                }
                
                case _AMO token_t::token_json_string: {
                    auto& object = jsonArray.push_back_object();
                    __parse_string(object);
                    break;
                }
                
                case _AMO token_t::token_sep_comma:
                    expectToken = token_json_string | token_json_null | token_json_number | token_json_negative_number
                                  | token_json_true | token_json_false | token_begin_array | token_begin_object;
                    break;
                    
                case _AMO token_t::token_end_array:
                case _AMO token_t::token_end_document:
                    return;
                    
                default:
                    __throw_error_message();
            }
        }
    }
    
    inline void __parse(ObjectType& object, int32_t expect = AllExpect) {
        char ch = __skip_left_blank_char();
        auto token_type_ch = (token_t)(((int32_t)__char_to_token_type(ch)) & expect);
        __parse_json_value(object, token_type_ch, ch);
    }
    // 判断是否为空白字符
    inline bool __is_white_space(uint8_t ch) const {
        return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');
    }
    
    // 跳过空白字符
    inline char __skip_left_blank_char() {
        char ch = '\0';
        while (reader.safe()) {
            ch = reader.next();
            if (!__is_white_space(ch)) { return ch; }
        }
        return '\0';
    }
    
    // 查表判断token类型
    inline _AMO token_t __char_to_token_type(unsigned char ch) const {
        static std::array< _AMO token_t, 256> token_map = {
            //0
            _AMO token_t::token_end_document, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            
            //8
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            
            //16
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            
            //24
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            
            //32 34 0x22 "
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_json_string, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            
            //token_json_negative_number 改成token_json_number 也一样
            //40  46 0x2E . 44 0x2C , 逗号 45 0x2D - 减号 / 破折号 43 0x2B + 加号不是合法的数字 JSON数字也不能以.开头
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_sep_comma, _AMO token_t::token_json_negative_number, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            
            //48 48 0x30 0 57 0x39 9
            _AMO token_t::token_json_number, _AMO token_t::token_json_number, _AMO token_t::token_json_number, _AMO token_t::token_json_number,
            _AMO token_t::token_json_number, _AMO token_t::token_json_number, _AMO token_t::token_json_number, _AMO token_t::token_json_number,
            
            //56 57 0x39 9 58 0x3A : 冒号
            _AMO token_t::token_json_number, _AMO token_t::token_json_number, _AMO token_t::token_sep_colon, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            
            //64
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            //72
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            //80
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            //88 93 0x5D ] 闭方括号 91 0x5B [ 开方括号
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_begin_array,
            _AMO token_t::token_invalid, _AMO token_t::token_end_array, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            
            //96 102 0x66 f
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_json_false, _AMO token_t::token_invalid,
            //104 110 0x6E n
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_json_null, _AMO token_t::token_invalid,
            //112 116 0x74 t 小写字母t
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            _AMO token_t::token_json_true, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
            //120 123 0x7B { 开花括号 125 0x7D } 闭花括号
            _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_invalid, _AMO token_t::token_begin_object,
            _AMO token_t::token_invalid, _AMO token_t::token_end_object, _AMO token_t::token_invalid, _AMO token_t::token_invalid,
        };
        
        return token_map[ch];
    }
    
    // 解析失败，抛出异常
    void __throw_error_message() {
        _AMO memory_writer<0> stream;
        stream << "json parse error, unexpected token at position [" << reader.processed_size() << "], error buffers: ";
        stream << reader.error_buffers();
        throw std::runtime_error(stream.to_string());
    }
};

_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_parser


#ifndef segment_empty_t
#define segment_empty_t

_AMO_NAMESPACE_BEGIN
// 空类型
struct empty_t {};
_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_empty_t


#ifndef segment_string_reader
#define segment_string_reader

_AMO_NAMESPACE_BEGIN
// parse json from string
struct string_reader {
    string_reader(const char* val_, size_t len_) : val(val_), len(len_) {}
    string_reader(const char* val_) : string_reader(val_, strlen(val_)) {}
    string_reader(const std::string& val_) : string_reader(val_.c_str(), val_.size()) {}
    string_reader(const std::string* val_) : string_reader(val_->c_str(), val_->size()) {}
    const char* val;
    size_t len;
};


_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_string_reader


#ifndef segment_file_reader
#define segment_file_reader

_AMO_NAMESPACE_BEGIN

// parse json from file
struct file_reader {
    file_reader(const char* val_) : filename(val_) {}
    file_reader(const std::string& val_) : filename(val_) {}
    std::string filename;
};

_AMO_NAMESPACE_END

///!@segment update timestamp 20200216211257
#endif //segment_file_reader


#ifndef segment_basic_json
#define segment_basic_json

_AMO_NAMESPACE_BEGIN

template<typename T, typename Enable = void> struct is_parse_type { const static bool value = false; };

template <typename T> struct is_parse_type < T, typename std::enable_if < std::is_same<T, std::istream>::value
    || std::is_same<T, std::ifstream>::value || std::is_same<T, std::fstream>::value
    || std::is_same<T, std::stringstream>::value, void >::type > {
    const static bool value = true;
};



// 释放资源，暂时不用
template<int gc > class release_resources {
public:
    const static int value = 1;
public:
    release_resources() : release_at_exit_(true) {}
    release_resources(bool b) : release_at_exit_(b) {}
    inline bool release_at_exit() const { return release_at_exit_; }
    inline void release_at_exit(bool b) const { ((release_resources*)this)->release_at_exit_ = b; }
public:
    bool release_at_exit_;
};
// 特化版本，不释放资源
template<> class release_resources<0> {
public:
    const static int value = 0;
public:
    release_resources() {}
    release_resources(bool) {}
    inline bool release_at_exit() const { return false; }
    inline void release_at_exit(bool b) const { }
};


template<typename ObjectTypeTraits> class basic_json : public ObjectTypeTraits::release_resources_type {
public:
    typedef typename ObjectTypeTraits::release_resources_type BaseType;
    typedef ObjectTypeTraits ObjectType;
    typedef ObjectType object_type;
    typedef typename ObjectType::MemoryAllocType MemoryAllocType;
    typedef typename ObjectType::JsonAllocType JsonAllocType;
    typedef typename ObjectType::KeyType key_type;
    typedef typename ObjectType::DataType DataType;
    typedef basic_json value_type;
    struct this_val_is_json_value_proxy {};
    struct this_val_is_json_object_type {};
    struct this_val_is_vector_type {};
    struct this_val_is_map_type {};
    struct this_val_is_unknown_type {};
    struct this_val_is_pair_type {};
public:
    template<int IterType = 1> class iterator_base : public std::iterator<std::forward_iterator_tag, value_type> {
        friend class basic_json;
    public:
        typedef typename ObjectType::MapType MapType;
        typedef typename ObjectType::ArrayType ArrayType;
        typedef typename MapType::iterator MapIter;
        typedef typename ArrayType::iterator ArrayIter;
        typedef typename ObjectType::KeyType KeyType;
        typedef typename ObjectType::JsonAllocType JsonAllocType;
    protected: 								// json的指针
        MapIter m_map_iter;			        // JsonObjet iterator;
        ArrayIter m_array_iter;		        // JsonArray iterator;
        value_t m_type;                     // 当前iterator的数据类型
        JsonAllocType m_allocator;          // 内存分配器
    public:
        iterator_base(const MapIter& iter_, const JsonAllocType& allocate_)
            : m_map_iter(iter_)
            , m_type(json_value_object)
            , m_allocator(allocate_) { }
        iterator_base(const ArrayIter& iter_, const JsonAllocType allocate_)
            : m_array_iter(iter_)
            , m_type(json_value_array)
            , m_allocator(allocate_) { }
            
        iterator_base operator++() {
            if (m_type == json_value_object) {
                ++m_map_iter;
            } else {
                ++m_array_iter;
            }
            return *this;
        }
        
        inline bool operator<(const iterator_base& rhs) const {
            if (m_type == json_value_object) {
                return m_map_iter < rhs.m_map_iter;
            } else {
                return m_array_iter < rhs.m_array_iter;
            }
        }
        inline bool operator==(const iterator_base& rhs) const {
            if (m_type == json_value_object) {
                return m_map_iter == rhs.m_map_iter;
            } else {
                return m_array_iter == rhs.m_array_iter;
            }
        }
        
        inline bool operator!=(const iterator_base& rhs) const {
            if (m_type == json_value_object) {
                return m_map_iter != rhs.m_map_iter;
            } else {
                return m_array_iter != rhs.m_array_iter;
            }
        }
        // operator* 用来支持JsonArray foreach
        // JsonArray 可以使用foreach来遍历 for(auto& p : json){}
        // JsonObject 也可以使用foreach来遍历，但只能使到值，拿不到键 for(auto& p : json){}
        inline const basic_json operator*() const {
            if (m_type == json_value_object) {
                return basic_json(m_map_iter->second, m_allocator);
            } else {
                return basic_json(*m_array_iter, m_allocator);
            }
        }
        // operator-> 因为JsonArray和JsonObject的迭代器表现不一致，只有JsonObject支持
        // for(auto iter = json.begin(); iter!= json.end(); ++iter){}
        const typename MapType::value_type* operator->() const {
            if (m_type == json_value_object) {
                return m_map_iter.operator ->();
            }
            // 只有JsonObject支持
            throw std::runtime_error("json array not support operator->");
        }
        
        // 当一个iter指向一个JsonObject时，可以通过该取到具体的键名
        inline const KeyType key() const {
            if (m_type == json_value_object) {
                return m_map_iter->first;
            } else {
                return KeyType();
            }
        }
        // value
        inline const basic_json value() const { return this->operator*(); }
    };
    
    typedef iterator_base<1> iterator;
    typedef iterator_base<0> const_iterator;
public:

    #pragma region constructor
    // 默认为空类型
    basic_json() : BaseType(), m_allocator(new MemoryAllocType()), m_data(m_allocator->root()) {}
    
    // 指定类型
    basic_json(value_t type_) : basic_json() {
        if (type_ == json_value_object) {
            m_data.set_object(m_allocator);
        } else if (type_ == json_value_array) {
            m_data.set_array(m_allocator);
        } else {
            m_data.set_type(type_);
        }
    }
    // 使用初始化列表构造
    basic_json(const std::initializer_list<basic_json>& list) : basic_json() {
        bool is_object_ = __check_initializer_list_is_json_object(list);
        if (is_object_) {
            __init_object_from_initializer_list(list);
        } else {
            __init_array_from_initializer_list(list);
        }
    }
    
    // 复制构造，浅拷贝,将json内部的Data转为json
    basic_json(const ObjectType& data_, const JsonAllocType& allocator)
        : m_allocator(allocator), m_data((ObjectType&)data_)  { BaseType::release_at_exit(false);}
    basic_json(const DataType& data_, const JsonAllocType& allocator)
        : m_allocator(allocator), m_data(ObjectType(std::move(data_))) {
        BaseType::release_at_exit(false);
    }
    
    // 赋值构造
    template<typename T > basic_json(const T& val,
                                     typename std::enable_if < !is_parse_type<T>::value&& !std::is_array<T>::value, void >::type* test = 0) : basic_json() {
        __construct_json_with_unknown_type(val);
    }
    // 使用字符串构造
    basic_json(const char* val) : basic_json() { m_data.set_value(val, m_allocator); }
    // 拷贝构造
    basic_json(const basic_json& rhs) : basic_json() { m_data.copy(rhs.m_data, m_allocator); }
    
    // 移动构造
    basic_json(const basic_json&& rhs) : m_allocator(rhs.m_allocator), m_data(rhs.m_data),
        BaseType(rhs.release_at_exit()) {
        rhs.release_at_exit(false);
    }
    
    // 通过解析流构造JSON
    basic_json(const std::istream& reader_) : basic_json() {
        try {
            typename ObjectType::JsonParserType parser_(m_allocator, &reader_);
            parser_.parse(m_data);
        } catch (const std::exception& e) {
            std::string error_msg_ = e.what();
            $cerr("%s", error_msg_.c_str());
            m_data.set_value(error_msg_, m_allocator);
            m_data.set_type(json_value_invalid);
        }
    }
    
    // 通过解析字符串构造JSON
    basic_json(const string_reader& reader_) : basic_json() {
        try {
            typename ObjectType::JsonParserType parser_(m_allocator, reader_.val, reader_.len);
            parser_.parse(m_data);
        } catch (const std::exception& e) {
            std::string error_msg_ = e.what();
            $cerr("%s", error_msg_.c_str());
            m_data.set_value(error_msg_, m_allocator);
            m_data.set_type(json_value_invalid);
        }
    }
    
    // 通过解析file文件构造JSON
    basic_json(const file_reader& reader_) : basic_json(std::ifstream(reader_.filename, std::ios::in | std::ios::binary)) {}
    
    ~basic_json() {
        //this->release<BaseType::value>(); // 不释放资源
    }
    template <int gc>  inline typename std::enable_if<gc == 0, void>::type release() {}
    template <int gc>  inline typename std::enable_if < gc != 0, void >::type release() {
        if (this->release_at_exit()) { m_data.release(m_allocator.get()); }
    }
    #pragma endregion
    
    #pragma region set_object/set_array
    /**
    * @fn inline void basic_json::set_object() const
    *
    * @brief Sets the object.
    */
    
    inline void set_object() const { m_data.set_object(m_allocator); }
    
    /**
     * @fn inline void basic_json::set_array() const
     *
     * @brief Sets the array.
     */
    
    inline void set_array() const { m_data.set_array(m_allocator); }
    
    /**
     * @fn inline void basic_json::set_array(size_t capcity) const
     *
     * @brief 将当前json设置为JsonArray 并设置一个容量，以避免大量的重复分配内存.
     *
     * @param capcity The capcity.
     */
    
    inline void set_array(size_t capcity) const { m_data.set_array(capcity, m_allocator); }
    
    inline void set_empty() { m_data.release(m_allocator.get()); }
    #pragma endregion
    
    #pragma region iterator
    iterator begin() {
        auto type_ = this->get_type();
        if (type_ == json_value_object) {
            return iterator(m_data.d.o.elements->begin(), m_allocator);
        } else if (type_ == json_value_array) {
            return iterator(m_data.d.a.elements->begin(), m_allocator);
        }
        throw std::runtime_error("invalid json type, need object or array.");
    }
    
    iterator end() {
        auto type_ = this->get_type();
        if (type_ == json_value_object) {
            return iterator(m_data.d.o.elements->end(), m_allocator);
        } else if (type_ == json_value_array) {
            return iterator(m_data.d.a.elements->end(), m_allocator);
        }
        throw std::runtime_error("invalid json type, need object or array.");
    }
    
    const_iterator begin() const {
        auto type_ = this->get_type();
        if (type_ == json_value_object) {
            return const_iterator(m_data.d.o.elements->begin(), m_allocator);
        } else if (type_ == json_value_array) {
            return const_iterator(m_data.d.a.elements->begin(), m_allocator);
        }
        throw std::runtime_error("invalid json type, need object or array.");
    }
    
    const_iterator end() const {
        auto type_ = this->get_type();
        if (type_ == json_value_object) {
            return const_iterator(m_data.d.o.elements->end(), m_allocator);
        } else if (type_ == json_value_array) {
            return const_iterator(m_data.d.a.elements->end(), m_allocator);
        }
        throw std::runtime_error("invalid json type, need object or array.");
    }
    #pragma endregion
    
    #pragma region get compatible
    //////////////////////////////////////////////////////////////////////////
    // 旧程序兼容
    std::string get_string(const std::string& key, const std::string& default_value_ = "")const {
        if (!has(key)) { return default_value_; }
        return this->operator[](key). template get<std::string>();
    }
    int32_t get_int(const std::string& key, const int32_t default_value_ = 0) const {
        if (!has(key)) { return default_value_; }
        return this->operator[](key). template get<int32_t>();
    }
    int64_t get_int64(const std::string& key, const int64_t default_value_ = 0) const {
        if (!has(key)) { return default_value_; }
        return this->operator[](key). template get<int64_t>();
    }
    basic_json get_json(const std::string& key, const basic_json& default_value_ = basic_json()) const {
        if (!has(key)) { return default_value_; }
        return this->operator[](key). template get<basic_json>();
    }
    bool get_bool(const std::string& key, bool default_value_ = false) const {
        if (!has(key)) { return default_value_; }
        return this->operator[](key). template get<bool>();
    }
    
    //////////////////////////////////////////////////////////////////////////
    #pragma endregion
    
    #pragma region operator T
    // 将JSON转换为指定类型
    template<typename T> inline operator T() const { return this->get<T>(); }
    #pragma endregion
    
    #pragma region get
    // 将JSON转换为指定类型
    template<typename T>
    inline typename std::enable_if < !std::is_same<T, basic_json>::value&& (json_value_proxy<ObjectType, T>::value !=
            __json_value_unknown__), T >::type get() const {
        return m_data. template get_value<T>(m_allocator);
    }
    
    // 将整个JSON转换为指定类型
    template<typename T>
    inline typename std::enable_if < !std::is_same<T, basic_json>::value&& (json_value_proxy<ObjectType, T>::value ==
            __json_value_unknown__), T >::type get() const {
        T retval{};
        _AMO single_object_get_set_helper< amo::json_type_upgrader<typename std::remove_cv<T>::type>, basic_json>().get(*this,
                retval);
        return std::move(retval);
    }
    
    //特化，获取一个json的副本，而不是引用（operator[]拿到的是json的引用）
    template<typename T>
    inline typename std::enable_if < std::is_same<T, basic_json>::value, basic_json >::type get() const {
        basic_json retval = *this;
        return retval;
    }
    
    #pragma endregion
    
    #pragma region opertaor[]
    /**
    * @fn template<typename T> inline typename std::enable_if < !std::is_integral<T>::value, basic_json >::type basic_json::operator[](const T&& key) const
    *
    * @brief 通过key值查找JSON对象.
    *
    * @tparam T Generic type parameter.
    * @param key The key.
    *
    * @return The result of the operation.
    */
    
    template<typename T> inline typename std::enable_if < !std::is_integral<T>::value,
    basic_json >::type operator[](const T&& key) const {
        __init_and_check_json_object();
        return basic_json(m_data.find(key, m_allocator), m_allocator);
    }
    // 通过key值查找JSON对象
    template<typename T>
    inline typename std::enable_if < !std::is_integral<T>::value&& !std::is_floating_point<T>::value,
    basic_json >::type operator[](const T& key) const {
        __init_and_check_json_object();
        return basic_json(m_data.find(key, m_allocator), m_allocator);
    }
    
    /**
     * @fn template<typename T> inline typename std::enable_if<std::is_integral<T>::value, basic_json>::type basic_json::operator[](const T&& index) const
     *
     * @brief 通过key值查找JsonArray.
     *
     * @tparam T Generic type parameter.
     * @param index Zero-based index of the.
     *
     * @return The result of the operation.
     */
    
    template<typename T> inline typename std::enable_if<std::is_integral<T>::value, basic_json>::type operator[](
        const T&& index) const {
        __init_and_check_json_array();
        return basic_json(m_data.find(index, m_allocator), m_allocator);
    }
    // 通过k查找JsonArray
    template<typename T>
    inline typename std::enable_if<std::is_integral<T>::value, basic_json>::type operator[](const T& index) const {
        __init_and_check_json_array();
        return basic_json(m_data.find(index, m_allocator), m_allocator);
    }
    #pragma endregion
    
    #pragma region operator=
    /**
     * @fn template<typename T> inline basic_json& basic_json::operator=(const T& val)
     *
     * @brief 将其他类型值转换为JSON.
     *
     * @tparam T Generic type parameter.
     * @param val The value.
     *
     * @return The result of the operation.
     */
    
    template<typename T> inline basic_json& operator=(const T& val) {
        m_data.release(m_allocator.get());
        typedef typename std::conditional < is_pair<T>::value, this_val_is_pair_type,
                typename std::conditional < json_value_proxy<ObjectType, T>::value != __json_value_unknown__,
                this_val_is_json_value_proxy, this_val_is_unknown_type >::type >::type type;
        __construct_json_with_unknown_type<T>(val, type());
        return *this;
    }
    
    inline basic_json& operator=(const char* val) {
        m_data.release(m_allocator.get());
        if (val != nullptr) {
            m_data.set_value(val, m_allocator);
        }
        return *this;
    }
    
    // 复制一个JSON对象
    inline basic_json& operator=(const basic_json& rhs) {
        m_data.release(m_allocator.get());
        m_data = rhs.m_data.clone(m_allocator);
        return *this;
    }
    inline basic_json& operator=(const string_reader& rhs) { return this->operator=(basic_json(rhs)); }
    inline basic_json& operator=(const file_reader& rhs) { return this->operator=(basic_json(rhs)); }
    // 移动一个JSON对象,同一个JSON内部不能移动创建引用快捷方式
    // 嵌套引用将有可能导致死循环
    inline basic_json& operator=(const basic_json&& rhs) {
        assert(this->get_allocator() != rhs.get_allocator());
        this->m_data.release(m_allocator.get());
        this->m_data = rhs.m_data;
        rhs.release_at_exit(false);
        
        switch (this->get_type()) {
            case json_value_empty:
            case json_value_null:
            case json_value_boolean:
            case json_value_integer:
            case json_value_unsigned:
            case json_value_float:
                break;
            default:
                this->m_allocator->add_allocator(rhs.m_allocator); // 关联rhs的内存分配器
                break;
        }
        
        //this->m_allocator->add_allocator(rhs.m_allocator); // 关联rhs的内存分配器
        return *this;
    }
    #pragma endregion
    
    #pragma region operator compare
    // 尽量不要与json比
    template<typename T> inline typename std::enable_if < !std::is_same<basic_json, T>::value,
    bool >::type operator== (const T& rhs) const { return this->get<T>() == rhs; }
    template<typename T> inline typename std::enable_if < !std::is_same<basic_json, T>::value,
    bool >::type operator!= (const T& rhs) const { return this->get<T>() != rhs; }
    template<typename T> inline typename std::enable_if < !std::is_same<basic_json, T>::value,
    bool >::type operator< (const T& rhs) const { return this->get<T>() < rhs; }
    template<typename T> inline typename std::enable_if < !std::is_same<basic_json, T>::value,
    bool >::type operator<= (const T& rhs) const { return this->get<T>() <= rhs; }
    template<typename T> inline typename std::enable_if < !std::is_same<basic_json, T>::value,
    bool >::type operator> (const T& rhs) const { return this->get<T>() > rhs; }
    template<typename T> inline typename std::enable_if < !std::is_same<basic_json, T>::value,
    bool >::type operator>=(const T& rhs) const { return this->get<T>() >= rhs ; }
    
    // const char* 特殊处理 char[] 要不要处理? char* 要不要处理?
    inline bool operator==(const char* rhs) const {
        if (m_data.get_type() != json_value_string) { return false; }
        size_t len = strlen(rhs);
        if (m_data.d.s.length != len) { return false; }
        return memcmp(m_data.d.s.elements, rhs, len) == 0;
    }
    
    // json 特殊处理一下
    inline bool operator==(const basic_json& rhs) const {
        if (this->get_type() != rhs.get_type()) { return false; }
        switch (m_data.get_type()) {
            case json_value_empty:
            case json_value_null:
                return true;
            case json_value_string:
                return json_key_string(this->m_data.d.s.elements, this->m_data.d.s.length)
                       == json_key_string(rhs.m_data.d.s.elements, rhs.m_data.d.s.length);
            case json_value_boolean:
                return this->get<bool>() == rhs.get<bool>();
            case json_value_unsigned:
            case json_value_integer:
                return this->get<uint64_t>() == rhs.get<uint64_t>();
            case json_value_float:
                return this->get<double>() == rhs.get<double>();
            case json_value_object: {
                if (this->size() != rhs.size()) { return false; }
                for (auto& p : * (this->m_data.d.o.elements)) {
                    if (basic_json(p.second, get_allocator()) == rhs[p.first]) {
                        continue;
                    }
                }
                
                return true;
            }
            case json_value_array: {
                if (this->size() != rhs.size()) { return false; }
                for (size_t i = 0; i < this->size(); ++i) {
                    if (this->operator [](i) == rhs[i]) { continue; }
                    return false;
                }
                return true;
            }
            default:
                if (this->m_data.d.s.length != rhs.m_data.d.s.length) { return false; }
                return std::memcmp(this->m_data.d.s.elements, rhs.m_data.d.s.elements, this->m_data.d.s.length) == 0;
        }
        return false;
    }
    
    // json 特殊处理一下
    inline bool operator!=(const basic_json& rhs) const { return !(this->operator==(rhs)); }
    #pragma endregion
    
    #pragma region put
    template<typename T> inline void put(const T&& val) { this->operator=(val); }
    template<typename T> inline void put(const T& val) { this->operator=(val); }
    
    /**
     * @fn template<typename T> inline void basic_json::put(const key_type&& key, const T&& val)
     *
     * @brief 通过Key值赋值.
     *
     * @tparam T Generic type parameter.
     * @param key The key.
     * @param val The value.
     */
    
    template<typename T> inline void put(const key_type&& key, const T&& val) { this->operator[](key) = std::move(val); }
    template<typename T> inline void put(const key_type& key, const T&& val) { this->operator[](key) = std::move(val); }
    template<typename T> inline void put(const key_type& key, const T& val) { this->operator[](key) = (val); }
    #pragma endregion
    
    #pragma region push_back
    /**
     * @fn template<typename T> inline basic_json& basic_json::push_back(const T& val)
     *
     * @brief 在数组末尾插入数据.
     *
     * @tparam T Generic type parameter.
     * @param val The value.
     *
     * @return A reference to a basic_json.
     */
    
    template<typename T> inline basic_json& push_back(const T& val) {
        __init_and_check_json_array();
        this->operator[](-1).operator = (val);
        return *this;
    }
    template<typename T> inline basic_json& push_back(const T&& val) {
        __init_and_check_json_array();
        this->operator[](-1).operator = (val);
        return *this;
    }
    
    /**
     * @fn template<typename T> inline basic_json& basic_json::push_back(const T& begin, const T& end)
     *
     * @brief 插入区间，如迭代器，指针等.
     *
     * @tparam T Generic type parameter.
     * @param begin The begin.
     * @param end   The end.
     *
     * @return A reference to a basic_json.
     */
    
    template<typename T> inline basic_json& push_back(const T& begin, const T& end) {
        __init_and_check_json_array();
        for (auto iter = begin; iter != end; ++iter) {
            this->operator[](-1).operator = (*iter);
        }
        return *this;
    }
    
    /**
     * @fn inline basic_json& basic_json::push_back(const std::initializer_list<basic_json>& list)
     *
     * @brief 使用初始化列表来push_back 如果初始化列表里面用初始化列表来构造json,那么该函数与构造函数表现不同
     * 		  json.push_back({"a", 1}).to_string() == ["a", 1]
     * 		  basic_json({"a", 1}).to_string() == {"a": 1}
     * 		  json.push_back({{"a",1}})[0].to_string() ==  {"a": 1}
     * 		  构造函数里面是生成一个对象，这里的函数是一个数组.
     *
     * @param list The list.
     *
     * @return A reference to a basic_json.
     */
    
    inline basic_json& push_back(const std::initializer_list<basic_json>& list) {
        for (auto& p : list) {
            if (!p.is_empty()) { this->push_back(p); }
        }
        return *this;
    }
    #pragma endregion
    
    #pragma region erase
    /**
     * @fn inline basic_json& basic_json::erase(const key_type& key)
     *
     * @brief 移除JsonObject中指定KEY值的数据.
     *
     * @param key The key.
     *
     * @return A reference to a basic_json.
     */
    
    inline basic_json& erase(const key_type& key) {
        __check_type(json_value_object);
        m_data.erase(key, m_allocator);
        return *this;
    }
    
    /**
     * @fn inline basic_json& basic_json::erase(const uint32_t start_pos, const uint32_t offset = 1)
     *
     * @brief 移除JsonArray中指定位置开始，指定长度的数据.
     *
     * @param start_pos The start position.
     * @param offset    (Optional) The offset.
     *
     * @return A reference to a basic_json.
     */
    
    inline basic_json& erase(const uint32_t start_pos, const uint32_t offset = 1) {
        __check_type(json_value_array);
        m_data.erase(start_pos, offset, m_allocator);
        return *this;
    }
    #pragma endregion
    
    #pragma region join
    /**
     * @fn inline basic_json& basic_json::join(const basic_json& rhs)
     *
     * @brief 合并一个json到当前json.
     *
     * @param rhs The right hand side.
     *
     * @return A reference to a basic_json.
     */
    
    inline basic_json& join(const basic_json& rhs) {
        __init_and_check_json_object();         // 当前对象只能是object 或empty
        if (!rhs.is_object()) { return *this; } // rhs 只能是object
        if (this->size() == 0) {
            return this->operator =(rhs);
        }
        rhs.transfer<key_type>([&](const key_type & key, const basic_json & data_) {
            this->operator[](key) = data_;
        });
        return *this;
    }
    inline basic_json& join(const basic_json&& rhs) {
        __init_and_check_json_object();              // 当前对象只能是object 或empty
        if (!rhs.is_object()) { return *this; }      // rhs 只能是object
        if (this->size() == 0) {
            return this->operator =(std::move(rhs)); // 直接移动到当前对象
        }
        rhs.transfer<key_type>([&](const key_type & key, const basic_json & data_) {
            this->operator[](key) = data_;
        });
        return *this;
    }
    #pragma endregion
    
    #pragma region transfer
    /**
     * @fn template<typename T> typename std::enable_if<std::is_integral<T>::value, void>::type basic_json::transfer(const std::function<void(const T&, basic_json&) >& fn) const
     *
     * @brief 遍历JsonArray.
     *
     * @tparam T Generic type parameter.
     * @param fn The function.
     *
     * @return A std::enable_if&lt;std::is_integral&lt;T&gt;::value,void&gt;::type.
     */
    
    template<typename T> typename std::enable_if<std::is_integral<T>::value, void>::type transfer(
        const std::function<void(const T&, basic_json&) >& fn) const {
        __init_and_check_json_array();
        static ObjectType object;
        basic_json tmp(object, get_allocator());
        return m_data.transfer([&](const T & key, const ObjectType & data_) {
            tmp.set_data_object(data_);
            //basic_json tmp(data_, m_allocator);
            fn(key, tmp);
        });
    }
    
    /**
     * @fn template<typename T> typename std::enable_if < !std::is_integral<T>::value, void >::type basic_json::transfer(const std::function<void(const T&, basic_json&) >& fn) const
     *
     * @brief 遍历JsonObject.
     *
     * @tparam T Generic type parameter.
     * @param fn The function.
     *
     * @return A std::enable_if.
     */
    
    template<typename T> typename std::enable_if < !std::is_integral<T>::value,
    void >::type transfer(const std::function<void(const T&, basic_json&) >& fn) const {
        __init_and_check_json_object();
        static ObjectType object;
        basic_json tmp(object, get_allocator());
        return m_data.transfer([&](const T & key, const ObjectType & data_) {
            tmp.set_data_object(data_);
            //basic_json tmp(data_, m_allocator);
            fn(key, tmp);
        });
    }
    #pragma endregion
    
    #pragma region find
    /**
    * @fn template<typename T> inline ObjectType& basic_json::find(const T&& key) const
    *
    * @brief 通过key值查找JsonData对象,可以直接操作JsonData来提高程序性能，但并不安全.
    *
    * @tparam T Generic type parameter.
    * @param key The key.
    *
    * @return A reference to an ObjectType.
    */
    
    template<typename T> inline ObjectType& find(const T&& key) const { return m_data.find(key, m_allocator); }
    
    /**
     * @fn template<typename T> inline ObjectType& basic_json::find(const T& key) const
     *
     * @brief Searches for the first match for the given constant t&amp;
     *
     * @tparam T Generic type parameter.
     * @param key The key.
     *
     * @return A reference to an ObjectType.
     */
    
    template<typename T> inline ObjectType& find(const T& key) const { return m_data.find(key, m_allocator); }
    
    /**
    * @fn std::vector<std::string> basic_json::keys() const
    *
    * @brief Gets the keys.
    *
    * @return A std::vector&lt;std::string&gt;
    */
    
    std::vector<std::string> keys() const {
        __check_type(json_value_object);
        std::vector<std::string> vec;
        for (auto& p : * ((m_data.d.o.elements))) {
            vec.push_back(p.first);
        }
        return vec;
    }
    
    /**
     * @fn inline bool basic_json::has(const key_type& key) const
     *
     * @brief 判断是否存在key.
     *
     * @param key The key.
     *
     * @return True if it succeeds, false if it fails.
     */
    
    inline bool has(const key_type& key) const { return this->contains_key(key); }
    
    /**
     * @fn inline bool basic_json::contains_key(const key_type& key) const
     *
     * @brief Query if 'key' contains key.
     *
     * @param key The key.
     *
     * @return True if it succeeds, false if it fails.
     */
    
    inline bool contains_key(const key_type& key) const {
        __check_type(json_value_object);
        return m_data.contains_key(key);
    }
    #pragma endregion
    
    #pragma region type check
    // 获取当前JSON的类型ID
    //inline int32_t type() const { return this->get_type(); }
    
    /**
     * @fn inline int32_t basic_json::get_type() const
     *
     * @brief Gets the type.
     *
     * @return The type.
     */
    
    inline int32_t get_type() const { return m_data.get_type(); }
    
    /**
    * @fn template<typename P1, typename P2, typename P3, typename P4, typename P5> inline bool basic_json::is() const
    *
    * @brief 判断当前json是否为所指定的类型，最多支持同时判断五种类型.例:
    * 		  amo::json = 3;
    * 		  bool b = json.is<int, bool>(); // b == true;
    *
    *
    * @tparam P1 Type of the p 1.
    * @tparam P2 Type of the p 2.
    * @tparam P3 Type of the p 3.
    * @tparam P4 Type of the p 4.
    * @tparam P5 Type of the p 5.
    *
    * @return True if it succeeds, false if it fails.
    */
    
    template<typename P1, typename P2, typename P3, typename P4, typename P5> inline bool is() const { return __is<P1>() || is<P2, P3, P4, P5>(); }
    template<typename P1, typename P2, typename P3, typename P4> inline bool is() const { return __is<P1>() || is<P2, P3, P4>(); }
    template<typename P1, typename P2, typename P3> inline bool is() const { return __is<P1>() || is<P2, P3>(); }
    template<typename P1, typename P2> inline bool is() const { return __is<P1>() || is<P2>(); }
    template<typename P1> inline bool is() const { return __is<P1>(); }
    
    
    /**
     * @fn inline bool basic_json::is(int8_t type_) const
     *
     * @brief 判断所当前json是否为所给类型.
     *
     * @param type_ 类型的值.
     *
     * @return True if it succeeds, false if it fails.
     */
    
    inline bool is(uint16_t type_) const { return this->get_type() == type_; }
    inline bool is_valid() const { return !is(json_value_invalid); }
    inline bool is_empty() const { return is(json_value_empty); }
    inline bool is_null() const { return is(json_value_null); }
    inline bool is_bool() const { return is(json_value_boolean); }
    inline bool is_true() const { return is_bool() && get<bool>(); }
    inline bool is_false() const { return is_bool() && !get<bool>(); }
    inline bool is_unsigned() const { return is(json_value_unsigned); }
    inline bool is_signed() const { return is(json_value_integer); }
    inline bool is_integer() const { return is_signed() || is_unsigned(); }
    //inline bool is_int() const { return is(json_value_integer); }
    inline bool is_float() const { return is(json_value_float); }
    inline bool is_number() const { return is_signed() || is_unsigned() || is_float(); }
    inline bool is_string() const { return is(json_value_string); }
    inline bool is_object() const { return is(json_value_object); }
    inline bool is_array() const { return is(json_value_array); }
    inline bool empty() const { return size() == 0; }
    
    #pragma endregion
    
    #pragma region size
    /**
     * @fn size_t basic_json::size() const
     *
     * @brief 返回JsonObject或JsonArray的长度，如果不是这两种类型中的一种，那么将抛出异常.
     *
     * @return A size_t.
     */
    
    size_t size() const { __check_type(json_value_object, json_value_array); return m_data.size(); }
    
    #pragma endregion
    
    #pragma region to_array
    /**
     * @fn std::vector<_AMO basic_json<ObjectType> > basic_json::to_array() const
     *
     * @brief 转换为将JsonArray换为vector，直接用foreach更好.
     *
     * @return 数组
     */
    
    std::vector<_AMO basic_json<ObjectType> > to_array() const {
        __check_type(json_value_array);
        std::vector<_AMO basic_json<ObjectType> > vec;
        m_data.transfer([&](const int32_t& key, const ObjectType & data_) {
            vec.push_back(std::move(_AMO basic_json<ObjectType>(data_, this->m_allocator)));
        });
        return vec;
    }
    
    #pragma endregion
    
    #pragma region native data / json_data_object
    
    /**
     * @fn inline ObjectType& basic_json::get_data_object()
     *
     * @brief 获取真正保存数据的对象，嫌性能不够的时候可以直接操作该对象.
     *
     * @return json_data_object&.
     */
    
    inline ObjectType& get_data_object() { return m_data; }
    
    inline void set_data_object(const ObjectType& data_) { m_data = data_; }
    /**
     * @fn inline const ObjectType& basic_json::get_data_object() const
     *
     * @brief 获取保存数据的对象引用，直接操作该对象可以提升增删改查的性能.
     *
     * @return json_data_object&.
     */
    
    inline const ObjectType& get_data_object() const { return m_data; }
    
    /**
     * @fn inline const JsonAllocType& basic_json::get_allocator() const
     *
     * @brief 获取内存分配器,直接操作json_data_object时需要用到这个函数.
     *
     * @return 内存分配器.
     */
    
    inline const JsonAllocType& get_allocator() const { return m_allocator; }
    
    #pragma endregion
    
    #pragma region error message
    
    /**
    * @fn inline const std::string basic_json::get_error_msg() const
    *
    * @brief 返回错误消息,如果没有错误，那么返回空字符串.
    *
    * @return The error message.
    */
    inline const std::string get_error_msg() const {
        if (is_valid()) { return ""; }
        // JSON解析出错时，会将错误信息放到json_value_string里面
        return { m_data.d.s.elements, (size_t)m_data.d.s.length };
    }
    
    #pragma endregion
    
    #pragma region ouput
    inline void to_string(std::shared_ptr<std::ostream>& stream, int32_t indent = 0) const {
        return this->to_string(*stream, indent);
    }
    
    /**
     * @fn inline void basic_json::to_string(std::ostream& stream, int32_t indent = 0) const
     *
     * @brief Converts this object to a string.
     *
     * @param [in,out] stream The stream.
     * @param 		   indent (Optional) The indent.
     */
    
    inline void to_string(std::ostream& stream, int32_t indent = 0) const {
        _AMO memory_writer < -2 > writer(stream);
        m_data.to_string(writer, indent);
        writer.flush();
    }
    
    /**
     * @fn inline void basic_json::to_string(std::string& str, int32_t indent = 0) const
     *
     * @brief Converts this object to a string.
     *
     * @param [in,out] str    The string.
     * @param 		   indent (Optional) The indent.
     */
    
    inline void to_string(std::string& str, int32_t indent = 0) const {
        _AMO memory_buffer<std::string> buffer(str, str.size());
        m_data.to_string(buffer, indent);
    }
    
    /**
    * @fn inline std::string basic_json::to_string(int32_t indent = 0) const
    *
    * @brief Converts an indent to a string.
    *
    * @param indent (Optional) The indent.
    *
    * @return Indent as a std::string.
    */
    
    inline std::string to_string(int32_t indent = 0) const {
        _AMO memory_writer < -1 > writer;
        m_data.to_string(writer, indent);
        return writer.to_string();
    }
    
    /**
     * @fn inline void basic_json::to_file(const std::string filename_, int32_t indent = 0) const
     *
     * @brief Converts this object to a file.
     *
     * @param filename_ Filename of the file.
     * @param indent    (Optional) The indent.
     */
    
    inline void to_file(const std::string filename_, int32_t indent = 0) const {
        std::ofstream ofs(filename_);
        to_string(ofs, indent);
        ofs.close();
    }
    template<typename T> friend T& operator<<(T& stream, const basic_json& t) {
        t.to_string(stream);
        return stream;
    }
    #pragma endregion
private:
    #pragma region construct_funtions
    template<typename T> inline void __construct_json_with_unknown_type(const T& val) {
        // 下面的代码不能直接在构造函数中执行，gcc4.8.5编译不过
        typedef typename std::conditional < _AMO is_pair<T>::value, this_val_is_pair_type,
                typename std::conditional < _AMO json_value_proxy<ObjectType, T>::value != __json_value_unknown__,
                this_val_is_json_value_proxy, this_val_is_unknown_type >::type >::type type;
        __construct_json_with_unknown_type<T>(val, type());
    }
    
    template<typename T> inline void __construct_json_with_unknown_type(const T& val, this_val_is_json_value_proxy) {
        m_data.set_value(val, m_allocator);
    }
    
    template<typename T> inline void __construct_json_with_unknown_type(const T& p, this_val_is_pair_type) {
        if (std::is_same<typename std::decay<typename T::first_type>::type, std::string>::value) {
            this->set_object();
            this->find(p.first).set_value(p.second, this->get_allocator());
        } else {
            this->set_array();
            this->find(-1).set_value(p.first, this->get_allocator());
            this->find(-1).set_value(p.second, this->get_allocator());
        }
    }
    
    template<typename T> void __construct_json_with_unknown_type(const T& val, this_val_is_unknown_type) {
        typedef amo::json_type_upgrader<typename std::remove_cv<T>::type> upgrade_type;
        amo::single_object_get_set_helper<upgrade_type, basic_json>().set(*this, &val);
    }
    #pragma endregion
    
    #pragma region initializer_list
    
    // 判断 initializer_list 的具体类型
    bool __check_initializer_list_is_json_object(const std::initializer_list<basic_json>& list) {
        // 如果list里面存在空对象，那么认为是一个array
        for (auto& p : list) {
            if (p.is_empty()) { return false; }
        }
        
        // 如果list只有两个值，且第一个为strig,那么认为这是一个object
        if (list.size() == 2 && list.begin()->is_string()) {
            return true;
        }
        
        // 如果list中有一项不是object，那么认为是一个array
        for (auto& p : list) {
            if (!p.is_object()) { return false; }
        }
        return true;
    }
    
    // 使用初始化列表初始化一个object
    void __init_object_from_initializer_list(const std::initializer_list<basic_json>& list) {
        this->set_object();
        if (list.size() == 2 && list.begin()->is_string()) {
            auto first = list.begin();
            auto second = list.begin();
            ++second;
            std::string key = *first;
            this->put(key, *second);
        } else {
            for (auto& p : list) {
                if (!p.is_empty()) { this->join(p); }
            }
        }
    }
    // 使用初始化列表初始化一个array
    void __init_array_from_initializer_list(const std::initializer_list<basic_json>& list) {
        this->set_array();
        for (auto& p : list) {
            if (!p.is_empty()) { this->push_back(p); }
        }
    }
    
    #pragma endregion
    
    #pragma region safety check
    // 非法类型，抛出异常
    void __check_type() const { throw std::runtime_error("invalid json type."); }
    template<typename ... Args> inline void __check_type(const value_t& type_, Args&& ... args) const {
        if (get_type() == (int32_t)type_) { return; }
        return __check_type(std::forward<Args>(args)...);
    }
    // 检测是否为JsonObject，如果类型为空，则初始化为JsonObject
    void __init_and_check_json_object() const {
        if (is(json_value_empty)) { this->set_object(); }
        __check_type(json_value_object);
    }
    
    // 检测是否为JsonArray，如果类型为空，则初始化为JsonArray
    void __init_and_check_json_array() const {
        if (is(json_value_empty)) { this->set_array(); }
        __check_type(json_value_array);
    }
    #pragma endregion
    
    #pragma region __is
    // 通过value id 来判断类型是否相同
    template<typename T> inline typename std::enable_if < !std::is_same<_AMO basic_json<ObjectType>, T>::value&&
    !std::is_same<empty_t, T>::value, bool >::type __is() const {
        return json_value_proxy<ObjectType, T>::value == this->get_type();
    }
    // 类型判断， 空类型特化
    template<typename T> inline typename std::enable_if <std::is_same<empty_t, T>::value, bool >::type __is() const {
        return is_empty();
    }
    // 类型判断,json 特化
    template<typename T>
    inline typename std::enable_if< std::is_same<_AMO basic_json<ObjectType>, T>::value, bool >::type __is() const {
        return is(json_value_object) || is(json_value_array);
    }
    #pragma endregion
    
private:
    JsonAllocType m_allocator;   // 当前JSON所使用的内存分配器
    ObjectType& m_data;          // 当前JSON所对应的数据地址
};

_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_basic_json


#ifndef segment_json_object_helper
#define segment_json_object_helper
_AMO_NAMESPACE_BEGIN
// 未知类型与JSON互转
template<typename JsonType, typename T, typename P> class json_object_helper {
public:
    typedef typename json_object_helper_traits<T>::value_type value_type;
    static void get_value_from_json(T& retval, const JsonType& json, const std::string& key, const T& default_) {
        json_object_helper<JsonType, T, value_type>::get_value_from_json(retval, json, key, default_);
    }
    
    static void set_json_from_value(JsonType& json, const std::string& key, const T& val) {
        json_object_helper<JsonType, T, value_type>::set_json_from_value(json, key, val);
    }
};

// 一个普通数据类型与JSON互转
template<typename JsonType, typename T> class json_object_helper<JsonType, T, ObjectPod> {
public:
    static void get_value_from_json(T& retval, const JsonType& json, const std::string& key, const T& default_) {
        if (!json.is_object() || !json.has(key)) {
            retval = default_;
        } else {
            retval = json[key].template get<T>();
        }
    }
    static void set_json_from_value(JsonType& json, const std::string& key, const T& val) { json[key] = val; }
};

// Class类型与JSON类型互转
template<typename JsonType, typename T> class json_object_helper<JsonType, T, ObjectClass> {
public:
    static void get_value_from_json(T& retval, const JsonType& json, const std::string& key, const T& default_) {
        if (json.is_object() && json.has(key)) {
            return single_json_object_helper<JsonType, T, ObjectClass>::get_value_from_json(retval, json[key], default_);
        }
        retval = default_;
    }
    
    static void set_json_from_value(JsonType& json, const std::string& key, const T& val) {
        JsonType tmp = json[key];
        single_json_object_helper<JsonType, T, ObjectClass>::set_json_from_value(tmp, val);
    }
};
// 容器类型与JSON类型互转
template<typename JsonType, typename T> class json_object_helper<JsonType, T, ObjectContainer> {
public:
    typedef typename T::value_type P1;
    typedef typename json_object_helper_traits<P1>::value_type value_type;
    
    static void get_value_from_json(T& retval, const JsonType& json, const std::string& key, const T& default_) {
        if (!json.is_object() || !json.has(key)) { retval = default_;  return; }
        JsonType child = json[key];  // 获取key 对应的 json
        if (!child.is_array()) { retval = default_;  return; }
        single_json_object_helper<JsonType, T, ObjectContainer>::get_value_from_json(retval, child, default_);
    }
    
    static void set_json_from_value(JsonType& json, const std::string& key, const T& val) {
        JsonType retval = json[key];
        retval.set_empty();
        single_json_object_helper<JsonType, T, ObjectContainer>::set_json_from_value(retval, val);
    }
};

template<typename JsonType, typename T> class json_object_helper<JsonType, T, ObjectPointer> {
public:
    typedef typename std::remove_pointer<T>::type P1;
    typedef typename json_object_helper_traits<P1>::value_type value_type;
    static void get_value_from_json(T& retval, const JsonType& json, const std::string& key, const T& default_) {
        if (!json.is_object() || !json.has(key)) { retval = default_; return; }
        if (retval == nullptr) { retval = (new P1()); }
        json_object_helper<JsonType, P1, value_type>::get_value_from_json(*retval, json, key, default_ ? *default_ : P1());
    }
    
    static void set_json_from_value(JsonType& json, const std::string& key, const T& val) {
        if (!val) { return; }
        json_object_helper<JsonType, P1, value_type>::set_json_from_value(json, key, val ? *val : P1());
    }
};

template<typename JsonType, typename T> class json_object_helper<JsonType, T, ObjectSmart> {
public:
    typedef typename T::element_type P1;
    typedef typename json_object_helper_traits<P1>::value_type value_type;
    
    static void get_value_from_json(T& retval, const JsonType& json, const std::string& key, const T& default_) {
        if (!json.is_object() || !json.has(key)) { retval = default_; return; }
        if (!retval) { retval.reset(new P1()); }
        json_object_helper<JsonType, P1, value_type>::get_value_from_json(*retval, json, key, default_ ? *default_ : P1());
    }
    
    static void set_json_from_value(JsonType& json, const std::string& key, const T& val) {
        if (!val) { return; }
        json_object_helper<JsonType, P1, value_type>::set_json_from_value(json, key, val ? *val : P1());
    }
};

// 返回值管理
template<typename TypeTraits, typename JsonType> struct json_object_get_set_helper {
    typedef typename TypeTraits::upgrade_type upgrade_type;
    typedef typename TypeTraits::raw_type raw_type;
    typedef typename TypeTraits::downgrade_type downgrade_type;
    typedef typename TypeTraits::raw_value_type raw_value_type;
    struct array_type_traits {};
    struct other_type_traits {};
    // 从JSON取一个值
    void get(const JsonType& json, raw_type& ptr, const std::string& key) {
        typedef typename std::conditional<std::is_array<raw_type>::value, array_type_traits, other_type_traits>::type type;
        return __get_impl(json, ptr, key, type());
    }
    // 将一个值赋值给JSON
    void set(JsonType& json, const raw_type* ptr, const std::string& key) {
        typedef typename std::conditional<std::is_array<raw_type>::value, array_type_traits, other_type_traits>::type type;
        return __set_impl(json, ptr, key, type());
    }
private:
    void __get_impl(const JsonType& json, raw_type& ptr, const std::string& key, array_type_traits) {
        // 将 array升级为vector 再处理 如: int [10]; 升级为vector<int>
        auto p = TypeTraits().upgrade(ptr, sizeof(ptr));
        auto default_value = p;
        p.clear();
        amo::json_object_helper<JsonType, upgrade_type, amo::ObjectUnknown>::get_value_from_json(p, json, key, default_value);
        TypeTraits().copy_from_container(ptr, p);
    }
    
    void __get_impl(const JsonType& json, raw_type& ptr, const std::string& key, other_type_traits) {
        raw_type& p = (raw_type&)TypeTraits().upgrade(ptr, sizeof(ptr));
        amo::json_object_helper<JsonType, upgrade_type, amo::ObjectUnknown>::get_value_from_json(p, json, key, p);
        TypeTraits().copy_from_container(ptr, p);
    }
    
    void __set_impl(JsonType& json, const raw_type* ptr, const std::string& key, array_type_traits) {
        amo::json_object_helper<JsonType, upgrade_type, amo::ObjectUnknown>::set_json_from_value(json, key,
                TypeTraits().upgrade((downgrade_type)*ptr, sizeof(*ptr)));
    }
    
    void __set_impl(JsonType& json, const raw_type* ptr, const std::string& key, other_type_traits) {
        amo::json_object_helper<JsonType, upgrade_type, amo::ObjectUnknown>::set_json_from_value(json, key, *ptr);
    }
};
_AMO_NAMESPACE_END
///!@segment update timestamp 20200216211257
#endif //segment_json_object_helper


#ifndef segment_json_object
#define segment_json_object

_AMO_NAMESPACE_BEGIN
template<typename BaseType_ > class json_object : public BaseType_ {
public:
    typedef BaseType_ JsonType;
    // to json
    virtual JsonType to_json(bool bAll = true) const { return JsonType(); }
    virtual void on_to_json(JsonType& json) const { return; }
    virtual std::string to_string() const { return to_json().to_string(); }
    // from json
    // from_json 函数在宏里面实现
    virtual void on_from_json(const JsonType& json) { return; }
    // format str
    virtual std::string format_json(bool h = true, int align = 0, int mode = 0, const std::string& split_str = "    ") { return ""; }
    virtual	std::string on_format_json(const std::string& key, const std::string& val) { return val; }
    virtual	int on_get_str_len(const std::string& str) const { return str.size(); }
};
_AMO_NAMESPACE_END

#define AMO_ENTITY_JOIN_JSON(ClassName)\
    virtual void join_json(const JsonType& other)  {\
        typedef ClassName ClassType;\
        JsonType json = this->to_json();\
        json.join(other);\
        ClassType::from_json(json, this);\
        return;\
    }

// 将值写入JSON的辅助函数
#define AMO_ON_TOJSON_IMPL()\
    template<typename JsonType_, typename ClassType_>\
    typename std::enable_if<std::is_base_of<JsonType_, ClassType_>::value, void>::type __on_to_json_impl(const ClassType_ * ptr, std::function<void(JsonType_ &)>& fn, JsonType_ & json) const {\
        if (fn) {fn(json);}\
        else {ptr->on_to_json(json);}\
    }\
    template<typename JsonType_, typename ClassType_>\
    typename std::enable_if<!std::is_base_of<JsonType_, ClassType_>::value, void>::type __on_to_json_impl(const ClassType_ * ptr, std::function<void(JsonType_ &)>& fn, JsonType_ & json) const {\
        if (fn) {fn(json);}\
    }\
    template<typename JsonType_, typename ClassType_>\
    typename std::enable_if<std::is_base_of<JsonType_, ClassType_>::value, void>::type __object_to_json_impl(const ClassType_ * ptr, JsonType_& json) const {\
        json = *(JsonType*)ptr;\
        return;\
    }\
    template<typename JsonType_, typename ClassType_>\
    typename std::enable_if<!std::is_base_of<JsonType_, ClassType_>::value, void>::type __object_to_json_impl(const ClassType_ * ptr, JsonType_& json) const {\
        return;\
    }


// 注册宏 开始
#define AMO_ENTITY_ARGS_SET_BEGIN(ClassName)\
    AMO_ENTITY_JOIN_JSON(ClassName)\
    AMO_ON_TOJSON_IMPL()\
    inline operator JsonType() const {return this->to_json();}\
    virtual JsonType to_json(bool bAll = true) const{\
        typedef ClassName ClassType;\
        std::function<void(JsonType&)> fn_on_to_json_callback;\
        JsonType json;\
        if(bAll && std::is_base_of<JsonType, ClassType>::value)  this->__object_to_json_impl<JsonType, ClassType>(this, json);\


#define AMO_ENTITY_ARGS_SET2(__key, __type) (amo::json_object_get_set_helper< __type, JsonType >().set(json,  &(this-> __key), #__key));
#define AMO_ENTITY_ARGS_SET(__key) AMO_ENTITY_ARGS_SET2(__key,  amo::json_type_upgrader<std::remove_cv<decltype(this-> __key)>::type> )

// 注册宏 结束
#define AMO_ENTITY_ARGS_SET_END()\
    __on_to_json_impl<JsonType, ClassType>(this, fn_on_to_json_callback, json);\
    return json;\
    }\
    virtual std::string to_string(bool bAll = true) const { return this->to_json(bAll).to_string(); }\

#define AMO_ENTITY_ARGS_SET_EXTEND(SuperClass)\
    {\
        typedef SuperClass SuperType;\
        JsonType other = SuperType ::to_json(bAll);\
        json.join(other);\
    }

#define AMO_ENTITY_ARGS_SET_CALLBACK(func) fn_on_to_json_callback = std::bind(&ClassType::func, this, std::placeholders::_1);

// 从JSON中获取值时的辅助函数
// __json_to_object的作用是将json合并到当前对象，因为有的Class没有完整的提取JSON中的内容，这部分内容可能还有用
// __on_from_json_impl,提供一个回调函数处理现在这些宏无法处理的数据类型
#define AMO_ON_FROMJSON_IMPL()\
    template<typename JsonType_, typename ClassType_>\
    static  typename std::enable_if<std::is_base_of<JsonType_, ClassType_>::value, void>::type __on_from_json_impl( ClassType_ * ptr, std::function<void(const JsonType_ &)>& fn, const JsonType_ & json)  {\
        if (fn) {fn(json);}\
        else {ptr->on_from_json(json);}\
    }\
    template<typename JsonType_, typename ClassType_>\
    static typename std::enable_if<!std::is_base_of<JsonType_, ClassType_>::value, void>::type __on_from_json_impl( ClassType_ * ptr, std::function<void(const JsonType_ &)>& fn, const JsonType_ & json)  {\
        if (fn) {fn(json);}\
    }\
    template<typename JsonType_, typename ClassType_>\
    static typename std::enable_if<std::is_base_of<JsonType_, ClassType_>::value, void>::type __json_to_object( ClassType_ * ptr, const JsonType_& json)  {\
        ptr->join(json);\
    }\
    template<typename JsonType_, typename ClassType_>\
    static typename std::enable_if<!std::is_base_of<JsonType_, ClassType_>::value, void>::type __json_to_object( ClassType_ * ptr, const JsonType_& json)  {\
        return;\
    }

// 将一个json转换成一个对象的流程
#define AMO_ENTITY_ARGS_GET_BEGIN(ClassName)\
    private:\
    AMO_ON_FROMJSON_IMPL()\
    /*callOnFromJson用来防止死循环*/\
    public:\
    static ClassName* from_json(const JsonType& json, ClassName* ptr, bool callOnFromJson = true) {\
        typedef ClassName ClassType; \
        if (ptr == nullptr) ptr = (new ClassType()); \
        __from_json_impl(json, ptr, callOnFromJson); \
        return ptr; \
    }\
    static std::shared_ptr<ClassName> from_json(const JsonType& json, std::shared_ptr<ClassName> ptr = {}, bool callOnFromJson = true) {\
        typedef ClassName ClassType; \
        if (!ptr) ptr.reset(new ClassType()); \
        __from_json_impl(json, ptr.get(), callOnFromJson);\
        return ptr;\
    }\
    static std::shared_ptr<ClassName> fromJson(const JsonType& json, std::shared_ptr<ClassName> ptr = {}, bool callOnFromJson = true) {\
        return from_json(json, ptr, callOnFromJson);\
    }\
    static ClassName* __from_json_impl(const JsonType& json, ClassName* ptr, bool callOnFromJson) {\
        typedef ClassName ClassType; \
        std::function<void(const JsonType&)> fn_on_from_json_callback; \
        __json_to_object<JsonType, ClassType>(ptr, json); \

#define AMO_ENTITY_ARGS_GET_BEGIN_WITH_JSON_CONSTRUCTOR(ClassName)\
    public:\
    ClassName (const JsonType& json): ClassName(){\
        from_json(json, this, true);\
    }\
    AMO_ENTITY_ARGS_GET_BEGIN(ClassName)

#define AMO_ENTITY_ARGS_GET_BEGIN_WITH_DEFAULT_CONSTRUCTOR(ClassName)\
    public:\
    ClassName() {}\
    AMO_ENTITY_ARGS_GET_BEGIN_WITH_JSON_CONSTRUCTOR(ClassName)

#define AMO_ENTITY_ARGS_GET2(__key, __type) ( amo::json_object_get_set_helper< __type, JsonType >().get(json,  ptr-> __key, #__key) );
#define AMO_ENTITY_ARGS_GET(__key) AMO_ENTITY_ARGS_GET2(__key, amo::json_type_upgrader<std::remove_cv<decltype(ptr-> __key)>::type> )

#define AMO_ENTITY_ARGS_GET_END()\
    if(callOnFromJson){  __on_from_json_impl<JsonType, ClassType>(ptr, fn_on_from_json_callback, json);}\
    return ptr;\
    }

#define AMO_ENTITY_ARGS_GET_EXTEND(SuperClass)\
    {\
        typedef SuperClass SuperType;\
        SuperType ::__from_json_impl(json, ptr, false);\
    }

#define AMO_ENTITY_ARGS_GET_CALLBACK(func) fn_on_from_json_callback = std::bind(&ClassType::func, ptr, std::placeholders::_1);


///!@segment update timestamp 20200216211257
#endif //segment_json_object

///!@import end
#endif // IMPORTS_70AAA82F_44D5_45BD_93FC_D6DFFA1B711C
//////////////////////////////////////////////////////////////////////////

_AMO_NAMESPACE_BEGIN

inline std::string to_string(const token_t& val) { return std::to_string(val); }

#pragma region typedef

template<typename MapType, typename ArrayType>
struct json_data_type_traits {
    union DataType {
        ShortString ss;         // 保存json_value_type  Null不需要保存， 直接设置flag就可以了
        int64_t i;              // 保存有符号整型数   Number
        uint64_t u;             // 保存有符号整形数   Number
        double d;               // 保存浮点数         Number
        bool b;                 // 保存boolean        Boolean
        String s;               // 保存string         String
        ObjectData<MapType> o;  // 保存键值对         Object
        ArrayData<ArrayType> a; // 保存数组           Array
    };
};

struct JsonTypeTraits {
    typedef size_t size_type;
    typedef _AMO release_resources<0> release_resources_type;           // 不释放资源
    typedef _AMO json_key_string KeyType;                               // JSON对象的Key类型
    typedef _AMO json_data_object<JsonTypeTraits> ValueType;            // 保存JSON值的类型
    typedef _AMO json_string_parser<ValueType> JsonStringParserType;    // type = json_value_string 的解析类
    typedef _AMO lite_json_string_parser<ValueType> JsonKeyParserType;  // json_key_string 的解析类
    typedef _AMO json_number_parser<ValueType> JsonNumberParserType;    // type = json_value_number 的解析类
    typedef _AMO json_memory_allocator<ValueType> MemoryAllocType;      // 内存分配器类
    typedef std::shared_ptr<_AMO json_memory_allocator<ValueType> > JsonAllocType; // 内存分配器的智能指针类
    typedef _AMO json_string_reader<JsonAllocType> CharReaderType;      // JSON 字符串 字符读取类
    typedef std::pair<const KeyType, ValueType> KeyValuePair;           // JSON 键值对
    typedef _AMO json_container_allocator<KeyValuePair, MemoryAllocType>  MapAllocType; //JsonObject的内存分配器
    typedef _AMO json_container_allocator<ValueType, MemoryAllocType > ArrAllocType;    // JsonArray的内存分配器
    typedef _AMO json_object_container<KeyType, ValueType, std::less<KeyType>, MapAllocType, 16>  MapType; // JsonObject类
    typedef _AMO json_array_container<ValueType, ArrAllocType, 4> ArrayType;     // JsonArray类
    typedef _AMO json_parser< ValueType > JsonParserType;                        // JSON解析类
    typedef _AMO json_data_type_traits<MapType, ArrayType>::DataType DataType;   // 保存JSON各项值的类
    
    // json key 初始化函数，构造KeyType对象时只调用默认构造函数，可以在这个函数中初始化key
    inline void init_key_string(KeyType& key) {}
    // json key string 资源释放函数，销毁key之前会调用该函数，可以在这个函数释放资源
    inline void release_key_string(KeyType& key, const MemoryAllocType* allocator_) {}
    // 查找或插入一个Object对象，不会为要插入的key分配内存，只在JSON字符串解析为Json对象时调用
    inline ValueType& find_or_insert_object_with_move(MapType* map, const KeyType& key) {
        // 1 表示使用快速插入模式，如果使用的是连续内存缓存空间，则不会去比较key是否已经存在
        // return map->find_or_insert_object_with_move<0>(key); // 使用这行代码过滤重复键值对
        return map->find_or_insert_object_with_move<1>(key);
    }
    // 查找或插入一个Object对象，插入时会使用Key的副本进行操作，在Json对象已经构造好后的其他接口调用
    inline ValueType& find_or_insert_object_with_copy(MapType* map, const KeyType& key) {
        return map->find_or_insert_object_with_copy(key);
    }
    // 向JsonArray push_back 一个空对象
    inline ValueType& push_back_object(ArrayType* arr) { return arr->push_back_object(); }
    // 根据key移除一个对象
    inline void erase(MapType* map, const KeyType& key, JsonAllocType allocator_) { map->erase(key); }
};

using json = basic_json<json_data_object<JsonTypeTraits  >  >;

// 下面几个宏里面的内容基本上没什么用
// 精简模式下的JSON,实际解析速度并没有大幅度的提升
#ifdef AMO_USE_LITE_JSON
struct LiteJsonTypeTraits {
    typedef size_t size_type;
    typedef _AMO release_resources<0> release_resources_type;          // 不释放资源
    typedef _AMO json_key_string KeyType;
    typedef _AMO json_data_object<LiteJsonTypeTraits> ValueType;
    typedef _AMO lite_json_string_parser<ValueType> JsonStringParserType;
    typedef _AMO lite_json_string_parser<ValueType> JsonKeyParserType;
    typedef _AMO json_number_parser<ValueType> JsonNumberParserType;
    typedef _AMO json_memory_allocator<ValueType> MemoryAllocType;
    typedef std::shared_ptr<_AMO json_memory_allocator<ValueType> > JsonAllocType;
    typedef _AMO json_string_reader<JsonAllocType> CharReaderType;
    typedef _AMO json_container_allocator<std::pair<const KeyType, ValueType>, MemoryAllocType > MapAllocType;
    typedef _AMO json_container_allocator<ValueType, MemoryAllocType > ArrAllocType;
    typedef _AMO json_object_container<KeyType, ValueType, std::less<KeyType>, MapAllocType, 16> MapType;
    typedef _AMO json_array_container<ValueType, ArrAllocType, 4 > ArrayType;
    typedef _AMO json_parser< ValueType > JsonParserType;
    typedef _AMO json_data_type_traits<MapType, ArrayType>::DataType DataType;
    typedef _AMO basic_json<_AMO json_data_object<LiteJsonTypeTraits  >  > JsonType;
    inline void init_key_string(KeyType& key) {}
    inline void release_key_string(KeyType& key, const MemoryAllocType* allocator_) {}
    inline ValueType& find_or_insert_object_with_move(MapType* map, const KeyType& key) {
        return map->find_or_insert_object_with_move<1>(key);
    }
    inline ValueType& find_or_insert_object_with_copy(MapType* map, const KeyType& key) {
        return map->find_or_insert_object_with_copy(key);
    }
    inline ValueType& push_back_object(ArrayType* arr) { return arr->push_back_object(); }
    inline void erase(MapType* map, const KeyType& key, JsonAllocType allocator_) { map->erase(key); }
};

namespace lite {
    using json = basic_json<json_data_object<LiteJsonTypeTraits  >  >;
}
#endif

// 大文件可能会提升一些解析速度
#ifdef AMO_USE_STREAM_JSON
struct StreamJsonTypeTraits {
    typedef size_t size_type;
    typedef _AMO release_resources<1> release_resources_type;          // 释放资源,实际上现在没有释放资源
    typedef _AMO json_key_string KeyType;
    typedef _AMO json_data_object<StreamJsonTypeTraits> ValueType;
    typedef _AMO json_string_parser<ValueType> JsonStringParserType;
    typedef _AMO lite_json_string_parser<ValueType> JsonKeyParserType;
    typedef _AMO json_number_parser<ValueType> JsonNumberParserType;
    typedef _AMO json_memory_allocator<ValueType> MemoryAllocType;
    typedef std::shared_ptr<_AMO json_memory_allocator<ValueType> > JsonAllocType;
    // 在解析大文件时，如果磁盘IO过低，那么可以使用json_stream_reader来提升解析速度
    typedef _AMO json_stream_reader<JsonAllocType> CharReaderType;
    typedef _AMO json_container_allocator<std::pair<const KeyType, ValueType>, MemoryAllocType > MapAllocType;
    typedef _AMO json_container_allocator<ValueType, MemoryAllocType> ArrAllocType;
    typedef _AMO json_object_container<KeyType, ValueType, std::less<KeyType>, MapAllocType, 16> MapType;
    typedef _AMO json_array_container< ValueType, ArrAllocType, 4> ArrayType;
    typedef _AMO json_parser< ValueType > JsonParserType;
    typedef _AMO json_data_type_traits<MapType, ArrayType>::DataType DataType;
    
    inline void init_key_string(KeyType& key) { }
    inline void release_key_string(KeyType& key, const MemoryAllocType* allocator_) { }
    inline ValueType& find_or_insert_object_with_move(MapType* map, const KeyType& key) {
        return map->find_or_insert_object_with_move<0>(key);
    }
    inline ValueType& find_or_insert_object_with_copy(MapType* map, const KeyType& key) {
        return map->find_or_insert_object_with_copy(key);
    }
    inline ValueType& push_back_object(ArrayType* arr) { return arr->push_back_object(); }
    inline void erase(MapType* map, const KeyType& key, JsonAllocType allocator_) { map->erase(key); }
};

namespace stream {
    using json = _AMO basic_json<_AMO json_data_object<StreamJsonTypeTraits > >;
}
#endif

// 只做演示用，各方便性能都比较差
#ifdef AMO_USE_STD_JSON
struct StdJsonTypeTraits {
    typedef size_t size_type;
    typedef _AMO release_resources<0> release_resources_type;          // 不释放资源
    typedef std::string KeyType;
    typedef _AMO json_data_object<StdJsonTypeTraits> ValueType;
    typedef _AMO json_string_parser<ValueType> JsonStringParserType;
    typedef _AMO lite_json_string_parser<ValueType> JsonKeyParserType;
    typedef _AMO json_number_parser<ValueType> JsonNumberParserType;
    typedef _AMO json_memory_allocator<ValueType> MemoryAllocType;
    typedef std::shared_ptr<_AMO json_memory_allocator<ValueType> > JsonAllocType;
    typedef _AMO json_stream_reader<JsonAllocType> CharReaderType;
    typedef _AMO json_container_allocator<std::pair<const KeyType, ValueType>, MemoryAllocType > MapAllocType;
    typedef _AMO json_container_allocator<ValueType, MemoryAllocType > ArrAllocType;
    typedef std::map<KeyType, ValueType, std::less<KeyType>, MapAllocType > MapType;
    typedef std::vector<ValueType, ArrAllocType > ArrayType;
    typedef _AMO json_parser< ValueType > JsonParserType;
    typedef _AMO json_data_type_traits<MapType, ArrayType>::DataType DataType;
    
    inline void init_key_string(KeyType& key) {}
    inline void release_key_string(KeyType& key, const MemoryAllocType* allocator_) {}
    inline ValueType& find_or_insert_object_with_move(MapType* map, const KeyType& key) {
        auto iter = map->find(key);
        if (iter == map->end()) {
            iter = map->insert({ key, ValueType() }).first;
        }
        return iter->second;
    }
    
    inline ValueType& find_or_insert_object_with_copy(MapType* map, const KeyType& key) {
        return find_or_insert_object_with_move(map, key);
    }
    
    inline ValueType& push_back_object(ArrayType* arr) {
        arr->push_back(ValueType());
        return *arr->rbegin();
    }
    
    inline void erase(MapType* map, const KeyType& key, JsonAllocType allocator_) {
        auto iter = map->find(key);
        if (iter != map->end()) {
            iter->second.release(allocator_.get());
            map->erase(iter);
        }
    }
};

namespace stl {
    using json = _AMO basic_json<_AMO json_data_object<StdJsonTypeTraits > >;
}
#endif

#pragma endregion

_AMO_NAMESPACE_END

// 使用字面常量字符串
inline _AMO string_reader operator""	_json_(const char* str, size_t	len) {
    return  _AMO string_reader(str, len);
}


#endif //JSON_JSON_18852008_BC51_457D_91D6_9A25CCA25F7C_HPP__
