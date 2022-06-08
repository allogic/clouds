#include <al/al.h>
#include <al/alut.h>

#include <assets.h>

extern sound_asset_t table_sound[256];
extern mesh_asset_t table_mesh[256];

u8 assets_create()
{
  u8 status = 0;
  status |= asset_load_sound();
  status |= asset_load_mesh();
  return status;
}
u8 asset_load_sound()
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
      alGenBuffers(1, &table_sound[i].id);
      if (table_sound[i].id != 0)
      {
        alBufferData(table_sound[i].id, format, data, size, freq);
        status = 0;
      }
      alutUnloadWAV(format, data, size, freq);
    }
  }
  return status;
}
u8 asset_load_mesh()
{
  u8 status = 0;
  return status;
}
sound_asset_t* asset_get_sound(u32 index)
{
  return &table_sound[index];
}
mesh_asset_t* asset_get_mesh(u32 index)
{
  return &table_mesh[index];
}
void assets_destroy()
{

}