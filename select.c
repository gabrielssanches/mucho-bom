#include <gb/gb.h>
#include "defines.h"
#include "select.h"
#include "fade.h"
#include "gamestate.h"
#include "cos.h"
#include "ram.h"
#include "sound.h"

#include "data/sprite/characters.h"
#include "data/sprite/arrow.h"

#include "data/bg/circles.h"
#include "data/bg/select.h"

#include "data/bg/selection1.h"
#include "data/bg/selection2.h"
#include "data/bg/selection3.h"
#include "data/bg/selection4.h"
#include "data/bg/selection_highscore.h"
#include "data/bg/selection_jukebox.h"
#include "data/bg/selection_locked.h"
#include "data/bg/selection_options.h"

UBYTE select_circle_index;
UBYTE select_ticks;
UBYTE select_scroll_dir;

extern UBYTE mainmenu_song_data;

void initSelect() {
	disable_interrupts();
	DISPLAY_OFF;

	move_bkg(0U, 0U);
	set_sprite_data(0U, 37U, characters_data);
	set_sprite_data(37U, arrow_data_length, arrow_data);

	set_bkg_data(0U, circles_data_length, circles_data);
	set_bkg_data_rle(select_offset, select_data_length, select_data);
	set_bkg_tiles_rle(0U, 0U, select_tiles_width, select_tiles_height, select_tiles);

	select_circle_index = 0U;
	ticks = 0U;

	OBP0_REG = 0xD0U; // 11010000
	OBP1_REG = 0xB4U; // 11100100
	BGP_REG = 0xB4U; // 11100100

	clearSprites();
	_selectUpdateScreen();

	setMusicBank(4U);
	playMusic(&mainmenu_song_data);

	HIDE_WIN;
	SPRITES_8x8;
	SHOW_SPRITES;
	SHOW_BKG;

	DISPLAY_ON;
	enable_interrupts();
}

UBYTE *selectGetBannerData() {
	if(selection <= 4U && selection > levels_completed+1U) {
		set_bkg_data(selection_locked_offset, selection_locked_data_length, selection_locked_data);
		return selection_locked_tiles;
	} else if(selection == 1U) {
		set_bkg_data(selection1_offset, selection1_data_length, selection1_data);
		return selection1_tiles;
	} else if(selection == 2U) {
		set_bkg_data(selection2_offset, selection2_data_length, selection2_data);
		return selection2_tiles;
	} else if(selection == 3U) {
		set_bkg_data(selection3_offset, selection3_data_length, selection3_data);
		return selection3_tiles;
	} else if(selection == 4U) {
		set_bkg_data(selection4_offset, selection4_data_length, selection4_data);
		return selection4_tiles;
	} else if(selection == 5U) {
		set_bkg_data(selection_jukebox_offset, selection_jukebox_data_length, selection_jukebox_data);
		return selection_jukebox_tiles;
	} else if(selection == 6U) {
		set_bkg_data(selection_highscore_offset, selection_highscore_data_length, selection_highscore_data);
		return selection_highscore_tiles;
	} else if(selection == 7U) {
		set_bkg_data(selection_options_offset, selection_options_data_length, selection_options_data);
		return selection_options_tiles;
	}

	return 0U;
}

void _selectUpdateScreen() {
	UBYTE *data = selectGetBannerData();
	set_bkg_tiles(0U, 10U, 20U, 6U, data);
}

void selectUpdateSprites() {
	UBYTE offset;

	offset = cos32_64[(ticks & 63U)] >> 3;

	setSprite(24U-offset, 61U, 37U, OBJ_PAL0);
	setSprite(32U-offset, 61U, 39U, OBJ_PAL0);
	setSprite(24U-offset, 69U, 38U, OBJ_PAL0);
	setSprite(32U-offset, 69U, 40U, OBJ_PAL0);

	setSprite(136U+offset, 61U, 39U, OBJ_PAL0 | FLIP_X);
	setSprite(144U+offset, 61U, 37U, OBJ_PAL0 | FLIP_X);
	setSprite(136U+offset, 69U, 40U, OBJ_PAL0 | FLIP_X);
	setSprite(144U+offset, 69U, 38U, OBJ_PAL0 | FLIP_X);
}

void selectScrollCircles() {
	select_circle_index = (select_circle_index+1U) & 7U;
	set_bkg_data(30U, 1U, &circles_data[(select_circle_index << 4)]);
}

void selectFadeOut() {
	UBYTE i;
	UBYTE tiles[6U];

	for(i = 0U; i != 6U; ++i) tiles[i] = 8U;

	for(i = 0U; i != 20U; ++i) {
		disable_interrupts();
		set_bkg_tiles(i, 10U, 1U, 6U, tiles);
		enable_interrupts();
		if(i & 1U) {
			ticks++;
			if((ticks & 3U) == 3U) {
				selectScrollCircles();
			}
			wait_vbl_done();
		}
	}
}

void selectFadeIn() {
	UBYTE i, j;
	UBYTE *data;
	UBYTE *ptr;
	UBYTE tiles[6];

	disable_interrupts();
	data = selectGetBannerData();
	enable_interrupts();

	for(i = 0U; i != 20U; ++i) {
		ptr = data + i;
		for(j = 0U; j != 6U; ++j) {
			tiles[j] = *ptr;
			ptr += 20U;
		}
		++ptr;

		disable_interrupts();
		set_bkg_tiles(i, 10U, 1U, 6U, tiles);
		enable_interrupts();
		if(i & 1U) {
			ticks++;
			if((ticks & 3U) == 3U) {
				selectScrollCircles();
			}
			wait_vbl_done();
		}
	}
}

void enterSelect() {
	UBYTE i, offset, name_index;
	initSelect();

	fadeFromWhite(6U);

	while(gamestate == GAMESTATE_SELECT) {
		updateJoystate();

		ticks++;
		if((ticks & 3U) == 3U) {
			selectScrollCircles();
		}

		if(ISDOWN(J_RIGHT)) {
			selection++;
			if(selection == 5U && levels_completed < 2U) selection++;
			if(selection > 7U) selection = 1U;
			clearRemainingSprites();
			selectFadeOut();
			selectFadeIn();
			selectUpdateSprites();
		}
		if(ISDOWN(J_LEFT)) {
			selection--;
			if(selection == 5U && levels_completed < 2U) selection--;
			if(selection == 0U) selection = 7U;
			clearRemainingSprites();
			selectFadeOut();
			selectFadeIn();
			selectUpdateSprites();
		}
		if(CLICKED(J_START) || CLICKED(J_A)) {
			if(selection == 5U) {
				gamestate = GAMESTATE_JUKEBOX;
			} else if(selection == 6U) {
				gamestate = GAMESTATE_HIGHSCORE;
			} else if(selection == 7U) {
				gamestate = GAMESTATE_OPTIONS;
			} else if(selection <= levels_completed+1U) {
				level = selection;
				gamestate = GAMESTATE_INGAME;
			}
		}
		if(CLICKED(J_B)) {
			gamestate = GAMESTATE_TITLE;
		}

		// Draw level name
		if(selection <= 4U && selection > levels_completed+1U) {
			name_index = 0U;
		} else {
			name_index = selection;
		}

		offset = 64U;
		if(level_names[name_index][5] == 10U) {
			offset += 4U;
		}
		for(i = 0U; i != 6; ++i) {
			setSprite(offset+(i << 3), 61U+cos4_16[(i+(ticks >> 1)) & 15U], level_names[name_index][i], OBJ_PAL0);
		}

		selectUpdateSprites();
		clearRemainingSprites();
		wait_vbl_done();
	}

	clearRemainingSprites(); // Remove all sprites
	fadeToWhite(6U);

	stopMusic();
}
