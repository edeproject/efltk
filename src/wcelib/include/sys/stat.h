//
// (c) Yuri Kiryanov, openh323@kiryanov.com
// for Openh323, www.Openh323.org
//
// Windows CE Port
// Extra header file 
// 

#include <stdlibx.h>
#include <sys/types.h>

#define _S_IFMT         0170000         /* file type mask */
#define _S_IFDIR        0040000         /* directory */
#define _S_IFCHR        0020000         /* character special */
#define _S_IFIFO        0010000         /* pipe */
#define _S_IFREG        0100000         /* regular */
#define _S_IREAD        0000400         /* read permission, owner */
#define _S_IWRITE       0000200         /* write permission, owner */
#define _S_IEXEC        0000100         /* execute/search permission, owner */


typedef __int64 __time64_t;
typedef unsigned short _ino_t;          /* i-node number (not used on DOS) */
typedef unsigned short ino_t;
typedef unsigned int _dev_t;            /* device code */
typedef unsigned int dev_t;
typedef long _off_t;      

struct stat {
        _dev_t st_dev;
        _ino_t st_ino;
        unsigned short st_mode;
        short st_nlink;
        short st_uid;
        short st_gid;
        _dev_t st_rdev;
        _off_t st_size;
        time_t st_atime;
        time_t st_mtime;
        time_t st_ctime;
        };


static int stat(const char *file, struct stat *st)
{
	return 0;
}

#define _stat(a,b) stat(a,b)
