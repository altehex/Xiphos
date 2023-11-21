#ifndef _XIPHOS_ATTRS_H_
#define _XIPHOS_ATTRS_H_


#define __IN__
#define __OUT__
#define __OPTIONAL__

/* Function attributes */
#define __ALIAS__(s)        __attribute__ ((alias(#s)))
#define __ALIGN__(n)        __attribute__ ((aligned(n)))
#define __COLD__            __attribute__ ((cold))
#define __CONST__           __attribute__ ((const))
#define __HOT__             __attribute__ ((hot))
#define __MALLOC_LIKE__     __attribute__ ((malloc))
#define __NORETURN__        __attribute__ ((noreturn))
#define __PACKED__          __attribute__ ((packed))
#define __PURE__            __attribute__ ((pure))
#define __SECTION__(s)      __attribute__ ((section(#s)))
#define __UNUSED__          __attribute__ ((unused))
#define __USED__            __attribute__ ((used))
#define __WEAK__            __attribute__ ((weak))

/* Variable attributes */
#define __NONSTRING__       __attribute__ ((nonstring))

#define __XINIT__(s)    __SECTION__(.init.s) __attribute__((no_stack_protector)) __COLD__
#define __XINIT_ACPI__  __XINIT__(acpi)
#define __XINIT_CPU__   __XINIT__(cpu)
#define __XINIT_IRQ__   __XINIT__(irq)
#define __XINIT_MEM__   __XINIT__(mem)
#define __XINIT_VIDEO__ __XINIT__(video)

#define __API__(s)      __SECTION__(.api.s)
#define __LIBOS__(s)    __SECTION__(.libos.s)


#define __LIKELY__(exp)     __builtin_expect(exp, 1)
#define __UNLIKELY__(exp)   __builtin_expect(exp, 0)


#endif /* ! _XIPHOS_ATTRS_H_ */
