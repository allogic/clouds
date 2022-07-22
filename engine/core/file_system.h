#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <core/types.h>
#include <core/platform.h>

#define ENGINE_ROOT_DIR "C:\\Users\\Michael\\Downloads\\clouds\\"

#ifdef __cplusplus
extern "C" {
#endif

  u8* file_load(i8 const* file_path);

#ifdef __cplusplus
}
#endif

#endif