/*
 The following is only used when building DLLs under _WIN32
*/

#if defined(_WIN32) && defined(FL_SHARED)
# ifdef FL_LIBRARY
#  define FL_API __declspec(dllexport)
# else
#  define FL_API __declspec(dllimport)
# endif
# ifdef FL_IMAGES_LIBRARY
#  define FL_IMAGES_API	__declspec(dllexport)
# else
#  define FL_IMAGES_API	__declspec(dllimport)
# endif
# ifdef FL_GL_LIBRARY
#  define FL_GL_API __declspec(dllexport)
# else
#  define FL_GL_API __declspec(dllimport)
# endif
#else
# define FL_API
# define FL_IMAGES_API
# define FL_GL_API
#endif
