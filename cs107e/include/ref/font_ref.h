#pragma once
#include "font.h"
const font_t *ref_font_get_font(void);
void ref_font_set_font(font_t *f);
size_t ref_font_get_glyph_height(void);
size_t ref_font_get_glyph_width(void);
size_t ref_font_get_glyph_size(void);
bool ref_font_get_glyph(char ch, unsigned char buf[], size_t buflen);
