#ifndef _XIPHOS_ATTRS_H_
#define _XIPHOS_ATTRS_H_


#define __IN__
#define __OUT__
#define __OPTIONAL__

#define __ALIAS__(s)        __attribute__ ((alias(#s)))
#define __ALIGN__(n)        __attribute__ ((aligned(n)))
#define __ALWAYS_INLINE__   __attribute__ ((always_inline))
#define __CDECL__           __attribute__ ((cdecl))
#define __COLD__            __attribute__ ((cold))
#define __CONST__           __attribute__ ((const))
#define __CONSTRUCTOR__     __attribute__ ((constructor))
#define __NORETURN__        __attribute__ ((noreturn))
#define __PACKED__          __attribute__ ((packed))
#define __PURE__            __attribute__ ((pure))
#define __SECTION__(s)      __attribute__ ((section(#s)))
#define __SENTINEL__(n)     __attribute__ ((sentinel(n)))
#define __UNUSED__          __attribute__ ((unused))
#define __USED__            __attribute__ ((used))
#define __WEAK__            __attribute__ ((weak))
#define __WEAKREF__(s)      __attribute__ ((weakref(#s)))

#define __XINIT__(s)    __SECTION__(.init.s) __attribute__((no_stack_protector)) __COLD__
#define __XINIT_ACPI__  __XINIT__(acpi)
#define __XINIT_CPU__   __XINIT__(cpu)
#define __XINIT_IRQ__   __XINIT__(irq)
#define __XINIT_VIDEO__ __XINIT__(video)

#define __API__(s)      __SECTION__(.api.s)
#define __LIBOS__(s)    __SECTION__(.libos.s)


#endif /* ! _XIPHOS_ATTRS_H_ */
