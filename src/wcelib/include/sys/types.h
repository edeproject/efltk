#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#ifndef _OFF_T_DEFINED
typedef long off_t;
#define _OFF_T_DEFINED
#endif

#ifdef __cplusplus


#endif 

#define HAVE_STRING_H 1


typedef __int64 __time64_t;
typedef unsigned short _ino_t;          /* i-node number (not used on DOS) */
typedef unsigned short ino_t;
typedef unsigned int _dev_t;            /* device code */
typedef unsigned int dev_t;
typedef long _off_t;                    /* file offset value */


#endif  /* TYPES_H */
