/*
 The following is only used when building DLLs under _WIN32
*/

#if defined(_WIN32) && defined(FL_SHARED) && (defined(_MSC_VER) || defined(__MWERKS__) || defined(__BORLANDC__) || __GNUC__ >= 3)
# ifdef FL_LIBRARY
#  define FL_API __declspec(dllexport)
# else
#  define FL_API __declspec(dllimport)
# endif

#else

# define FL_API

#endif
