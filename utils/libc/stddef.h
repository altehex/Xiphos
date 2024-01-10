#ifndef _STDDEF_H_
#define _STDDEF_H_


#define offsetof(STRUCT, MEMBER)				\
	__builtin_offsetof(STRUCT, MEMBER)


#endif /* ! _STDDEF_H_ */
