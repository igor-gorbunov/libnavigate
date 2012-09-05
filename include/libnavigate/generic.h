#ifndef INCLUDE_navi_generic_h
#define INCLUDE_navi_generic_h

#ifdef __cplusplus

#define NAVI_BEGIN_DECL		extern "C" {
#define NAVI_END_DECL		}

#else

#define NAVI_BEGIN_DECL		/* empty */
#define NAVI_END_DECL		/* empty */

#endif //  __cplusplus

#if __GNUC__ >= 4

#define NAVI_EXTERN(type)	extern __attribute__((visibility("default"))) type

#elif defined(_MSC_VER)

#define NAVI_EXTERN(type)	__declspec(dllexport) type

#else

#define NAVI_EXTERN(type)	extern type

#endif // __GNUC__ >= 4

#endif // INCLUDE_navi_generic_h

