
#ifndef enu_graphics_framework_EXPORT_H
#define enu_graphics_framework_EXPORT_H

#ifdef enu_graphics_framework_BUILT_AS_STATIC
#  define enu_graphics_framework_EXPORT
#  define ENU_GRAPHICS_FRAMEWORK_NO_EXPORT
#else
#  ifndef enu_graphics_framework_EXPORT
#    ifdef enu_graphics_framework_EXPORTS
        /* We are building this library */
#      define enu_graphics_framework_EXPORT 
#    else
        /* We are using this library */
#      define enu_graphics_framework_EXPORT 
#    endif
#  endif

#  ifndef ENU_GRAPHICS_FRAMEWORK_NO_EXPORT
#    define ENU_GRAPHICS_FRAMEWORK_NO_EXPORT 
#  endif
#endif

#ifndef ENU_GRAPHICS_FRAMEWORK_DEPRECATED
#  define ENU_GRAPHICS_FRAMEWORK_DEPRECATED __declspec(deprecated)
#endif

#ifndef ENU_GRAPHICS_FRAMEWORK_DEPRECATED_EXPORT
#  define ENU_GRAPHICS_FRAMEWORK_DEPRECATED_EXPORT enu_graphics_framework_EXPORT ENU_GRAPHICS_FRAMEWORK_DEPRECATED
#endif

#ifndef ENU_GRAPHICS_FRAMEWORK_DEPRECATED_NO_EXPORT
#  define ENU_GRAPHICS_FRAMEWORK_DEPRECATED_NO_EXPORT ENU_GRAPHICS_FRAMEWORK_NO_EXPORT ENU_GRAPHICS_FRAMEWORK_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ENU_GRAPHICS_FRAMEWORK_NO_DEPRECATED
#    define ENU_GRAPHICS_FRAMEWORK_NO_DEPRECATED
#  endif
#endif

#endif
