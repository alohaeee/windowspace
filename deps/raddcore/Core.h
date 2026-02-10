// Copyright (c) Epic Games Tools
// Licensed under the MIT license (https://opensource.org/license/mit/)
#ifndef CORE_H
#define CORE_H


////////////////////////////////
//~ rjf: Foreign Includes

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#define global static
#define internal static
#define local static

#if defined(__clang__)

# define CORE_COMPILER_CLANG 1

# if defined(__APPLE__) && defined(__MACH__)
#  define CORE_OS_MAC 1
# elif defined(__gnu_linux__)
#  define CORE_OS_LINUX 1
# elif defined(_WIN32)
#  define CORE_OS_WINDOWS 1
# else
#  error This compiler/platform combo is not supported yet
# endif

# if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#  define CORE_ARCH_X64 1
# elif defined(i386) || defined(__i386) || defined(__i386__)
#  define CORE_ARCH_X86 1
# elif defined(__aarch64__)
#  define CORE_ARCH_ARM64 1
# elif defined(__arm__)
#  define CORE_ARCH_ARM32 1
# else
#  error architecture not supported yet
# endif

#elif defined(_MSC_VER)

# define CORE_COMPILER_MSVC 1

# if defined(_WIN32)
#  define CORE_OS_WINDOWS 1
# else
#  error This compiler/platform combo is not supported yet
# endif

# if defined(_M_AMD64)
#  define CORE_ARCH_X64 1
# elif defined(_M_IX86)
#  define CORE_ARCH_X86 1
# elif defined(_M_ARM64)
#  define CORE_ARCH_ARM64 1
# elif defined(_M_ARM)
#  define CORE_ARCH_ARM32 1
# else
#  error architecture not supported yet
# endif

# if _MSC_VER >= 1920
#  define CORE_COMPILER_CL_YEAR 2019
# elif _MSC_VER >= 1910
#  define CORE_COMPILER_CL_YEAR 2017
# elif _MSC_VER >= 1900
#  define CORE_COMPILER_CL_YEAR 2015
# elif _MSC_VER >= 1800
#  define CORE_COMPILER_CL_YEAR 2013
# elif _MSC_VER >= 1700
#  define CORE_COMPILER_CL_YEAR 2012
# elif _MSC_VER >= 1600
#  define CORE_COMPILER_CL_YEAR 2010
# elif _MSC_VER >= 1500
#  define CORE_COMPILER_CL_YEAR 2008
# elif _MSC_VER >= 1400
#  define CORE_COMPILER_CL_YEAR 2005
# else
#  define CORE_COMPILER_CL_YEAR 0
# endif

#elif defined(__GNUC__) || defined(__GNUG__)

# define CORE_COMPILER_GCC 1

# if defined(__gnu_linux__)
#  define CORE_OS_LINUX 1
# else
#  error This compiler/platform combo is not supported yet
# endif

# if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#  define CORE_ARCH_X64 1
# elif defined(i386) || defined(__i386) || defined(__i386__)
#  define CORE_ARCH_X86 1
# elif defined(__aarch64__)
#  define CORE_ARCH_ARM64 1
# elif defined(__arm__)
#  define CORE_ARCH_ARM32 1
# else
#  error architecture not supported yet
# endif

#else
# error This compiler is not supported yet
#endif

#if defined(CORE_ARCH_X64)
# define CORE_ARCH_64BIT 1
#elif defined(CORE_ARCH_X86)
# define CORE_ARCH_32BIT 1
#endif

#if defined(__cplusplus)
# define CORE_LANG_CPP 1

// We can't get this 100% correct thanks to Microsoft's compiler.
// So this check lets us pre-define CORE_CPP_VERSION if we have to.
# if !defined(CORE_CPP_VERSION)
#  if defined(CORE_COMPILER_MSVC)
// CL is annoying and didn't update __cplusplus over time
// If it is available _MSVC_LANG serves the same role
#   if defined(_MSVC_LANG)
#    if _MSVC_LANG <= 199711L
#     define CORE_CPP_VERSION 98
#    elif _MSVC_LANG <= 201103L
#     define CORE_CPP_VERSION 11
#    elif _MSVC_LANG <= 201402L
#     define CORE_CPP_VERSION 14
#    elif _MSVC_LANG <= 201703L
#     define CORE_CPP_VERSION 17
#    elif _MSVC_LANG <= 202002L
#     define CORE_CPP_VERSION 20
#    else
#     define CORE_CPP_VERSION 23
#    endif
// If we don't have _MSVC_LANG we can guess from the compiler version
#   else
#    if CORE_COMPILER_MSVC_YEAR <= 2010
#     define CORE_CPP_VERSION 98
#    elif CORE_COMPILER_MSVC_YEAR <= 2015
#     define CORE_CPP_VERSION 11
#    else
#     define CORE_CPP_VERSION 17
#    endif
#   endif
#  else
// Other compilers use __cplusplus correctly
#   if __cplusplus <= 199711L
#    define CORE_CPP_VERSION 98
#   elif __cplusplus <= 201103L
#    define CORE_CPP_VERSION 11
#   elif __cplusplus <= 201402L
#    define CORE_CPP_VERSION 14
#   elif __cplusplus <= 201703L
#    define CORE_CPP_VERSION 17
#   elif __cplusplus <= 202002L
#    define CORE_CPP_VERSION 20
#   else
#    define CORE_CPP_VERSION 23
#   endif
#  endif
# endif

#else
# define CORE_LANG_C 1
#endif

// zeroify

#if !defined(CORE_ARCH_32BIT)
# define CORE_ARCH_32BIT 0
#endif
#if !defined(CORE_ARCH_64BIT)
# define CORE_ARCH_64BIT 0
#endif
#if !defined(CORE_ARCH_X64)
# define CORE_ARCH_X64 0
#endif
#if !defined(CORE_ARCH_X86)
# define CORE_ARCH_X86 0
#endif
#if !defined(CORE_ARCH_ARM64)
# define CORE_ARCH_ARM64 0
#endif
#if !defined(CORE_ARCH_ARM32)
# define CORE_ARCH_ARM32 0
#endif
#if !defined(CORE_COMPILER_MSVC)
# define CORE_COMPILER_MSVC 0
#endif
#if !defined(CORE_COMPILER_GCC)
# define CORE_COMPILER_GCC 0
#endif
#if !defined(CORE_COMPILER_CLANG)
# define CORE_COMPILER_CLANG 0
#endif
#if !defined(CORE_OS_WINDOWS)
# define CORE_OS_WINDOWS 0
#endif
#if !defined(CORE_OS_LINUX)
# define CORE_OS_LINUX 0
#endif
#if !defined(CORE_OS_MAC)
# define CORE_OS_MAC 0
#endif
#if !defined(CORE_LANG_C)
# define CORE_LANG_C 0
#endif
#if !defined(CORE_LANG_CPP)
# define CORE_LANG_CPP 0
#endif
#if !defined(CORE_CPP_VERSION)
# define CORE_CPP_VERSION 0
#endif

#if CORE_LANG_CPP
# define CORE_ZERO_STRUCT {}
#else
# define CORE_ZERO_STRUCT {0}
#endif

#if CORE_LANG_C
# define CORE_C_LINKAGE_BEGIN
# define CORE_C_LINKAGE_END
#else
# define CORE_C_LINKAGE_BEGIN extern "C"{
# define CORE_C_LINKAGE_END }
#endif

#if CORE_COMPILER_MSVC
# define THREAD_LOCAL __declspec(thread)
#elif CORE_COMPILER_GCC || CORE_COMPILER_CLANG
# define THREAD_LOCAL __thread
#endif

#if CORE_COMPILER_MSVC || (CORE_COMPILER_CLANG && CORE_OS_WINDOWS)
# pragma section(".rdata$", read)
# define read_only __declspec(allocate(".rdata$"))
#elif (COMPILER_CLANG && OS_LINUX)
# define read_only __attribute__((section(".rodata")))
#else
// NOTE(rjf): I don't know of a useful way to do this in GCC land.
// __attribute__((section(".rodata"))) looked promising, but it introduces a
// strange warning about malformed section attributes, and it doesn't look
// like writing to that section reliably produces access violations, strangely
// enough. (It does on Clang)
# define read_only
#endif

#if CORE_OS_WINDOWS
# define shared_function C_LINKAGE __declspec(dllexport)
#else
# define shared_function C_LINKAGE
#endif

#if LANG_CPP
# define C_LINKAGE_BEGIN extern "C"{
# define C_LINKAGE_END }
# define C_LINKAGE extern "C"
#else
# define C_LINKAGE_BEGIN
# define C_LINKAGE_END
# define C_LINKAGE
#endif

#if CORE_COMPILER_MSVC
# define OPTIMIZE_BEGIN _Pragma("optimize(\"\", on)")
# define OPTIMIZE_END _Pragma("optimize(\"\", off)")
#elif CORE_COMPILER_CLANG
# define OPTIMIZE_BEGIN _Pragma("clang optimize on")
# define OPTIMIZE_END _Pragma("clang optimize off")
#elif CORE_COMPILER_GCC
# define OPTIMIZE_BEGIN _Pragma("GCC push_options") _Pragma("GCC optimize(\"O2\")")
# define OPTIMIZE_END _Pragma("GCC pop_options")
#else
# define OPTIMIZE_BEGIN
# define OPTIMIZE_END
#endif

#if COMPILER_MSVC && !BUILD_DEBUG
# define NO_OPTIMIZE_BEGIN _Pragma("optimize(\"\", off)")
# define NO_OPTIMIZE_END _Pragma("optimize(\"\", on)")
#elif COMPILER_CLANG && !BUILD_DEBUG
# define NO_OPTIMIZE_BEGIN _Pragma("clang optimize off")
# define NO_OPTIMIZE_END _Pragma("clang optimize on")
#elif COMPILER_GCC && !BUILD_DEBUG
# define NO_OPTIMIZE_BEGIN _Pragma("GCC push_options") _Pragma("GCC optimize(\"O0\")")
# define NO_OPTIMIZE_END _Pragma("GCC pop_options")
#else
# define NO_OPTIMIZE_BEGIN
# define NO_OPTIMIZE_END
#endif

////////////////////////////////
//~ rjf: Versions

#define Version(major, minor, patch) (U64)((((U64)(major) & 0xffff) << 32) | ((((U64)(minor) & 0xffff) << 16)) | ((((U64)(patch) & 0xffff) << 0)))
#define MajorFromVersion(version) (((version) & 0xffff00000000ull) >> 32)
#define MinorFromVersion(version) (((version) & 0x0000ffff0000ull) >> 16)
#define PatchFromVersion(version) (((version) & 0x00000000ffffull) >> 0)

////////////////////////////////
//~ rjf: Units

#define KB(n)  (((uint64_t)(n)) << 10)
#define MB(n)  (((uint64_t)(n)) << 20)
#define GB(n)  (((uint64_t)(n)) << 30)
#define TB(n)  (((uint64_t)(n)) << 40)
#define Thousand(n)   ((n)*1000)
#define Million(n)    ((n)*1000000)
#define Billion(n)    ((n)*1000000000)

////////////////////////////////
//~ rjf: Branch Predictor Hints
#if defined(__clang__)
# define Expect(expr, val) __builtin_expect((expr), (val))
#else
# define Expect(expr, val) (expr)
#endif

#define Likely(expr)            Expect(expr,1)
#define Unlikely(expr)          Expect(expr,0)


////////////////////////////////
//~ rjf: Clamps, Mins, Maxes

#define Min(A,B) (((A)<(B))?(A):(B))
#define Max(A,B) (((A)>(B))?(A):(B))
#define ClampTop(A,X) Min(A,X)
#define ClampBot(X,B) Max(X,B)
#define Clamp(A,X,B) (((X)<(A))?(A):((X)>(B))?(B):(X))

////////////////////////////////
//~ rjf: Type -> Alignment

#if CORE_COMPILER_MSVC
# define AlignOf(T) __alignof(T)
#elif CORE_COMPILER_CLANG
# define AlignOf(T) __alignof(T)
#elif CORE_COMPILER_GCC
# define AlignOf(T) __alignof__(T)
#else
# error AlignOf not defined for this compiler.
#endif

#if CORE_COMPILER_MSVC
# define AlignType(x) __declspec(align(x))
#elif CORE_COMPILER_CLANG || CORE_COMPILER_GCC
# define AlignType(x) __attribute__((aligned(x)))
#else
# error AlignType not defined for this compiler.
#endif

////////////////////////////////
//~ rjf: Member Offsets

#define Member(T,m)                 (((T*)0)->m)
#define OffsetOf(T,m)               IntFromPtr(&Member(T,m))
#define MemberFromOffset(T,ptr,off) (T)((((U8 *)ptr)+(off)))
#define CastFromMember(T,m,ptr)     (T*)(((U8*)ptr) - OffsetOf(T,m))

////////////////////////////////
//~ rjf: For-Loop Construct Macros

#define DeferLoop(begin, end)        for(int _i_ = ((begin), 0); !_i_; _i_ += 1, (end))
#define DeferLoopChecked(begin, end) for(int _i_ = 2 * !(begin); (_i_ == 2 ? ((end), 0) : !_i_); _i_ += 1, (end))

#define EachIndex(it, count) (uint64_t it = 0; it < (count); it += 1)
#define EachElement(it, array) (uint64_t it = 0; it < ArrayCount(array); it += 1)
#define EachEnumVal(type, it) (type it = (type)0; it < type##_COUNT; it = (type)(it+1))
#define EachNonZeroEnumVal(type, it) (type it = (type)1; it < type##_COUNT; it = (type)(it+1))
#define EachInRange(it, range) (uint64_t it = (range).min; it < (range).max; it += 1)
#define EachNode_N(it, T, first, next) (T *it = first; it != 0; it = it->next)
#define EachNode(it, T, first) (T *it = first; it != 0; it = it->next)
////////////////////////////////
//~ rjf: Memory Operation Macros

#define MemoryCopy(dst, src, size)    memmove((dst), (src), (size))
#define MemorySet(dst, byte, size)    memset((dst), (byte), (size))
#define MemoryCompare(a, b, size)     memcmp((a), (b), (size))
#define MemoryStrlen(ptr)             strlen(ptr)

#define MemoryCopyStruct(d,s)  MemoryCopy((d),(s),sizeof(*(d)))
#define MemoryCopyArray(d,s)   MemoryCopy((d),(s),sizeof(d))
#define MemoryCopyTyped(d,s,c) MemoryCopy((d),(s),sizeof(*(d))*(c))
#define MemoryCopyStr8(dst, s) MemoryCopy(dst, (s).str, (s).size)
#define MemoryCopyStr16(dst, s) MemoryCopy(dst, (s).str, (s).size * sizeof(U16))

#define MemoryZero(s,z)       memset((s),0,(z))
#define MemoryZeroStruct(s)   MemoryZero((s),sizeof(*(s)))
#define MemoryZeroArray(a)    MemoryZero((a),sizeof(a))
#define MemoryZeroTyped(m,c)  MemoryZero((m),sizeof(*(m))*(c))

#define MemoryMatch(a,b,z)     (MemoryCompare((a),(b),(z)) == 0)
#define MemoryMatchStruct(a,b)  MemoryMatch((a),(b),sizeof(*(a)))
#define MemoryMatchArray(a,b)   MemoryMatch((a),(b),sizeof(a))

#define MemoryIsZeroStruct(ptr) memory_is_zero((ptr), sizeof(*(ptr)))

#define MemoryRead(T,p,e)    ( ((p)+sizeof(T)<=(e))?(*(T*)(p)):(0) )
#define MemoryConsume(T,p,e) ( ((p)+sizeof(T)<=(e))?((p)+=sizeof(T),*(T*)((p)-sizeof(T))):((p)=(e),0) )

#if CORE_COMPILER_MSVC
# define Trap() __debugbreak()
#elif CORE_COMPILER_CLANG || CORE_COMPILER_GCC
# define Trap() __builtin_trap()
#else
# error Unknown trap intrinsic for this compiler.
#endif

#define AssertAlways(x) do{if(!(x)) {Trap();}}while(0)
#if BUILD_DEBUG
# define Assert(x) AssertAlways(x)
#else
# define Assert(x) (void)(x)
#endif
#define InvalidPath        Assert(!"Invalid Path!")
#define NotImplemented     Assert(!"Not Implemented!")
#define NoOp               ((void)0)

////////////////////////////////
//~ rjf: Misc. Helper Macros

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)

#define Glue_(A,B) A##B
#define Glue(A,B) Glue_(A,B)

#define ArrayCount(a) (sizeof(a) / sizeof((a)[0]))

#define CeilIntegerDiv(a,b) (((a) + (b) - 1)/(b))

#define Swap(T,a,b) do{T t__ = a; a = b; b = t__;}while(0)

#if CORE_ARCH_64BIT
# define IntFromPtr(ptr) ((uint64_t)(ptr))
#elif CORE_ARCH_32BIT
# define IntFromPtr(ptr) ((uint32_t)(ptr))
#else
# error Missing pointer-to-integer cast for this architecture.
#endif
#define PtrFromInt(i) (void*)(i)

#define Compose64Bit(a,b)  ((((uint64_t)a) << 32) | ((uint64_t)b))
#define Compose32Bit(a,b)  ((((uint32_t)a) << 16) | ((uint32_t)b))
#define AlignPow2(x,b)     (((x) + (b) - 1)&(~((b) - 1)))
#define AlignDownPow2(x,b) ((x)&(~((b) - 1)))
#define AlignPadPow2(x,b)  ((0-(x)) & ((b) - 1))
#define IsPow2(x)          ((x)!=0 && ((x)&((x)-1))==0)
#define IsPow2OrZero(x)    ((((x) - 1)&(x)) == 0)

#define ExtractBit(word, idx) (((word) >> (idx)) & 1)
#define Extract8(word, pos)   (((word) >> ((pos)*8))  & max_U8)
#define Extract16(word, pos)  (((word) >> ((pos)*16)) & max_U16)
#define Extract32(word, pos)  (((word) >> ((pos)*32)) & max_U32)

////////////////////////////////
//~ rjf: Base Types

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int8_t   S8;
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;
typedef S8       B8;
typedef S16      B16;
typedef S32      B32;
typedef S64      B64;
typedef float    F32;
typedef double   F64;
typedef void VoidProc(void);
typedef union U128 U128;
union U128
{
  U8 u8[16];
  U16 u16[8];
  U32 u32[4];
  U64 u64[2];
};
typedef union U256 U256;
union U256
{
  U8 u8[32];
  U16 u16[16];
  U32 u32[8];
  U64 u64[4];
  U128 u128[2];
};
typedef union U512 U512;
union U512
{
  U8 u8[64];
  U16 u16[32];
  U32 u32[16];
  U64 u64[8];
  U128 u128[4];
  U256 u256[2];
};

////////////////////////////////
//~ rjf: Linked List Building Macros

//- rjf: linked list macro helpers
#define CheckNil(nil,p) ((p) == 0 || (p) == nil)
#define SetNil(nil,p) ((p) = nil)

//- rjf: doubly-linked-lists
#define DLLInsert_NPZ(nil,f,l,p,n,next,prev) (CheckNil(nil,f) ? \
((f) = (l) = (n), SetNil(nil,(n)->next), SetNil(nil,(n)->prev)) :\
CheckNil(nil,p) ? \
((n)->next = (f), (f)->prev = (n), (f) = (n), SetNil(nil,(n)->prev)) :\
((p)==(l)) ? \
((l)->next = (n), (n)->prev = (l), (l) = (n), SetNil(nil, (n)->next)) :\
(((!CheckNil(nil,p) && CheckNil(nil,(p)->next)) ? (0) : ((p)->next->prev = (n))), ((n)->next = (p)->next), ((p)->next = (n)), ((n)->prev = (p))))
#define DLLPushBack_NPZ(nil,f,l,n,next,prev) DLLInsert_NPZ(nil,f,l,l,n,next,prev)
#define DLLPushFront_NPZ(nil,f,l,n,next,prev) DLLInsert_NPZ(nil,l,f,f,n,prev,next)
#define DLLRemove_NPZ(nil,f,l,n,next,prev) (((n) == (f) ? (f) = (n)->next : (0)),\
((n) == (l) ? (l) = (l)->prev : (0)),\
(CheckNil(nil,(n)->prev) ? (0) :\
((n)->prev->next = (n)->next)),\
(CheckNil(nil,(n)->next) ? (0) :\
((n)->next->prev = (n)->prev)))

//- rjf: singly-linked, doubly-headed lists (queues)
#define SLLQueuePush_NZ(nil,f,l,n,next) (CheckNil(nil,f)?\
((f)=(l)=(n),SetNil(nil,(n)->next)):\
((l)->next=(n),(l)=(n),SetNil(nil,(n)->next)))
#define SLLQueuePushFront_NZ(nil,f,l,n,next) (CheckNil(nil,f)?\
((f)=(l)=(n),SetNil(nil,(n)->next)):\
((n)->next=(f),(f)=(n)))
#define SLLQueuePop_NZ(nil,f,l,next) ((f)==(l)?\
(SetNil(nil,f),SetNil(nil,l)):\
((f)=(f)->next))

//- rjf: singly-linked, singly-headed lists (stacks)
#define SLLStackPush_N(f,n,next) ((n)->next=(f), (f)=(n))
#define SLLStackPop_N(f,next) ((f)=(f)->next)

//- rjf: doubly-linked-list helpers
#define DLLInsert_NP(f,l,p,n,next,prev) DLLInsert_NPZ(0,f,l,p,n,next,prev)
#define DLLPushBack_NP(f,l,n,next,prev) DLLPushBack_NPZ(0,f,l,n,next,prev)
#define DLLPushFront_NP(f,l,n,next,prev) DLLPushFront_NPZ(0,f,l,n,next,prev)
#define DLLRemove_NP(f,l,n,next,prev) DLLRemove_NPZ(0,f,l,n,next,prev)
#define DLLInsert(f,l,p,n) DLLInsert_NPZ(0,f,l,p,n,next,prev)
#define DLLPushBack(f,l,n) DLLPushBack_NPZ(0,f,l,n,next,prev)
#define DLLPushFront(f,l,n) DLLPushFront_NPZ(0,f,l,n,next,prev)
#define DLLRemove(f,l,n) DLLRemove_NPZ(0,f,l,n,next,prev)

//- rjf: singly-linked, doubly-headed list helpers
#define SLLQueuePush_N(f,l,n,next) SLLQueuePush_NZ(0,f,l,n,next)
#define SLLQueuePushFront_N(f,l,n,next) SLLQueuePushFront_NZ(0,f,l,n,next)
#define SLLQueuePop_N(f,l,next) SLLQueuePop_NZ(0,f,l,next)
#define SLLQueuePush(f,l,n) SLLQueuePush_NZ(0,f,l,n,next)
#define SLLQueuePushFront(f,l,n) SLLQueuePushFront_NZ(0,f,l,n,next)
#define SLLQueuePop(f,l) SLLQueuePop_NZ(0,f,l,next)

//- rjf: singly-linked, singly-headed list helpers
#define SLLStackPush(f,n) SLLStackPush_N(f,n,next)
#define SLLStackPop(f) SLLStackPop_N(f,next)

////////////////////////////////
//~ rjf: Address Sanitizer Markup

#if CORE_COMPILER_MSVC
# if defined(__SANITIZE_ADDRESS__)
#  define CORE_ASAN_ENABLED 1
#  define NO_ASAN __declspec(no_sanitize_address)
# else
#  define NO_ASAN
# endif
#elif CORE_COMPILER_CLANG
# if defined(__has_feature)
#  if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#   define CORE_ASAN_ENABLED 1
#  endif
# endif
# define CORE_NO_ASAN __attribute__((no_sanitize("address")))
#else
# define CORE_NO_ASAN
#endif

#if CORE_ASAN_ENABLED
C_LINKAGE void __asan_poison_memory_region(void const volatile *addr, size_t size);
C_LINKAGE void __asan_unpoison_memory_region(void const volatile *addr, size_t size);
# define AsanPoisonMemoryRegion(addr, size)   __asan_poison_memory_region((addr), (size))
# define AsanUnpoisonMemoryRegion(addr, size) __asan_unpoison_memory_region((addr), (size))
#else
# define AsanPoisonMemoryRegion(addr, size)   ((void)(addr), (void)(size))
# define AsanUnpoisonMemoryRegion(addr, size) ((void)(addr), (void)(size))
#endif

////////////////////////////////
//~ rjf: Basic Constants
global const uint32_t sign32     = 0x80000000;
global const uint32_t exponent32 = 0x7F800000;
global const uint32_t mantissa32 = 0x007FFFFF;

global const float   big_golden32 = 1.61803398875f;
global float small_golden32 = 0.61803398875f;

global const float pi32 = 3.1415926535897f;

global const double machine_epsilon64 = 4.94065645841247e-324;

global const uint64_t max_U64 = 0xffffffffffffffffull;
global const uint32_t max_U32 = 0xffffffff;
global const uint16_t max_U16 = 0xffff;
global const uint8_t  max_U8  = 0xff;

global const int64_t max_S64 = (int64_t)0x7fffffffffffffffll;
global const int32_t max_S32 = (int32_t)0x7fffffff;
global const int16_t max_S16 = (int16_t)0x7fff;
global const int8_t  max_S8  =  (int8_t)0x7f;

global const int64_t min_S64 = (int64_t)0x8000000000000000ll;
global const int32_t min_S32 = (int32_t)0x80000000;

// NOTE(rjf): Lookup table for hex/decimal digit values. 0xFF = invalid digit.
read_only global U8 integer_symbol_reverse[128] =
{
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};
global const int16_t min_S16 = (int16_t)0x8000;
global const int8_t  min_S8  =  (int8_t)0x80;

global const uint32_t bitmask1  = 0x00000001;
global const uint32_t bitmask2  = 0x00000003;
global const uint32_t bitmask3  = 0x00000007;
global const uint32_t bitmask4  = 0x0000000f;
global const uint32_t bitmask5  = 0x0000001f;
global const uint32_t bitmask6  = 0x0000003f;
global const uint32_t bitmask7  = 0x0000007f;
global const uint32_t bitmask8  = 0x000000ff;
global const uint32_t bitmask9  = 0x000001ff;
global const uint32_t bitmask10 = 0x000003ff;
global const uint32_t bitmask11 = 0x000007ff;
global const uint32_t bitmask12 = 0x00000fff;
global const uint32_t bitmask13 = 0x00001fff;
global const uint32_t bitmask14 = 0x00003fff;
global const uint32_t bitmask15 = 0x00007fff;
global const uint32_t bitmask16 = 0x0000ffff;
global const uint32_t bitmask17 = 0x0001ffff;
global const uint32_t bitmask18 = 0x0003ffff;
global const uint32_t bitmask19 = 0x0007ffff;
global const uint32_t bitmask20 = 0x000fffff;
global const uint32_t bitmask21 = 0x001fffff;
global const uint32_t bitmask22 = 0x003fffff;
global const uint32_t bitmask23 = 0x007fffff;
global const uint32_t bitmask24 = 0x00ffffff;
global const uint32_t bitmask25 = 0x01ffffff;
global const uint32_t bitmask26 = 0x03ffffff;
global const uint32_t bitmask27 = 0x07ffffff;
global const uint32_t bitmask28 = 0x0fffffff;
global const uint32_t bitmask29 = 0x1fffffff;
global const uint32_t bitmask30 = 0x3fffffff;
global const uint32_t bitmask31 = 0x7fffffff;
global const uint32_t bitmask32 = 0xffffffff;

global const uint64_t bitmask33 = 0x00000001ffffffffull;
global const uint64_t bitmask34 = 0x00000003ffffffffull;
global const uint64_t bitmask35 = 0x00000007ffffffffull;
global const uint64_t bitmask36 = 0x0000000fffffffffull;
global const uint64_t bitmask37 = 0x0000001fffffffffull;
global const uint64_t bitmask38 = 0x0000003fffffffffull;
global const uint64_t bitmask39 = 0x0000007fffffffffull;
global const uint64_t bitmask40 = 0x000000ffffffffffull;
global const uint64_t bitmask41 = 0x000001ffffffffffull;
global const uint64_t bitmask42 = 0x000003ffffffffffull;
global const uint64_t bitmask43 = 0x000007ffffffffffull;
global const uint64_t bitmask44 = 0x00000fffffffffffull;
global const uint64_t bitmask45 = 0x00001fffffffffffull;
global const uint64_t bitmask46 = 0x00003fffffffffffull;
global const uint64_t bitmask47 = 0x00007fffffffffffull;
global const uint64_t bitmask48 = 0x0000ffffffffffffull;
global const uint64_t bitmask49 = 0x0001ffffffffffffull;
global const uint64_t bitmask50 = 0x0003ffffffffffffull;
global const uint64_t bitmask51 = 0x0007ffffffffffffull;
global const uint64_t bitmask52 = 0x000fffffffffffffull;
global const uint64_t bitmask53 = 0x001fffffffffffffull;
global const uint64_t bitmask54 = 0x003fffffffffffffull;
global const uint64_t bitmask55 = 0x007fffffffffffffull;
global const uint64_t bitmask56 = 0x00ffffffffffffffull;
global const uint64_t bitmask57 = 0x01ffffffffffffffull;
global const uint64_t bitmask58 = 0x03ffffffffffffffull;
global const uint64_t bitmask59 = 0x07ffffffffffffffull;
global const uint64_t bitmask60 = 0x0fffffffffffffffull;
global const uint64_t bitmask61 = 0x1fffffffffffffffull;
global const uint64_t bitmask62 = 0x3fffffffffffffffull;
global const uint64_t bitmask63 = 0x7fffffffffffffffull;
global const uint64_t bitmask64 = 0xffffffffffffffffull;

global const uint32_t bit1  = (1<<0);
global const uint32_t bit2  = (1<<1);
global const uint32_t bit3  = (1<<2);
global const uint32_t bit4  = (1<<3);
global const uint32_t bit5  = (1<<4);
global const uint32_t bit6  = (1<<5);
global const uint32_t bit7  = (1<<6);
global const uint32_t bit8  = (1<<7);
global const uint32_t bit9  = (1<<8);
global const uint32_t bit10 = (1<<9);
global const uint32_t bit11 = (1<<10);
global const uint32_t bit12 = (1<<11);
global const uint32_t bit13 = (1<<12);
global const uint32_t bit14 = (1<<13);
global const uint32_t bit15 = (1<<14);
global const uint32_t bit16 = (1<<15);
global const uint32_t bit17 = (1<<16);
global const uint32_t bit18 = (1<<17);
global const uint32_t bit19 = (1<<18);
global const uint32_t bit20 = (1<<19);
global const uint32_t bit21 = (1<<20);
global const uint32_t bit22 = (1<<21);
global const uint32_t bit23 = (1<<22);
global const uint32_t bit24 = (1<<23);
global const uint32_t bit25 = (1<<24);
global const uint32_t bit26 = (1<<25);
global const uint32_t bit27 = (1<<26);
global const uint32_t bit28 = (1<<27);
global const uint32_t bit29 = (1<<28);
global const uint32_t bit30 = (1<<29);
global const uint32_t bit31 = (1<<30);
global const uint32_t bit32 = (1<<31);

global const uint64_t bit33 = (1ull<<32);
global const uint64_t bit34 = (1ull<<33);
global const uint64_t bit35 = (1ull<<34);
global const uint64_t bit36 = (1ull<<35);
global const uint64_t bit37 = (1ull<<36);
global const uint64_t bit38 = (1ull<<37);
global const uint64_t bit39 = (1ull<<38);
global const uint64_t bit40 = (1ull<<39);
global const uint64_t bit41 = (1ull<<40);
global const uint64_t bit42 = (1ull<<41);
global const uint64_t bit43 = (1ull<<42);
global const uint64_t bit44 = (1ull<<43);
global const uint64_t bit45 = (1ull<<44);
global const uint64_t bit46 = (1ull<<45);
global const uint64_t bit47 = (1ull<<46);
global const uint64_t bit48 = (1ull<<47);
global const uint64_t bit49 = (1ull<<48);
global const uint64_t bit50 = (1ull<<49);
global const uint64_t bit51 = (1ull<<50);
global const uint64_t bit52 = (1ull<<51);
global const uint64_t bit53 = (1ull<<52);
global const uint64_t bit54 = (1ull<<53);
global const uint64_t bit55 = (1ull<<54);
global const uint64_t bit56 = (1ull<<55);
global const uint64_t bit57 = (1ull<<56);
global const uint64_t bit58 = (1ull<<57);
global const uint64_t bit59 = (1ull<<58);
global const uint64_t bit60 = (1ull<<59);
global const uint64_t bit61 = (1ull<<60);
global const uint64_t bit62 = (1ull<<61);
global const uint64_t bit63 = (1ull<<62);
global const uint64_t bit64 = (1ull<<63);

//- Arena
#define ARENA_HEADER_SIZE 128

typedef U64 ArenaFlags;
enum
{
  ArenaFlag_NoChain    = (1<<0),
  //ArenaFlag_LargePages = (1<<1),
};

typedef struct ArenaParams ArenaParams;
struct ArenaParams
{
  ArenaFlags flags;
  U64 reserve_size;
  U64 commit_size;
  void *optional_backing_buffer;
  const char *allocation_site_file;
  int allocation_site_line;
};

typedef struct Arena Arena;
struct Arena
{
  Arena *prev;    // previous arena in chain
  Arena *current; // current arena in chain
  ArenaFlags flags;
  U64 cmt_size;
  U64 res_size;
  U64 base_pos;
  U64 pos;
  U64 cmt;
  U64 res;
  const char *allocation_site_file;
  int allocation_site_line;
#if ARENA_FREE_LIST
  Arena *free_last;
#endif
};
static_assert(sizeof(Arena) <= ARENA_HEADER_SIZE, "arena_header_size_check");

typedef struct Temp Temp;
struct Temp
{
  Arena *arena;
  U64 pos;
};

////////////////////////////////
//~ rjf: Arena Functions

global U64 arena_default_reserve_size = MB(64);
global U64 arena_default_commit_size  = KB(64);
global ArenaFlags arena_default_flags = 0;

//- rjf: arena creation/destruction
internal Arena *arena_alloc_(ArenaParams *params);
#define arena_alloc(...) arena_alloc_(&(ArenaParams){.reserve_size = arena_default_reserve_size, .commit_size = arena_default_commit_size, .flags = arena_default_flags, .allocation_site_file = __FILE__, .allocation_site_line = __LINE__, __VA_ARGS__})
#define arena_alloc_cpp(...) arena_alloc_(&(ArenaParams){.reserve_size = arena_default_reserve_size, .commit_size = arena_default_commit_size, .flags = arena_default_flags, .allocation_site_file = __FILE__, .allocation_site_line = __LINE__, __VA_ARGS__})
internal void arena_release(Arena *arena);

//- rjf: arena push/pop/pos core functions
internal void *arena_push(Arena *arena, U64 size, U64 align, B32 zero);
internal U64   arena_pos(Arena *arena);
internal void  arena_pop_to(Arena *arena, U64 pos);

//- rjf: arena push/pop helpers
internal void arena_clear(Arena *arena);
internal void arena_pop(Arena *arena, U64 amt);

//- rjf: temporary arena scopes
internal Temp temp_begin(Arena *arena);
internal void temp_end(Temp temp);

//- rjf: push helper macros
#define push_array_no_zero_aligned(a, T, c, align) (T *)arena_push((a), sizeof(T)*(c), (align), (0))
#define push_array_aligned(a, T, c, align) (T *)arena_push((a), sizeof(T)*(c), (align), (1))
#define push_array_no_zero(a, T, c) push_array_no_zero_aligned(a, T, c, Max(8, AlignOf(T)))
#define push_array(a, T, c) push_array_aligned(a, T, c, Max(8, AlignOf(T)))

////////////////////////////////
//~ rjf: String Types

typedef struct String8 String8;
struct String8 {
  U8 *str;
  U64 size;
};

typedef struct String16 String16;
struct String16 {
  U16 *str;
  U64 size;
};

typedef struct String32 String32;
struct String32
{
  U32 *str;
  U64 size;
};

////////////////////////////////
//~ rjf: String List & Array Types

typedef struct String8Node String8Node;
struct String8Node
{
  String8Node *next;
  String8 string;
};

typedef struct String8List String8List;
struct String8List
{
  String8Node *first;
  String8Node *last;
  U64 node_count;
  U64 total_size;
};

////////////////////////////////
//~ rjf: String Matching Flags

typedef U32 StringMatchFlags;
enum
{
  StringMatchFlag_CaseInsensitive  = (1 << 0),
  StringMatchFlag_RightSideSloppy  = (1 << 1),
  StringMatchFlag_SlashInsensitive = (1 << 2),
};

////////////////////////////////
//~ rjf: Range Types

typedef union Rng1U64 Rng1U64;
union Rng1U64
{
  struct
  {
    U64 min;
    U64 max;
  };
  U64 v[2];
};

////////////////////////////////
//~ rjf: Fuzzy Match Types

typedef struct FuzzyMatchRangeNode FuzzyMatchRangeNode;
struct FuzzyMatchRangeNode
{
  FuzzyMatchRangeNode *next;
  Rng1U64 range;
};

typedef struct FuzzyMatchRangeList FuzzyMatchRangeList;
struct FuzzyMatchRangeList
{
  FuzzyMatchRangeNode *first;
  FuzzyMatchRangeNode *last;
  U64 count;
  U64 needle_part_count;
  U64 total_dim;
};

////////////////////////////////
//~ rjf: UTF Decoding Types

typedef struct UnicodeDecode UnicodeDecode;
struct UnicodeDecode
{
  U32 inc;
  U32 codepoint;
};

////////////////////////////////
//~ rjf: String Constructors
#define str8_lit(S)  str8((U8*)(S), sizeof(S) - 1)
#define str8_lit_comp(S) {(U8*)(S), sizeof(S) - 1,}
#define str8_varg(S) (int)((S).size), ((S).str)

#define str8_array(S,C) str8((U8*)(S), sizeof(*(S))*(C))
#define str8_array_fixed(S) str8((U8*)(S), sizeof(S))
#define str8_struct(S) str8((U8*)(S), sizeof(*(S)))

internal String8  str8(U8 *str, U64 size);
internal String8  str8_range(U8 *first, U8 *one_past_last);
internal String8  str8_zero(void);
internal String8  str8_from_16(Arena *arena, String16 in);
internal String16 str16(U16 *str, U64 size);
internal String16 str16_range(U16 *first, U16 *one_past_last);
internal String16 str16_zero(void);
internal String16 str16_from_8(Arena *arena, String8 in);
internal String32 str32(U32 *str, U64 size);
internal String32 str32_range(U32 *first, U32 *one_past_last);
internal String32 str32_zero(void);
internal U64      cstring8_length(U8 *c);
internal U64      cstring16_length(U16 *c);
internal U64      cstring32_length(U32 *c);
internal String8  str8_cstring(char *c);
internal String16 str16_cstring(U16 *c);
internal String32 str32_cstring(U32 *c);
internal String8  str8_cstring_capped(void *cstr, void *cap);
internal String16 str16_cstring_capped(void *cstr, void *cap);
internal String8  str8_cstring_capped_reverse(void *raw_start, void *raw_cap);

internal String8 str8_skip(String8 str, U64 amt);
internal String8 str8_substr(String8 str, U64 start, U64 size);
internal S32 str8_cmp(String8 str1, String8 str2);
internal S32 str8_equals(String8 str1, String8 str2);
internal B32 str8_wildcard(String8 str, String8 pattern);
internal B32 str8_match(String8 a, String8 b, StringMatchFlags flags);
internal U64 str8_find_needle(String8 string, U64 start_pos, String8 needle, StringMatchFlags flags);
internal String8 str8_chop_last_slash(String8 string);
internal String8 str8_skip_last_slash(String8 string);
internal String8 str8_chop_last_dot(String8 string);
internal String8 str8_skip_last_dot(String8 string);
internal U64 str8_index_of(String8 str, U8* character, U64 character_count);

////////////////////////////////
//~ rjf: Path Style Type

typedef enum PathStyle
{
  PathStyle_Null,
  PathStyle_Relative,
  PathStyle_WindowsAbsolute,
  PathStyle_UnixAbsolute,
  
#if CORE_OS_WINDOWS
  PathStyle_SystemAbsolute = PathStyle_WindowsAbsolute
#elif CORE_OS_LINUX
  PathStyle_SystemAbsolute = PathStyle_UnixAbsolute
#else
# error Absolute path style is undefined for this OS.
#endif
}
PathStyle;

////////////////////////////////
//~ rjf: String Path Helpers

internal B32         char_is_alpha(U8 c);
internal PathStyle   path_style_from_str8(String8 string);
internal String8List str8_split_path(Arena *arena, String8 string);
internal String8     str8_path_list_join_by_style(Arena *arena, String8List *path, PathStyle style);
internal String8     path_separator_string_from_style(PathStyle style);
internal String8     path_convert_slashes(Arena *arena, String8 path, PathStyle path_style);
internal String8     path_replace_file_extension(Arena *arena, String8 file_name, String8 ext);

////////////////////////////////
//~ rjf: Fuzzy Match Functions

internal FuzzyMatchRangeList fuzzy_match_find(Arena *arena, String8 needle, String8 haystack);
internal FuzzyMatchRangeList fuzzy_match_range_list_copy(Arena *arena, FuzzyMatchRangeList *src);

internal String16 str16_copy_to(Arena *arena, String16 str);
internal String16 str16_substr(String16 str, U64 start, U64 size);
internal String16 str16_clamp_to(String16 str, U64 size);

////////////////////////////////
//~ rjf: String Join Type

typedef struct StringJoin StringJoin;
struct StringJoin
{
  String8 pre;
  String8 sep;
  String8 post;
};

////////////////////////////////
//~ rjf: String Formatting Functions

internal String8 str8_cat(Arena *arena, String8 s1, String8 s2);
internal String8 str8_copy(Arena *arena, String8 s);
internal String8 str8fv(Arena *arena, char *fmt, va_list args);
internal String8 str8f(Arena *arena, char *fmt, ...);
#define push_str8_cat(arena, s1, s2) str8_cat((arena), (s1), (s2))
#define push_str8_copy(arena, s) str8_copy((arena), (s))
#define push_str8fv(arena, fmt, args) str8fv((arena), (fmt), (args))
#define push_str8f(arena, ...) str8f((arena), __VA_ARGS__)

////////////////////////////////
//~ rjf: String List Functions

internal void         str8_list_push(Arena *arena, String8List *list, String8 string);
internal String8List  str8_split(Arena *arena, String8 string, U8 *split_chars, U64 split_char_count);
internal String8      str8_list_join(Arena *arena, String8List *list, StringJoin *optional_params);

internal B32 wildcard_match_inner(char* str, size_t str_len, char* pattern, size_t pattern_len);
internal B32 wildcard_match(char* str, char* pattern);

////////////////////////////////
//~ rjf: String Parsing Functions

internal String8 str8_prefix(String8 str, U64 size);
internal S64     sign_from_str8(String8 string, String8 *string_tail);
internal B32     str8_is_integer(String8 string, U32 radix);
internal U64     u64_from_str8(String8 string, U32 radix);
internal S64     s64_from_str8(String8 string, U32 radix);
internal B32     try_u64_from_str8_c_rules(String8 string, U64 *x);
internal B32     try_s64_from_str8_c_rules(String8 string, S64 *x);

////////////////////////////////
//~ rjf: Thread Types

typedef struct Thread Thread;
struct Thread
{
  U64 u64[1];
};
typedef void ThreadEntryPointFunctionType(void *p);

////////////////////////////////
//~ rjf: Synchronization Primitive Types

typedef struct Mutex Mutex;
struct Mutex
{
  U64 u64[1];
};

typedef struct RWMutex RWMutex;
struct RWMutex
{
  U64 u64[1];
};

typedef struct CondVar CondVar;
struct CondVar
{
  U64 u64[1];
};

typedef struct Semaphore Semaphore;
struct Semaphore
{
  U64 u64[1];
};

typedef struct Barrier Barrier;
struct Barrier
{
  U64 u64[1];
};

////////////////////////////////
//~ rjf: OS Handle Type

typedef struct OS_Handle OS_Handle;
struct OS_Handle
{
  U64 u64[1];
};

////////////////////////////////
//~ rjf: System Info

typedef struct OS_SystemInfo OS_SystemInfo;
struct OS_SystemInfo
{
  U32 logical_processor_count;
  U64 page_size;
  U64 large_page_size;
  U64 allocation_granularity;
  String8 machine_name;
};

////////////////////////////////
//~ rjf: Process Info

typedef struct OS_ProcessInfo OS_ProcessInfo;
struct OS_ProcessInfo
{
  U32 pid;
  B32 is_elevated;
  String8 binary_path;
  String8 initial_path;
  String8 user_program_data_path;
};

////////////////////////////////
//~ rjf: Access Flags

typedef U32 OS_AccessFlags;
enum
{
  OS_AccessFlag_Read        = (1<<0),
  OS_AccessFlag_Write       = (1<<1),
  OS_AccessFlag_Execute     = (1<<2),
  OS_AccessFlag_Append      = (1<<3),
  OS_AccessFlag_ShareRead   = (1<<4),
  OS_AccessFlag_ShareWrite  = (1<<5),
  OS_AccessFlag_Inherited   = (1<<6),
};

////////////////////////////////
//~ rjf: File Properties

typedef U32 FilePropertyFlags;
enum
{
  FilePropertyFlag_IsFolder = (1 << 0),
};

typedef U64 DenseTime;

typedef struct FileProperties FileProperties;
struct FileProperties
{
  U64 size;
  DenseTime modified;
  DenseTime created;
  FilePropertyFlags flags;
};

////////////////////////////////
//~ rjf: File Iteration Types

typedef U32 OS_FileIterFlags;
enum
{
  OS_FileIterFlag_SkipFolders     = (1 << 0),
  OS_FileIterFlag_SkipFiles       = (1 << 1),
  OS_FileIterFlag_SkipHiddenFiles = (1 << 2),
  OS_FileIterFlag_Done            = (1 << 31),
};

typedef struct OS_FileIter OS_FileIter;
struct OS_FileIter
{
  OS_FileIterFlags flags;
  U8 memory[800];
};

typedef struct OS_FileInfo OS_FileInfo;
struct OS_FileInfo
{
  String8 name;
  FileProperties props;
};

////////////////////////////////
//~ rjf: Process Launch Parameters

typedef struct OS_ProcessLaunchParams OS_ProcessLaunchParams;
struct OS_ProcessLaunchParams
{
  String8List cmd_line;
  String8 path;
  String8List env;
  B32 inherit_env;
  B32 consoleless;
  B32 non_elevated;
  B32 new_process_group;
  OS_Handle stdout_file;
  OS_Handle stderr_file;
  OS_Handle stdin_file;
};

////////////////////////////////
//~ rjf: Memory Allocation Functions

//- rjf: basic
internal void *os_reserve(U64 size);
internal B32   os_commit(void *ptr, U64 size);
internal void  os_decommit(void *ptr, U64 size);
internal void  os_release(void *ptr, U64 size);

//- rjf: large pages
internal void *os_reserve_large(U64 size);
internal B32   os_commit_large(void *ptr, U64 size);

////////////////////////////////
//~ rjf: Thread Functions

internal Thread os_thread_launch(ThreadEntryPointFunctionType *f, void *p);
internal B32    os_thread_join(Thread handle, U64 endt_us);
internal void   os_thread_detach(Thread handle);
internal U32    os_tid(void);
internal void   os_set_thread_name(String8 string);

////////////////////////////////
//~ rjf: Synchronization Primitive Functions

//- rjf: recursive mutexes
internal Mutex os_mutex_alloc(void);
internal void  os_mutex_release(Mutex mutex);
internal void  os_mutex_take(Mutex mutex);
internal void  os_mutex_drop(Mutex mutex);

//- rjf: reader/writer mutexes
internal RWMutex os_rw_mutex_alloc(void);
internal void    os_rw_mutex_release(RWMutex mutex);
internal void    os_rw_mutex_take(RWMutex mutex, B32 write_mode);
internal void    os_rw_mutex_drop(RWMutex mutex, B32 write_mode);
#define os_rw_mutex_take_r(m) os_rw_mutex_take((m), (0))
#define os_rw_mutex_take_w(m) os_rw_mutex_take((m), (1))
#define os_rw_mutex_drop_r(m) os_rw_mutex_drop((m), (0))
#define os_rw_mutex_drop_w(m) os_rw_mutex_drop((m), (1))

//- rjf: condition variables
internal CondVar os_cond_var_alloc(void);
internal void    os_cond_var_release(CondVar cv);
internal B32     os_cond_var_wait(CondVar cv, Mutex mutex, U64 endt_us);
internal B32     os_cond_var_wait_rw(CondVar cv, RWMutex mutex_rw, B32 write_mode, U64 endt_us);
#define os_cond_var_wait_rw_r(cv, m, endt) os_cond_var_wait_rw((cv), (m), (0), (endt))
#define os_cond_var_wait_rw_w(cv, m, endt) os_cond_var_wait_rw((cv), (m), (1), (endt))
internal void    os_cond_var_signal(CondVar cv);
internal void    os_cond_var_broadcast(CondVar cv);

//- rjf: cross-process semaphores
internal Semaphore os_semaphore_alloc(U32 initial_count, U32 max_count, String8 name);
internal void      os_semaphore_release(Semaphore semaphore);
internal Semaphore os_semaphore_open(String8 name);
internal void      os_semaphore_close(Semaphore semaphore);
internal B32       os_semaphore_take(Semaphore semaphore, U64 endt_us);
internal void      os_semaphore_drop(Semaphore semaphore);

//- rjf: barriers
internal Barrier os_barrier_alloc(U64 count);
internal void    os_barrier_release(Barrier barrier);
internal void    os_barrier_wait(Barrier barrier);

//- rjf: scope macros
#define MutexScope(mutex) DeferLoop(os_mutex_take(mutex), os_mutex_drop(mutex))
#define RWMutexScope(mutex, write_mode) DeferLoop(os_rw_mutex_take((mutex), (write_mode)), os_rw_mutex_drop((mutex), (write_mode)))
#define MutexScopeR(mutex) DeferLoop(os_rw_mutex_take_r(mutex), os_rw_mutex_drop_r(mutex))
#define MutexScopeW(mutex) DeferLoop(os_rw_mutex_take_w(mutex), os_rw_mutex_drop_w(mutex))

////////////////////////////////
//~ rjf: Range Helpers

internal Rng1U64 r1u64(U64 min, U64 max);
internal U64     dim_1u64(Rng1U64 r);

////////////////////////////////
//~ rjf: Safe Casts

internal U16 safe_cast_u16(U32 x);
internal U32 u32_from_u64_saturate(U64 x);

////////////////////////////////
//~ rjf: OS Handle Functions

internal OS_Handle os_handle_zero(void);
internal B32       os_handle_match(OS_Handle a, OS_Handle b);

////////////////////////////////
//~ rjf: Shared Memory Functions

internal OS_Handle os_shared_memory_alloc(U64 size, String8 name);
internal OS_Handle os_shared_memory_open(String8 name);
internal void      os_shared_memory_close(OS_Handle handle);
internal void *    os_shared_memory_view_open(OS_Handle handle, Rng1U64 range);
internal void      os_shared_memory_view_close(OS_Handle handle, void *ptr, Rng1U64 range);

////////////////////////////////
//~ rjf: File System Functions

internal OS_Handle      os_file_open(OS_AccessFlags flags, String8 path);
internal void           os_file_close(OS_Handle file);
internal U64            os_file_read(OS_Handle file, Rng1U64 rng, void *out_data);
internal U64            os_file_write(OS_Handle file, Rng1U64 rng, void *data);
internal FileProperties os_properties_from_file(OS_Handle file);

//- rjf: file path operations
internal B32            os_delete_file_at_path(String8 path);
internal B32            os_copy_file_path(String8 dst, String8 src);
internal B32            os_move_file_path(String8 dst, String8 src);
internal String8        os_full_path_from_path(Arena *arena, String8 path);
internal B32            os_file_path_exists(String8 path);
internal B32            os_folder_path_exists(String8 path);
internal FileProperties os_properties_from_file_path(String8 path);

//- rjf: directory iteration
internal OS_FileIter *os_file_iter_begin(Arena *arena, String8 path, OS_FileIterFlags flags);
internal B32          os_file_iter_next(Arena *arena, OS_FileIter *iter, OS_FileInfo *info_out);
internal void         os_file_iter_end(OS_FileIter *iter);

//- rjf: directory creation
internal B32 os_make_directory(String8 path);

//- rjf: file helpers
internal String8 os_data_from_file_path(Arena *arena, String8 path);
internal B32     os_write_data_to_file_path(String8 path, String8 data);

////////////////////////////////
//~ rjf: System/Process Info Functions

internal OS_SystemInfo  *os_get_system_info(void);
internal OS_ProcessInfo *os_get_process_info(void);

////////////////////////////////
//~ rjf: Current Path

internal String8 os_get_current_path(Arena *arena);
internal String8 os_get_home_path(Arena *arena);

////////////////////////////////
//~ rjf: Child Processes Functions

internal OS_Handle os_process_launch(OS_ProcessLaunchParams *params);
internal B32       os_process_join(OS_Handle handle, U64 endt_us, U64 *exit_code_out);
internal void      os_process_detach(OS_Handle handle);
internal B32       os_process_kill(OS_Handle handle);

//- rjf: process launch helpers
internal OS_Handle os_cmd_line_launch(String8 string, B32 non_elevated, B32 new_process_group);

////////////////////////////////
//~ rjf: Time Types

typedef enum WeekDay
{
  WeekDay_Sun,
  WeekDay_Mon,
  WeekDay_Tue,
  WeekDay_Wed,
  WeekDay_Thu,
  WeekDay_Fri,
  WeekDay_Sat,
  WeekDay_COUNT,
}
WeekDay;

typedef enum Month
{
  Month_Jan,
  Month_Feb,
  Month_Mar,
  Month_Apr,
  Month_May,
  Month_Jun,
  Month_Jul,
  Month_Aug,
  Month_Sep,
  Month_Oct,
  Month_Nov,
  Month_Dec,
  Month_COUNT,
}
Month;

typedef struct DateTime DateTime;
struct DateTime
{
  U16 micro_sec; // [0,999]
  U16 msec; // [0,999]
  U16 sec;  // [0,60]
  U16 min;  // [0,59]
  U16 hour; // [0,24]
  U16 day;  // [0,30]
  union
  {
    WeekDay week_day;
    U32 wday;
  };
  union
  {
    Month month;
    U32 mon;
  };
  U32 year; // 1 = 1 CE, 0 = 1 BC
};

typedef U64 DenseTime;

////////////////////////////////
//~ rjf: Time Functions

internal U64      os_now_microseconds(void);
internal U32      os_now_unix(void);
internal DateTime os_now_universal_time(void);
internal DateTime os_now_local_time(void);
internal DateTime os_universal_time_from_local(DateTime *local_time);
internal DateTime os_local_time_from_universal(DateTime *universal_time);
internal void     os_sleep_milliseconds(U32 msec);

internal DenseTime dense_time_from_date_time(DateTime dt);
internal DateTime  date_time_from_dense_time(DenseTime t);

////////////////////////////////
//~ rjf: Atomic Operations

#if CORE_COMPILER_MSVC
# include <intrin.h>
# if CORE_ARCH_X64
#  define ins_atomic_u64_eval(x)                  *((volatile U64 *)(x))
#  define ins_atomic_u64_inc_eval(x)              InterlockedIncrement64((__int64 *)(x))
#  define ins_atomic_u64_dec_eval(x)              InterlockedDecrement64((__int64 *)(x))
#  define ins_atomic_u64_eval_assign(x,c)         InterlockedExchange64((__int64 *)(x),(c))
#  define ins_atomic_u64_add_eval(x,c)            InterlockedAdd64((__int64 *)(x), c)
#  define ins_atomic_u64_eval_cond_assign(x,k,c)  InterlockedCompareExchange64((__int64 *)(x),(k),(c))
#  define ins_atomic_u32_eval(x)                  *((volatile U32 *)(x))
#  define ins_atomic_u32_inc_eval(x)              InterlockedIncrement((LONG *)(x))
#  define ins_atomic_u32_dec_eval(x)              InterlockedDecrement((LONG *)(x))
#  define ins_atomic_u32_eval_assign(x,c)         InterlockedExchange((LONG *)(x),(c))
#  define ins_atomic_u32_eval_cond_assign(x,k,c)  InterlockedCompareExchange((LONG *)(x),(k),(c))
#  define ins_atomic_u32_add_eval(x,c)            InterlockedAdd((LONG *)(x), (c))
# endif
#elif CORE_COMPILER_CLANG || CORE_COMPILER_GCC
#  define ins_atomic_u64_eval(x)                  __atomic_load_n(x, __ATOMIC_SEQ_CST)
#  define ins_atomic_u64_inc_eval(x)              (__atomic_fetch_add((U64 *)(x), 1, __ATOMIC_SEQ_CST) + 1)
#  define ins_atomic_u64_dec_eval(x)              (__atomic_fetch_sub((U64 *)(x), 1, __ATOMIC_SEQ_CST) - 1)
#  define ins_atomic_u64_eval_assign(x,c)         __atomic_exchange_n(x, c, __ATOMIC_SEQ_CST)
#  define ins_atomic_u64_add_eval(x,c)            (__atomic_fetch_add((U64 *)(x), c, __ATOMIC_SEQ_CST) + (c))
#  define ins_atomic_u64_eval_cond_assign(x,k,c)  ({ U64 _new = (c); __atomic_compare_exchange_n((U64 *)(x),&_new,(k),0,__ATOMIC_SEQ_CST,__ATOMIC_SEQ_CST); _new; })
#  define ins_atomic_u32_eval(x)                  __atomic_load_n(x, __ATOMIC_SEQ_CST)
#  define ins_atomic_u32_inc_eval(x)              (__atomic_fetch_add((U32 *)(x), 1, __ATOMIC_SEQ_CST) + 1)
#  define ins_atomic_u32_dec_eval(x)              (__atomic_fetch_sub((U32 *)(x), 1, __ATOMIC_SEQ_CST) - 1)
#  define ins_atomic_u32_add_eval(x,c)            (__atomic_fetch_add((U32 *)(x), c, __ATOMIC_SEQ_CST) + (c))
#  define ins_atomic_u32_eval_assign(x,c)         __atomic_exchange_n((x), (c), __ATOMIC_SEQ_CST)
#  define ins_atomic_u32_eval_cond_assign(x,k,c)  ({ U32 _new = (c); __atomic_compare_exchange_n((U32 *)(x),&_new,(k),0,__ATOMIC_SEQ_CST,__ATOMIC_SEQ_CST); _new; })
#endif

#if CORE_ARCH_64BIT
# define ins_atomic_ptr_eval_cond_assign(x,k,c) (void *)ins_atomic_u64_eval_cond_assign((U64 *)(x), (U64)(k), (U64)(c))
# define ins_atomic_ptr_eval_assign(x,c)        (void *)ins_atomic_u64_eval_assign((U64 *)(x), (U64)(c))
# define ins_atomic_ptr_eval(x)                 (void *)ins_atomic_u64_eval((U64 *)x)
#endif

////////////////////////////////
//~ rjf: Bit Operations

internal U16 bswap_u16(U16 x);
internal U32 bswap_u32(U32 x);
internal U64 bswap_u64(U64 x);

internal U64 ctz32(U32 val);
internal U64 ctz64(U64 val);
internal U64 clz32(U32 val);
internal U64 clz64(U64 val);

internal U64 count_bits_set32(U32 val);
internal U64 count_bits_set64(U64 val);

#endif

#ifdef CORE__IMPLEMENTATION
#if CORE_OS_WINDOWS
#include <Windows.h>
#include <shlobj.h>
internal void *
os_reserve(U64 size)
{
  void *result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE);
  return result;
}

internal B32
os_commit(void *ptr, U64 size)
{
  B32 result = (VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE) != 0);
  //w32_rio_functions.RIODeregisterBuffer(w32_rio_functions.RIORegisterBuffer(ptr, size));
  return result;
}

internal void
os_decommit(void *ptr, U64 size)
{
  VirtualFree(ptr, size, MEM_DECOMMIT);
}

internal void
os_release(void *ptr, U64 size)
{
  // NOTE(rjf): size not used - not necessary on Windows, but necessary for other OSes.
  VirtualFree(ptr, 0, MEM_RELEASE);
}

//- rjf: large pages

internal void *
os_reserve_large(U64 size)
{
  // we commit on reserve because windows
  void *result = VirtualAlloc(0, size, MEM_RESERVE|MEM_COMMIT|MEM_LARGE_PAGES, PAGE_READWRITE);
  return result;
}

internal B32
os_commit_large(void *ptr, U64 size)
{
  return 1;
}

#elif (CORE_OS_LINUX || CORE_OS_MAC)

internal void *
os_reserve(U64 size)
{
  void *result = mmap(0, size, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  if(result == MAP_FAILED)
  {
    result = 0;
  }
  return result;
}

internal B32
os_commit(void *ptr, U64 size)
{
  mprotect(ptr, size, PROT_READ|PROT_WRITE);
  return 1;
}

internal void
os_decommit(void *ptr, U64 size)
{
  madvise(ptr, size, MADV_DONTNEED);
  mprotect(ptr, size, PROT_NONE);
}

internal void
os_release(void *ptr, U64 size)
{
  munmap(ptr, size);
}

#endif

////////////////////////////////
//~ rjf: Arena Functions

//- rjf: arena creation/destruction

#define PAGE_SIZE (4096)

internal Arena *
arena_alloc_(ArenaParams *params)
{
  // rjf: round up reserve/commit sizes
  U64 reserve_size = params->reserve_size;
  U64 commit_size = params->commit_size;
//   if(params->flags & ArenaFlag_LargePages)
//   {
//     reserve_size = AlignPow2(reserve_size, os_get_system_info()->large_page_size);
//     commit_size  = AlignPow2(commit_size,  os_get_system_info()->large_page_size);
//   }
//   else
//   {
//     reserve_size = AlignPow2(reserve_size, os_get_system_info()->page_size);
//     commit_size  = AlignPow2(commit_size,  os_get_system_info()->page_size);
//   }

  reserve_size = AlignPow2(reserve_size, PAGE_SIZE);
  commit_size  = AlignPow2(commit_size,  PAGE_SIZE);
  
  // rjf: reserve/commit initial block
  void *base = params->optional_backing_buffer;
  if(base == 0)
  {
    // if(params->flags & ArenaFlag_LargePages)
    // {
    //   base = os_reserve_large(reserve_size);
    //   os_commit_large(base, commit_size);
    // }
    // else
    {
      base = os_reserve(reserve_size);
      os_commit(base, commit_size);
    }
    //raddbg_annotate_vaddr_range(base, reserve_size, "arena %s:%i", params->allocation_site_file, params->allocation_site_line);
  }
  
  // rjf: panic on arena creation failure
#if OS_FEATURE_GRAPHICAL
  if(Unlikely(base == 0))
  {
    os_graphical_message(1, str8_lit("Fatal Allocation Failure"), str8_lit("Unexpected memory allocation failure."));
    os_abort(1);
  }
#endif
  
  // rjf: extract arena header & fill
  Arena *arena = (Arena *)base;
  arena->current = arena;
  arena->flags = params->flags;
  arena->cmt_size = params->commit_size;
  arena->res_size = params->reserve_size;
  arena->base_pos = 0;
  arena->pos = ARENA_HEADER_SIZE;
  arena->cmt = commit_size;
  arena->res = reserve_size;
  arena->allocation_site_file = params->allocation_site_file;
  arena->allocation_site_line = params->allocation_site_line;
#if ARENA_FREE_LIST
  arena->free_last = 0;
#endif
  AsanPoisonMemoryRegion(base, commit_size);
  AsanUnpoisonMemoryRegion(base, ARENA_HEADER_SIZE);
  return arena;
}

internal void
arena_release(Arena *arena)
{
  for(Arena *n = arena->current, *prev = 0; n != 0; n = prev)
  {
    prev = n->prev;
    os_release(n, n->res);
  }
}

//- rjf: arena push/pop core functions

internal void *
arena_push(Arena *arena, U64 size, U64 align, B32 zero)
{
  Arena *current = arena->current;
  U64 pos_pre = AlignPow2(current->pos, align);
  U64 pos_pst = pos_pre + size;
  
  // rjf: chain, if needed
  if(current->res < pos_pst && !(arena->flags & ArenaFlag_NoChain))
  {
    Arena *new_block = 0;
    
#if ARENA_FREE_LIST
    {
      Arena *prev_block;
      for(new_block = arena->free_last, prev_block = 0; new_block != 0; prev_block = new_block, new_block = new_block->prev)
      {
        if(new_block->res >= AlignPow2(new_block->pos, align) + size)
        {
          if(prev_block)
          {
            prev_block->prev = new_block->prev;
          }
          else
          {
            arena->free_last = new_block->prev;
          }
          break;
        }
      }
    }
#endif
    
    if(new_block == 0)
    {
      U64 res_size = current->res_size;
      U64 cmt_size = current->cmt_size;
      if(size + ARENA_HEADER_SIZE > res_size)
      {
        res_size = AlignPow2(size + ARENA_HEADER_SIZE, align);
        cmt_size = AlignPow2(size + ARENA_HEADER_SIZE, align);
      }
      new_block = arena_alloc(.reserve_size = res_size,
                              .commit_size  = cmt_size,
                              .flags        = current->flags,
                              .allocation_site_file = current->allocation_site_file,
                              .allocation_site_line = current->allocation_site_line);
    }
    
    new_block->base_pos = current->base_pos + current->res;
    SLLStackPush_N(arena->current, new_block, prev);
    
    current = new_block;
    pos_pre = AlignPow2(current->pos, align);
    pos_pst = pos_pre + size;
  }
  
  // rjf: compute the size we need to zero
  U64 size_to_zero = 0;
  if(zero)
  {
    size_to_zero = Min(current->cmt, pos_pst) - pos_pre;
  }
  
  // rjf: commit new pages, if needed
  if(current->cmt < pos_pst)
  {
    U64 cmt_pst_aligned = pos_pst + current->cmt_size-1;
    cmt_pst_aligned -= cmt_pst_aligned%current->cmt_size;
    U64 cmt_pst_clamped = ClampTop(cmt_pst_aligned, current->res);
    U64 cmt_size = cmt_pst_clamped - current->cmt;
    U8 *cmt_ptr = (U8 *)current + current->cmt;
    // if(current->flags & ArenaFlag_LargePages)
    // {
    //   os_commit_large(cmt_ptr, cmt_size);
    // }
    // else
    {
      os_commit(cmt_ptr, cmt_size);
    }
    current->cmt = cmt_pst_clamped;
  }
  
  // rjf: push onto current block
  void *result = 0;
  if(current->cmt >= pos_pst)
  {
    result = (U8 *)current+pos_pre;
    current->pos = pos_pst;
    AsanUnpoisonMemoryRegion(result, size);
    if(size_to_zero != 0)
    {
      MemoryZero(result, size_to_zero);
    }
  }
  
  // rjf: panic on failure
#if OS_FEATURE_GRAPHICAL
  if(Unlikely(result == 0))
  {
    os_graphical_message(1, str8_lit("Fatal Allocation Failure"), str8_lit("Unexpected memory allocation failure."));
    os_abort(1);
  }
#endif
  
  return result;
}

internal U64
arena_pos(Arena *arena)
{
  Arena *current = arena->current;
  U64 pos = current->base_pos + current->pos;
  return pos;
}

internal void
arena_pop_to(Arena *arena, U64 pos)
{
  U64 big_pos = ClampBot(ARENA_HEADER_SIZE, pos);
  Arena *current = arena->current;
  
#if ARENA_FREE_LIST
  for(Arena *prev = 0; current->base_pos >= big_pos; current = prev)
  {
    prev = current->prev;
    current->pos = ARENA_HEADER_SIZE;
    SLLStackPush_N(arena->free_last, current, prev);
    AsanPoisonMemoryRegion((U8*)current + ARENA_HEADER_SIZE, current->res - ARENA_HEADER_SIZE);
  }
#else
  for(Arena *prev = 0; current->base_pos >= big_pos; current = prev)
  {
    prev = current->prev;
    os_release(current, current->res);
  }
#endif
  arena->current = current;
  U64 new_pos = big_pos - current->base_pos;
  AssertAlways(new_pos <= current->pos);
  AsanPoisonMemoryRegion((U8*)current + new_pos, (current->pos - new_pos));
  current->pos = new_pos;
}

//- rjf: arena push/pop helpers

internal void
arena_clear(Arena *arena)
{
  arena_pop_to(arena, 0);
}

internal void
arena_pop(Arena *arena, U64 amt)
{
  U64 pos_old = arena_pos(arena);
  U64 pos_new = pos_old;
  if(amt < pos_old)
  {
    pos_new = pos_old - amt;
  }
  arena_pop_to(arena, pos_new);
}

//- rjf: temporary arena scopes

internal Temp
temp_begin(Arena *arena)
{
  U64 pos = arena_pos(arena);
  Temp temp = {arena, pos};
  return temp;
}

internal void
temp_end(Temp temp)
{
  arena_pop_to(temp.arena, temp.pos);
}
////////////////////////////////
//~ rjf: String Constructors

internal String8
str8(U8 *str, U64 size)
{
  String8 result = {str, size};
  return result;
}

internal String8
str8_range(U8 *first, U8 *one_past_last)
{
  String8 result = {first, (U64)(one_past_last - first)};
  return result;
}

internal String8
str8_zero(void)
{
  String8 result = {0};
  return result;
}

internal String16
str16(U16 *str, U64 size)
{
  String16 result = {str, size};
  return result;
}

internal String16
str16_range(U16 *first, U16 *one_past_last)
{
  String16 result = {first, (U64)(one_past_last - first)};
  return result;
}

internal String16
str16_zero(void)
{
  String16 result = {0};
  return result;
}

internal String32
str32(U32 *str, U64 size)
{
  String32 result = {str, size};
  return result;
}

internal String32
str32_range(U32 *first, U32 *one_past_last)
{
  String32 result = {first, (U64)(one_past_last - first)};
  return result;
}

internal String32
str32_zero(void)
{
  String32 result = {0};
  return result;
}

internal U64
cstring8_length(U8 *c)
{
  U64 length = 0;
  if(c)
  {
    U8 *p = c;
    for(;*p != 0; p += 1);
    length = (U64)(p - c);
  }
  return length;
}

internal U64
cstring16_length(U16 *c)
{
  U64 length = 0;
  if(c)
  {
    U16 *p = c;
    for(;*p != 0; p += 1);
    length = (U64)(p - c);
  }
  return length;
}

internal U64
cstring32_length(U32 *c)
{
  U64 length = 0;
  if(c)
  {
    U32 *p = c;
    for(;*p != 0; p += 1);
    length = (U64)(p - c);
  }
  return length;
}

internal String8
str8_cstring(char *c)
{
  String8 result = {(U8*)c, cstring8_length((U8*)c)};
  return result;
}

internal String16
str16_cstring(U16 *c)
{
  String16 result = {(U16*)c, cstring16_length((U16*)c)};
  return result;
}

internal String32
str32_cstring(U32 *c)
{
  String32 result = {(U32*)c, cstring32_length((U32*)c)};
  return result;
}

internal String8
str8_cstring_capped(void *cstr, void *cap)
{
  char *ptr = (char *)cstr;
  char *opl = (char *)cap;
  for (;ptr < opl && *ptr != 0; ptr += 1);
  U64 size = (U64)(ptr - (char *)cstr);
  String8 result = str8((U8*)cstr, size);
  return result;
}

internal String16
str16_cstring_capped(void *cstr, void *cap)
{
  U16 *ptr = (U16 *)cstr;
  U16 *opl = (U16 *)cap;
  for (;ptr < opl && *ptr != 0; ptr += 1);
  U64 size = (U64)(ptr - (U16 *)cstr);
  String16 result = str16(cstr, size);
  return result;
}

internal String8
str8_cstring_capped_reverse(void *raw_start, void *raw_cap)
{
  U8 *start = raw_start;
  U8 *ptr   = raw_cap;
  for(; ptr > start; )
  {
    ptr -= 1;
    if (*ptr == '\0')
    {
      break;
    }
  }
  U64 size = (U64)(ptr - start);
  String8 result  = str8(start, size);
  return result;
}

internal String8 str8_skip(String8 str, U64 amt) {
  U64 clamped_amt = Min(amt, str.size);
  String8 result = {str.str + clamped_amt, str.size - clamped_amt};
  return result;
}

internal String8 str8_substr(String8 str, U64 start, U64 size) {
  Assert(start + size <= str.size);
  String8 result = {str.str + start, size};
  return result;
}

internal S32 str8_cmp(String8 str1, String8 str2) {
  if (str1.size == str2.size) {
    return MemoryCompare(str1.str, str2.str, str1.size);
  }
  return str1.size - str2.size;
}

internal B32 str8_equals(String8 str1, String8 str2) {
  return str8_cmp(str1, str2) == 0;
}

internal B32 str8_wildcard(String8 str, String8 pattern) {
  return wildcard_match_inner(str.str, str.size, pattern.str, pattern.size);
}
  
internal String16 str16_copy_to(Arena *arena, String16 str) {
  U16 *new_str = push_array(arena, U16, str.size);
  MemoryCopy(new_str, str.str, str.size);
  String16 result = {new_str, str.size};
  return result;
}

internal String16 str16_substr(String16 str, U64 start, U64 size) {
  Assert(start + size <= str.size);
  String16 result = {str.str + start, size};
  return result;
}

internal String16 str16_clamp_to(String16 str, U64 size) {
  String16 result = {str.str, ClampTop(size, str.size)};
  return result;
}

////////////////////////////////
//~ rjf: UTF-8 & UTF-16 Decoding/Encoding

read_only global U8 utf8_class[32] =
{
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,2,2,2,2,3,3,4,5,
};

internal UnicodeDecode
utf8_decode(U8 *str, U64 max)
{
  UnicodeDecode result = {1, max_U32};
  U8 byte = str[0];
  U8 byte_class = utf8_class[byte >> 3];
  switch(byte_class)
  {
    case 1:
    {
      result.codepoint = byte;
    }break;
    case 2:
    {
      if(1 < max)
      {
        U8 cont_byte = str[1];
        if(utf8_class[cont_byte >> 3] == 0)
        {
          result.codepoint = (byte & bitmask5) << 6;
          result.codepoint |=  (cont_byte & bitmask6);
          result.inc = 2;
        }
      }
    }break;
    case 3:
    {
      if(2 < max)
      {
        U8 cont_byte[2] = {str[1], str[2]};
        if(utf8_class[cont_byte[0] >> 3] == 0 &&
           utf8_class[cont_byte[1] >> 3] == 0)
        {
          result.codepoint = (byte & bitmask4) << 12;
          result.codepoint |= ((cont_byte[0] & bitmask6) << 6);
          result.codepoint |=  (cont_byte[1] & bitmask6);
          result.inc = 3;
        }
      }
    }break;
    case 4:
    {
      if(3 < max)
      {
        U8 cont_byte[3] = {str[1], str[2], str[3]};
        if(utf8_class[cont_byte[0] >> 3] == 0 &&
           utf8_class[cont_byte[1] >> 3] == 0 &&
           utf8_class[cont_byte[2] >> 3] == 0)
        {
          result.codepoint = (byte & bitmask3) << 18;
          result.codepoint |= ((cont_byte[0] & bitmask6) << 12);
          result.codepoint |= ((cont_byte[1] & bitmask6) <<  6);
          result.codepoint |=  (cont_byte[2] & bitmask6);
          result.inc = 4;
        }
      }
    }
  }
  return result;
}

internal UnicodeDecode
utf16_decode(U16 *str, U64 max)
{
  UnicodeDecode result = {1, max_U32};
  result.codepoint = str[0];
  result.inc = 1;
  if(max > 1 && 0xD800 <= str[0] && str[0] < 0xDC00 && 0xDC00 <= str[1] && str[1] < 0xE000)
  {
    result.codepoint = ((str[0] - 0xD800) << 10) | ((str[1] - 0xDC00) + 0x10000);
    result.inc = 2;
  }
  return result;
}

internal U32
utf8_encode(U8 *str, U32 codepoint)
{
  U32 inc = 0;
  if(codepoint <= 0x7F)
  {
    str[0] = (U8)codepoint;
    inc = 1;
  }
  else if(codepoint <= 0x7FF)
  {
    str[0] = (bitmask2 << 6) | ((codepoint >> 6) & bitmask5);
    str[1] = bit8 | (codepoint & bitmask6);
    inc = 2;
  }
  else if(codepoint <= 0xFFFF)
  {
    str[0] = (bitmask3 << 5) | ((codepoint >> 12) & bitmask4);
    str[1] = bit8 | ((codepoint >> 6) & bitmask6);
    str[2] = bit8 | ( codepoint       & bitmask6);
    inc = 3;
  }
  else if(codepoint <= 0x10FFFF)
  {
    str[0] = (bitmask4 << 4) | ((codepoint >> 18) & bitmask3);
    str[1] = bit8 | ((codepoint >> 12) & bitmask6);
    str[2] = bit8 | ((codepoint >>  6) & bitmask6);
    str[3] = bit8 | ( codepoint        & bitmask6);
    inc = 4;
  }
  else
  {
    str[0] = '?';
    inc = 1;
  }
  return inc;
}

internal U32
utf16_encode(U16 *str, U32 codepoint)
{
  U32 inc = 1;
  if(codepoint == max_U32)
  {
    str[0] = (U16)'?';
  }
  else if(codepoint < 0x10000)
  {
    str[0] = (U16)codepoint;
  }
  else
  {
    U32 v = codepoint - 0x10000;
    str[0] = safe_cast_u16(0xD800 + (v >> 10));
    str[1] = safe_cast_u16(0xDC00 + (v & bitmask10));
    inc = 2;
  }
  return inc;
}

////////////////////////////////
//~ rjf: Unicode String Conversions

internal String8
str8_from_16(Arena *arena, String16 in)
{
  String8 result = str8_zero();
  if(in.size)
  {
    U64 cap = in.size*3;
    U8 *str = push_array_no_zero(arena, U8, cap + 1);
    U16 *ptr = in.str;
    U16 *opl = ptr + in.size;
    U64 size = 0;
    UnicodeDecode consume;
    for(;ptr < opl; ptr += consume.inc)
    {
      consume = utf16_decode(ptr, opl - ptr);
      size += utf8_encode(str + size, consume.codepoint);
    }
    str[size] = 0;
    arena_pop(arena, (cap - size));
    result = str8(str, size);
  }
  return result;
}

internal String16
str16_from_8(Arena *arena, String8 in)
{
  String16 result = str16_zero();
  if(in.size)
  {
    U64 cap = in.size*2;
    U16 *str = push_array_no_zero(arena, U16, cap + 1);
    U8 *ptr = in.str;
    U8 *opl = ptr + in.size;
    U64 size = 0;
    UnicodeDecode consume;
    for(;ptr < opl; ptr += consume.inc)
    {
      consume = utf8_decode(ptr, opl - ptr);
      size += utf16_encode(str + size, consume.codepoint);
    }
    str[size] = 0;
    arena_pop(arena, (cap - size)*2);
    result = str16(str, size);
  }
  return result;
}

internal String8
str8_from_32(Arena *arena, String32 in)
{
  String8 result = str8_zero();
  if(in.size)
  {
    U64 cap = in.size*4;
    U8 *str = push_array_no_zero(arena, U8, cap + 1);
    U32 *ptr = in.str;
    U32 *opl = ptr + in.size;
    U64 size = 0;
    for(;ptr < opl; ptr += 1)
    {
      size += utf8_encode(str + size, *ptr);
    }
    str[size] = 0;
    arena_pop(arena, (cap - size));
    result = str8(str, size);
  }
  return result;
}

internal String32
str32_from_8(Arena *arena, String8 in)
{
  String32 result = str32_zero(); 
  if(in.size)
  {
    U64 cap = in.size;
    U32 *str = push_array_no_zero(arena, U32, cap + 1);
    U8 *ptr = in.str;
    U8 *opl = ptr + in.size;
    U64 size = 0;
    UnicodeDecode consume;
    for(;ptr < opl; ptr += consume.inc)
    {
      consume = utf8_decode(ptr, opl - ptr);
      str[size] = consume.codepoint;
      size += 1;
    }
    str[size] = 0;
    arena_pop(arena, (cap - size)*4);
    result = str32(str, size);
  }
  return result;
}

internal B32 wildcard_match_inner(char* str, size_t str_len, char* pattern, size_t pattern_len) {
    char* submatch = NULL;
    size_t submatch_len = 0;
    char* subpattern = NULL;
    size_t subpattern_len = 0;

    while (str_len > 0) {
        if (pattern_len > 0) {
            if (pattern[0] == '\\') {
                if (pattern_len >= 2) {
                    char lit = pattern[1];
                    if (str[0] == lit) {
                        str++; str_len--;
                        pattern += 2; pattern_len -= 2;
                        continue;
                    }
                } else {
                    if (str[0] == '\\') {
                        str++; str_len--;
                        pattern++; pattern_len--;
                        continue;
                    }
                }
            }
            else if (pattern[0] == str[0] || pattern[0] == '?') {
                str++; str_len--;
                pattern++; pattern_len--;
                continue;
            }
            else if (pattern[0] == '*') {
                submatch = str; submatch_len = str_len;

                subpattern = ++pattern; subpattern_len = --pattern_len;
                continue;
            }
        }
        if (submatch != NULL) {
            str = ++submatch; str_len = --submatch_len;
            pattern = subpattern; pattern_len = subpattern_len;
            continue;
        }
        return 0;
    }
    while (pattern_len > 0 && pattern[0] == '*') {
        pattern++; pattern_len--;
    }
    return pattern_len == 0;
}

internal B32 wildcard_match(char* str, char* pattern) {
    return wildcard_match_inner(str, strlen(str), pattern, strlen(pattern));
}

////////////////////////////////
//~ rjf: String Parsing Functions

internal String8
str8_prefix(String8 str, U64 size)
{
  str.size = ClampTop(size, str.size);
  return str;
}

internal S64
sign_from_str8(String8 string, String8 *string_tail)
{
  // count negative signs
  U64 neg_count = 0;
  U64 i = 0;
  for(; i < string.size; i += 1)
  {
    if (string.str[i] == '-'){
      neg_count += 1;
    }
    else if (string.str[i] != '+'){
      break;
    }
  }
  
  // output part of string after signs
  *string_tail = str8_skip(string, i);
  
  // output integer sign
  S64 sign = (neg_count & 1) ? -1 : +1;
  return sign;
}

internal B32
str8_is_integer(String8 string, U32 radix)
{
  B32 result = 0;
  if(string.size > 0)
  {
    if(1 < radix && radix <= 16)
    {
      result = 1;
      for(U64 i = 0; i < string.size; i += 1)
      {
        U8 c = string.str[i];
        if(!(c < 0x80) || integer_symbol_reverse[c] >= radix)
        {
          result = 0;
          break;
        }
      }
    }
  }
  return result;
}

internal U64
u64_from_str8(String8 string, U32 radix)
{
  U64 x = 0;
  if(1 < radix && radix <= 16)
  {
    for(U64 i = 0; i < string.size; i += 1)
    {
      x *= radix;
      x += integer_symbol_reverse[string.str[i] & 0x7F];
    }
  }
  return x;
}

internal S64
s64_from_str8(String8 string, U32 radix)
{
  S64 sign = sign_from_str8(string, &string);
  S64 x = (S64)u64_from_str8(string, radix) * sign;
  return x;
}

internal B32
try_u64_from_str8_c_rules(String8 string, U64 *x)
{
  // unpack radix / prefix size based on string prefix
  U64 radix = 0;
  U64 prefix_size = 0;
  
  // hex
  if(str8_match(str8_prefix(string, 2), str8_lit("0x"), StringMatchFlag_CaseInsensitive))
  {
    radix = 0x10; prefix_size = 2;
  }
  // binary
  else if(str8_match(str8_prefix(string, 2), str8_lit("0b"), StringMatchFlag_CaseInsensitive))
  {
    radix = 2; prefix_size = 2;
  }
  // octal
  else if(str8_match(str8_prefix(string, 1), str8_lit("0"), StringMatchFlag_CaseInsensitive) && string.size > 1)
  {
    radix = 010; prefix_size = 1;
  }
  // decimal
  else
  {
    radix = 10; prefix_size = 0;
  }
  
  // convert if we can
  String8 integer    = str8_skip(string, prefix_size);
  B32     is_integer = str8_is_integer(integer, radix);
  if(is_integer)
  {
    *x = u64_from_str8(integer, radix);
  }
  
  return is_integer;
}

internal B32
try_s64_from_str8_c_rules(String8 string, S64 *x)
{
  String8 string_tail = {0};
  S64 sign = sign_from_str8(string, &string_tail);
  U64 x_u64 = 0;
  B32 is_integer = try_u64_from_str8_c_rules(string_tail, &x_u64);
  *x = x_u64 * sign;
  return is_integer;
}

////////////////////////////////
//~ rjf: Character Helpers

internal U8 upper_from_char(U8 c) {
  return (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c;
}

internal B32 char_is_slash(U8 c) {
  return (c == '/' || c == '\\');
}

internal U8 correct_slash_from_char(U8 c) {
  return char_is_slash(c) ? '/' : c;
}

////////////////////////////////
//~ rjf: String Matching

internal B32
str8_match(String8 a, String8 b, StringMatchFlags flags)
{
  B32 result = 0;
  if(a.size == b.size && flags == 0)
  {
    result = MemoryMatch(a.str, b.str, b.size);
  }
  else if(a.size == b.size || (flags & StringMatchFlag_RightSideSloppy))
  {
    B32 case_insensitive  = (flags & StringMatchFlag_CaseInsensitive);
    B32 slash_insensitive = (flags & StringMatchFlag_SlashInsensitive);
    U64 size              = Min(a.size, b.size);
    result = 1;
    for(U64 i = 0; i < size; i += 1)
    {
      U8 at = a.str[i];
      U8 bt = b.str[i];
      if(case_insensitive)
      {
        at = upper_from_char(at);
        bt = upper_from_char(bt);
      }
      if(slash_insensitive)
      {
        at = correct_slash_from_char(at);
        bt = correct_slash_from_char(bt);
      }
      if(at != bt)
      {
        result = 0;
        break;
      }
    }
  }
  return result;
}

internal String8
str8_chop_last_slash(String8 string)
{
  if(string.size > 0)
  {
    U8 *ptr = string.str + string.size - 1;
    for(;ptr >= string.str; ptr -= 1)
    {
      if(*ptr == '/' || *ptr == '\\')
      {
        break;
      }
    }
    if(ptr >= string.str)
    {
      string.size = (U64)(ptr - string.str);
    }
    else
    {
      string.size = 0;
    }
  }
  return string;
}

internal String8
str8_skip_last_slash(String8 string)
{
  if(string.size > 0)
  {
    U8 *ptr = string.str + string.size - 1;
    for(;ptr >= string.str; ptr -= 1)
    {
      if(*ptr == '/' || *ptr == '\\')
      {
        break;
      }
    }
    if(ptr >= string.str)
    {
      ptr += 1;
      string.size = (U64)(string.str + string.size - ptr);
      string.str = ptr;
    }
  }
  return string;
}

internal String8
str8_chop_last_dot(String8 string)
{
  String8 result = string;
  U64 p = string.size;
  for(;p > 0;)
  {
    p -= 1;
    if(string.str[p] == '.')
    {
      result = str8_prefix(string, p);
      break;
    }
  }
  return result;
}

internal String8
str8_skip_last_dot(String8 string)
{
  String8 result = string;
  U64 p = string.size;
  for(;p > 0;)
  {
    p -= 1;
    if(string.str[p] == '.')
    {
      result = str8_skip(string, p + 1);
      break;
    }
  }
  return result;
}

////////////////////////////////
//~ rjf: String Path Helpers Implementation

internal B32
char_is_alpha(U8 c)
{
  return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

internal PathStyle
path_style_from_str8(String8 string)
{
  PathStyle result = PathStyle_Relative;
  if(string.size >= 1 && string.str[0] == '/')
  {
    result = PathStyle_UnixAbsolute;
  }
  else if(string.size >= 2 &&
          char_is_alpha(string.str[0]) &&
          string.str[1] == ':')
  {
    if(string.size == 2 || char_is_slash(string.str[2]))
    {
      result = PathStyle_WindowsAbsolute;
    }
  }
  return result;
}

internal String8List
str8_split_path(Arena *arena, String8 string)
{
  String8List result = str8_split(arena, string, (U8*)"/\\", 2);
  return result;
}

internal String8
str8_path_list_join_by_style(Arena *arena, String8List *path, PathStyle style)
{
  StringJoin params = {0};
  switch(style)
  {
    case PathStyle_Null:{}break;
    case PathStyle_Relative:
    case PathStyle_WindowsAbsolute:
    {
      params.sep = str8_lit("/");
    }break;
    
    case PathStyle_UnixAbsolute:
    {
      params.pre = str8_lit("/");
      params.sep = str8_lit("/");
    }break;
  }
  String8 result = str8_list_join(arena, path, &params);
  return result;
}

internal String8
path_separator_string_from_style(PathStyle style)
{
  String8 result = str8_zero();
  switch(style)
  {
    case PathStyle_Null:     break;
    case PathStyle_Relative: break;
    case PathStyle_WindowsAbsolute: result = str8_lit("\\"); break;
    case PathStyle_UnixAbsolute:    result = str8_lit("/");  break;
  }
  return result;
}

internal String8
path_convert_slashes(Arena *arena, String8 path, PathStyle path_style)
{
  Temp scratch = temp_begin(arena_alloc());
  String8List list = str8_split_path(scratch.arena, path);
  StringJoin join = {0};
  join.sep = path_separator_string_from_style(path_style);
  String8 result = str8_list_join(arena, &list, &join);
  temp_end(scratch);
  return result;
}

internal String8
path_replace_file_extension(Arena *arena, String8 file_name, String8 ext)
{
  String8 file_name_no_ext = str8_chop_last_dot(file_name);
  String8 result           = str8f(arena, "%S.%S", file_name_no_ext, ext);
  return result;
}

internal U64 
str8_index_of(String8 str, U8* character, U64 character_count) 
{
  for (U64 i = 0; i < str.size; i++) {
    for (U64 j = 0; j < character_count; j++) {
      if (str.str[i] == character[j]) {
        return i;
      }
    }
  }
  return max_U64;
}

internal U64
str8_find_needle(String8 string, U64 start_pos, String8 needle, StringMatchFlags flags)
{
  U8 *p = string.str + start_pos;
  U64 stop_offset = Max(string.size + 1, needle.size) - needle.size;
  U8 *stop_p = string.str + stop_offset;
  if(needle.size > 0)
  {
    U8 *string_opl = string.str + string.size;
    String8 needle_tail = str8_skip(needle, 1);
    StringMatchFlags adjusted_flags = flags | StringMatchFlag_RightSideSloppy;
    U8 needle_first_char_adjusted = needle.str[0];
    if(adjusted_flags & StringMatchFlag_CaseInsensitive)
    {
      needle_first_char_adjusted = upper_from_char(needle_first_char_adjusted);
    }
    for(; p < stop_p; p += 1)
    {
      U8 haystack_char_adjusted = *p;
      if(adjusted_flags & StringMatchFlag_CaseInsensitive)
      {
        haystack_char_adjusted = upper_from_char(haystack_char_adjusted);
      }
      if(haystack_char_adjusted == needle_first_char_adjusted)
      {
        if(str8_match(str8_range(p + 1, string_opl), needle_tail, adjusted_flags))
        {
          break;
        }
      }
    }
  }
  U64 result = string.size;
  if(p < stop_p)
  {
    result = (U64)(p - string.str);
  }
  return result;
}

////////////////////////////////
//~ rjf: Fuzzy Match Implementation

internal FuzzyMatchRangeList
fuzzy_match_find(Arena *arena, String8 needle, String8 haystack)
{
  FuzzyMatchRangeList result = {0};
  Temp scratch = temp_begin(arena);
  U8 space = ' ';
  String8List needles = str8_split(scratch.arena, needle, &space, 1);
  result.needle_part_count = needles.node_count;
  for(String8Node *needle_n = needles.first; needle_n != 0; needle_n = needle_n->next)
  {
    U64 find_pos = 0;
    for(; find_pos < haystack.size;)
    {
      find_pos = str8_find_needle(haystack, find_pos, needle_n->string, StringMatchFlag_CaseInsensitive|StringMatchFlag_SlashInsensitive);
      B32 is_in_gathered_ranges = 0;
      for(FuzzyMatchRangeNode *n = result.first; n != 0; n = n->next)
      {
        if(n->range.min <= find_pos && find_pos < n->range.max)
        {
          is_in_gathered_ranges = 1;
          find_pos = n->range.max;
          break;
        }
      }
      if(!is_in_gathered_ranges)
      {
        break;
      }
    }
    if(find_pos < haystack.size)
    {
      Rng1U64 range = r1u64(find_pos, find_pos + needle_n->string.size);
      FuzzyMatchRangeNode *n = push_array(arena, FuzzyMatchRangeNode, 1);
      n->range = range;
      SLLQueuePush(result.first, result.last, n);
      result.count += 1;
      result.total_dim += dim_1u64(range);
    }
  }
  temp_end(scratch);
  return result;
}

internal FuzzyMatchRangeList
fuzzy_match_range_list_copy(Arena *arena, FuzzyMatchRangeList *src)
{
  FuzzyMatchRangeList dst = {0};
  for(FuzzyMatchRangeNode *src_n = src->first; src_n != 0; src_n = src_n->next)
  {
    FuzzyMatchRangeNode *dst_n = push_array(arena, FuzzyMatchRangeNode, 1);
    SLLQueuePush(dst.first, dst.last, dst_n);
    dst_n->range = src_n->range;
  }
  dst.count = src->count;
  dst.needle_part_count = src->needle_part_count;
  dst.total_dim = src->total_dim;
  return dst;
}

////////////////////////////////
//~ rjf: String List Functions

internal void
str8_list_push(Arena *arena, String8List *list, String8 string)
{
  String8Node *node = push_array_no_zero(arena, String8Node, 1);
  node->next = 0;
  node->string = string;
  SLLQueuePush(list->first, list->last, node);
  list->node_count += 1;
  list->total_size += string.size;
}

internal String8List
str8_split(Arena *arena, String8 string, U8 *split_chars, U64 split_char_count)
{
  String8List list = {0};
  U8 *ptr = string.str;
  U8 *opl = string.str + string.size;
  for(; ptr < opl;)
  {
    U8 *first = ptr;
    for(; ptr < opl; ptr += 1)
    {
      U8 c = *ptr;
      B32 is_split = 0;
      for(U64 i = 0; i < split_char_count; i += 1)
      {
        if(split_chars[i] == c)
        {
          is_split = 1;
          break;
        }
      }
      if(is_split)
      {
        break;
      }
    }
    String8 substr = str8_range(first, ptr);
    if(substr.size > 0)
    {
      str8_list_push(arena, &list, substr);
    }
    ptr += 1;
  }
  return list;
}

internal String8
str8_cat(Arena *arena, String8 s1, String8 s2)
{
  String8 str;
  str.size = s1.size + s2.size;
  str.str = push_array_no_zero(arena, U8, str.size + 1);
  MemoryCopy(str.str, s1.str, s1.size);
  MemoryCopy(str.str + s1.size, s2.str, s2.size);
  str.str[str.size] = 0;
  return str;
}

internal String8
str8_copy(Arena *arena, String8 s)
{
  String8 result;
  result.size = s.size;
  result.str = push_array_no_zero(arena, U8, result.size + 1);
  MemoryCopy(result.str, s.str, s.size);
  result.str[result.size] = 0;
  return result;
}

internal String8
str8fv(Arena *arena, char *fmt, va_list args)
{
  va_list args2;
  va_copy(args2, args);
  int needed_bytes = vsnprintf(0, 0, fmt, args) + 1;
  String8 result = {0};
  result.str = push_array_no_zero(arena, U8, needed_bytes);
  result.size = vsnprintf((char*)result.str, needed_bytes, fmt, args2);
  result.str[result.size] = 0;
  va_end(args2);
  return result;
}

internal String8
str8f(Arena *arena, char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  String8 result = str8fv(arena, fmt, args);
  va_end(args);
  return result;
}

internal String8
str8_list_join(Arena *arena, String8List *list, StringJoin *optional_params)
{
  StringJoin join = {0};
  if(optional_params != 0)
  {
    MemoryCopyStruct(&join, optional_params);
  }
  U64 sep_count = 0;
  if(list->node_count > 0)
  {
    sep_count = list->node_count - 1;
  }
  String8 result;
  result.size = join.pre.size + join.post.size + sep_count*join.sep.size + list->total_size;
  U8 *ptr = result.str = push_array_no_zero(arena, U8, result.size + 1);
  MemoryCopy(ptr, join.pre.str, join.pre.size);
  ptr += join.pre.size;
  for(String8Node *node = list->first; node != 0; node = node->next)
  {
    MemoryCopy(ptr, node->string.str, node->string.size);
    ptr += node->string.size;
    if(node->next != 0)
    {
      MemoryCopy(ptr, join.sep.str, join.sep.size);
      ptr += join.sep.size;
    }
  }
  MemoryCopy(ptr, join.post.str, join.post.size);
  ptr += join.post.size;
  *ptr = 0;
  return result;
}

////////////////////////////////
//~ rjf: Threading Implementation

#if CORE_OS_WINDOWS

////////////////////////////////
//~ rjf: Windows Entity Types

typedef enum OS_W32_EntityKind
{
  OS_W32_EntityKind_Null,
  OS_W32_EntityKind_Thread,
  OS_W32_EntityKind_Mutex,
  OS_W32_EntityKind_RWMutex,
  OS_W32_EntityKind_ConditionVariable,
  OS_W32_EntityKind_Barrier,
}
OS_W32_EntityKind;

typedef struct OS_W32_Entity OS_W32_Entity;
struct OS_W32_Entity
{
  OS_W32_Entity *next;
  OS_W32_EntityKind kind;
  union
  {
    struct
    {
      ThreadEntryPointFunctionType *func;
      void *ptr;
      HANDLE handle;
      DWORD tid;
    } thread;
    CRITICAL_SECTION mutex;
    SRWLOCK rw_mutex;
    CONDITION_VARIABLE cv;
    SYNCHRONIZATION_BARRIER sb;
  };
};

////////////////////////////////
//~ rjf: Windows Threading State

typedef struct OS_W32_ThreadState OS_W32_ThreadState;
struct OS_W32_ThreadState
{
  Arena *entity_arena;
  CRITICAL_SECTION entity_mutex;
  OS_W32_Entity *entity_free;
  B32 initialized;
};

global OS_W32_ThreadState os_w32_thread_state = {0};

////////////////////////////////
//~ rjf: Windows System/Process Info State

typedef struct OS_W32_State OS_W32_State;
struct OS_W32_State
{
  Arena *arena;
  OS_SystemInfo system_info;
  OS_ProcessInfo process_info;
  B32 initialized;
};

global OS_W32_State os_w32_state = {0};

////////////////////////////////
//~ rjf: Windows Entity Functions

internal void
os_w32_thread_state_init(void)
{
  if(!os_w32_thread_state.initialized)
  {
    InitializeCriticalSection(&os_w32_thread_state.entity_mutex);
    os_w32_thread_state.entity_arena = arena_alloc();
    os_w32_thread_state.initialized = 1;
  }
}

internal OS_W32_Entity *
os_w32_entity_alloc(OS_W32_EntityKind kind)
{
  os_w32_thread_state_init();
  OS_W32_Entity *result = 0;
  EnterCriticalSection(&os_w32_thread_state.entity_mutex);
  {
    result = os_w32_thread_state.entity_free;
    if(result)
    {
      SLLStackPop(os_w32_thread_state.entity_free);
    }
    else
    {
      result = push_array_no_zero(os_w32_thread_state.entity_arena, OS_W32_Entity, 1);
    }
    MemoryZeroStruct(result);
  }
  LeaveCriticalSection(&os_w32_thread_state.entity_mutex);
  result->kind = kind;
  return result;
}

internal void
os_w32_entity_release(OS_W32_Entity *entity)
{
  entity->kind = OS_W32_EntityKind_Null;
  EnterCriticalSection(&os_w32_thread_state.entity_mutex);
  SLLStackPush(os_w32_thread_state.entity_free, entity);
  LeaveCriticalSection(&os_w32_thread_state.entity_mutex);
}

////////////////////////////////
//~ rjf: Windows Thread Entry Point

internal DWORD
os_w32_thread_entry_point(void *ptr)
{
  OS_W32_Entity *entity = (OS_W32_Entity *)ptr;
  ThreadEntryPointFunctionType *func = entity->thread.func;
  void *thread_ptr = entity->thread.ptr;
  func(thread_ptr);
  return 0;
}

////////////////////////////////
//~ rjf: Windows Sleep Helper

internal U32
os_w32_sleep_ms_from_endt_us(U64 endt_us)
{
  U32 sleep_ms = 0;
  if(endt_us == max_U64)
  {
    sleep_ms = INFINITE;
  }
  else
  {
    LARGE_INTEGER perf_freq;
    LARGE_INTEGER perf_counter;
    QueryPerformanceFrequency(&perf_freq);
    QueryPerformanceCounter(&perf_counter);
    U64 now_us = (perf_counter.QuadPart * 1000000) / perf_freq.QuadPart;
    if(now_us < endt_us)
    {
      U64 sleep_us = endt_us - now_us;
      sleep_ms = (U32)((sleep_us + 999)/1000);
    }
  }
  return sleep_ms;
}

////////////////////////////////
//~ rjf: Windows Thread Info

internal U32
os_tid(void)
{
  DWORD id = GetCurrentThreadId();
  return (U32)id;
}

internal void
os_set_thread_name(String8 name)
{
  // NOTE: This uses the raise-exception style naming which works with debuggers
  // For Windows 10+, SetThreadDescription would be preferred but requires dynamic loading
  (void)name;
}

////////////////////////////////
//~ rjf: Windows Threads

internal Thread
os_thread_launch(ThreadEntryPointFunctionType *f, void *p)
{
  OS_W32_Entity *entity = os_w32_entity_alloc(OS_W32_EntityKind_Thread);
  entity->thread.func = f;
  entity->thread.ptr = p;
  entity->thread.handle = CreateThread(0, 0, os_w32_thread_entry_point, entity, 0, &entity->thread.tid);
  Thread result = {IntFromPtr(entity)};
  return result;
}

internal B32
os_thread_join(Thread handle, U64 endt_us)
{
  DWORD sleep_ms = os_w32_sleep_ms_from_endt_us(endt_us);
  OS_W32_Entity *entity = (OS_W32_Entity *)PtrFromInt(handle.u64[0]);
  DWORD wait_result = WAIT_OBJECT_0;
  if(entity != 0)
  {
    wait_result = WaitForSingleObject(entity->thread.handle, sleep_ms);
    CloseHandle(entity->thread.handle);
    os_w32_entity_release(entity);
  }
  return (wait_result == WAIT_OBJECT_0);
}

internal void
os_thread_detach(Thread thread)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(thread.u64[0]);
  if(entity != 0)
  {
    CloseHandle(entity->thread.handle);
    os_w32_entity_release(entity);
  }
}

////////////////////////////////
//~ rjf: Windows Mutexes

internal Mutex
os_mutex_alloc(void)
{
  OS_W32_Entity *entity = os_w32_entity_alloc(OS_W32_EntityKind_Mutex);
  InitializeCriticalSection(&entity->mutex);
  Mutex result = {IntFromPtr(entity)};
  return result;
}

internal void
os_mutex_release(Mutex mutex)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(mutex.u64[0]);
  DeleteCriticalSection(&entity->mutex);
  os_w32_entity_release(entity);
}

internal void
os_mutex_take(Mutex mutex)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(mutex.u64[0]);
  EnterCriticalSection(&entity->mutex);
}

internal void
os_mutex_drop(Mutex mutex)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(mutex.u64[0]);
  LeaveCriticalSection(&entity->mutex);
}

////////////////////////////////
//~ rjf: Windows RW Mutexes

internal RWMutex
os_rw_mutex_alloc(void)
{
  OS_W32_Entity *entity = os_w32_entity_alloc(OS_W32_EntityKind_RWMutex);
  InitializeSRWLock(&entity->rw_mutex);
  RWMutex result = {IntFromPtr(entity)};
  return result;
}

internal void
os_rw_mutex_release(RWMutex rw_mutex)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(rw_mutex.u64[0]);
  os_w32_entity_release(entity);
}

internal void
os_rw_mutex_take(RWMutex rw_mutex, B32 write_mode)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(rw_mutex.u64[0]);
  if(write_mode)
  {
    AcquireSRWLockExclusive(&entity->rw_mutex);
  }
  else
  {
    AcquireSRWLockShared(&entity->rw_mutex);
  }
}

internal void
os_rw_mutex_drop(RWMutex rw_mutex, B32 write_mode)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(rw_mutex.u64[0]);
  if(write_mode)
  {
    ReleaseSRWLockExclusive(&entity->rw_mutex);
  }
  else
  {
    ReleaseSRWLockShared(&entity->rw_mutex);
  }
}

////////////////////////////////
//~ rjf: Windows Condition Variables

internal CondVar
os_cond_var_alloc(void)
{
  OS_W32_Entity *entity = os_w32_entity_alloc(OS_W32_EntityKind_ConditionVariable);
  InitializeConditionVariable(&entity->cv);
  CondVar result = {IntFromPtr(entity)};
  return result;
}

internal void
os_cond_var_release(CondVar cv)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(cv.u64[0]);
  os_w32_entity_release(entity);
}

internal B32
os_cond_var_wait(CondVar cv, Mutex mutex, U64 endt_us)
{
  U32 sleep_ms = os_w32_sleep_ms_from_endt_us(endt_us);
  BOOL result = 0;
  if(sleep_ms > 0)
  {
    OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(cv.u64[0]);
    OS_W32_Entity *mutex_entity = (OS_W32_Entity*)PtrFromInt(mutex.u64[0]);
    result = SleepConditionVariableCS(&entity->cv, &mutex_entity->mutex, sleep_ms);
  }
  return result;
}

internal B32
os_cond_var_wait_rw(CondVar cv, RWMutex mutex_rw, B32 write_mode, U64 endt_us)
{
  U32 sleep_ms = os_w32_sleep_ms_from_endt_us(endt_us);
  BOOL result = 0;
  if(sleep_ms > 0)
  {
    OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(cv.u64[0]);
    OS_W32_Entity *mutex_entity = (OS_W32_Entity*)PtrFromInt(mutex_rw.u64[0]);
    result = SleepConditionVariableSRW(&entity->cv, &mutex_entity->rw_mutex, sleep_ms,
                                       write_mode ? 0 : CONDITION_VARIABLE_LOCKMODE_SHARED);
  }
  return result;
}

internal void
os_cond_var_signal(CondVar cv)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(cv.u64[0]);
  WakeConditionVariable(&entity->cv);
}

internal void
os_cond_var_broadcast(CondVar cv)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(cv.u64[0]);
  WakeAllConditionVariable(&entity->cv);
}

////////////////////////////////
//~ rjf: Windows Semaphores

internal Semaphore
os_semaphore_alloc(U32 initial_count, U32 max_count, String8 name)
{
  HANDLE handle = CreateSemaphoreA(0, initial_count, max_count, (char*)name.str);
  Semaphore result = {(U64)handle};
  return result;
}

internal void
os_semaphore_release(Semaphore semaphore)
{
  HANDLE handle = (HANDLE)semaphore.u64[0];
  CloseHandle(handle);
}

internal Semaphore
os_semaphore_open(String8 name)
{
  HANDLE handle = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, 0, (char*)name.str);
  Semaphore result = {(U64)handle};
  return result;
}

internal void
os_semaphore_close(Semaphore semaphore)
{
  HANDLE handle = (HANDLE)semaphore.u64[0];
  CloseHandle(handle);
}

internal B32
os_semaphore_take(Semaphore semaphore, U64 endt_us)
{
  U32 sleep_ms = os_w32_sleep_ms_from_endt_us(endt_us);
  HANDLE handle = (HANDLE)semaphore.u64[0];
  DWORD wait_result = WaitForSingleObject(handle, sleep_ms);
  B32 result = (wait_result == WAIT_OBJECT_0);
  return result;
}

internal void
os_semaphore_drop(Semaphore semaphore)
{
  HANDLE handle = (HANDLE)semaphore.u64[0];
  ReleaseSemaphore(handle, 1, 0);
}

////////////////////////////////
//~ rjf: Windows Barriers

internal Barrier
os_barrier_alloc(U64 count)
{
  OS_W32_Entity *entity = os_w32_entity_alloc(OS_W32_EntityKind_Barrier);
  if(entity != 0)
  {
    BOOL init_good = InitializeSynchronizationBarrier(&entity->sb, (LONG)count, -1);
    (void)init_good;
  }
  Barrier result = {IntFromPtr(entity)};
  return result;
}

internal void
os_barrier_release(Barrier barrier)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(barrier.u64[0]);
  if(entity != 0)
  {
    DeleteSynchronizationBarrier(&entity->sb);
    os_w32_entity_release(entity);
  }
}

internal void
os_barrier_wait(Barrier barrier)
{
  OS_W32_Entity *entity = (OS_W32_Entity*)PtrFromInt(barrier.u64[0]);
  if(entity != 0)
  {
    EnterSynchronizationBarrier(&entity->sb, 0);
  }
}

#elif (CORE_OS_LINUX || CORE_OS_MAC)

#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#if CORE_OS_LINUX
#include <sys/syscall.h>
#endif

////////////////////////////////
//~ rjf: Linux Entity Types

typedef enum OS_LNX_EntityKind
{
  OS_LNX_EntityKind_Thread,
  OS_LNX_EntityKind_Mutex,
  OS_LNX_EntityKind_RWMutex,
  OS_LNX_EntityKind_ConditionVariable,
  OS_LNX_EntityKind_Barrier,
}
OS_LNX_EntityKind;

typedef struct OS_LNX_Entity OS_LNX_Entity;
struct OS_LNX_Entity
{
  OS_LNX_Entity *next;
  OS_LNX_EntityKind kind;
  union
  {
    struct
    {
      pthread_t handle;
      ThreadEntryPointFunctionType *func;
      void *ptr;
    } thread;
    pthread_mutex_t mutex_handle;
    pthread_rwlock_t rwmutex_handle;
    struct
    {
      pthread_cond_t cond_handle;
      pthread_mutex_t rwlock_mutex_handle;
    } cv;
    pthread_barrier_t barrier;
  };
};

////////////////////////////////
//~ rjf: Linux Threading State

typedef struct OS_LNX_ThreadState OS_LNX_ThreadState;
struct OS_LNX_ThreadState
{
  Arena *entity_arena;
  pthread_mutex_t entity_mutex;
  OS_LNX_Entity *entity_free;
  B32 initialized;
};

global OS_LNX_ThreadState os_lnx_thread_state = {0};

////////////////////////////////
//~ rjf: Linux System/Process Info State

typedef struct OS_LNX_State OS_LNX_State;
struct OS_LNX_State
{
  Arena *arena;
  OS_SystemInfo system_info;
  OS_ProcessInfo process_info;
  B32 initialized;
};

global OS_LNX_State os_lnx_state = {0};

////////////////////////////////
//~ rjf: Linux Entity Functions

internal void
os_lnx_thread_state_init(void)
{
  if(!os_lnx_thread_state.initialized)
  {
    pthread_mutex_init(&os_lnx_thread_state.entity_mutex, 0);
    os_lnx_thread_state.entity_arena = arena_alloc();
    os_lnx_thread_state.initialized = 1;
  }
}

internal OS_LNX_Entity *
os_lnx_entity_alloc(OS_LNX_EntityKind kind)
{
  os_lnx_thread_state_init();
  OS_LNX_Entity *entity = 0;
  pthread_mutex_lock(&os_lnx_thread_state.entity_mutex);
  {
    entity = os_lnx_thread_state.entity_free;
    if(entity)
    {
      SLLStackPop(os_lnx_thread_state.entity_free);
    }
    else
    {
      entity = push_array_no_zero(os_lnx_thread_state.entity_arena, OS_LNX_Entity, 1);
    }
  }
  pthread_mutex_unlock(&os_lnx_thread_state.entity_mutex);
  MemoryZeroStruct(entity);
  entity->kind = kind;
  return entity;
}

internal void
os_lnx_entity_release(OS_LNX_Entity *entity)
{
  pthread_mutex_lock(&os_lnx_thread_state.entity_mutex);
  {
    SLLStackPush(os_lnx_thread_state.entity_free, entity);
  }
  pthread_mutex_unlock(&os_lnx_thread_state.entity_mutex);
}

////////////////////////////////
//~ rjf: Linux Thread Entry Point

internal void *
os_lnx_thread_entry_point(void *ptr)
{
  OS_LNX_Entity *entity = (OS_LNX_Entity *)ptr;
  ThreadEntryPointFunctionType *func = entity->thread.func;
  void *thread_ptr = entity->thread.ptr;
  func(thread_ptr);
  return 0;
}

////////////////////////////////
//~ rjf: Linux Thread Info

internal U32
os_tid(void)
{
#if CORE_OS_LINUX
  U32 result = (U32)syscall(SYS_gettid);
#else
  U32 result = (U32)pthread_self();
#endif
  return result;
}

internal void
os_set_thread_name(String8 name)
{
#if CORE_OS_LINUX
  char name_cstr[16] = {0};
  U64 copy_size = Min(name.size, sizeof(name_cstr)-1);
  MemoryCopy(name_cstr, name.str, copy_size);
  pthread_setname_np(pthread_self(), name_cstr);
#endif
}

////////////////////////////////
//~ rjf: Linux Threads

internal Thread
os_thread_launch(ThreadEntryPointFunctionType *func, void *ptr)
{
  OS_LNX_Entity *entity = os_lnx_entity_alloc(OS_LNX_EntityKind_Thread);
  entity->thread.func = func;
  entity->thread.ptr = ptr;
  {
    int pthread_result = pthread_create(&entity->thread.handle, 0, os_lnx_thread_entry_point, entity);
    if(pthread_result == -1)
    {
      os_lnx_entity_release(entity);
      entity = 0;
    }
  }
  Thread handle = {(U64)entity};
  return handle;
}

internal B32
os_thread_join(Thread handle, U64 endt_us)
{
  if(handle.u64[0] == 0) { return 0; }
  OS_LNX_Entity *entity = (OS_LNX_Entity *)handle.u64[0];
  int join_result = pthread_join(entity->thread.handle, 0);
  B32 result = (join_result == 0);
  os_lnx_entity_release(entity);
  return result;
}

internal void
os_thread_detach(Thread handle)
{
  if(handle.u64[0] == 0) { return; }
  OS_LNX_Entity *entity = (OS_LNX_Entity *)handle.u64[0];
  os_lnx_entity_release(entity);
}

////////////////////////////////
//~ rjf: Linux Mutexes

internal Mutex
os_mutex_alloc(void)
{
  OS_LNX_Entity *entity = os_lnx_entity_alloc(OS_LNX_EntityKind_Mutex);
  int init_result = pthread_mutex_init(&entity->mutex_handle, 0);
  if(init_result == -1)
  {
    os_lnx_entity_release(entity);
    entity = 0;
  }
  Mutex handle = {(U64)entity};
  return handle;
}

internal void
os_mutex_release(Mutex mutex)
{
  if(mutex.u64[0] == 0) { return; }
  OS_LNX_Entity *entity = (OS_LNX_Entity *)mutex.u64[0];
  pthread_mutex_destroy(&entity->mutex_handle);
  os_lnx_entity_release(entity);
}

internal void
os_mutex_take(Mutex mutex)
{
  if(mutex.u64[0] == 0) { return; }
  OS_LNX_Entity *entity = (OS_LNX_Entity *)mutex.u64[0];
  pthread_mutex_lock(&entity->mutex_handle);
}

internal void
os_mutex_drop(Mutex mutex)
{
  if(mutex.u64[0] == 0) { return; }
  OS_LNX_Entity *entity = (OS_LNX_Entity *)mutex.u64[0];
  pthread_mutex_unlock(&entity->mutex_handle);
}

////////////////////////////////
//~ rjf: Linux RW Mutexes

internal RWMutex
os_rw_mutex_alloc(void)
{
  OS_LNX_Entity *entity = os_lnx_entity_alloc(OS_LNX_EntityKind_RWMutex);
  int init_result = pthread_rwlock_init(&entity->rwmutex_handle, 0);
  if(init_result == -1)
  {
    os_lnx_entity_release(entity);
    entity = 0;
  }
  RWMutex handle = {(U64)entity};
  return handle;
}

internal void
os_rw_mutex_release(RWMutex rw_mutex)
{
  if(rw_mutex.u64[0] == 0) { return; }
  OS_LNX_Entity *entity = (OS_LNX_Entity *)rw_mutex.u64[0];
  pthread_rwlock_destroy(&entity->rwmutex_handle);
  os_lnx_entity_release(entity);
}

internal void
os_rw_mutex_take(RWMutex rw_mutex, B32 write_mode)
{
  if(rw_mutex.u64[0] == 0) { return; }
  OS_LNX_Entity *entity = (OS_LNX_Entity *)rw_mutex.u64[0];
  if(write_mode)
  {
    pthread_rwlock_wrlock(&entity->rwmutex_handle);
  }
  else
  {
    pthread_rwlock_rdlock(&entity->rwmutex_handle);
  }
}

internal void
os_rw_mutex_drop(RWMutex rw_mutex, B32 write_mode)
{
  if(rw_mutex.u64[0] == 0) { return; }
  OS_LNX_Entity *entity = (OS_LNX_Entity *)rw_mutex.u64[0];
  pthread_rwlock_unlock(&entity->rwmutex_handle);
}

////////////////////////////////
//~ rjf: Linux Condition Variables

internal CondVar
os_cond_var_alloc(void)
{
  OS_LNX_Entity *entity = os_lnx_entity_alloc(OS_LNX_EntityKind_ConditionVariable);
  int init_result = pthread_cond_init(&entity->cv.cond_handle, 0);
  if(init_result == -1)
  {
    os_lnx_entity_release(entity);
    entity = 0;
  }
  int init2_result = 0;
  if(entity)
  {
    init2_result = pthread_mutex_init(&entity->cv.rwlock_mutex_handle, 0);
  }
  if(init2_result == -1)
  {
    pthread_cond_destroy(&entity->cv.cond_handle);
    os_lnx_entity_release(entity);
    entity = 0;
  }
  CondVar handle = {(U64)entity};
  return handle;
}

internal void
os_cond_var_release(CondVar cv)
{
  if(cv.u64[0] == 0) { return; }
  OS_LNX_Entity *entity = (OS_LNX_Entity *)cv.u64[0];
  pthread_cond_destroy(&entity->cv.cond_handle);
  pthread_mutex_destroy(&entity->cv.rwlock_mutex_handle);
  os_lnx_entity_release(entity);
}

internal B32
os_cond_var_wait(CondVar cv, Mutex mutex, U64 endt_us)
{
  if(cv.u64[0] == 0) { return 0; }
  if(mutex.u64[0] == 0) { return 0; }
  OS_LNX_Entity *cv_entity = (OS_LNX_Entity *)cv.u64[0];
  OS_LNX_Entity *mutex_entity = (OS_LNX_Entity *)mutex.u64[0];
  struct timespec endt_timespec;
  endt_timespec.tv_sec = endt_us/1000000;
  endt_timespec.tv_nsec = 1000 * (endt_us - (endt_us/1000000)*1000000);
  int wait_result = pthread_cond_timedwait(&cv_entity->cv.cond_handle, &mutex_entity->mutex_handle, &endt_timespec);
  B32 result = (wait_result != ETIMEDOUT);
  return result;
}

internal B32
os_cond_var_wait_rw(CondVar cv, RWMutex mutex_rw, B32 write_mode, U64 endt_us)
{
  if(cv.u64[0] == 0) { return 0; }
  if(mutex_rw.u64[0] == 0) { return 0; }
  OS_LNX_Entity *cv_entity = (OS_LNX_Entity *)cv.u64[0];
  OS_LNX_Entity *rw_mutex_entity = (OS_LNX_Entity *)mutex_rw.u64[0];
  struct timespec endt_timespec;
  endt_timespec.tv_sec = endt_us/1000000;
  endt_timespec.tv_nsec = 1000 * (endt_us - (endt_us/1000000)*1000000);
  B32 result = 0;
  pthread_mutex_lock(&cv_entity->cv.rwlock_mutex_handle);
  pthread_rwlock_unlock(&rw_mutex_entity->rwmutex_handle);
  for(;;)
  {
    int wait_result = pthread_cond_timedwait(&cv_entity->cv.cond_handle, &cv_entity->cv.rwlock_mutex_handle, &endt_timespec);
    if(wait_result != ETIMEDOUT)
    {
      if(write_mode)
      {
        pthread_rwlock_wrlock(&rw_mutex_entity->rwmutex_handle);
      }
      else
      {
        pthread_rwlock_rdlock(&rw_mutex_entity->rwmutex_handle);
      }
      result = 1;
      break;
    }
    if(wait_result == ETIMEDOUT)
    {
      if(write_mode)
      {
        pthread_rwlock_wrlock(&rw_mutex_entity->rwmutex_handle);
      }
      else
      {
        pthread_rwlock_rdlock(&rw_mutex_entity->rwmutex_handle);
      }
      break;
    }
  }
  pthread_mutex_unlock(&cv_entity->cv.rwlock_mutex_handle);
  return result;
}

internal void
os_cond_var_signal(CondVar cv)
{
  if(cv.u64[0] == 0) { return; }
  OS_LNX_Entity *cv_entity = (OS_LNX_Entity *)cv.u64[0];
  pthread_cond_signal(&cv_entity->cv.cond_handle);
}

internal void
os_cond_var_broadcast(CondVar cv)
{
  if(cv.u64[0] == 0) { return; }
  OS_LNX_Entity *cv_entity = (OS_LNX_Entity *)cv.u64[0];
  pthread_cond_broadcast(&cv_entity->cv.cond_handle);
}

////////////////////////////////
//~ rjf: Linux Semaphores

internal Semaphore
os_semaphore_alloc(U32 initial_count, U32 max_count, String8 name)
{
  Semaphore result = {0};
  if(name.size > 0)
  {
    sem_t *s = sem_open((char *)name.str, O_CREAT | O_EXCL, 0666, initial_count);
    if(s == SEM_FAILED)
    {
      s = sem_open((char *)name.str, 0);
    }
    if(s != SEM_FAILED)
    {
      result.u64[0] = (U64)s;
    }
  }
  else
  {
    sem_t *s = (sem_t *)mmap(0, sizeof(*s), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if(s != MAP_FAILED)
    {
      int err = sem_init(s, 0, initial_count);
      if(err == 0)
      {
        result.u64[0] = (U64)s;
      }
    }
  }
  return result;
}

internal void
os_semaphore_release(Semaphore semaphore)
{
  munmap((void*)semaphore.u64[0], sizeof(sem_t));
}

internal Semaphore
os_semaphore_open(String8 name)
{
  Semaphore result = {0};
  sem_t *s = sem_open((char *)name.str, 0);
  if(s != SEM_FAILED)
  {
    result.u64[0] = (U64)s;
  }
  return result;
}

internal void
os_semaphore_close(Semaphore semaphore)
{
  sem_t *s = (sem_t *)semaphore.u64[0];
  sem_close(s);
}

internal B32
os_semaphore_take(Semaphore semaphore, U64 endt_us)
{
  for(;;)
  {
    int err = sem_wait((sem_t*)semaphore.u64[0]);
    if(err == 0)
    {
      break;
    }
    else if(errno == EAGAIN)
    {
      continue;
    }
    break;
  }
  return 1;
}

internal void
os_semaphore_drop(Semaphore semaphore)
{
  for(;;)
  {
    int err = sem_post((sem_t*)semaphore.u64[0]);
    if(err == 0)
    {
      break;
    }
    else if(errno == EAGAIN)
    {
      continue;
    }
    break;
  }
}

////////////////////////////////
//~ rjf: Linux Barriers

internal Barrier
os_barrier_alloc(U64 count)
{
  OS_LNX_Entity *entity = os_lnx_entity_alloc(OS_LNX_EntityKind_Barrier);
  if(entity != 0)
  {
    pthread_barrier_init(&entity->barrier, 0, (unsigned)count);
  }
  Barrier result = {IntFromPtr(entity)};
  return result;
}

internal void
os_barrier_release(Barrier barrier)
{
  OS_LNX_Entity *entity = (OS_LNX_Entity*)PtrFromInt(barrier.u64[0]);
  if(entity != 0)
  {
    pthread_barrier_destroy(&entity->barrier);
    os_lnx_entity_release(entity);
  }
}

internal void
os_barrier_wait(Barrier barrier)
{
  OS_LNX_Entity *entity = (OS_LNX_Entity*)PtrFromInt(barrier.u64[0]);
  if(entity != 0)
  {
    pthread_barrier_wait(&entity->barrier);
  }
}

#endif // CORE_OS_LINUX || CORE_OS_MAC

////////////////////////////////
//~ rjf: Time Implementation

#if CORE_OS_WINDOWS

internal U64
os_now_microseconds(void)
{
  LARGE_INTEGER perf_freq;
  LARGE_INTEGER perf_counter;
  QueryPerformanceFrequency(&perf_freq);
  QueryPerformanceCounter(&perf_counter);
  U64 result = (perf_counter.QuadPart * 1000000) / perf_freq.QuadPart;
  return result;
}

internal U32
os_now_unix(void)
{
  FILETIME file_time;
  GetSystemTimeAsFileTime(&file_time);
  U64 win32_time = ((U64)file_time.dwHighDateTime << 32) | file_time.dwLowDateTime;
  U64 unix_time64 = ((win32_time - 0x19DB1DED53E8000ULL) / 10000000);
  return (U32)unix_time64;
}

internal DateTime
os_now_universal_time(void)
{
  SYSTEMTIME systime = {0};
  GetSystemTime(&systime);
  DateTime result = {0};
  result.year = systime.wYear;
  result.mon  = systime.wMonth - 1;
  result.wday = systime.wDayOfWeek;
  result.day  = systime.wDay;
  result.hour = systime.wHour;
  result.min  = systime.wMinute;
  result.sec  = systime.wSecond;
  result.msec = systime.wMilliseconds;
  return result;
}

internal DateTime
os_now_local_time(void)
{
  SYSTEMTIME systime = {0};
  GetLocalTime(&systime);
  DateTime result = {0};
  result.year = systime.wYear;
  result.mon  = systime.wMonth - 1;
  result.wday = systime.wDayOfWeek;
  result.day  = systime.wDay;
  result.hour = systime.wHour;
  result.min  = systime.wMinute;
  result.sec  = systime.wSecond;
  result.msec = systime.wMilliseconds;
  return result;
}

internal DateTime
os_universal_time_from_local(DateTime *date_time)
{
  SYSTEMTIME systime = {0};
  systime.wYear         = (WORD)(date_time->year);
  systime.wMonth        = date_time->mon + 1;
  systime.wDay          = date_time->day;
  systime.wHour         = date_time->hour;
  systime.wMinute       = date_time->min;
  systime.wSecond       = date_time->sec;
  systime.wMilliseconds = date_time->msec;
  FILETIME ftime = {0};
  SystemTimeToFileTime(&systime, &ftime);
  FILETIME ftime_local = {0};
  LocalFileTimeToFileTime(&ftime, &ftime_local);
  FileTimeToSystemTime(&ftime_local, &systime);
  DateTime result = {0};
  result.year = systime.wYear;
  result.mon  = systime.wMonth - 1;
  result.wday = systime.wDayOfWeek;
  result.day  = systime.wDay;
  result.hour = systime.wHour;
  result.min  = systime.wMinute;
  result.sec  = systime.wSecond;
  result.msec = systime.wMilliseconds;
  return result;
}

internal DateTime
os_local_time_from_universal(DateTime *date_time)
{
  SYSTEMTIME systime = {0};
  systime.wYear         = (WORD)(date_time->year);
  systime.wMonth        = date_time->mon + 1;
  systime.wDay          = date_time->day;
  systime.wHour         = date_time->hour;
  systime.wMinute       = date_time->min;
  systime.wSecond       = date_time->sec;
  systime.wMilliseconds = date_time->msec;
  FILETIME ftime = {0};
  SystemTimeToFileTime(&systime, &ftime);
  FILETIME ftime_local = {0};
  FileTimeToLocalFileTime(&ftime, &ftime_local);
  FileTimeToSystemTime(&ftime_local, &systime);
  DateTime result = {0};
  result.year = systime.wYear;
  result.mon  = systime.wMonth - 1;
  result.wday = systime.wDayOfWeek;
  result.day  = systime.wDay;
  result.hour = systime.wHour;
  result.min  = systime.wMinute;
  result.sec  = systime.wSecond;
  result.msec = systime.wMilliseconds;
  return result;
}

internal void
os_sleep_milliseconds(U32 msec)
{
  Sleep(msec);
}

#elif (CORE_OS_LINUX || CORE_OS_MAC)

internal U64
os_now_microseconds(void)
{
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  U64 result = t.tv_sec * 1000000 + (t.tv_nsec / 1000);
  return result;
}

internal U32
os_now_unix(void)
{
  time_t t = time(0);
  return (U32)t;
}

internal DateTime
os_now_universal_time(void)
{
  time_t t = 0;
  time(&t);
  struct tm universal_tm = {0};
  gmtime_r(&t, &universal_tm);
  DateTime result = {0};
  result.sec  = universal_tm.tm_sec;
  result.min  = universal_tm.tm_min;
  result.hour = universal_tm.tm_hour;
  result.day  = universal_tm.tm_mday - 1;
  result.mon  = universal_tm.tm_mon;
  result.year = universal_tm.tm_year + 1900;
  return result;
}

internal DateTime
os_now_local_time(void)
{
  time_t t = 0;
  time(&t);
  struct tm local_tm = {0};
  localtime_r(&t, &local_tm);
  DateTime result = {0};
  result.sec  = local_tm.tm_sec;
  result.min  = local_tm.tm_min;
  result.hour = local_tm.tm_hour;
  result.day  = local_tm.tm_mday - 1;
  result.mon  = local_tm.tm_mon;
  result.year = local_tm.tm_year + 1900;
  return result;
}

internal DateTime
os_universal_time_from_local(DateTime *date_time)
{
  struct tm local_tm = {0};
  local_tm.tm_sec  = date_time->sec;
  local_tm.tm_min  = date_time->min;
  local_tm.tm_hour = date_time->hour;
  local_tm.tm_mday = date_time->day + 1;
  local_tm.tm_mon  = date_time->mon;
  local_tm.tm_year = date_time->year - 1900;
  local_tm.tm_isdst = -1;
  time_t universal_t = mktime(&local_tm);
  struct tm universal_tm = {0};
  gmtime_r(&universal_t, &universal_tm);
  DateTime result = {0};
  result.sec  = universal_tm.tm_sec;
  result.min  = universal_tm.tm_min;
  result.hour = universal_tm.tm_hour;
  result.day  = universal_tm.tm_mday - 1;
  result.mon  = universal_tm.tm_mon;
  result.year = universal_tm.tm_year + 1900;
  return result;
}

internal DateTime
os_local_time_from_universal(DateTime *date_time)
{
  struct tm universal_tm = {0};
  universal_tm.tm_sec  = date_time->sec;
  universal_tm.tm_min  = date_time->min;
  universal_tm.tm_hour = date_time->hour;
  universal_tm.tm_mday = date_time->day + 1;
  universal_tm.tm_mon  = date_time->mon;
  universal_tm.tm_year = date_time->year - 1900;
  universal_tm.tm_isdst = -1;
  time_t universal_t = timegm(&universal_tm);
  struct tm local_tm = {0};
  localtime_r(&universal_t, &local_tm);
  DateTime result = {0};
  result.sec  = local_tm.tm_sec;
  result.min  = local_tm.tm_min;
  result.hour = local_tm.tm_hour;
  result.day  = local_tm.tm_mday - 1;
  result.mon  = local_tm.tm_mon;
  result.year = local_tm.tm_year + 1900;
  return result;
}

internal void
os_sleep_milliseconds(U32 msec)
{
  usleep(msec * 1000);
}

#endif

////////////////////////////////
//~ rjf: DenseTime Functions

internal DenseTime
dense_time_from_date_time(DateTime dt)
{
  DenseTime result = 0;
  result += dt.year;
  result *= 12;
  result += dt.mon;
  result *= 31;
  result += dt.day;
  result *= 24;
  result += dt.hour;
  result *= 60;
  result += dt.min;
  result *= 61;
  result += dt.sec;
  result *= 1000;
  result += dt.msec;
  return result;
}

internal DateTime
date_time_from_dense_time(DenseTime t)
{
  DateTime result = {0};
  result.msec = t%1000;
  t /= 1000;
  result.sec = t%61;
  t /= 61;
  result.min = t%60;
  t /= 60;
  result.hour = t%24;
  t /= 24;
  result.day = t%31;
  t /= 31;
  result.mon = t%12;
  t /= 12;
  result.year = (U32)t;
  return result;
}

////////////////////////////////
//~ rjf: Bit Operations Implementation

internal U16
bswap_u16(U16 x)
{
#if CORE_COMPILER_MSVC
  return _byteswap_ushort(x);
#else
  return __builtin_bswap16(x);
#endif
}

internal U32
bswap_u32(U32 x)
{
#if CORE_COMPILER_MSVC
  return _byteswap_ulong(x);
#else
  return __builtin_bswap32(x);
#endif
}

internal U64
bswap_u64(U64 x)
{
#if CORE_COMPILER_MSVC
  return _byteswap_uint64(x);
#else
  return __builtin_bswap64(x);
#endif
}

internal U64
ctz32(U32 val)
{
  if(val == 0) return 32;
#if CORE_COMPILER_MSVC
  unsigned long idx;
  _BitScanForward(&idx, val);
  return idx;
#else
  return __builtin_ctz(val);
#endif
}

internal U64
ctz64(U64 val)
{
  if(val == 0) return 64;
#if CORE_COMPILER_MSVC
  unsigned long idx;
  _BitScanForward64(&idx, val);
  return idx;
#else
  return __builtin_ctzll(val);
#endif
}

internal U64
clz32(U32 val)
{
  if(val == 0) return 32;
#if CORE_COMPILER_MSVC
  unsigned long idx;
  _BitScanReverse(&idx, val);
  return 31 - idx;
#else
  return __builtin_clz(val);
#endif
}

internal U64
clz64(U64 val)
{
  if(val == 0) return 64;
#if CORE_COMPILER_MSVC
  unsigned long idx;
  _BitScanReverse64(&idx, val);
  return 63 - idx;
#else
  return __builtin_clzll(val);
#endif
}

internal U64
count_bits_set32(U32 val)
{
#if CORE_COMPILER_MSVC
  return __popcnt(val);
#else
  return __builtin_popcount(val);
#endif
}

internal U64
count_bits_set64(U64 val)
{
#if CORE_COMPILER_MSVC
  return __popcnt64(val);
#else
  return __builtin_popcountll(val);
#endif
}

////////////////////////////////
//~ rjf: Range Helpers Implementation

internal Rng1U64
r1u64(U64 min, U64 max)
{
  Rng1U64 r = {0};
  r.min = min;
  r.max = max;
  return r;
}

internal U64
dim_1u64(Rng1U64 r)
{
  return r.max - r.min;
}

////////////////////////////////
//~ rjf: Safe Casts Implementation

internal U16
safe_cast_u16(U32 x)
{
  Assert(x <= max_U16);
  U16 result = (U16)x;
  return result;
}

internal U32
u32_from_u64_saturate(U64 x)
{
  U32 result = (x > max_U32) ? max_U32 : (U32)x;
  return result;
}

////////////////////////////////
//~ rjf: OS Handle Functions Implementation

internal OS_Handle
os_handle_zero(void)
{
  OS_Handle handle = {0};
  return handle;
}

internal B32
os_handle_match(OS_Handle a, OS_Handle b)
{
  return a.u64[0] == b.u64[0];
}

////////////////////////////////
//~ rjf: File System Implementation

#if CORE_OS_WINDOWS

internal OS_Handle
os_file_open(OS_AccessFlags flags, String8 path)
{
  OS_Handle result = {0};
  Temp scratch = temp_begin(arena_alloc());
  String16 path16 = str16_from_8(scratch.arena, path);
  DWORD access_flags = 0;
  DWORD share_mode = 0;
  DWORD creation_disposition = OPEN_EXISTING;
  SECURITY_ATTRIBUTES security_attributes = {sizeof(security_attributes), 0, 0};
  if(flags & OS_AccessFlag_Read)        {access_flags |= GENERIC_READ;}
  if(flags & OS_AccessFlag_Write)       {access_flags |= GENERIC_WRITE;}
  if(flags & OS_AccessFlag_Execute)     {access_flags |= GENERIC_EXECUTE;}
  if(flags & OS_AccessFlag_ShareRead)   {share_mode |= FILE_SHARE_READ;}
  if(flags & OS_AccessFlag_ShareWrite)  {share_mode |= FILE_SHARE_WRITE|FILE_SHARE_DELETE;}
  if(flags & OS_AccessFlag_Write)       {creation_disposition = CREATE_ALWAYS;}
  if(flags & OS_AccessFlag_Append)      {creation_disposition = OPEN_ALWAYS; access_flags |= FILE_APPEND_DATA; }
  if(flags & OS_AccessFlag_Inherited)
  {
    security_attributes.bInheritHandle = 1;
  }
  HANDLE file = CreateFileW((WCHAR *)path16.str, access_flags, share_mode, &security_attributes, creation_disposition, FILE_ATTRIBUTE_NORMAL, 0);
  if(file != INVALID_HANDLE_VALUE)
  {
    result.u64[0] = (U64)file;
  }
  temp_end(scratch);
  return result;
}

internal void
os_file_close(OS_Handle file)
{
  if(os_handle_match(file, os_handle_zero())) { return; }
  HANDLE handle = (HANDLE)file.u64[0];
  CloseHandle(handle);
}

internal U64
os_file_read(OS_Handle file, Rng1U64 rng, void *out_data)
{
  if(os_handle_match(file, os_handle_zero())) { return 0; }
  HANDLE handle = (HANDLE)file.u64[0];
  
  // clamp range by file size
  U64 size = 0;
  GetFileSizeEx(handle, (LARGE_INTEGER *)&size);
  Rng1U64 rng_clamped = r1u64(ClampTop(rng.min, size), ClampTop(rng.max, size));
  U64 total_read_size = 0;
  
  // read loop
  {
    U64 to_read = dim_1u64(rng_clamped);
    for(U64 off = rng.min; total_read_size < to_read;)
    {
      U64 amt64 = to_read - total_read_size;
      U32 amt32 = u32_from_u64_saturate(amt64);
      DWORD read_size = 0;
      OVERLAPPED overlapped = {0};
      overlapped.Offset     = (DWORD)(off & 0x00000000ffffffffull);
      overlapped.OffsetHigh = (DWORD)((off & 0xffffffff00000000ull) >> 32);
      ReadFile(handle, (U8 *)out_data + total_read_size, amt32, &read_size, &overlapped);
      off += read_size;
      total_read_size += read_size;
      if(read_size != amt32)
      {
        break;
      }
    }
  }
  
  return total_read_size;
}

internal U64
os_file_write(OS_Handle file, Rng1U64 rng, void *data)
{
  if(os_handle_match(file, os_handle_zero())) { return 0; }
  HANDLE win_handle = (HANDLE)file.u64[0];
  U64 src_off = 0;
  U64 dst_off = rng.min;
  U64 total_write_size = dim_1u64(rng);
  for(;;)
  {
    void *bytes_src = (U8 *)data + src_off;
    U64 bytes_left = total_write_size - src_off;
    DWORD write_size = (DWORD)Min(MB(1), bytes_left);
    DWORD bytes_written = 0;
    OVERLAPPED overlapped = {0};
    overlapped.Offset = (DWORD)(dst_off & 0x00000000ffffffffull);
    overlapped.OffsetHigh = (DWORD)((dst_off & 0xffffffff00000000ull) >> 32);
    BOOL success = WriteFile(win_handle, bytes_src, write_size, &bytes_written, &overlapped);
    if(success == 0)
    {
      break;
    }
    src_off += bytes_written;
    dst_off += bytes_written;
    if(bytes_left == 0)
    {
      break;
    }
  }
  return src_off;
}

internal FileProperties
os_properties_from_file(OS_Handle file)
{
  FileProperties props = {0};
  if(os_handle_match(file, os_handle_zero())) { return props; }
  HANDLE handle = (HANDLE)file.u64[0];
  BY_HANDLE_FILE_INFORMATION info;
  BOOL info_good = GetFileInformationByHandle(handle, &info);
  if(info_good)
  {
    U32 size_lo = info.nFileSizeLow;
    U32 size_hi = info.nFileSizeHigh;
    props.size = (U64)size_lo | (((U64)size_hi)<<32);
    // Note: skipping time conversion for simplicity
    if(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
      props.flags |= FilePropertyFlag_IsFolder;
    }
  }
  return props;
}

//- rjf: file path operations

internal B32
os_delete_file_at_path(String8 path)
{
  Temp scratch = temp_begin(arena_alloc());
  String16 path16 = str16_from_8(scratch.arena, path);
  B32 result = DeleteFileW((WCHAR*)path16.str);
  temp_end(scratch);
  return result;
}

internal B32
os_copy_file_path(String8 dst, String8 src)
{
  Temp scratch = temp_begin(arena_alloc());
  String16 dst16 = str16_from_8(scratch.arena, dst);
  String16 src16 = str16_from_8(scratch.arena, src);
  B32 result = CopyFileW((WCHAR*)src16.str, (WCHAR*)dst16.str, 0);
  temp_end(scratch);
  return result;
}

internal B32
os_move_file_path(String8 dst, String8 src)
{
  Temp scratch = temp_begin(arena_alloc());
  String16 dst16 = str16_from_8(scratch.arena, dst);
  String16 src16 = str16_from_8(scratch.arena, src);
  B32 result = MoveFileW((WCHAR*)src16.str, (WCHAR*)dst16.str);
  temp_end(scratch);
  return result;
}

internal String8
os_full_path_from_path(Arena *arena, String8 path)
{
  Temp scratch = temp_begin(arena_alloc());
  DWORD     buffer_size = Max(MAX_PATH, path.size * 2) + 1;
  String16  path16      = str16_from_8(scratch.arena, path);
  WCHAR    *buffer      = push_array_no_zero(scratch.arena, WCHAR, buffer_size);
  DWORD     path16_size = GetFullPathNameW((WCHAR*)path16.str, buffer_size, buffer, NULL);
  if(path16_size > buffer_size)
  {
    buffer_size = path16_size + 1;
    buffer      = push_array_no_zero(scratch.arena, WCHAR, buffer_size);
    path16_size = GetFullPathNameW((WCHAR*)path16.str, buffer_size, buffer, NULL);
  }
  String8 full_path = str8_from_16(arena, str16((U16*)buffer, path16_size));
  temp_end(scratch);
  return full_path;
}

internal B32
os_file_path_exists(String8 path)
{
  Temp scratch = temp_begin(arena_alloc());
  String16 path16 = str16_from_8(scratch.arena, path);
  DWORD attributes = GetFileAttributesW((WCHAR *)path16.str);
  B32 exists = (attributes != INVALID_FILE_ATTRIBUTES) && !!(~attributes & FILE_ATTRIBUTE_DIRECTORY);
  temp_end(scratch);
  return exists;
}

internal B32
os_folder_path_exists(String8 path)
{
  Temp scratch = temp_begin(arena_alloc());
  String16 path16     = str16_from_8(scratch.arena, path);
  DWORD    attributes = GetFileAttributesW((WCHAR *)path16.str);
  B32      exists     = (attributes != INVALID_FILE_ATTRIBUTES) && !!(attributes & FILE_ATTRIBUTE_DIRECTORY);
  temp_end(scratch);
  return exists;
}

internal FileProperties
os_properties_from_file_path(String8 path)
{
  WIN32_FIND_DATAW find_data = {0};
  Temp scratch = temp_begin(arena_alloc());
  String16 path16 = str16_from_8(scratch.arena, path);
  HANDLE handle = FindFirstFileW((WCHAR *)path16.str, &find_data);
  FileProperties props = {0};
  if(handle != INVALID_HANDLE_VALUE)
  {
    props.size = Compose64Bit(find_data.nFileSizeHigh, find_data.nFileSizeLow);
    if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
      props.flags |= FilePropertyFlag_IsFolder;
    }
  }
  FindClose(handle);
  temp_end(scratch);
  return props;
}

//- rjf: directory iteration

typedef struct OS_W32_FileIter OS_W32_FileIter;
struct OS_W32_FileIter
{
  HANDLE handle;
  WIN32_FIND_DATAW find_data;
};
static_assert(sizeof(Member(OS_FileIter, memory)) >= sizeof(OS_W32_FileIter), "w32_file_iter_memory_size");

internal OS_FileIter *
os_file_iter_begin(Arena *arena, String8 path, OS_FileIterFlags flags)
{
  Temp scratch = temp_begin(arena_alloc());
  String8 path_with_wildcard = push_str8f(scratch.arena, "%S\\*", path);
  String16 path16 = str16_from_8(scratch.arena, path_with_wildcard);
  OS_FileIter *iter = push_array(arena, OS_FileIter, 1);
  iter->flags = flags;
  OS_W32_FileIter *w32_iter = (OS_W32_FileIter*)iter->memory;
  w32_iter->handle = FindFirstFileExW((WCHAR*)path16.str, FindExInfoBasic, &w32_iter->find_data, FindExSearchNameMatch, 0, FIND_FIRST_EX_LARGE_FETCH);
  temp_end(scratch);
  return iter;
}

internal B32
os_file_iter_next(Arena *arena, OS_FileIter *iter, OS_FileInfo *info_out)
{
  B32 result = 0;
  OS_FileIterFlags flags = iter->flags;
  OS_W32_FileIter *w32_iter = (OS_W32_FileIter*)iter->memory;
  if(!(flags & OS_FileIterFlag_Done) && w32_iter->handle != INVALID_HANDLE_VALUE)
  {
    do
    {
      B32 usable_file = 1;
      WCHAR *file_name = w32_iter->find_data.cFileName;
      DWORD attributes = w32_iter->find_data.dwFileAttributes;
      if(file_name[0] == '.')
      {
        if(flags & OS_FileIterFlag_SkipHiddenFiles)
        {
          usable_file = 0;
        }
        else if(file_name[1] == 0)
        {
          usable_file = 0;
        }
        else if(file_name[1] == '.' && file_name[2] == 0)
        {
          usable_file = 0;
        }
      }
      if(attributes & FILE_ATTRIBUTE_DIRECTORY)
      {
        if(flags & OS_FileIterFlag_SkipFolders)
        {
          usable_file = 0;
        }
      }
      else
      {
        if(flags & OS_FileIterFlag_SkipFiles)
        {
          usable_file = 0;
        }
      }
      if(usable_file)
      {
        info_out->name = str8_from_16(arena, str16_cstring((U16*)file_name));
        info_out->props.size = (U64)w32_iter->find_data.nFileSizeLow | (((U64)w32_iter->find_data.nFileSizeHigh)<<32);
        if(attributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          info_out->props.flags |= FilePropertyFlag_IsFolder;
        }
        result = 1;
        if(!FindNextFileW(w32_iter->handle, &w32_iter->find_data))
        {
          iter->flags |= OS_FileIterFlag_Done;
        }
        break;
      }
    }while(FindNextFileW(w32_iter->handle, &w32_iter->find_data));
  }
  if(!result)
  {
    iter->flags |= OS_FileIterFlag_Done;
  }
  return result;
}

internal void
os_file_iter_end(OS_FileIter *iter)
{
  OS_W32_FileIter *w32_iter = (OS_W32_FileIter*)iter->memory;
  HANDLE zero_handle;
  MemoryZeroStruct(&zero_handle);
  if(!MemoryMatchStruct(&zero_handle, &w32_iter->handle))
  {
    FindClose(w32_iter->handle);
  }
}

//- rjf: directory creation

internal B32
os_make_directory(String8 path)
{
  B32 result = 0;
  Temp scratch = temp_begin(arena_alloc());
  String16 name16 = str16_from_8(scratch.arena, path);
  WIN32_FILE_ATTRIBUTE_DATA attributes = {0};
  GetFileAttributesExW((WCHAR*)name16.str, GetFileExInfoStandard, &attributes);
  if(attributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
  {
    result = 1;
  }
  else if(CreateDirectoryW((WCHAR*)name16.str, 0))
  {
    result = 1;
  }
  temp_end(scratch);
  return(result);
}

#elif (CORE_OS_LINUX || CORE_OS_MAC)

#include <sys/stat.h>

internal OS_Handle
os_file_open(OS_AccessFlags flags, String8 path)
{
  OS_Handle result = {0};
  Temp scratch = temp_begin(arena_alloc());
  
  char *path_cstr = push_array(scratch.arena, char, path.size + 1);
  MemoryCopy(path_cstr, path.str, path.size);
  path_cstr[path.size] = 0;
  
  int open_flags = 0;
  if((flags & OS_AccessFlag_Read) && (flags & OS_AccessFlag_Write))
  {
    open_flags = O_RDWR;
  }
  else if(flags & OS_AccessFlag_Read)
  {
    open_flags = O_RDONLY;
  }
  else if(flags & OS_AccessFlag_Write)
  {
    open_flags = O_WRONLY;
  }
  
  if(flags & OS_AccessFlag_Write)
  {
    open_flags |= O_CREAT | O_TRUNC;
  }
  if(flags & OS_AccessFlag_Append)
  {
    open_flags |= O_CREAT | O_APPEND;
  }
  
  int fd = open(path_cstr, open_flags, 0644);
  if(fd >= 0)
  {
    result.u64[0] = (U64)(fd + 1); // +1 to avoid 0 being valid
  }
  
  temp_end(scratch);
  return result;
}

internal void
os_file_close(OS_Handle file)
{
  if(os_handle_match(file, os_handle_zero())) { return; }
  int fd = (int)(file.u64[0] - 1);
  close(fd);
}

internal U64
os_file_read(OS_Handle file, Rng1U64 rng, void *out_data)
{
  if(os_handle_match(file, os_handle_zero())) { return 0; }
  int fd = (int)(file.u64[0] - 1);
  
  U64 to_read = dim_1u64(rng);
  lseek(fd, rng.min, SEEK_SET);
  
  U64 total_read = 0;
  while(total_read < to_read)
  {
    ssize_t bytes_read = read(fd, (U8 *)out_data + total_read, to_read - total_read);
    if(bytes_read <= 0) break;
    total_read += bytes_read;
  }
  
  return total_read;
}

internal U64
os_file_write(OS_Handle file, Rng1U64 rng, void *data)
{
  if(os_handle_match(file, os_handle_zero())) { return 0; }
  int fd = (int)(file.u64[0] - 1);
  
  U64 to_write = dim_1u64(rng);
  lseek(fd, rng.min, SEEK_SET);
  
  U64 total_written = 0;
  while(total_written < to_write)
  {
    ssize_t bytes_written = write(fd, (U8 *)data + total_written, to_write - total_written);
    if(bytes_written <= 0) break;
    total_written += bytes_written;
  }
  
  return total_written;
}

internal FileProperties
os_properties_from_file(OS_Handle file)
{
  FileProperties props = {0};
  if(os_handle_match(file, os_handle_zero())) { return props; }
  int fd = (int)(file.u64[0] - 1);
  
  struct stat st;
  if(fstat(fd, &st) == 0)
  {
    props.size = st.st_size;
    if(S_ISDIR(st.st_mode))
    {
      props.flags |= FilePropertyFlag_IsFolder;
    }
  }
  
  return props;
}

//- rjf: file path operations

#include <dirent.h>

internal B32
os_delete_file_at_path(String8 path)
{
  Temp scratch = temp_begin(arena_alloc());
  B32 result = 0;
  String8 path_copy = push_str8_copy(scratch.arena, path);
  if(remove((char*)path_copy.str) != -1)
  {
    result = 1;
  }
  temp_end(scratch);
  return result;
}

internal B32
os_copy_file_path(String8 dst, String8 src)
{
  B32 result = 0;
  OS_Handle src_h = os_file_open(OS_AccessFlag_Read, src);
  OS_Handle dst_h = os_file_open(OS_AccessFlag_Write, dst);
  if(!os_handle_match(src_h, os_handle_zero()) &&
     !os_handle_match(dst_h, os_handle_zero()))
  {
    FileProperties src_props = os_properties_from_file(src_h);
    U64 size = src_props.size;
    if(size > 0)
    {
      Temp scratch = temp_begin(arena_alloc());
      U8 *buffer = push_array_no_zero(scratch.arena, U8, size);
      U64 bytes_read = os_file_read(src_h, r1u64(0, size), buffer);
      if(bytes_read > 0)
      {
        U64 bytes_written = os_file_write(dst_h, r1u64(0, bytes_read), buffer);
        result = (bytes_written == bytes_read);
      }
      temp_end(scratch);
    }
  }
  os_file_close(src_h);
  os_file_close(dst_h);
  return result;
}

internal B32
os_move_file_path(String8 dst, String8 src)
{
  B32 good = 0;
  Temp scratch = temp_begin(arena_alloc());
  {
    char *src_cstr = (char *)push_str8_copy(scratch.arena, src).str;
    char *dst_cstr = (char *)push_str8_copy(scratch.arena, dst).str;
    int rename_result = rename(src_cstr, dst_cstr);
    good = (rename_result != -1);
  }
  temp_end(scratch);
  return good;
}

internal String8
os_full_path_from_path(Arena *arena, String8 path)
{
  Temp scratch = temp_begin(arena_alloc());
  String8 path_copy = push_str8_copy(scratch.arena, path);
  char buffer[PATH_MAX] = {0};
  realpath((char *)path_copy.str, buffer);
  String8 result = push_str8_copy(arena, str8_cstring(buffer));
  temp_end(scratch);
  return result;
}

internal B32
os_file_path_exists(String8 path)
{
  Temp scratch = temp_begin(arena_alloc());
  String8 path_copy = push_str8_copy(scratch.arena, path);
  int access_result = access((char *)path_copy.str, F_OK);
  B32 result = (access_result == 0);
  temp_end(scratch);
  return result;
}

internal B32
os_folder_path_exists(String8 path)
{
  Temp scratch = temp_begin(arena_alloc());
  B32      exists    = 0;
  String8  path_copy = push_str8_copy(scratch.arena, path);
  DIR     *handle    = opendir((char*)path_copy.str);
  if(handle)
  {
    closedir(handle);
    exists = 1;
  }
  temp_end(scratch);
  return exists;
}

internal FileProperties
os_properties_from_file_path(String8 path)
{
  Temp scratch = temp_begin(arena_alloc());
  String8 path_copy = push_str8_copy(scratch.arena, path);
  struct stat f_stat = {0};
  int stat_result = stat((char *)path_copy.str, &f_stat);
  FileProperties props = {0};
  if(stat_result != -1)
  {
    props.size = f_stat.st_size;
    if(f_stat.st_mode & S_IFDIR)
    {
      props.flags |= FilePropertyFlag_IsFolder;
    }
  }
  temp_end(scratch);
  return props;
}

//- rjf: directory iteration

typedef struct OS_LNX_FileIter OS_LNX_FileIter;
struct OS_LNX_FileIter
{
  DIR *dir;
  struct dirent *dp;
  String8 path;
};
static_assert(sizeof(Member(OS_FileIter, memory)) >= sizeof(OS_LNX_FileIter), "lnx_file_iter_memory_size");

internal OS_FileIter *
os_file_iter_begin(Arena *arena, String8 path, OS_FileIterFlags flags)
{
  OS_FileIter *base_iter = push_array(arena, OS_FileIter, 1);
  base_iter->flags = flags;
  OS_LNX_FileIter *iter = (OS_LNX_FileIter *)base_iter->memory;
  {
    String8 path_copy = push_str8_copy(arena, path);
    iter->dir = opendir((char *)path_copy.str);
    iter->path = path_copy;
  }
  return base_iter;
}

internal B32
os_file_iter_next(Arena *arena, OS_FileIter *iter, OS_FileInfo *info_out)
{
  B32 good = 0;
  OS_LNX_FileIter *lnx_iter = (OS_LNX_FileIter *)iter->memory;
  for(;lnx_iter->dir != 0;)
  {
    lnx_iter->dp = readdir(lnx_iter->dir);
    good = (lnx_iter->dp != 0);
    
    struct stat st = {0};
    int stat_result = 0;
    if(good)
    {
      Temp scratch = temp_begin(arena_alloc());
      String8 full_path = push_str8f(scratch.arena, "%S/%s", lnx_iter->path, lnx_iter->dp->d_name);
      stat_result = stat((char *)full_path.str, &st);
      temp_end(scratch);
    }
    
    B32 filtered = 0;
    if(good)
    {
      filtered = ((S_ISDIR(st.st_mode)  && (iter->flags & OS_FileIterFlag_SkipFolders)) ||
                  (S_ISREG(st.st_mode)  && (iter->flags & OS_FileIterFlag_SkipFiles)) ||
                  (lnx_iter->dp->d_name[0] == '.' && lnx_iter->dp->d_name[1] == 0) ||
                  (lnx_iter->dp->d_name[0] == '.' && lnx_iter->dp->d_name[1] == '.' && lnx_iter->dp->d_name[2] == 0));
    }
    
    if(good && !filtered)
    {
      info_out->name = push_str8_copy(arena, str8_cstring(lnx_iter->dp->d_name));
      if(stat_result != -1)
      {
        info_out->props.size = st.st_size;
        if(S_ISDIR(st.st_mode))
        {
          info_out->props.flags |= FilePropertyFlag_IsFolder;
        }
      }
      break;
    }
    
    if(!good)
    {
      break;
    }
  }
  return good;
}

internal void
os_file_iter_end(OS_FileIter *iter)
{
  OS_LNX_FileIter *lnx_iter = (OS_LNX_FileIter *)iter->memory;
  if(lnx_iter->dir)
  {
    closedir(lnx_iter->dir);
  }
}

//- rjf: directory creation

internal B32
os_make_directory(String8 path)
{
  Temp scratch = temp_begin(arena_alloc());
  B32 result = 0;
  String8 path_copy = push_str8_copy(scratch.arena, path);
  if(mkdir((char*)path_copy.str, 0755) != -1)
  {
    result = 1;
  }
  else
  {
    // already exists?
    struct stat st;
    if(stat((char*)path_copy.str, &st) == 0 && S_ISDIR(st.st_mode))
    {
      result = 1;
    }
  }
  temp_end(scratch);
  return result;
}

#endif // CORE_OS_WINDOWS / CORE_OS_LINUX / CORE_OS_MAC

////////////////////////////////
//~ rjf: Shared Memory Implementation

#if CORE_OS_WINDOWS

internal OS_Handle
os_shared_memory_alloc(U64 size, String8 name)
{
  Temp scratch = temp_begin(arena_alloc());
  String16 name16 = str16_from_8(scratch.arena, name);
  HANDLE file = CreateFileMappingW(INVALID_HANDLE_VALUE,
                                   0,
                                   PAGE_READWRITE,
                                   (U32)((size & 0xffffffff00000000) >> 32),
                                   (U32)((size & 0x00000000ffffffff)),
                                   (WCHAR *)name16.str);
  OS_Handle result = {(U64)file};
  temp_end(scratch);
  return result;
}

internal OS_Handle
os_shared_memory_open(String8 name)
{
  Temp scratch = temp_begin(arena_alloc());
  String16 name16 = str16_from_8(scratch.arena, name);
  HANDLE file = OpenFileMappingW(FILE_MAP_ALL_ACCESS, 0, (WCHAR *)name16.str);
  OS_Handle result = {(U64)file};
  temp_end(scratch);
  return result;
}

internal void
os_shared_memory_close(OS_Handle handle)
{
  HANDLE file = (HANDLE)(handle.u64[0]);
  CloseHandle(file);
}

internal void *
os_shared_memory_view_open(OS_Handle handle, Rng1U64 range)
{
  HANDLE file = (HANDLE)(handle.u64[0]);
  U64 offset = range.min;
  U64 size = range.max - range.min;
  void *ptr = MapViewOfFile(file, FILE_MAP_ALL_ACCESS,
                            (U32)((offset & 0xffffffff00000000) >> 32),
                            (U32)((offset & 0x00000000ffffffff)),
                            size);
  return ptr;
}

internal void
os_shared_memory_view_close(OS_Handle handle, void *ptr, Rng1U64 range)
{
  UnmapViewOfFile(ptr);
}

#elif (CORE_OS_LINUX || CORE_OS_MAC)

#include <sys/mman.h>

internal OS_Handle
os_shared_memory_alloc(U64 size, String8 name)
{
  Temp scratch = temp_begin(arena_alloc());
  String8 name_copy = push_str8_copy(scratch.arena, name);
  int id = shm_open((char *)name_copy.str, O_RDWR|O_CREAT, 0666);
  ftruncate(id, size);
  OS_Handle result = {(U64)id};
  temp_end(scratch);
  return result;
}

internal OS_Handle
os_shared_memory_open(String8 name)
{
  Temp scratch = temp_begin(arena_alloc());
  String8 name_copy = push_str8_copy(scratch.arena, name);
  int id = shm_open((char *)name_copy.str, O_RDWR, 0);
  OS_Handle result = {(U64)id};
  temp_end(scratch);
  return result;
}

internal void
os_shared_memory_close(OS_Handle handle)
{
  if(os_handle_match(handle, os_handle_zero())){return;}
  int id = (int)handle.u64[0];
  close(id);
}

internal void *
os_shared_memory_view_open(OS_Handle handle, Rng1U64 range)
{
  if(os_handle_match(handle, os_handle_zero())){return 0;}
  int id = (int)handle.u64[0];
  void *base = mmap(0, dim_1u64(range), PROT_READ|PROT_WRITE, MAP_SHARED, id, range.min);
  if(base == MAP_FAILED)
  {
    base = 0;
  }
  return base;
}

internal void
os_shared_memory_view_close(OS_Handle handle, void *ptr, Rng1U64 range)
{
  if(os_handle_match(handle, os_handle_zero())){return;}
  munmap(ptr, dim_1u64(range));
}

#endif // CORE_OS_WINDOWS / CORE_OS_LINUX / CORE_OS_MAC

////////////////////////////////
//~ rjf: File Helpers Implementation (Platform-Independent)

internal String8
os_data_from_file_path(Arena *arena, String8 path)
{
  OS_Handle file = os_file_open(OS_AccessFlag_Read | OS_AccessFlag_ShareRead, path);
  FileProperties props = os_properties_from_file(file);
  String8 data = {0};
  if(props.size > 0)
  {
    data.str = push_array_no_zero(arena, U8, props.size);
    data.size = os_file_read(file, r1u64(0, props.size), data.str);
  }
  os_file_close(file);
  return data;
}

internal B32
os_write_data_to_file_path(String8 path, String8 data)
{
  B32 good = 0;
  OS_Handle file = os_file_open(OS_AccessFlag_Write, path);
  if(!os_handle_match(file, os_handle_zero()))
  {
    U64 bytes_written = os_file_write(file, r1u64(0, data.size), data.str);
    good = (bytes_written == data.size);
    os_file_close(file);
  }
  return good;
}

////////////////////////////////
//~ rjf: Current Path Implementation

#if CORE_OS_WINDOWS

internal String8
os_get_current_path(Arena *arena)
{
  Temp scratch = temp_begin(arena_alloc());
  DWORD length = GetCurrentDirectoryW(0, 0);
  U16 *memory = push_array_no_zero(scratch.arena, U16, length + 1);
  length = GetCurrentDirectoryW(length + 1, (WCHAR*)memory);
  String8 name = str8_from_16(arena, str16(memory, length));
  temp_end(scratch);
  return name;
}

#elif (CORE_OS_LINUX || CORE_OS_MAC)

internal String8
os_get_current_path(Arena *arena)
{
  char *cwd = getcwd(0, 0);
  String8 result = {0};
  if(cwd)
  {
    U64 len = strlen(cwd);
    result.str = push_array_no_zero(arena, U8, len);
    result.size = len;
    MemoryCopy(result.str, cwd, len);
    free(cwd);
  }
  return result;
}

#endif // CORE_OS_WINDOWS / CORE_OS_LINUX / CORE_OS_MAC

////////////////////////////////
//~ rjf: Home Path Implementation

#if CORE_OS_WINDOWS

internal String8
os_get_home_path(Arena *arena)
{
  String8 result = {0};
  Temp scratch = temp_begin(arena);
  U64 size = KB(32);
  U16 *buffer = push_array_no_zero(scratch.arena, U16, size);
  if(SUCCEEDED(SHGetFolderPathW(0, CSIDL_PROFILE, 0, 0, (WCHAR*)buffer)))
  {
    result = str8_from_16(arena, str16_cstring(buffer));
  }
  temp_end(scratch);
  return result;
}

#elif (CORE_OS_LINUX || CORE_OS_MAC)

internal String8
os_get_home_path(Arena *arena)
{
  String8 result = {0};
  char *home = getenv("HOME");
  if(home)
  {
    result = push_str8_copy(arena, str8_cstring(home));
  }
  return result;
}

#endif // CORE_OS_WINDOWS / CORE_OS_LINUX / CORE_OS_MAC

////////////////////////////////
//~ rjf: System/Process Info Implementation

#if CORE_OS_WINDOWS

internal void
os_w32_state_init(void)
{
  if(!os_w32_state.initialized)
  {
    os_w32_state.arena = arena_alloc();
    Arena *arena = os_w32_state.arena;
    
    // system info
    {
      SYSTEM_INFO sysinfo;
      GetSystemInfo(&sysinfo);
      OS_SystemInfo *info = &os_w32_state.system_info;
      info->logical_processor_count = (U32)sysinfo.dwNumberOfProcessors;
      info->page_size               = sysinfo.dwPageSize;
      info->large_page_size         = GetLargePageMinimum();
      info->allocation_granularity  = sysinfo.dwAllocationGranularity;
      
      char buffer[MAX_COMPUTERNAME_LENGTH + 1] = {0};
      DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
      if(GetComputerNameA(buffer, &size))
      {
        info->machine_name = push_str8_copy(arena, str8_cstring(buffer));
      }
    }
    
    // process info
    {
      OS_ProcessInfo *info = &os_w32_state.process_info;
      info->pid = GetCurrentProcessId();
      info->is_elevated = 0;
      {
        HANDLE token = 0;
        if(OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token))
        {
          TOKEN_ELEVATION elevation = {0};
          DWORD bytes = 0;
          if(GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &bytes))
          {
            info->is_elevated = (B32)elevation.TokenIsElevated;
          }
          CloseHandle(token);
        }
      }
      
      // binary path
      {
        Temp scratch = temp_begin(arena);
        DWORD size = KB(32);
        U16 *buffer = push_array_no_zero(scratch.arena, U16, size);
        DWORD length = GetModuleFileNameW(0, (WCHAR*)buffer, size);
        String8 name8 = str8_from_16(scratch.arena, str16(buffer, length));
        String8 name_chopped = str8_chop_last_slash(name8);
        info->binary_path = push_str8_copy(arena, name_chopped);
        temp_end(scratch);
      }
      
      // initial path
      info->initial_path = os_get_current_path(arena);
      
      // user program data path (AppData)
      {
        Temp scratch = temp_begin(arena);
        U64 size = KB(32);
        U16 *buffer = push_array_no_zero(scratch.arena, U16, size);
        if(SUCCEEDED(SHGetFolderPathW(0, CSIDL_APPDATA, 0, 0, (WCHAR*)buffer)))
        {
          info->user_program_data_path = str8_from_16(arena, str16_cstring(buffer));
        }
        temp_end(scratch);
      }
    }
    
    os_w32_state.initialized = 1;
  }
}

internal OS_SystemInfo *
os_get_system_info(void)
{
  os_w32_state_init();
  return &os_w32_state.system_info;
}

internal OS_ProcessInfo *
os_get_process_info(void)
{
  os_w32_state_init();
  return &os_w32_state.process_info;
}

#elif (CORE_OS_LINUX || CORE_OS_MAC)

internal void
os_lnx_state_init(void)
{
  if(!os_lnx_state.initialized)
  {
    os_lnx_state.arena = arena_alloc();
    Arena *arena = os_lnx_state.arena;
    
    // system info
    {
      OS_SystemInfo *info = &os_lnx_state.system_info;
      info->logical_processor_count = (U32)sysconf(_SC_NPROCESSORS_ONLN);
      info->page_size               = (U64)getpagesize();
      info->large_page_size         = MB(2);
      info->allocation_granularity  = info->page_size;
      
      char hostname[256] = {0};
      if(gethostname(hostname, sizeof(hostname)) == 0)
      {
        info->machine_name = push_str8_copy(arena, str8_cstring(hostname));
      }
    }
    
    // process info
    {
      OS_ProcessInfo *info = &os_lnx_state.process_info;
      info->pid = (U32)getpid();
      info->is_elevated = (geteuid() == 0);
      
      // binary path
      {
        char path[4096] = {0};
        ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
        if(len > 0)
        {
          path[len] = 0;
          String8 full_path = str8_cstring(path);
          info->binary_path = push_str8_copy(arena, str8_chop_last_slash(full_path));
        }
      }
      
      // initial path
      info->initial_path = os_get_current_path(arena);
      
      // user program data path (HOME)
      {
        char *home = getenv("HOME");
        if(home)
        {
          info->user_program_data_path = push_str8_copy(arena, str8_cstring(home));
        }
      }
    }
    
    os_lnx_state.initialized = 1;
  }
}

internal OS_SystemInfo *
os_get_system_info(void)
{
  os_lnx_state_init();
  return &os_lnx_state.system_info;
}

internal OS_ProcessInfo *
os_get_process_info(void)
{
  os_lnx_state_init();
  return &os_lnx_state.process_info;
}

#endif // CORE_OS_WINDOWS / CORE_OS_LINUX / CORE_OS_MAC

////////////////////////////////
//~ rjf: Process Launcher Helpers Implementation

internal OS_Handle
os_cmd_line_launch(String8 string, B32 non_elevated, B32 new_process_group)
{
  Temp scratch = temp_begin(arena_alloc());
  
  // rjf: parse command line with quote support
  String8List parts = {0};
  {
    U8 *ptr = string.str;
    U8 *end = string.str + string.size;
    while(ptr < end)
    {
      // skip whitespace
      while(ptr < end && (*ptr == ' ' || *ptr == '\t'))
      {
        ptr++;
      }
      if(ptr >= end) break;
      
      // parse token
      U8 *token_start = ptr;
      U8 *token_end = ptr;
      if(*ptr == '"')
      {
        // quoted token - find closing quote
        ptr++;
        token_start = ptr;
        while(ptr < end && *ptr != '"')
        {
          ptr++;
        }
        token_end = ptr;
        if(ptr < end) ptr++; // skip closing quote
      }
      else
      {
        // unquoted token - read until whitespace
        while(ptr < end && *ptr != ' ' && *ptr != '\t')
        {
          ptr++;
        }
        token_end = ptr;
      }
      
      // push token
      if(token_end > token_start)
      {
        String8 token = str8(token_start, (U64)(token_end - token_start));
        str8_list_push(scratch.arena, &parts, token);
      }
    }
  }
  
  OS_Handle handle = {0};
  if(parts.node_count != 0)
  {
    // rjf: unpack exe part
    String8 exe = parts.first->string;
    String8 exe_folder = str8_chop_last_slash(exe);
    if(exe_folder.size == 0 || exe_folder.size == exe.size)
    {
      exe_folder = os_get_current_path(scratch.arena);
    }
    
    // rjf: find stdout delimiter
    String8Node *stdout_delimiter_n = 0;
    for(String8Node *n = parts.first; n != 0; n = n->next)
    {
      if(str8_match(n->string, str8_lit(">"), 0))
      {
        stdout_delimiter_n = n;
        break;
      }
    }
    
    // rjf: read stdout path
    String8 stdout_path = {0};
    if(stdout_delimiter_n && stdout_delimiter_n->next)
    {
      stdout_path = stdout_delimiter_n->next->string;
    }
    
    // rjf: open stdout handle
    OS_Handle stdout_handle = {0};
    if(stdout_path.size != 0)
    {
      OS_Handle file = os_file_open(OS_AccessFlag_Write|OS_AccessFlag_Read, stdout_path);
      os_file_close(file);
      stdout_handle = os_file_open(OS_AccessFlag_Write|OS_AccessFlag_Append|OS_AccessFlag_ShareRead|OS_AccessFlag_ShareWrite|OS_AccessFlag_Inherited, stdout_path);
    }
    
    // rjf: form command line
    String8List cmdline = {0};
    for(String8Node *n = parts.first; n != stdout_delimiter_n && n != 0; n = n->next)
    {
      str8_list_push(scratch.arena, &cmdline, n->string);
    }
    
    // rjf: launch
    OS_ProcessLaunchParams params = {0};
    params.cmd_line = cmdline;
    params.path = exe_folder;
    params.inherit_env = 1;
    params.consoleless = 1;
    params.non_elevated = non_elevated;
    params.new_process_group = new_process_group;
    params.stdout_file = stdout_handle;
    handle = os_process_launch(&params);
    
    // rjf: close stdout handle
    if(stdout_path.size != 0)
    {
      os_file_close(stdout_handle);
    }
  }
  temp_end(scratch);
  return handle;
}

////////////////////////////////
//~ rjf: Child Processes Implementation

#if CORE_OS_WINDOWS

internal OS_Handle
os_process_launch(OS_ProcessLaunchParams *params)
{
  OS_Handle result = {0};
  Temp scratch = temp_begin(arena_alloc());
  
  //- rjf: form full command string
  String8 cmd = {0};
  {
    // Join command line parts with space
    StringJoin join = {str8_lit(""), str8_lit(" "), str8_lit("")};
    cmd = str8_list_join(scratch.arena, &params->cmd_line, &join);
  }
  
  //- rjf: form environment
  B32 use_null_env_arg = 0;
  String8 env = {0};
  {
    String8List all_opts = params->env;
    if(params->inherit_env != 0)
    {
      if(all_opts.node_count == 0)
      {
        use_null_env_arg = 1;
      }
    }
    if(use_null_env_arg == 0 && all_opts.node_count > 0)
    {
      U64 total_size = 0;
      for(String8Node *n = all_opts.first; n != 0; n = n->next)
      {
        total_size += n->string.size + 1; // null terminator
      }
      total_size += 1; // final null
      U8 *env_buffer = push_array_no_zero(scratch.arena, U8, total_size);
      U64 pos = 0;
      for(String8Node *n = all_opts.first; n != 0; n = n->next)
      {
        MemoryCopy(env_buffer + pos, n->string.str, n->string.size);
        pos += n->string.size;
        env_buffer[pos++] = 0;
      }
      env_buffer[pos] = 0;
      env = str8(env_buffer, pos);
    }
  }
  
  //- rjf: utf-8 -> utf-16
  String16 cmd16 = str16_from_8(scratch.arena, cmd);
  String16 dir16 = str16_from_8(scratch.arena, params->path);
  String16 env16 = {0};
  if(use_null_env_arg == 0 && env.size > 0)
  {
    env16 = str16_from_8(scratch.arena, env);
  }
  
  //- rjf: determine creation flags
  DWORD creation_flags = CREATE_UNICODE_ENVIRONMENT;
  if(params->consoleless)
  {
    creation_flags |= CREATE_NO_WINDOW;
  }
  if(params->new_process_group)
  {
    creation_flags |= CREATE_NEW_PROCESS_GROUP;
  }
  
  //- rjf: launch
  STARTUPINFOW startup_info = {sizeof(startup_info)};
  BOOL inherit_handles = 0;
  if(!os_handle_match(params->stdout_file, os_handle_zero()))
  {
    HANDLE stdout_handle = (HANDLE)params->stdout_file.u64[0];
    startup_info.hStdOutput = stdout_handle;
    startup_info.dwFlags |= STARTF_USESTDHANDLES;
    inherit_handles = 1;
  }
  if(!os_handle_match(params->stderr_file, os_handle_zero()))
  {
    HANDLE stderr_handle = (HANDLE)params->stderr_file.u64[0];
    startup_info.hStdError = stderr_handle;
    startup_info.dwFlags |= STARTF_USESTDHANDLES;
    inherit_handles = 1;
  }
  if(!os_handle_match(params->stdin_file, os_handle_zero()))
  {
    HANDLE stdin_handle = (HANDLE)params->stdin_file.u64[0];
    startup_info.hStdInput = stdin_handle;
    startup_info.dwFlags |= STARTF_USESTDHANDLES;
    inherit_handles = 1;
  }
  PROCESS_INFORMATION process_info = {0};
  B32 current_is_elevated = os_get_process_info()->is_elevated;
  
  if(params->non_elevated && current_is_elevated)
  {
    //enable SE_IMPERSONATE_NAME privilege (required for CreateProcessWithTokenW)
    {
      HANDLE token = 0;
      if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &token))
      {
        LUID luid = {0};
        if(LookupPrivilegeValueW(0, SE_IMPERSONATE_NAME, &luid))
        {
          TOKEN_PRIVILEGES tp = {0};
          tp.PrivilegeCount = 1;
          tp.Privileges[0].Luid = luid;
          tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
          AdjustTokenPrivileges(token, 0, &tp, 0, 0, 0);
        }
        CloseHandle(token);
      }
    }
    
    HWND shell_wnd = GetShellWindow();
    DWORD shell_pid = 0;
    GetWindowThreadProcessId(shell_wnd, &shell_pid);
    
    HANDLE shell_process = 0;
    HANDLE shell_token = 0;
    HANDLE user_token = 0;

    do
    {
      shell_process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, 0, shell_pid);
      if(!shell_process) { break; }

      if(!OpenProcessToken(shell_process, TOKEN_DUPLICATE|TOKEN_QUERY, &shell_token)) { break; }

      if(!DuplicateTokenEx(shell_token,
                           TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_DEFAULT | TOKEN_ADJUST_SESSIONID,
                           0, SecurityImpersonation, TokenPrimary, &user_token))
      { break; }

      if(!CreateProcessWithTokenW(user_token, 0, 0, (WCHAR*)cmd16.str,
                                  creation_flags,
                                  use_null_env_arg ? 0 : (WCHAR*)env16.str,
                                  dir16.size > 0 ? (WCHAR*)dir16.str : 0,
                                  &startup_info, &process_info))
      { break; }
    } while(0);

    if(user_token)   { CloseHandle(user_token); }
    if(shell_token)  { CloseHandle(shell_token); }
    if(shell_process){ CloseHandle(shell_process); }
  }
  else
  {
    CreateProcessW(0, (WCHAR*)cmd16.str, 0, 0, inherit_handles, creation_flags,
                   use_null_env_arg ? 0 : (WCHAR*)env16.str,
                   dir16.size > 0 ? (WCHAR*)dir16.str : 0,
                   &startup_info, &process_info);
  }
  if(process_info.hProcess)
  {
    result.u64[0] = (U64)process_info.hProcess;
    CloseHandle(process_info.hThread);
  }
  
  temp_end(scratch);
  return result;
}

internal B32
os_process_join(OS_Handle handle, U64 endt_us, U64 *exit_code_out)
{
  HANDLE process = (HANDLE)(handle.u64[0]);
  U32 sleep_ms = 0;
  if(endt_us == max_U64)
  {
    sleep_ms = INFINITE;
  }
  else
  {
    U64 now_us = os_now_microseconds();
    if(now_us < endt_us)
    {
      U64 sleep_us = endt_us - now_us;
      sleep_ms = (U32)((sleep_us + 999)/1000);
    }
  }
  DWORD result = WaitForSingleObject(process, sleep_ms);
  B32 process_joined = (result == WAIT_OBJECT_0);
  if(process_joined && exit_code_out)
  {
    DWORD exit_code = 0;
    if(GetExitCodeProcess(process, &exit_code))
    {
      *exit_code_out = exit_code;
    }
  }
  return process_joined;
}

internal B32
os_process_kill(OS_Handle handle)
{
  HANDLE process = (HANDLE)handle.u64[0];
  BOOL was_terminated = TerminateProcess(process, 999);
  return was_terminated;
}

internal void
os_process_detach(OS_Handle handle)
{
  HANDLE process = (HANDLE)(handle.u64[0]);
  CloseHandle(process);
}

#elif (CORE_OS_LINUX || CORE_OS_MAC)

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <spawn.h>

extern char **environ;

internal OS_Handle
os_process_launch(OS_ProcessLaunchParams *params)
{
  OS_Handle result = {0};
  Temp scratch = temp_begin(arena_alloc());
  
  // Build argv array
  U64 argc = params->cmd_line.node_count;
  char **argv = push_array(scratch.arena, char *, argc + 1);
  U64 i = 0;
  for(String8Node *n = params->cmd_line.first; n != 0; n = n->next, i++)
  {
    char *arg = push_array(scratch.arena, char, n->string.size + 1);
    MemoryCopy(arg, n->string.str, n->string.size);
    arg[n->string.size] = 0;
    argv[i] = arg;
  }
  argv[argc] = 0;
  
  // Build envp array
  char **envp = environ;
  if(!params->inherit_env && params->env.node_count > 0)
  {
    U64 envc = params->env.node_count;
    envp = push_array(scratch.arena, char *, envc + 1);
    i = 0;
    for(String8Node *n = params->env.first; n != 0; n = n->next, i++)
    {
      char *env = push_array(scratch.arena, char, n->string.size + 1);
      MemoryCopy(env, n->string.str, n->string.size);
      env[n->string.size] = 0;
      envp[i] = env;
    }
    envp[envc] = 0;
  }
  
  // Change directory if specified
  char *old_cwd = 0;
  if(params->path.size > 0)
  {
    old_cwd = getcwd(0, 0);
    char *path = push_array(scratch.arena, char, params->path.size + 1);
    MemoryCopy(path, params->path.str, params->path.size);
    path[params->path.size] = 0;
    chdir(path);
  }
  
  // Fork and exec
  pid_t pid = fork();
  if(pid == 0)
  {
    // Child process
    if(params->new_process_group)
    {
      setpgid(0, 0);
    }
    if(!os_handle_match(params->stdout_file, os_handle_zero()))
    {
      dup2((int)params->stdout_file.u64[0], STDOUT_FILENO);
    }
    if(!os_handle_match(params->stderr_file, os_handle_zero()))
    {
      dup2((int)params->stderr_file.u64[0], STDERR_FILENO);
    }
    if(!os_handle_match(params->stdin_file, os_handle_zero()))
    {
      dup2((int)params->stdin_file.u64[0], STDIN_FILENO);
    }
    execve(argv[0], argv, envp);
    _exit(127);
  }
  else if(pid > 0)
  {
    result.u64[0] = (U64)pid;
  }
  
  // Restore directory
  if(old_cwd)
  {
    chdir(old_cwd);
    free(old_cwd);
  }
  
  temp_end(scratch);
  return result;
}

internal B32
os_process_join(OS_Handle handle, U64 endt_us, U64 *exit_code_out)
{
  pid_t pid = (pid_t)handle.u64[0];
  int status = 0;
  
  if(endt_us == max_U64)
  {
    // Blocking wait
    pid_t result = waitpid(pid, &status, 0);
    if(result == pid)
    {
      if(exit_code_out && WIFEXITED(status))
      {
        *exit_code_out = WEXITSTATUS(status);
      }
      return 1;
    }
  }
  else
  {
    // Non-blocking wait with timeout
    while(1)
    {
      pid_t result = waitpid(pid, &status, WNOHANG);
      if(result == pid)
      {
        if(exit_code_out && WIFEXITED(status))
        {
          *exit_code_out = WEXITSTATUS(status);
        }
        return 1;
      }
      if(result < 0) return 0;
      
      U64 now_us = os_now_microseconds();
      if(now_us >= endt_us) return 0;
      
      usleep(1000); // 1ms sleep
    }
  }
  return 0;
}

internal B32
os_process_kill(OS_Handle handle)
{
  pid_t pid = (pid_t)handle.u64[0];
  int result = kill(pid, SIGKILL);
  return (result == 0);
}

internal void
os_process_detach(OS_Handle handle)
{
  // On POSIX, we don't need to close anything for the PID
  // But we should wait to avoid zombie processes
  pid_t pid = (pid_t)handle.u64[0];
  waitpid(pid, 0, WNOHANG);
}

#endif // CORE_OS_WINDOWS / CORE_OS_LINUX / CORE_OS_MAC

#endif