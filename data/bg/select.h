#ifndef __select_tiles__
#define __select_tiles__

#define select_data_length 31
const unsigned char select_data[] = {
	255,   0, 255,   0, 255,   0, 255,   0, 255,   0, 255,   0, 255,   0, 255,   0, 
	243,  12, 227,  16, 227,  16, 224,  17, 224,  17, 224,  16, 226,  16, 226,  16, 
	158,  97,  28, 130,  24, 132,  16,   8,  17,   8,  17,   8,  16, 137,  16, 136, 
	120, 135, 112,   8,  48,   8,  28,   2,  28, 130,  28, 130,  28, 130,  28,   2, 
	 25, 230,  17,   8,  17,   8, 113,   8, 112,   8, 112,   8, 112,   8, 112,   8, 
	159,  96,  31, 128,  31, 128,  31, 128,  31, 128,  31, 128,  31,   0,  31,   0, 
	243,  12, 227,  16, 227,  16, 224,  17, 224,  17, 224,  16, 224,  18, 224,  18, 
	152, 103,  16, 136,  16, 136,  17,   8,  16,   9,  16,   8,  16, 136,  17, 136, 
	 25, 230,  17,   8,  17,   8, 241,   8,  48, 200,  48,   8,  48,   8, 240,   8, 
	153, 102,  17, 136,  17, 136,  17, 136,  17, 136,  17, 136,  17,   8,  17,   8, 
	159,  96,  31, 128,  31, 128,  31, 128,  31, 128,  31, 128,  31, 128,  31, 128, 
	227,  16, 227,  16, 227,  16, 227,  16, 227,  16, 255,   0, 255,   0, 255,   0, 
	 16, 136,  17, 136,  17, 136,  17, 136,  17, 136, 255,   0, 255,   0, 255,   0, 
	 28,   2,  28, 130,  24, 134,  16, 136,  16, 136, 255,   0, 255,   0, 255,   0, 
	112,   9, 112,   9,  17, 104,  17,   8,  17,   8, 255,   0, 255,   0, 255,   0, 
	 31,   0,  31,   0,  31, 128,  31, 128,  31, 128, 255,   0, 255,   0, 255,   0, 
	 17, 136,  17, 136,  16, 137,  16, 136,  16, 136, 255,   0, 255,   0, 255,   0, 
	240,   9, 240,   9,  17, 232,  17,   8,  17,   8, 255,   0, 255,   0, 255,   0, 
	 17,   8,  17,   8,  16, 137,  16, 136,  24, 132, 255,   0, 255,   0, 255,   0, 
	 31, 128,  31, 128,  31, 128,  31,   0,  63,   0, 255,   0, 255,   0, 255,   0, 
	255,   0, 255,   0,   0, 255, 255,   0,   0, 255,   0, 255,   0, 255, 255, 255, 
	255,   0, 231,   0, 195,   0, 129,   0, 129,   0, 195,   0, 231,   0, 255,   0, 
	255,  31, 224,  32, 192,  64, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
	255, 255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
	255, 248,  15,   4,   7,   2,   3,   1,   3,   1,   3,   1,   3,   1,   3,   1, 
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
	  3,   1,   3,   1,   3,   1,   3,   1,   3,   1,   3,   1,   3,   1,   3,   1, 
	128, 128, 128, 128, 128, 128, 128, 128, 192, 128, 224,  64, 255,  32, 255,  31, 
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255,   0, 255, 255, 
	  3,   1,   3,   1,   3,   1,   3,   1,   3,   1,   7,   2, 255,   4, 255, 248, 
};

#define select_tiles_width 20
#define select_tiles_height 18
#define select_offset 9
const unsigned char select_tiles[] = {
	  9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9, 
	  9,   9,   9,   9,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,   9,   9,   9,   9,   9, 
	  9,   9,   9,   9,   9,  20,  21,  22,  23,  24,  20,  25,  26,  27,  28,   9,   9,   9,   9,   9, 
	 29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29, 
	 30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30, 
	 30,  30,  30,  30,  30,  31,  32,  32,  32,  32,  32,  32,  32,  32,  33,  30,  30,  30,  30,  30, 
	 30,  30,  30,  30,  30,  34,  35,  35,  35,  35,  35,  35,  35,  35,  36,  30,  30,  30,  30,  30, 
	 30,  30,  30,  30,  30,  37,  38,  38,  38,  38,  38,  38,  38,  38,  39,  30,  30,  30,  30,  30, 
	 30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30, 
	 30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30, 
	 35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35, 
	 35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35, 
	 35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35, 
	 35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35, 
	 35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35, 
	 35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35, 
	 30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30, 
	 30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30, 
};

#endif