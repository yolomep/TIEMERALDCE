#ifndef sprite_include_file
#define sprite_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define sprite_width 8
#define sprite_height 8
#define sprite_size 66
#define sprite ((gfx_sprite_t*)sprite_data)
extern unsigned char sprite_data[66];

#ifdef __cplusplus
}
#endif

#endif
