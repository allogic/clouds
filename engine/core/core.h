#ifndef CORE_H
#define CORE_H

#define ARRAY_SIZE(ARRAY) ((sizeof(ARRAY) / sizeof(0[ARRAY])) / ((size_t)(!(sizeof(ARRAY) % sizeof(0[ARRAY])))))
#define VALUE_REMAP(V, L0, H0, L1, H1) ((float)(L1 + (V - L0) * (H1 - L1) / (H0 - L0)))

#endif