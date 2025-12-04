/**
 * @file renderer_opengl.h
 * @author khalilhenoud@gmail.com
 * @brief
 * @version 0.1
 * @date 2023-01-14
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef RENDERER_OPENGL_H
#define RENDERER_OPENGL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <renderer/internal/module.h>
#include <renderer/pipeline.h>
#include <renderer/platform/opengl_platform.h>
#include <math/c/vector3f.h>


typedef
struct unit_quad_t {
  float data[6];
} unit_quad_t;

typedef
struct color_t {
  float data[4];
} color_t;

typedef
enum renderer_image_format_t {
  RENDERER_OPENGL_RGBA,
  RENDERER_OPENGL_BGRA,
  RENDERER_OPENGL_RGB,
  RENDERER_OPENGL_BGR,
  RENDERER_OPENGL_LA,           /// Luminance/Alpha.
  RENDERER_OPENGL_L,
  RENDERER_OPENGL_A,
  RENDERER_OPENGL_IMAGE_FORMAT_COUNT
} renderer_image_format_t;

typedef
struct mesh_render_data_t {
  float* vertices;    // 3 floats per vertex.
  float* normals;     // 3 floats per vertex.
  float* uv_coords;   // 3 floats per vertex.
  uint32_t vertex_count;    // applies to the previous 3 arrays.
  uint32_t* indices;
  uint32_t indices_count;
  color_t ambient;
  color_t diffuse;
  color_t specular;
} mesh_render_data_t;

typedef
enum renderer_light_type_t {
  RENDERER_LIGHT_TYPE_POINT,
  RENDERER_LIGHT_TYPE_SPOT,
  RENDERER_LIGHT_TYPE_DIRECTIONAL,
  RENDERER_LIGHT_TYPE_COUNT
} renderer_light_type_t;

typedef
struct renderer_light_t {
  vector3f position;
  vector3f direction;
  vector3f up;
  float inner_cone;
  float outer_cone;
  float attenuation_constant;
  float attenuation_linear;
  float attenuation_quadratic;
  color_t diffuse;
  color_t specular;
  color_t ambient;
  renderer_light_type_t type;
} renderer_light_t;

RENDERER_API
void
renderer_initialize();

RENDERER_API
void
renderer_cleanup();

RENDERER_API
void
disable_depth_test();

RENDERER_API
void
enable_depth_test();

RENDERER_API
void
clear_color_and_depth_buffers();

RENDERER_API
void
flush_operations();

RENDERER_API
void
update_viewport(const pipeline_t* pipeline);

RENDERER_API
void
update_projection(const pipeline_t* pipeline);

RENDERER_API
void
disable_light(uint32_t index);

RENDERER_API
void
enable_light(uint32_t index);

RENDERER_API
void
set_light_properties(
  uint32_t index,
  renderer_light_t* light,
  pipeline_t* pipeline);

RENDERER_API
void
draw_grid(
  pipeline_t* pipeline,
  float width,
  int32_t lines_per_axis);

RENDERER_API
void
draw_points(
  const float* vertices,
  uint32_t vertices_count,
  color_t color,
  float size,
  pipeline_t* pipeline);

RENDERER_API
void
draw_lines(
  const float* vertices,
  uint32_t vertices_count,
  color_t color,
  float width,
  pipeline_t* pipeline);

RENDERER_API
void
draw_unit_quads(
  const unit_quad_t* uvs,
  uint32_t uvs_count,
  int32_t texture_id,
  color_t tint,
  pipeline_t* pipeline);

RENDERER_API
void
draw_meshes_wireframe(
  const mesh_render_data_t* mesh,
  uint32_t mesh_count,
  color_t color,
  float width,
  pipeline_t* pipeline);

RENDERER_API
void
draw_meshes(
  const mesh_render_data_t* mesh,
  const uint32_t* texture_data,
  uint32_t mesh_count,
  pipeline_t* pipeline);

/// @brief bookkeeping is left to the user code.
RENDERER_API
uint32_t
upload_to_gpu(
  const char* path,
  const uint8_t* buffer,
  uint32_t width,
  uint32_t height,
  renderer_image_format_t format);

RENDERER_API
uint32_t
evict_from_gpu(uint32_t texture_id);

#ifdef __cplusplus
}
#endif

#endif