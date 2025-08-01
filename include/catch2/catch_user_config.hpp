
//              Copyright Catch2 Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

/**\file
 * **AUTOGENERATED FROM CMAKE CONFIGURATION**
 *
 * Contains materialized compile-time configuration provided to Catch2's
 * CMake configuration. All compile-time configuration options need to
 * be here, and also documented in `docs/configuration.md`.
 */

#ifndef CATCH_USER_CONFIG_HPP_INCLUDED
#define CATCH_USER_CONFIG_HPP_INCLUDED


// ------
// Overridable compilation flags,
// these can have 3 "states": Force Yes, Force No, Use Default.
// Setting both Force Yes and Force No is an error
// ------

/* #undef CATCH_CONFIG_ANDROID_LOGWRITE */
/* #undef CATCH_CONFIG_NO_ANDROID_LOGWRITE */

#if defined( CATCH_CONFIG_ANDROID_LOGWRITE ) && \
    defined( CATCH_CONFIG_NO_ANDROID_LOGWRITE )
#    error Cannot force ANDROID_LOGWRITE to both ON and OFF
#endif

/* #undef CATCH_CONFIG_COLOUR_WIN32 */
/* #undef CATCH_CONFIG_NO_COLOUR_WIN32 */

#if defined( CATCH_CONFIG_COLOUR_WIN32 ) && \
    defined( CATCH_CONFIG_NO_COLOUR_WIN32 )
#    error Cannot force COLOUR_WIN32 to be ON and OFF
#endif

/* #undef CATCH_CONFIG_COUNTER */
/* #undef CATCH_CONFIG_NO_COUNTER */

#if defined( CATCH_CONFIG_COUNTER ) && \
    defined( CATCH_CONFIG_NO_COUNTER )
#    error Cannot force COUNTER to both ON and OFF
#endif



/* #undef CATCH_CONFIG_CPP11_TO_STRING */
/* #undef CATCH_CONFIG_NO_CPP11_TO_STRING */

#if defined( CATCH_CONFIG_CPP11_TO_STRING ) && \
    defined( CATCH_CONFIG_NO_CPP11_TO_STRING )
#    error Cannot force CPP11_TO_STRING to both ON and OFF
#endif



/* #undef CATCH_CONFIG_CPP17_BYTE */
/* #undef CATCH_CONFIG_NO_CPP17_BYTE */

#if defined( CATCH_CONFIG_CPP17_BYTE ) && \
    defined( CATCH_CONFIG_NO_CPP17_BYTE )
#    error Cannot force CPP17_BYTE to both ON and OFF
#endif



/* #undef CATCH_CONFIG_CPP17_OPTIONAL */
/* #undef CATCH_CONFIG_NO_CPP17_OPTIONAL */

#if defined( CATCH_CONFIG_CPP17_OPTIONAL ) && \
    defined( CATCH_CONFIG_NO_CPP17_OPTIONAL )
#    error Cannot force CPP17_OPTIONAL to both ON and OFF
#endif



/* #undef CATCH_CONFIG_CPP17_STRING_VIEW */
/* #undef CATCH_CONFIG_NO_CPP17_STRING_VIEW */

#if defined( CATCH_CONFIG_CPP17_STRING_VIEW ) && \
    defined( CATCH_CONFIG_NO_CPP17_STRING_VIEW )
#    error Cannot force CPP17_STRING_VIEW to both ON and OFF
#endif



/* #undef CATCH_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS */
/* #undef CATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS */

#if defined( CATCH_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS ) && \
    defined( CATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS )
#    error Cannot force CPP17_UNCAUGHT_EXCEPTIONS to both ON and OFF
#endif



/* #undef CATCH_CONFIG_CPP17_VARIANT */
/* #undef CATCH_CONFIG_NO_CPP17_VARIANT */

#if defined( CATCH_CONFIG_CPP17_VARIANT ) && \
    defined( CATCH_CONFIG_NO_CPP17_VARIANT )
#    error Cannot force CPP17_VARIANT to both ON and OFF
#endif



/* #undef CATCH_CONFIG_GLOBAL_NEXTAFTER */
/* #undef CATCH_CONFIG_NO_GLOBAL_NEXTAFTER */

#if defined( CATCH_CONFIG_GLOBAL_NEXTAFTER ) && \
    defined( CATCH_CONFIG_NO_GLOBAL_NEXTAFTER )
#    error Cannot force GLOBAL_NEXTAFTER to both ON and OFF
#endif



/* #undef CATCH_CONFIG_POSIX_SIGNALS */
/* #undef CATCH_CONFIG_NO_POSIX_SIGNALS */

#if defined( CATCH_CONFIG_POSIX_SIGNALS ) && \
    defined( CATCH_CONFIG_NO_POSIX_SIGNALS )
#    error Cannot force POSIX_SIGNALS to both ON and OFF
#endif



/* #undef CATCH_CONFIG_GETENV */
/* #undef CATCH_CONFIG_NO_GETENV */

#if defined( CATCH_CONFIG_GETENV ) && \
    defined( CATCH_CONFIG_NO_GETENV )
#    error Cannot force GETENV to both ON and OFF
#endif



/* #undef CATCH_CONFIG_USE_ASYNC */
/* #undef CATCH_CONFIG_NO_USE_ASYNC */

#if defined( CATCH_CONFIG_USE_ASYNC ) && \
    defined( CATCH_CONFIG_NO_USE_ASYNC )
#    error Cannot force USE_ASYNC to both ON and OFF
#endif



/* #undef CATCH_CONFIG_WCHAR */
/* #undef CATCH_CONFIG_NO_WCHAR */

#if defined( CATCH_CONFIG_WCHAR ) && \
    defined( CATCH_CONFIG_NO_WCHAR )
#    error Cannot force WCHAR to both ON and OFF
#endif



/* #undef CATCH_CONFIG_WINDOWS_SEH */
/* #undef CATCH_CONFIG_NO_WINDOWS_SEH */

#if defined( CATCH_CONFIG_WINDOWS_SEH ) && \
    defined( CATCH_CONFIG_NO_WINDOWS_SEH )
#    error Cannot force WINDOWS_SEH to both ON and OFF
#endif


/* #undef CATCH_CONFIG_EXPERIMENTAL_STATIC_ANALYSIS_SUPPORT */
/* #undef CATCH_CONFIG_NO_EXPERIMENTAL_STATIC_ANALYSIS_SUPPORT */

#if defined( CATCH_CONFIG_EXPERIMENTAL_STATIC_ANALYSIS_SUPPORT ) && \
    defined( CATCH_CONFIG_NO_EXPERIMENTAL_STATIC_ANALYSIS_SUPPORT )
#    error Cannot force STATIC_ANALYSIS_SUPPORT to both ON and OFF
#endif


/* #undef CATCH_CONFIG_USE_BUILTIN_CONSTANT_P */
/* #undef CATCH_CONFIG_NO_USE_BUILTIN_CONSTANT_P */

#if defined( CATCH_CONFIG_USE_BUILTIN_CONSTANT_P ) && \
    defined( CATCH_CONFIG_NO_USE_BUILTIN_CONSTANT_P )
#    error Cannot force USE_BUILTIN_CONSTANT_P to both ON and OFF
#endif


/* #undef CATCH_CONFIG_DEPRECATION_ANNOTATIONS */
/* #undef CATCH_CONFIG_NO_DEPRECATION_ANNOTATIONS */

#if defined( CATCH_CONFIG_DEPRECATION_ANNOTATIONS ) && \
    defined( CATCH_CONFIG_NO_DEPRECATION_ANNOTATIONS )
#    error Cannot force DEPRECATION_ANNOTATIONS to both ON and OFF
#endif


/* #undef CATCH_CONFIG_EXPERIMENTAL_THREAD_SAFE_ASSERTIONS */
/* #undef CATCH_CONFIG_NO_EXPERIMENTAL_THREAD_SAFE_ASSERTIONS */

#if defined( CATCH_CONFIG_EXPERIMENTAL_THREAD_SAFE_ASSERTIONS ) && \
    defined( CATCH_CONFIG_NO_EXPERIMENTAL_THREAD_SAFE_ASSERTIONS )
#    error Cannot force EXPERIMENTAL_THREAD_SAFE_ASSERTIONS to both ON and OFF
#endif


// ------
// Simple toggle defines
// their value is never used and they cannot be overridden
// ------


/* #undef CATCH_CONFIG_BAZEL_SUPPORT */
/* #undef CATCH_CONFIG_DISABLE_EXCEPTIONS */
/* #undef CATCH_CONFIG_DISABLE_EXCEPTIONS_CUSTOM_HANDLER */
/* #undef CATCH_CONFIG_DISABLE */
/* #undef CATCH_CONFIG_DISABLE_STRINGIFICATION */
/* #undef CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS */
/* #undef CATCH_CONFIG_ENABLE_OPTIONAL_STRINGMAKER */
/* #undef CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER */
/* #undef CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER */
/* #undef CATCH_CONFIG_ENABLE_VARIANT_STRINGMAKER */
/* #undef CATCH_CONFIG_EXPERIMENTAL_REDIRECT */
/* #undef CATCH_CONFIG_FAST_COMPILE */
/* #undef CATCH_CONFIG_NOSTDOUT */
/* #undef CATCH_CONFIG_PREFIX_ALL */
/* #undef CATCH_CONFIG_PREFIX_MESSAGES */
/* #undef CATCH_CONFIG_WINDOWS_CRTDBG */

/* #undef CATCH_CONFIG_SHARED_LIBRARY */


// ------
// "Variable" defines, these have actual values
// ------

#define CATCH_CONFIG_DEFAULT_REPORTER "console"
#define CATCH_CONFIG_CONSOLE_WIDTH 80

// Unlike the macros above, CATCH_CONFIG_FALLBACK_STRINGIFIER does not
// have a good default value, so we cannot always define it, and cannot
// even expose it as a variable in CMake. The users will have to find
// out about it from docs and set it only if they use it.
/* #undef CATCH_CONFIG_FALLBACK_STRINGIFIER */

#endif // CATCH_USER_CONFIG_HPP_INCLUDED
