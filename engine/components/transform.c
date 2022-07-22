#include <constants.h>

#include <components/transform.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 transform_create(transform_t* transform)
  {
    transform->model[0][0] = 0.0f;
    transform->model[0][1] = 0.0f;
    transform->model[0][2] = 0.0f;
    transform->model[0][3] = 1.0f;
    transform->model[1][0] = 0.0f;
    transform->model[1][1] = 0.0f;
    transform->model[1][2] = 0.0f;
    transform->model[1][3] = 1.0f;
    transform->model[2][0] = 1.0f;
    transform->model[2][1] = 1.0f;
    transform->model[2][2] = 1.0f;
    transform->model[2][3] = 1.0f;
    transform->model[3][0] = 0.0f;
    transform->model[3][1] = 0.0f;
    transform->model[3][2] = 0.0f;
    transform->model[3][3] = 1.0f;
    transform->local_right[0] = right[0];
    transform->local_right[1] = right[1];
    transform->local_right[2] = right[2];
    transform->local_up[0] = up[0];
    transform->local_up[1] = up[1];
    transform->local_up[2] = up[2];
    transform->local_front[0] = front[0];
    transform->local_front[1] = front[1];
    transform->local_front[2] = front[2];
    transform->mask = 0;
    transform->transform_parent_id = -1;
    transform->transform_id = -1;
    transform->rigidbody_id = -1;
    return 0;
  }
  void transform_toggle(transform_t* transform, transform_ctrl_t ctrl)
  {
    transform->mask ^= ctrl;
  }
  void transform_set_position(transform_t* transform, r32 x, r32 y, r32 z)
  {
    transform->model[0][0] = x;
    transform->model[0][1] = y;
    transform->model[0][2] = z;
    transform->model[0][3] = 1.0f;
  }
  void transform_set_rotation(transform_t* transform, r32 x, r32 y, r32 z)
  {
    transform->model[1][0] = x;
    transform->model[1][1] = y;
    transform->model[1][2] = z;
    transform->model[1][3] = 1.0f;
  }
  void transform_set_scale(transform_t* transform, r32 x, r32 y, r32 z)
  {
    transform->model[2][0] = x;
    transform->model[2][1] = y;
    transform->model[2][2] = z;
    transform->model[2][3] = 1.0f;
  }
  void transform_add_position(transform_t* transform, r32 x, r32 y, r32 z)
  {
    transform->model[0][0] += x;
    transform->model[0][1] += y;
    transform->model[0][2] += z;
    transform->model[0][3] = 1.0f;
  }
  void transform_add_rotation(transform_t* transform, r32 x, r32 y, r32 z)
  {
    transform->model[1][0] += x;
    transform->model[1][1] += y;
    transform->model[1][2] += z;
    transform->model[1][3] = 1.0f;
  }
  void transform_add_scale(transform_t* transform, r32 x, r32 y, r32 z)
  {
    transform->model[2][0] += x;
    transform->model[2][1] += y;
    transform->model[2][2] += z;
    transform->model[2][3] = 1.0f;
  }

#ifdef __cplusplus
}
#endif