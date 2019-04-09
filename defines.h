#ifndef DEFINES_H
#define DEFINES_H

#define NONE	0U

#define UP		1U
#define RIGHT	2U
#define DOWN	3U
#define LEFT	4U

#define UPLEFT		5U
#define UPRIGHT		6U
#define DOWNLEFT	7U
#define DOWNRIGHT	8U

// Entity properties
#define FLIP_X 32U
#define FLIP_Y 64U

#define OBJ_PAL0 0U
#define OBJ_PAL1 16U

#define GET_RED(c) (c & 0x1FU)
#define GET_GREEN(c) ((c >> 5) & 0x1FU)
#define GET_BLUE(c) ((c >> 10) & 0x1FU)

#define GAME_BACKGROUNDS_BANK 7U
#define PAUSE_DATA_BANK 8U
#define WINSCREEN_BACKGROUNDS_BANK 9U
#define CLOUD_ANIMATIONS_BANK 8U
#define SELECTION_DATA_BANK  11U
#define SGB_BANK 10U

#define SONG_BANK_DREAM       13U
#define SONG_BANK_DREAM_SCORE 13U
#define SONG_BANK_MAINMENU    13U

#define SONG_BANK_CLOUDS    14U
#define SONG_BANK_PLAINS    14U
#define SONG_BANK_HIGHSCORE 14U
#define SONG_BANK_MINIGAME  14U

#define SONG_BANK_ENDING_PART1  15U
#define SONG_BANK_ENDING_PART2  15U
#define SONG_BANK_INTRO         15U
#define SONG_BANK_LEVEL_CLEAR   15U
#define SONG_BANK_POTATO_JINGLE 15U
#define SONG_BANK_SCORE_TALLY   15U
#define SONG_BANK_SPACE         15U
#define SONG_BANK_TANGRAM_SHINE 15U
#define SONG_BANK_TANGRAM_VOX   15U
#define SONG_BANK_TITLE         15U
#define SONG_BANK_UNLOCKED      15U
#define SONG_BANK_POTAKA        15U

#define SGB_P1_LOW 32U
#define SGB_P1_HIGH 16U
#define SGB_P1_NEUTRAL 48U

#endif
