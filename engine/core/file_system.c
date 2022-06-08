#include <core/file_system.h>

#ifdef OS_WINDOWS
  #define _AMD64_
  #define WIN32_LEAN_AND_MEAN
  #include <handleapi.h>
  #include <fileapi.h>
#elif OS_UNIX

#endif

u8* file_load(i8 const* file_path)
{
  u8* source = NULL;
#ifdef OS_WINDOWS
  HANDLE file = CreateFileA(file_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (file != INVALID_HANDLE_VALUE)
  {
    DWORD file_size = GetFileSize(file, NULL);
    if (file_size > 0)
    {
      source = calloc(file_size + 1, sizeof(u8));
      if (source != NULL)
      {
        DWORD bytes_read;
        if (ReadFile(file, source, file_size, &bytes_read, NULL) == TRUE)
        {
          source[file_size] = 0u;
        }
      }
    }
    CloseHandle(file);
  }
#elif OS_UNIX
  FILE* file = NULL;
  if (fopen_s(&file, file_path, "rt") == 0)
  {
    fseek(file, 0, SEEK_END);
    u32 file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    source = (i8*)calloc(file_size, sizeof(i8));
    if (source != NULL)
    {
      fread(source, sizeof(i8), file_size, file);
    }
    fclose(file);
  }
  return source;
#endif
  return source;
}