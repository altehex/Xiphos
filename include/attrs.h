#ifndef _ATTRS_H_
#define _ATTRS_H_


#define __ALIGN__(n)        __attribute__ ((aligned(n)))
#define __ALWAYS_INLINE__   __attribute__ ((always_inline))
#define __CONSTRUCTOR__     __attribute__ ((constructor))
#define __NORETURN__        __attribute__ ((noreturn))
#define __PACKED__          __attribute__ ((packed))
#define __SECTION__(s)      __attribute__ ((section (#s)))
#define __UNUSED__          __attribute__ ((unused))
#define __WEAK__            __attribute__ ((weak))

#define __KINIT__(s)    __SECTION__(.init.s) __attribute__((no_stack_protector))
#define __KINIT_ACPI__  __KINIT__(acpi)
#define __KINIT_CPU__   __KINIT__(cpu)
#define __KINIT_IRQ__   __KINIT__(irq)
#define __KINIT_VIDEO__ __KINIT__(video)

#define __LIBOS__(s)    __SECTION__(.libos.s)


#endif /* ! _ATTRS_H_ */
