#ifndef HUD_DX_MAP_H
#define HUD_DX_MAP_H
#define hud_dx_data_length 19
#define hud_dx_tiles_width 2
#define hud_dx_tiles_height 18
#define hud_dx_tiles_offset 0
const unsigned char hud_dx_data[] = {
      0, 128,   0, 128,   0, 128,  96, 128, 112, 128, 120, 128, 120, 128, 112, 128,
     12,   0,  30,   0,  63,   0,  63,   0,  30,   0,  12,   0,   0,   0,   0,   0,
      0, 127,   0, 128,   0, 128,   0, 128,   0, 128,   0, 128,   0, 128,   0, 128,
      0, 255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0, 128,   0, 128,   0, 128,   0, 128,   0, 128,   0, 128,   0, 128,   0, 127,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255,
      0, 127,  99, 128,   7, 128,  15, 128,  15, 128,   7, 128,   0, 128,   0, 131,
      0, 255,   0,   0, 128,   0, 192,   0, 192,   0,   0,   0,   0, 192, 192,  96,
      3, 134,   7, 143,   7, 136,  99, 133, 115, 135, 121, 131, 120, 129, 112, 129,
    228, 112, 230,  80, 115, 136, 243, 120, 230,  48, 140,  96,   0, 192,   0,  64,
     96, 129,   0, 129,   4, 129,  12, 129,  12, 129,   4, 129,   0, 129,   0, 129,
      0,  64,   0,  64,   0,  64,   0,  64,   0,  64,   0,  64,   0,  64,   0,  64,
      0, 129,   0, 129,   0, 129,  96, 129, 112, 129, 120, 129, 120, 129, 112, 129,
     12,  64,  30,  64,  31,  64,  31,  64,  30,  64,  12,  64,   0,  64,   0,  64,
      0, 129,   0, 129,  96, 129, 112, 129, 120, 129, 120, 129, 112, 129,  96, 129,
    129, 129, 129, 129, 131, 130, 132, 135, 135, 132, 135, 132, 131, 130, 129, 129,
     64,  64, 192, 192,  96, 160, 112, 144, 112, 144, 144, 112,  32, 224, 192, 192,
     96, 128,   3, 128,   7, 128,  15, 128,  15, 128,   7, 128,   3, 128,   0, 128,
      0,   0,   0,   0, 128,   0, 192,   0, 192,   0, 128,   0,   0,   0,   0,   0
};

const unsigned char hud_dx_tiles[] = {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  10,  11,  12,  13,  10,  11,
     12,  13,  10,  11,  14,  13,  15,  16,   0,   1,   2,   3,   4,   5,  17,  18
};
#define hud_dx_palette_data_length 2
#define hud_dx_palette_offset 5
const unsigned char hud_dx_palettes[] = {
      5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,
      5,   5,   5,   5,   5,   5,   6,   6,   5,   5,   5,   5,   5,   5,   5,   5
};

const unsigned int hud_dx_palette_data[] = {
    28638, 30300,   0, 18668,
    28638, 8937, 27849,   0
};
#endif
