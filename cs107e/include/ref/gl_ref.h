#pragma once
#include "gl.h"
void ref_gl_init(unsigned int width, unsigned int height, gl_mode_t mode);
unsigned int ref_gl_get_width(void);
unsigned int ref_gl_get_height(void);
color_t ref_gl_color(unsigned char r, unsigned char g, unsigned char b);
void ref_gl_clear(color_t c);
void ref_gl_swap_buffer(void);
void ref_gl_draw_pixel(unsigned int x, unsigned int y, color_t c);
color_t ref_gl_read_pixel(unsigned int x, unsigned int y);
void ref_gl_draw_char(unsigned int x, unsigned int y, char ch, color_t c);
void ref_gl_draw_string(unsigned int x, unsigned int y, const char* str, color_t c);
unsigned int ref_gl_get_char_height(void);
unsigned int ref_gl_get_char_width(void);
void ref_gl_draw_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, color_t c);
void ref_gl_draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, color_t c);
void ref_gl_draw_triangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, color_t c);
