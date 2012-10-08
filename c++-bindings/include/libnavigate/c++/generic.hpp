#ifndef INCLUDE_navi_genericplusplus
#define INCLUDE_navi_genericplusplus

#if defined(navigate_EXPORTS)

#if defined(__GNUC__) && __GNUC__ >= 4
#define NAVI_EXTERN_CLASS(name)		class __attribute__((visibility("default"))) name
#elif defined(_MSC_VER)
#define NAVI_EXTERN_CLASS(name)		class __declspec(dllexport) name
#else
#define NAVI_EXTERN_CLASS(name)		extern class name
#endif // __GNUC__, _MSC_VER or other compiler

#else

#if defined(__GNUC__) && __GNUC__ >= 4
#define NAVI_EXTERN_CLASS(name)		class __attribute__((visibility("default"))) name
#elif defined(_MSC_VER)
#define NAVI_EXTERN_CLASS(name)		class __declspec(dllimport) name
#else
#define NAVI_EXTERN_CLASS(name)		extern class name
#endif // __GNUC__, _MSC_VER or other compiler

#endif // navigate_EXPORTS

#endif // INCLUDE_navi_genericplusplus

