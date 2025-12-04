/**
 * @file opengl_platform.h
 * @author khalilhenoud@gmail.com
 * @brief defines the api that is to be implemented per system (do not include)
 * @version 0.1
 * @date 2023-01-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef OPENGL_PLATFORM_H
#define OPENGL_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <renderer/internal/module.h>


RENDERER_API
void
opengl_initialize(const opengl_parameters_t *params);

RENDERER_API
void
opengl_swapbuffer();

RENDERER_API
void
opengl_cleanup();

#ifdef __cplusplus
}
#endif

#endif