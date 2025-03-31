#ifndef GOOBOS_STDDEF_H_
#define GOOBOS_STDDEF_H_

#undef NULL
#define NULL ((void *) 0)

#undef offsetof
#define offsetof(TYPE, MEMBER) __builtin_offsetof(TYPE, MEMBER)

typedef long unsigned int size_t;

#endif // GOOBOS_STDDEF_H_
