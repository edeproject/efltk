#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#ifndef _OFF_T_DEFINED
typedef long off_t;
#define _OFF_T_DEFINED
#endif

#ifdef __cplusplus

/*typedef DWORD  SERVICE_STATUS_HANDLE;
typedef struct _SERVICE_STATUS {
    DWORD   dwServiceType;
    DWORD   dwCurrentState;
    DWORD   dwControlsAccepted;
    DWORD   dwWin32ExitCode;
    DWORD   dwServiceSpecificExitCode;
    DWORD   dwCheckPoint;
    DWORD   dwWaitHint;
} SERVICE_STATUS, *LPSERVICE_STATUS;

#define HAVE_STRING_H 1
*/

#endif 

typedef __int64 __time64_t;
typedef unsigned short _ino_t;          /* i-node number (not used on DOS) */
typedef unsigned short ino_t;
typedef unsigned int _dev_t;            /* device code */
typedef unsigned int dev_t;
typedef long _off_t;                    /* file offset value */


#endif  /* TYPES_H */
