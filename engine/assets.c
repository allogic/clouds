#include <al/al.h>
#include <al/alut.h>

#include <ufbx/ufbx.h>

#include <assets.h>

extern sound_asset_t table_sound[256];
extern model_asset_t table_model[256];
extern texture_asset_t table_texture[256];

#ifdef __cplusplus
extern "C" {
#endif

  u8 assets_create()
  {
    u8 status = 0;
    status |= assets_load_sound();
    status |= assets_load_model();
    status |= assets_load_texture();
    return status;
  }
  u8 assets_load_sound()
  {
    u8 status = 1;
    i32 format, size, freq;
    i8 loop;
    void* data = NULL;
    for (u32 i = 0; i < SOUND_TABLE_SIZE; i++)
    {
      alutLoadWAVFile(table_sound[i].file, &format, &data, &size, &freq, &loop);
      if (data != NULL)
      {
        alGenBuffers(1, &table_sound[i].sound.id);
        if (table_sound[i].sound.id != 0)
        {
          alBufferData(table_sound[i].sound.id, format, data, size, freq);
          status = 0;
        }
        alutUnloadWAV(format, data, size, freq);
      }
    }
    return status;
  }
  u8 assets_load_model()
  {
    u8 status = 0;
    ufbx_load_opts opts = { 0 };
    ufbx_error error;
    for (u32 model_idx = 0; model_idx < MODEL_TABLE_SIZE; model_idx++)
    {
      ufbx_scene* scene = ufbx_load_file(table_model[model_idx].file, &opts, &error);
      if (scene != NULL)
      {
        for (u32 node_idx = 0; node_idx < scene->nodes.count; node_idx++)
        {
          ufbx_node* node = ufbx_find_node(scene, scene->nodes.data[node_idx]->name.data);
          if (node != NULL)
          {
            ufbx_mesh* mesh = node->mesh;
            if (mesh != NULL)
            {
              for (u32 face_idx = 0; face_idx < mesh->num_faces; face_idx++)
              {
                ufbx_face face = mesh->faces[face_idx];
                for (u32 vertex_idx = 0; vertex_idx < face.num_indices; vertex_idx++)
                {
                  u32 index = face.index_begin + vertex_idx;

                  ufbx_vec3 position = ufbx_get_vertex_vec3(&mesh->vertex_position, index);
                  //ufbx_vec3 normal = ufbx_get_vertex_vec3(&mesh->vertex_normal, index);
                  //ufbx_vec4 color = ufbx_get_vertex_vec4(&mesh->vertex_color, index);
                  //ufbx_vec2 uv = ufbx_get_vertex_vec2(&mesh->vertex_uv, index);
                }
              }
            }
          }
        }
        ufbx_free_scene(scene);
      }
    }
    // There's also helper functions for evaluating animations:
    //for (double time = 0.0; time <= 1.0; time += 1.0 / 60.0) {
    //  ufbx_transform transform = ufbx_evaluate_transform(&scene->anim, cube, time);
    //  ufbx_matrix matrix = ufbx_transform_to_matrix(&transform);
    //  push_pose(&matrix);
    //}
    return status;
  }
  u8 assets_load_texture()
  {
    u8 status = 0;
    return status;
  }
  sound_asset_t* assets_get_sound(u32 index)
  {
    return &table_sound[index];
  }
  model_asset_t* assets_get_model(u32 index)
  {
    return &table_model[index];
  }
  texture_asset_t* assets_get_texture(u32 index)
  {
    return &table_texture[index];
  }
  void assets_destroy()
  {

  }

#ifdef __cplusplus
}
#endif