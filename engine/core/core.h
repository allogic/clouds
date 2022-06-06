#ifndef CORE_H
#define CORE_H

#if defined(__unix__)
  #define OS_UNIX
#elif defined(_WIN32) || defined(WIN32)
  #define OS_WINDOWS
#endif

#ifdef OS_WINDOWS
  #define _AMD64_
  #define WIN32_LEAN_AND_MEAN
  #include <handleapi.h>
  #include <fileapi.h>
#elif OS_UNIX

#endif

#endif