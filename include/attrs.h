#ifndef _XIPHOS_ATTRS_H_
#define _XIPHOS_ATTRS_H_


#define __IN__
#define __OUT__
#define __OPTIONAL__

#define __ALIAS__(S)        __attribute__ ((alias(#S)))
#define __ALIGN__(N)        __attribute__ ((aligned(N)))
#define __COLD__            __attribute__ ((cold))
#define __CONST__           __attribute__ ((const))
#define __HOT__             __attribute__ ((hot))
#define __MALLOC_LIKE__     __attribute__ ((malloc))
#define __NAKED__           __attribute__ ((naked))
#define __NONNULL__(N, ...)      __attribute__ ((nonnull(N, ##__VA_ARGS__)))
#define __NORETURN__        __attribute__ ((noreturn))
#define __PACKED__          __attribute__ ((packed))
#define __PURE__            __attribute__ ((pure))
#define __SECTION__(S)      __attribute__ ((section(#S)))
#define __UNUSED__          __attribute__ ((unused))
#define __USED__            __attribute__ ((used))
#define __WEAK__            __attribute__ ((weak))

#define __NONSTRING__       __attribute__ ((nonstring))

#define __XINIT__(S)    __SECTION__(.init.S) __attribute__((no_stack_protector)) __COLD__

#define __API__(S)      __SECTION__(.api.S)
#define __LIBOS__(S)    __SECTION__(.libos.S)


#define __LIKELY__(EXP)     __builtin_expect(EXP, 1)
#define __UNLIKELY__(EXP)   __builtin_expect(EXP, 0)


#endif /* ! _XIPHOS_ATTRS_H_ */
