#ifndef PHYSIC_H
#define PHYSIC_H

#include <core/types.h>

#include <ecs.h>

u8 physic_create();
void physic_simulate();
void physic_destroy();

#endif