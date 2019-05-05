#ifndef HUD_SGB_MAP_H
#define HUD_SGB_MAP_H
#define hud_sgb_data_length 19U
#define hud_sgb_tiles_width 2U
#define hud_sgb_tiles_height 18U
#define hud_sgb_tiles_offset 0U
const unsigned char hud_sgb_data[] = {
	128, 128, 128, 128, 128, 128, 128, 224, 128, 240, 128, 248, 128, 248, 128, 240,
      0,  12,   0,  30,   0,  63,   0,  63,   0,  30,   0,  12,   0,   0,   0,   0,
    127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    255, 255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255,
    127, 127, 128, 227, 128, 135, 128, 143, 128, 143, 128, 135, 128, 128, 131, 131,
    255, 255,   0,   0,   0, 128,   0, 192,   0, 192,   0,   0, 192, 192,  96,  32,
    134, 132, 143, 136, 136, 136, 133, 228, 135, 244, 131, 250, 129, 249, 129, 241,
    112,  20,  80,  22, 136, 139, 120,  11,  48,  22,  96, 108, 192, 192,  64,  64,
    129, 225, 129, 129, 129, 133, 129, 141, 129, 141, 129, 133, 129, 129, 129, 129,
     64,  64,  64,  64,  64,  64,  64,  64,  64,  64,  64,  64,  64,  64,  64,  64,
    129, 129, 129, 129, 129, 129, 129, 225, 129, 241, 129, 249, 129, 249, 129, 241,
     64,  76,  64,  94,  64,  95,  64,  95,  64,  94,  64,  76,  64,  64,  64,  64,
    129, 129, 129, 129, 129, 225, 129, 241, 129, 249, 129, 249, 129, 241, 129, 225,
    129, 129, 129, 129, 130, 131, 132, 132, 132, 135, 132, 135, 130, 131, 129, 129,
     64,  64, 192, 192,  32,  96,  16, 112,  16, 112,  16, 144,  32,  32, 192, 192,
    128, 224, 128, 131, 128, 135, 128, 143, 128, 143, 128, 135, 128, 131, 128, 128,
      0,   0,   0,   0,   0, 128,   0, 192,   0, 192,   0, 128,   0,   0,   0,   0
};
const unsigned char hud_sgb_tiles[] = {
	  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  10,  11,  12,  13,  10,  11,
     12,  13,  10,  11,  14,  13,  15,  16,   0,   1,   2,   3,   4,   5,  17,  18
};


#endif