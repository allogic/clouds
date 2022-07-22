#ifndef SANDBOX_H
#define SANDBOX_H

#include <core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 sandbox_create();
  void sandbox_destroy();

#ifdef __cplusplus
}
#endif

#endif