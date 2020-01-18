//
//  BRInt.h
//
//  Created by Aaron Voisine on 8/16/15.
//  Copyright (c) 2015 breadwallet LLC.
//  Update by Roshii on 4/1/18.
//  Copyright (c) 2018 ravencoin core team
//

#ifndef Int_h
#define Int_h

#include <inttypes.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

// large integers

typedef union {
    uint8_t u8[128/8];
    uint16_t u16[128/16];
    uint32_t u32[128/32];
    uint64_t u64[128/64];
} UInt128;

typedef union {
    uint8_t u8[160/8];
    uint16_t u16[160/16];
    uint32_t u32[160/32];
} UInt160;

typedef union {
    uint8_t u8[256/8];
    uint16_t u16[256/16];
    uint32_t u32[256/32];
    uint64_t u64[256/64];
} UInt256;

typedef union {
    uint8_t u8[512/8];
    uint16_t u16[512/16];
    uint32_t u32[512/32];
    uint64_t u64[512/64];
} UInt512;

inline static int UInt128Eq(UInt128 a, UInt128 b)
{
    return (a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1]);
}

inline static int UInt160Eq(UInt160 a, UInt160 b)
{
    return (a.u32[0] == b.u32[0] && a.u32[1] == b.u32[1] && a.u32[2] == b.u32[2] && a.u32[3] == b.u32[3] &&
            a.u32[4] == b.u32[4]);
}

inline static int UInt256Eq(UInt256 a, UInt256 b)
{
    return (a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1] && a.u64[2] == b.u64[2] && a.u64[3] == b.u64[3]);
}

inline static int UInt256SupEq(UInt256 a, UInt256 b)
{
    return (a.u64[3] > b.u64[3]) || ((a.u64[3] == b.u64[3]) && ((a.u64[2] > b.u64[2]) ||
                                                                ((a.u64[2] == b.u64[2]) && ((a.u64[1] > b.u64[1]) || ((a.u64[1] == b.u64[1]) && (a.u64[0] >= b.u64[0]))))));
}

inline static int UInt512Eq(UInt512 a, UInt512 b)
{
    return (a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1] && a.u64[2] == b.u64[2] && a.u64[3] == b.u64[3] &&
            a.u64[4] == b.u64[4] && a.u64[5] == b.u64[5] && a.u64[6] == b.u64[6] && a.u64[7] == b.u64[7]);
}

inline static int UInt128IsZero(UInt128 u)
{
    return ((u.u64[0] | u.u64[1]) == 0);
}

inline static int UInt160IsZero(UInt160 u)
{
    return ((u.u32[0] | u.u32[1] | u.u32[2] | u.u32[3] | u.u32[4]) == 0);
}

inline static int UInt256IsZero(UInt256 u)
{
    return ((u.u64[0] | u.u64[1] | u.u64[2] | u.u64[3]) == 0);
}

inline static int UInt512IsZero(UInt512 u)
{
    return ((u.u64[0] | u.u64[1] | u.u64[2] | u.u64[3] | u.u64[4] | u.u64[5] | u.u64[6] | u.u64[7]) == 0);
}

inline static UInt256 UInt256Reverse(UInt256 u)
{
    return ((UInt256) { .u8 = { u.u8[31], u.u8[30], u.u8[29], u.u8[28], u.u8[27], u.u8[26], u.u8[25], u.u8[24],
                                u.u8[23], u.u8[22], u.u8[21], u.u8[20], u.u8[19], u.u8[18], u.u8[17], u.u8[16],
                                u.u8[15], u.u8[14], u.u8[13], u.u8[12], u.u8[11], u.u8[10], u.u8[ 9], u.u8[ 8],
                                u.u8[ 7], u.u8[ 6], u.u8[5],  u.u8[ 4], u.u8[ 3], u.u8[ 2], u.u8[ 1], u.u8[ 0] } });
}

#define UINT128_ZERO ((UInt128) { .u64 = { 0, 0 } })
#define UINT160_ZERO ((UInt160) { .u32 = { 0, 0, 0, 0, 0 } })
#define UINT256_ZERO ((UInt256) { .u64 = { 0, 0, 0, 0 } })
#define UINT256_MAX ((UInt256) { .u64 = { 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF } })
#define UINT512_ZERO ((UInt512) { .u64 = { 0, 0, 0, 0, 0, 0, 0, 0 } })

// hex encoding/decoding

#define u256_hex_encode(u) ((const char[]) {\
    _hexc((u).u8[ 0] >> 4), _hexc((u).u8[ 0]), _hexc((u).u8[ 1] >> 4), _hexc((u).u8[ 1]),\
    _hexc((u).u8[ 2] >> 4), _hexc((u).u8[ 2]), _hexc((u).u8[ 3] >> 4), _hexc((u).u8[ 3]),\
    _hexc((u).u8[ 4] >> 4), _hexc((u).u8[ 4]), _hexc((u).u8[ 5] >> 4), _hexc((u).u8[ 5]),\
    _hexc((u).u8[ 6] >> 4), _hexc((u).u8[ 6]), _hexc((u).u8[ 7] >> 4), _hexc((u).u8[ 7]),\
    _hexc((u).u8[ 8] >> 4), _hexc((u).u8[ 8]), _hexc((u).u8[ 9] >> 4), _hexc((u).u8[ 9]),\
    _hexc((u).u8[10] >> 4), _hexc((u).u8[10]), _hexc((u).u8[11] >> 4), _hexc((u).u8[11]),\
    _hexc((u).u8[12] >> 4), _hexc((u).u8[12]), _hexc((u).u8[13] >> 4), _hexc((u).u8[13]),\
    _hexc((u).u8[14] >> 4), _hexc((u).u8[14]), _hexc((u).u8[15] >> 4), _hexc((u).u8[15]),\
    _hexc((u).u8[16] >> 4), _hexc((u).u8[16]), _hexc((u).u8[17] >> 4), _hexc((u).u8[17]),\
    _hexc((u).u8[18] >> 4), _hexc((u).u8[18]), _hexc((u).u8[19] >> 4), _hexc((u).u8[19]),\
    _hexc((u).u8[20] >> 4), _hexc((u).u8[20]), _hexc((u).u8[21] >> 4), _hexc((u).u8[21]),\
    _hexc((u).u8[22] >> 4), _hexc((u).u8[22]), _hexc((u).u8[23] >> 4), _hexc((u).u8[23]),\
    _hexc((u).u8[24] >> 4), _hexc((u).u8[24]), _hexc((u).u8[25] >> 4), _hexc((u).u8[25]),\
    _hexc((u).u8[26] >> 4), _hexc((u).u8[26]), _hexc((u).u8[27] >> 4), _hexc((u).u8[27]),\
    _hexc((u).u8[28] >> 4), _hexc((u).u8[28]), _hexc((u).u8[29] >> 4), _hexc((u).u8[29]),\
    _hexc((u).u8[30] >> 4), _hexc((u).u8[30]), _hexc((u).u8[31] >> 4), _hexc((u).u8[31]), '\0' })

#define u256_hex_decode(s) ((UInt256) { .u8 = {\
    (_hexu((s)[ 0]) << 4) | _hexu((s)[ 1]), (_hexu((s)[ 2]) << 4) | _hexu((s)[ 3]),\
    (_hexu((s)[ 4]) << 4) | _hexu((s)[ 5]), (_hexu((s)[ 6]) << 4) | _hexu((s)[ 7]),\
    (_hexu((s)[ 8]) << 4) | _hexu((s)[ 9]), (_hexu((s)[10]) << 4) | _hexu((s)[11]),\
    (_hexu((s)[12]) << 4) | _hexu((s)[13]), (_hexu((s)[14]) << 4) | _hexu((s)[15]),\
    (_hexu((s)[16]) << 4) | _hexu((s)[17]), (_hexu((s)[18]) << 4) | _hexu((s)[19]),\
    (_hexu((s)[20]) << 4) | _hexu((s)[21]), (_hexu((s)[22]) << 4) | _hexu((s)[23]),\
    (_hexu((s)[24]) << 4) | _hexu((s)[25]), (_hexu((s)[26]) << 4) | _hexu((s)[27]),\
    (_hexu((s)[28]) << 4) | _hexu((s)[29]), (_hexu((s)[30]) << 4) | _hexu((s)[31]),\
    (_hexu((s)[32]) << 4) | _hexu((s)[33]), (_hexu((s)[34]) << 4) | _hexu((s)[35]),\
    (_hexu((s)[36]) << 4) | _hexu((s)[37]), (_hexu((s)[38]) << 4) | _hexu((s)[39]),\
    (_hexu((s)[40]) << 4) | _hexu((s)[41]), (_hexu((s)[42]) << 4) | _hexu((s)[43]),\
    (_hexu((s)[44]) << 4) | _hexu((s)[45]), (_hexu((s)[46]) << 4) | _hexu((s)[47]),\
    (_hexu((s)[48]) << 4) | _hexu((s)[49]), (_hexu((s)[50]) << 4) | _hexu((s)[51]),\
    (_hexu((s)[52]) << 4) | _hexu((s)[53]), (_hexu((s)[54]) << 4) | _hexu((s)[55]),\
    (_hexu((s)[56]) << 4) | _hexu((s)[57]), (_hexu((s)[58]) << 4) | _hexu((s)[59]),\
    (_hexu((s)[60]) << 4) | _hexu((s)[61]), (_hexu((s)[62]) << 4) | _hexu((s)[63]) } })

#define _hexc(u) (((u) & 0x0f) + ((((u) & 0x0f) <= 9) ? '0' : 'a' - 0x0a))
#define _hexu(c) (((c) >= '0' && (c) <= '9') ? (c) - '0' : ((c) >= 'a' && (c) <= 'f') ? (c) - ('a' - 0x0a) :\
                  ((c) >= 'A' && (c) <= 'F') ? (c) - ('A' - 0x0a) : 0)

// unaligned memory access helpers

inline static void UInt16SetBE(void *b2, uint16_t u)
{
    *(union _u16 { uint8_t u8[16/8]; } *)b2 = (union _u16) { (u >> 8) & 0xff, u & 0xff };
}

inline static void UInt16SetLE(void *b2, uint16_t u)
{
    *(union _u16 { uint8_t u8[16/8]; } *)b2 = (union _u16) { u & 0xff, (u >> 8) & 0xff };
}

inline static void UInt32SetBE(void *b4, uint32_t u)
{
    *(union _u32 { uint8_t u8[32/8]; } *)b4 =
        (union _u32) { (u >> 24) & 0xff, (u >> 16) & 0xff, (u >> 8) & 0xff, u & 0xff };
}

inline static void UInt32SetLE(void *b4, uint32_t u)
{
    *(union _u32 { uint8_t u8[32/8]; } *)b4 =
        (union _u32) { u & 0xff, (u >> 8) & 0xff, (u >> 16) & 0xff, (u >> 24) & 0xff };
}

inline static void UInt64SetBE(void *b8, uint64_t u)
{
    *(union _u64 { uint8_t u8[64/8]; } *)b8 =
        (union _u64) { (u >> 56) & 0xff, (u >> 48) & 0xff, (u >> 40) & 0xff, (u >> 32) & 0xff,
                       (u >> 24) & 0xff, (u >> 16) & 0xff, (u >> 8) & 0xff, u & 0xff };
}

inline static void UInt64SetLE(void *b8, uint64_t u)
{
    *(union _u64 { uint8_t u8[64/8]; } *)b8 =
        (union _u64) { u & 0xff, (u >> 8) & 0xff, (u >> 16) & 0xff, (u >> 24) & 0xff,
                       (u >> 32) & 0xff, (u >> 40) & 0xff, (u >> 48) & 0xff, (u >> 56) & 0xff };
}

inline static void UInt128Set(void *b16, UInt128 u)
{
    *(union _u128 { uint8_t u8[128/8]; } *)b16 =
        (union _u128) { u.u8[0], u.u8[1], u.u8[2],  u.u8[3],  u.u8[4],  u.u8[5],  u.u8[6],  u.u8[7],
                        u.u8[8], u.u8[9], u.u8[10], u.u8[11], u.u8[12], u.u8[13], u.u8[14], u.u8[15] };
}

inline static void UInt160Set(void *b20, UInt160 u)
{
    *(union _u160 { uint8_t u8[160/8]; } *)b20 =
        (union _u160) { u.u8[0],  u.u8[1],  u.u8[2],  u.u8[3],  u.u8[4],  u.u8[5],  u.u8[6],  u.u8[7],
                        u.u8[8],  u.u8[9],  u.u8[10], u.u8[11], u.u8[12], u.u8[13], u.u8[14], u.u8[15],
                        u.u8[16], u.u8[17], u.u8[18], u.u8[19] };
}

inline static void UInt256Set(void *b32, UInt256 u)
{
    *(union _u256 { uint8_t u8[256/8]; } *)b32 =
        (union _u256) { u.u8[0],  u.u8[1],  u.u8[2],  u.u8[3],  u.u8[4],  u.u8[5],  u.u8[6],  u.u8[7],
                        u.u8[8],  u.u8[9],  u.u8[10], u.u8[11], u.u8[12], u.u8[13], u.u8[14], u.u8[15],
                        u.u8[16], u.u8[17], u.u8[18], u.u8[19], u.u8[20], u.u8[21], u.u8[22], u.u8[23],
                        u.u8[24], u.u8[25], u.u8[26], u.u8[27], u.u8[28], u.u8[29], u.u8[30], u.u8[31] };
}

inline static uint16_t UInt16GetBE(const void *b2)
{
    return (((uint16_t)((const uint8_t *)b2)[0] << 8) | ((uint16_t)((const uint8_t *)b2)[1]));
}

inline static uint16_t UInt16GetLE(const void *b2)
{
    return (((uint16_t)((const uint8_t *)b2)[1] << 8) | ((uint16_t)((const uint8_t *)b2)[0]));
}

inline static uint32_t UInt32GetBE(const void *b4)
{
    return (((uint32_t)((const uint8_t *)b4)[0] << 24) | ((uint32_t)((const uint8_t *)b4)[1] << 16) |
            ((uint32_t)((const uint8_t *)b4)[2] << 8)  | ((uint32_t)((const uint8_t *)b4)[3]));
}

inline static uint32_t UInt32GetLE(const void *b4)
{
    return (((uint32_t)((const uint8_t *)b4)[3] << 24) | ((uint32_t)((const uint8_t *)b4)[2] << 16) |
            ((uint32_t)((const uint8_t *)b4)[1] << 8)  | ((uint32_t)((const uint8_t *)b4)[0]));
}

inline static uint64_t UInt64GetBE(const void *b8)
{
    return (((uint64_t)((const uint8_t *)b8)[0] << 56) | ((uint64_t)((const uint8_t *)b8)[1] << 48) |
            ((uint64_t)((const uint8_t *)b8)[2] << 40) | ((uint64_t)((const uint8_t *)b8)[3] << 32) |
            ((uint64_t)((const uint8_t *)b8)[4] << 24) | ((uint64_t)((const uint8_t *)b8)[5] << 16) |
            ((uint64_t)((const uint8_t *)b8)[6] << 8)  | ((uint64_t)((const uint8_t *)b8)[7]));
}

inline static uint64_t UInt64GetLE(const void *b8)
{
    return (((uint64_t)((const uint8_t *)b8)[7] << 56) | ((uint64_t)((const uint8_t *)b8)[6] << 48) |
            ((uint64_t)((const uint8_t *)b8)[5] << 40) | ((uint64_t)((const uint8_t *)b8)[4] << 32) |
            ((uint64_t)((const uint8_t *)b8)[3] << 24) | ((uint64_t)((const uint8_t *)b8)[2] << 16) |
            ((uint64_t)((const uint8_t *)b8)[1] << 8)  | ((uint64_t)((const uint8_t *)b8)[0]));
}

inline static UInt128 UInt128Get(const void *b16)
{
    return (UInt128) { .u8 = {
        ((const uint8_t *)b16)[0],  ((const uint8_t *)b16)[1],  ((const uint8_t *)b16)[2],  ((const uint8_t *)b16)[3],
        ((const uint8_t *)b16)[4],  ((const uint8_t *)b16)[5],  ((const uint8_t *)b16)[6],  ((const uint8_t *)b16)[7],
        ((const uint8_t *)b16)[8],  ((const uint8_t *)b16)[9],  ((const uint8_t *)b16)[10], ((const uint8_t *)b16)[11],
        ((const uint8_t *)b16)[12], ((const uint8_t *)b16)[13], ((const uint8_t *)b16)[14], ((const uint8_t *)b16)[15]
    } };
}

inline static UInt160 UInt160Get(const void *b20)
{
    return (UInt160) { .u8 = {
        ((const uint8_t *)b20)[0],  ((const uint8_t *)b20)[1],  ((const uint8_t *)b20)[2],  ((const uint8_t *)b20)[3],
        ((const uint8_t *)b20)[4],  ((const uint8_t *)b20)[5],  ((const uint8_t *)b20)[6],  ((const uint8_t *)b20)[7],
        ((const uint8_t *)b20)[8],  ((const uint8_t *)b20)[9],  ((const uint8_t *)b20)[10], ((const uint8_t *)b20)[11],
        ((const uint8_t *)b20)[12], ((const uint8_t *)b20)[13], ((const uint8_t *)b20)[14], ((const uint8_t *)b20)[15],
        ((const uint8_t *)b20)[16], ((const uint8_t *)b20)[17], ((const uint8_t *)b20)[18], ((const uint8_t *)b20)[19]
    } };
}

inline static UInt256 UInt256Get(const void *b32)
{
    return (UInt256) { .u8 = {
        ((const uint8_t *)b32)[0],  ((const uint8_t *)b32)[1],  ((const uint8_t *)b32)[2],  ((const uint8_t *)b32)[3],
        ((const uint8_t *)b32)[4],  ((const uint8_t *)b32)[5],  ((const uint8_t *)b32)[6],  ((const uint8_t *)b32)[7],
        ((const uint8_t *)b32)[8],  ((const uint8_t *)b32)[9],  ((const uint8_t *)b32)[10], ((const uint8_t *)b32)[11],
        ((const uint8_t *)b32)[12], ((const uint8_t *)b32)[13], ((const uint8_t *)b32)[14], ((const uint8_t *)b32)[15],
        ((const uint8_t *)b32)[16], ((const uint8_t *)b32)[17], ((const uint8_t *)b32)[18], ((const uint8_t *)b32)[19],
        ((const uint8_t *)b32)[20], ((const uint8_t *)b32)[21], ((const uint8_t *)b32)[22], ((const uint8_t *)b32)[23],
        ((const uint8_t *)b32)[24], ((const uint8_t *)b32)[25], ((const uint8_t *)b32)[26], ((const uint8_t *)b32)[27],
        ((const uint8_t *)b32)[28], ((const uint8_t *)b32)[29], ((const uint8_t *)b32)[30], ((const uint8_t *)b32)[31]
    } };
}

//UInt256 functions
inline static uint8_t bits(UInt256 number)
{
    for (int pos = 8 - 1; pos >= 0; pos--) {
        if (number.u32[pos]) {
            for (int bits = 31; bits > 0; bits--) {
                if (number.u32[pos] & 1 << bits)
                    return 32 * pos + bits + 1;
            }
            return 32 * pos + 1;
        }
    }
    return 0;
}

inline static UInt256 add(UInt256 a, UInt256 b) {
    uint64_t carry = 0;
    UInt256 r = UINT256_ZERO;
    for (int i = 0; i < 8; i++) {
        uint64_t sum = (uint64_t)a.u32[i] + (uint64_t)b.u32[i] + carry;
        r.u32[i] = (uint32_t)sum;
        carry = sum >> 32;
    }
    return r;
}

inline static UInt256 addOne(UInt256 a) {
    UInt256 r = ((UInt256) { .u64 = { 1, 0, 0, 0 } });
    return add(a, r);
}

inline static UInt256 neg(UInt256 a) {
    UInt256 r = UINT256_ZERO;
    for (int i = 0; i < 4; i++) {
        r.u64[i] = ~a.u64[i];
    }
    return r;
}

inline static UInt256 subtract(UInt256 a, UInt256 b) {
    return add(a,addOne(neg(b)));
}

inline static UInt256 shiftLeft(UInt256 a, uint8_t bits) {
    UInt256 r = UINT256_ZERO;
    int k = bits / 64;
    bits = bits % 64;
    for (int i = 0; i < 4; i++) {
        if (i + k + 1 < 4 && bits != 0)
            r.u64[i + k + 1] |= (a.u64[i] >> (64 - bits));
        if (i + k < 4)
            r.u64[i + k] |= (a.u64[i] << bits);
    }
    return r;
}

inline static UInt256 shiftRight(UInt256 a, uint8_t bits) {
    UInt256 r = UINT256_ZERO;
    int k = bits / 64;
    bits = bits % 64;
    for (int i = 0; i < 4; i++) {
        if (i - k - 1 >= 0 && bits != 0)
            r.u64[i - k - 1] |= (a.u64[i] << (64 - bits));
        if (i - k >= 0)
            r.u64[i - k] |= (a.u64[i] >> bits);
    }
    return r;
}

inline static UInt256 divide (UInt256 a,UInt256 b)
{
    UInt256 div = b;     // make a copy, so we can shift.
    UInt256 num = a;     // make a copy, so we can subtract.
    UInt256 r = UINT256_ZERO;                  // the quotient.
    int num_bits = bits(num);
    int div_bits = bits(div);
    assert (div_bits != 0);
    if (div_bits > num_bits) // the result is certainly 0.
        return r;
    int shift = num_bits - div_bits;
    div = shiftLeft(div, shift); // shift so that div and nun align.
    while (shift >= 0) {
        if (UInt256SupEq(num,div)) {
            num = subtract(num,div);
            r.u32[shift / 32] |= (1 << (shift & 31)); // set a bit of the result.
        }
        div = shiftRight(div, 1); // shift back.
        shift--;
    }
    // num now contains the remainder of the division.
    return r;
}

inline static UInt256 multiplyThis32 (UInt256 a,uint32_t b)
{
    uint64_t carry = 0;
    for (int i = 0; i < 8; i++) {
        uint64_t n = carry + (uint64_t)b * (uint64_t)a.u32[i];
        a.u32[i] = n & 0xffffffff;
        carry = n >> 32;
    }
    return a;
}

inline static UInt256 setCompact(int32_t nCompact)
{
    int nSize = nCompact >> 24;
    UInt256 nWord = UINT256_ZERO;
    nWord.u32[0] = nCompact & 0x007fffff;
    if (nSize <= 3) {
        nWord = shiftRight(nWord, 8 * (3 - nSize));
    } else {
        nWord = shiftLeft(nWord, 8 * (nSize - 3));
    }
    return nWord;
}

inline static uint32_t getCompact(UInt256 number)
{
    int nSize = (bits(number) + 7) / 8;
    uint32_t nCompact = 0;
    if (nSize <= 3) {
        nCompact = number.u32[0] << 8 * (3 - nSize);
    } else {
        UInt256 bn = shiftRight(number, 8 * (nSize - 3));
        nCompact = bn.u32[0];
    }
    // The 0x00800000 bit denotes the sign.
    // Thus, if it is already set, divide the mantissa by 256 and increase the exponent.
    if (nCompact & 0x00800000) {
        nCompact >>= 8;
        nSize++;
    }
    assert((nCompact & ~0x007fffff) == 0);
    assert(nSize < 256);
    nCompact |= nSize << 24;
    return nCompact;
}

#ifdef __cplusplus
}
#endif

#endif // BRInt_h
