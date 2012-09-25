#ifndef INCLUDE_navi_generic_h
#define INCLUDE_navi_generic_h

#ifdef __cplusplus

#define NAVI_BEGIN_DECL		extern "C" {
#define NAVI_END_DECL		}

#else

#define NAVI_BEGIN_DECL		/* empty */
#define NAVI_END_DECL		/* empty */

#endif //  __cplusplus

#if defined(navigate_EXPORTS)

#if defined(__GNUC__) && __GNUC__ >= 4

#define NAVI_EXTERN(type)			extern __attribute__((visibility("default"))) type
#define NAVI_STRUCT(type, name)		type name

#elif defined(_MSC_VER)

#define NAVI_EXTERN(type)			__declspec(dllexport) type
#define NAVI_STRUCT(type, name)		type name

#else

#define NAVI_EXTERN(type)			extern type
#define NAVI_STRUCT(type, name)		type name

#endif // __GNUC__, _MSC_VER or other compiler

#else

#if defined(__GNUC__) && __GNUC__ >= 4

#define NAVI_EXTERN(type)			extern __attribute__((visibility("default"))) type
#define NAVI_STRUCT(type, name)		type name

#elif defined(_MSC_VER)

#define NAVI_EXTERN(type)			__declspec(dllimport) type
#define NAVI_STRUCT(type, name)		type name

#else

#define NAVI_EXTERN(type)			extern type
#define NAVI_STRUCT(type, name)		type name

#endif // __GNUC__, _MSC_VER or other compiler

#endif // navigate_EXPORTS

#endif // INCLUDE_navi_generic_h
