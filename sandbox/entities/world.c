#include <stdlib.h>
#include <string.h>

#include <assets.h>
#include <vertex.h>
#include <gizmo.h>
#include <constants.h>

#include <entities/world.h>

static entity_t* chunks[CHUNK_NUM_ROOTS][CHUNK_NUM_LEAFS];

static void gizmo_chunk_proc(entity_t* entity)
{
  transform_t* transform = ECS_TRANSFORM(entity);

  gizmo_push_line(zero, right1000, red);
  gizmo_push_line(zero, up1000, green);
  gizmo_push_line(zero, front1000, blue);
  r32v3 s = { CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z };
  gizmo_push_box(zero, s, yellow);

  gizmo_push_box(TRANSFORM_POSITION(transform), TRANSFORM_SCALE(transform), white);
}

#ifdef __cplusplus
extern "C" {
#endif

  u8 world_create()
  {
    u8 status = 0;
    u32 i, j;
    r32 x, y, z;
    srand(1337);
    for (i = 0; i < CHUNK_NUM_ROOTS; i++)
    {
      x = (rand() % 20000) - (20000 / 2.0f);
      y = (rand() % 2000) - (2000 / 2.0f);
      z = (rand() % 20000) - (20000 / 2.0f);
      for (j = 0; j < CHUNK_NUM_LEAFS; j++)
      {
        chunks[i][j] = ecs_create_entity();

        // Setup transform
        transform_t* transform = ecs_attach_transform(chunks[i][j], NULL, &status);
        transform_set_position(transform, x, y, z);
        transform_set_rotation(transform, 0.0f, 0.0f, 0.0f);
        transform_set_scale(transform, 32.0f, 300.0f, 32.0f);

        // Setup mesh
        mesh_t* mesh = ecs_attach_mesh(chunks[i][j], &status);
        status |= mesh_from(mesh, assets_get_model(0));

        // Setup callbacks
        status |= ecs_register_dynamic(chunks[i][j], proc_idx_gizmo, proc_bit_gizmo, gizmo_chunk_proc);

        status |= ecs_update_queues(chunks[i][j]);
      }
    }
    return status;
  }
  void world_build()
  {

  }
  void world_destroy()
  {

  }

#ifdef __cplusplus
}
#endif