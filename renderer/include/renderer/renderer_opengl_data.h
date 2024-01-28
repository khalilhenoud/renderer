/**
 * @file renderer_opengl_data.h
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2023-01-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef RENDERER_OPENGL_DATA_H
#define RENDERER_OPENGL_DATA_H

#include <stdint.h>
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

#endif