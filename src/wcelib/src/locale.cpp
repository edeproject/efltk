#include <locale.h>
#include <string.h>

static lconv CONV;

struct lconv *localeconv( void )
{

	memset(&CONV,0,sizeof(lconv));
	
	return &CONV;
}

char * setlocale(int, const char *)
{

	return 0;
}
