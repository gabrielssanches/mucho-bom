#include <gb/gb.h>
#include <string.h>
#include "music.h"
#include "notes.h"
#include "freq.h"
#include "noisefreq.h"

#define MAX_REPEATS 4

UBYTE mus_paused;
UBYTE *mus_song;
UWORD mus_freq1, mus_freq2, mus_freq3;
UBYTE mus_freq4;
UWORD mus_target1, mus_target2, mus_target4;
UBYTE mus_slide1, mus_slide2, mus_slide4;
UBYTE *mus_data1, *mus_data2, *mus_data3, *mus_data4;
UBYTE *mus_loop1, *mus_loop2, *mus_loop3, *mus_loop4;
UBYTE mus_octave1, mus_octave2, mus_octave3, mus_octave4;
UBYTE mus_length1, mus_length2, mus_length3, mus_length4;
UBYTE mus_volume1, mus_volume2, mus_volume3, mus_volume4;
UBYTE mus_env1, mus_env2, mus_env4;
UBYTE mus_wait1, mus_wait2, mus_wait3, mus_wait4;
UBYTE *mus_rep1[MAX_REPEATS], *mus_rep2[MAX_REPEATS], *mus_rep3[MAX_REPEATS], *mus_rep4[MAX_REPEATS];
UBYTE mus_repeats1[MAX_REPEATS], mus_repeats2[MAX_REPEATS], mus_repeats3[MAX_REPEATS], mus_repeats4[MAX_REPEATS];
UBYTE mus_rep_depth1, mus_rep_depth2, mus_rep_depth3, mus_rep_depth4;

void mus_init(UBYTE *song_data) {
	UBYTE i;

	NR52_REG = 0x80U; // Enable sound
	NR51_REG = 0xFFU;
	NR50_REG = 0xFFU;

	// Kill sound
	NR10_REG = 0U;
	NR12_REG = 0U;
	NR22_REG = 0U;
	NR30_REG = 0U;
	NR32_REG = 0U;
	NR42_REG = 0U;

	// Setup timer
	TAC_REG = 0x04U; // TAC clock = 4096 Hz
	TMA_REG = 255U - 51U; // Default to ~150 bpm

	// Setup data
	mus_paused = 0U;

	mus_song = song_data;
	mus_data1 = mus_loop1 = mus_song + ((UWORD*)mus_song)[CHN1_OFFSET];
	mus_data2 = mus_loop2 = mus_song + ((UWORD*)mus_song)[CHN2_OFFSET];
	mus_data3 = mus_loop3 = mus_song + ((UWORD*)mus_song)[CHN3_OFFSET];
	mus_data4 = mus_loop4 = mus_song + ((UWORD*)mus_song)[CHN4_OFFSET];

	mus_wait1 = mus_wait2 = mus_wait3 = mus_wait4 = 0U;
	mus_octave1 = mus_octave2 = mus_octave3 = mus_octave4 = 4U;
	mus_length1 = mus_length2 = mus_length3 = mus_length4 = 48U;
	mus_volume1 = mus_volume2 = mus_volume4 = 15U;
	mus_volume3 = 1U;
	mus_env1 = mus_env2 = mus_env4 = 3U;
	mus_rep_depth1 = mus_rep_depth2 = mus_rep_depth3 = mus_rep_depth4 = 255U;
	mus_slide1 = mus_slide2 = 0U;
	for(i = 0U; i != MAX_REPEATS; ++i) {
		mus_repeats1[i] = 0U;
		mus_repeats2[i] = 0U;
		mus_repeats3[i] = 0U;
		mus_repeats4[i] = 0U;
	}
}

void mus_setPaused(UBYTE p) {
	mus_paused = p;

	if(mus_paused) {
		NR12_REG = NR22_REG = NR32_REG = NR42_REG = 0U;
		NR14_REG = NR24_REG = NR34_REG = NR44_REG = 0x80U;
	}
}

void mus_togglePaused() {
	mus_setPaused(mus_paused ^ 1U);
}

void mus_update() {
	if(mus_paused) return;

	mus_update1();
	mus_update2();
	mus_update3();
	mus_update4();
}

void mus_update1() {
	UBYTE note;

	if(mus_slide1) {
		if(mus_target1 > mus_freq1) {
			mus_freq1 += mus_slide1;
			if(mus_freq1 > mus_target1) {
				mus_freq1 = mus_target1;
			}
		}
		else if(mus_target1 < mus_freq1) {
			mus_freq1 -= mus_slide1;
			if(mus_freq1 < mus_target1) {
				mus_freq1 = mus_target1;
			}
		}
		NR13_REG = (UBYTE)mus_freq1;
		NR14_REG = mus_freq1 >> 8;
	}

	if(mus_wait1) {
		mus_wait1--;
		if(mus_wait1) return;
	}

	while(1U) {
		note = *mus_data1++;
		if(note & MUS_HAS_LENGTH || note <= T_WAIT) {
			if(note & MUS_HAS_LENGTH) {
				note ^= MUS_HAS_LENGTH;
				mus_wait1 = *mus_data1++;
			}
			else {
				mus_wait1 = mus_length1;
			}
			if(note == T_WAIT) {
				return;
			} else if(note == T_REST) {
				mus_freq1 = 0U;
				NR12_REG = 0U;
			} else {
				if(mus_slide1) {
					mus_target1 = freq[((mus_octave1-MUS_FIRST_OCTAVE) << 4) + note];
				} else {
					mus_freq1 = freq[((mus_octave1-MUS_FIRST_OCTAVE) << 4) + note];
				}
				NR12_REG = (mus_volume1 << 4) | mus_env1;
			}
			NR13_REG = (UBYTE)mus_freq1;
			NR14_REG = 0x80U | (mus_freq1 >> 8);
			return;
		}
		switch(note) {
			case T_LENGTH:
				mus_length1 = *mus_data1++;
				break;
			case T_OCTAVE:
				mus_octave1 = *mus_data1++;
				break;
			case T_OCT_UP:
				mus_octave1++;
				break;
			case T_OCT_DOWN:
				mus_octave1--;
				break;
			case T_VOL:
				mus_volume1 = *mus_data1++;
				NR12_REG = (mus_volume1 << 4) | mus_env1;
				break;
			case T_ENV:
				mus_env1 = *mus_data1++;
				NR12_REG = (mus_volume1 << 4) | mus_env1;
				break;
			case T_WAVE:
				mus_data1++;
				break;
			case T_TEMPO:
				TMA_REG = *mus_data1++;
				break;
			case T_WAVEDUTY:
				note = *mus_data1++;
				NR11_REG = (note << 5);
				break;
			case T_PAN:
				note = *mus_data1++;
				NR51_REG = (NR51_REG & 0xEEU) | note; // 11101110
				break;
			case T_LOOP:
				mus_loop1 = mus_data1;
				break;
			case T_REP_START:
				mus_rep_depth1++;
				mus_rep1[mus_rep_depth1] = mus_data1;
				break;
			case T_REP_END:
				note = *mus_data1++;
				if(!mus_repeats1[mus_rep_depth1]) {
					mus_repeats1[mus_rep_depth1] = note;
					mus_data1 = mus_rep1[mus_rep_depth1];
				}
				mus_repeats1[mus_rep_depth1]--;
				if(mus_repeats1[mus_rep_depth1]) {
					mus_data1 = mus_rep1[mus_rep_depth1];
				} else {
					mus_rep_depth1--;
				}
				break;
			case T_PORTAMENTO:
				mus_slide1 = *mus_data1++;
				break;
			case T_EOF:
				mus_data1 = mus_loop1;
				if(*mus_data1 == T_EOF) {
					mus_wait1 = 255U;
					return;
				}
				break;
		}
	}
}

void mus_update2() {
	UBYTE note;

	if(mus_slide2) {
		if(mus_target2 > mus_freq2) {
			mus_freq2 += mus_slide2;
			if(mus_freq2 > mus_target2) {
				mus_freq2 = mus_target2;
			}
		}
		else if(mus_target2 < mus_freq2) {
			mus_freq2 -= mus_slide2;
			if(mus_freq2 < mus_target2) {
				mus_freq2 = mus_target2;
			}
		}
		NR23_REG = (UBYTE)mus_freq2;
		NR24_REG = mus_freq2 >> 8;
	}

	if(mus_wait2) {
		mus_wait2--;
		if(mus_wait2) return;
	}

	while(1U) {
		note = *mus_data2++;
		if(note & MUS_HAS_LENGTH || note <= T_WAIT) {
			if(note & MUS_HAS_LENGTH) {
				note ^= MUS_HAS_LENGTH;
				mus_wait2 = *mus_data2++;
			}
			else {
				mus_wait2 = mus_length2;
			}
			if(note == T_WAIT) {
				return;
			} else if(note == T_REST) {
				mus_freq2 = 0U;
				NR22_REG = 0U;
			} else {
				if(mus_slide2) {
					mus_target2 = freq[((mus_octave2-MUS_FIRST_OCTAVE) << 4) + note];
				} else {
					mus_freq2 = freq[((mus_octave2-MUS_FIRST_OCTAVE) << 4) + note];
				}
				NR22_REG = (mus_volume2 << 4) | mus_env2;
			}
			NR23_REG = (UBYTE)mus_freq2;
			NR24_REG = 0x80U | (mus_freq2 >> 8);
			return;
		}
		switch(note) {
			case T_LENGTH:
				mus_length2 = *mus_data2++;
				break;
			case T_OCTAVE:
				mus_octave2 = *mus_data2++;
				break;
			case T_OCT_UP:
				mus_octave2++;
				break;
			case T_OCT_DOWN:
				mus_octave2--;
				break;
			case T_VOL:
				mus_volume2 = *mus_data2++;
				NR22_REG = (mus_volume2 << 4) | mus_env2;
				break;
			case T_ENV:
				mus_env2 = *mus_data2++;
				NR22_REG = (mus_volume2 << 4) | mus_env2;
				break;
			case T_WAVE:
				mus_data2++;
				break;
			case T_TEMPO:
				TMA_REG = *mus_data2++;
				break;
			case T_WAVEDUTY:
				note = *mus_data2++;
				NR21_REG = note << 5;
				break;
			case T_PAN:
				note = *mus_data2++;
				NR51_REG = (NR51_REG & 0xDDU) | (note << 1); // 11011101
				break;
			case T_LOOP:
				mus_loop2 = mus_data2;
				break;
			case T_REP_START:
				mus_rep_depth2++;
				mus_rep2[mus_rep_depth2] = mus_data2;
				break;
			case T_REP_END:
				note = *mus_data2++;
				if(!mus_repeats2[mus_rep_depth2]) {
					mus_repeats2[mus_rep_depth2] = note;
					mus_data2 = mus_rep2[mus_rep_depth2];
				}
				mus_repeats2[mus_rep_depth2]--;
				if(mus_repeats2[mus_rep_depth2]) {
					mus_data2 = mus_rep2[mus_rep_depth2];
				} else {
					mus_rep_depth2--;
				}
				break;
			case T_EOF:
				mus_data2 = mus_loop2;
				if(*mus_data2 == T_EOF) {
					mus_wait2 = 255U;
					return;
				}
				break;
		}
	}
}

void mus_update3() {
	UBYTE note;

	if(mus_wait3) {
		mus_wait3--;
		if(mus_wait3) return;
	}

	while(1U) {
		note = *mus_data3++;
		if(note & MUS_HAS_LENGTH || note <= T_WAIT) {
			if(note & MUS_HAS_LENGTH) {
				note ^= MUS_HAS_LENGTH;
				mus_wait3 = *mus_data3++;
			} else {
				mus_wait3 = mus_length3;
			}
			if(note == T_WAIT) {
				return;
			} else if(note == T_REST) {
				mus_freq3 = 0U;
				NR32_REG = 0U;
			} else {
				mus_freq3 = freq[((mus_octave3-MUS_FIRST_OCTAVE) << 4) + note];
				NR32_REG = mus_volume3 << 5;
			}
			NR30_REG = 0x0U;
			NR30_REG = 0x80U;
			NR33_REG = (UBYTE)mus_freq3;
			NR34_REG = 0x80U | (mus_freq3 >> 8);
			return;
		}
		switch(note) {
			case T_LENGTH:
				mus_length3 = *mus_data3++;
				break;
			case T_OCTAVE:
				mus_octave3 = *mus_data3++;
				break;
			case T_OCT_UP:
				mus_octave3++;
				break;
			case T_OCT_DOWN:
				mus_octave3--;
				break;
			case T_VOL:
				mus_volume3 = *mus_data3++;
				NR32_REG = mus_volume3 << 5;
				break;
			case T_ENV:
				mus_data3++;
				break;
			case T_WAVE:
				note = *mus_data3++;
				NR30_REG = 0x0U;
				memcpy(0xFF30, mus_song + WAVE_OFFSET + (note << 4), 16U);
				NR30_REG = 0x80U;
				break;
			case T_TEMPO:
				TMA_REG = *mus_data3++;
				break;
			case T_WAVEDUTY:
				mus_data3++;
				break;
			case T_PAN:
				note = *mus_data3++;
				NR51_REG = (NR51_REG & 0xBBU) | (note << 2); // 10111011
				break;
			case T_LOOP:
				mus_loop3 = mus_data3;
				break;
			case T_REP_START:
				mus_rep_depth3++;
				mus_rep3[mus_rep_depth3] = mus_data3;
				break;
			case T_REP_END:
				note = *mus_data3++;
				if(!mus_repeats3[mus_rep_depth3]) {
					mus_repeats3[mus_rep_depth3] = note;
					mus_data3 = mus_rep3[mus_rep_depth3];
				}
				mus_repeats3[mus_rep_depth3]--;
				if(mus_repeats3[mus_rep_depth3]) {
					mus_data3 = mus_rep3[mus_rep_depth3];
				} else {
					mus_rep_depth3--;
				}
				break;
			case T_EOF:
				mus_data3 = mus_loop3;
				if(*mus_data3 == T_EOF) {
					mus_wait3 = 255U;
					return;
				}
				break;
		}
	}
}

void mus_update4() {
	UBYTE note;

	if(mus_slide4) {
		if(mus_target4 > mus_freq4) {
			mus_freq4 += mus_slide4;
			if(mus_freq4 > mus_target4) {
				mus_freq4 = mus_target4;
			}
		}
		else if(mus_target4 < mus_freq4) {
			mus_freq4 -= mus_slide4;
			if(mus_freq4 < mus_target4) {
				mus_freq4 = mus_target4;
			}
		}
		NR43_REG = mus_freq4;
	}

	if(mus_wait4) {
		mus_wait4--;
		if(mus_wait4) return;
	}

	while(1U) {
		note = *mus_data4++;
		if(note & MUS_HAS_LENGTH || note <= T_WAIT) {
			if(note & MUS_HAS_LENGTH) {
				note ^= MUS_HAS_LENGTH;
				mus_wait4 = *mus_data4++;
			} else {
				mus_wait4 = mus_length4;
			}
			if(note == T_WAIT) {
				return;
			} else if(note == T_REST) {
				mus_freq4 = 0U;
				NR42_REG = 0U;
			} else {
				if(mus_slide4) {
					mus_target4 = noise_freq[((mus_octave4-MUS_NOISE_FIRST_OCTAVE) << 4) + note];
				} else {
					mus_freq4 = noise_freq[((mus_octave4-MUS_NOISE_FIRST_OCTAVE) << 4) + note];
				}
				NR42_REG = (mus_volume4 << 4) | mus_env4;
			}
			NR43_REG = mus_freq4;
			NR44_REG = 0x80U;
			return;
		}
		switch(note) {
			case T_LENGTH:
				mus_length4 = *mus_data4++;
				break;
			case T_OCTAVE:
				mus_octave4 = *mus_data4++;
				break;
			case T_OCT_UP:
				mus_octave4++;
				break;
			case T_OCT_DOWN:
				mus_octave4--;
				break;
			case T_VOL:
				mus_volume4 = *mus_data4++;
				NR42_REG = (mus_volume4 << 4) | mus_env4;
				break;
			case T_ENV:
				mus_env4 = *mus_data4++;
				NR42_REG = (mus_volume4 << 4) | mus_env4;
				break;
			case T_TEMPO:
				TMA_REG = *mus_data4++;
				break;
			case T_PAN:
				note = *mus_data4++;
				NR51_REG = (NR51_REG & 0x77U) | (note << 3); // 01110111
				break;
			case T_LOOP:
				mus_loop4 = mus_data4;
				break;
			case T_REP_START:
				mus_rep_depth4++;
				mus_rep4[mus_rep_depth4] = mus_data4;
				break;
			case T_REP_END:
				note = *mus_data4++;
				if(!mus_repeats4[mus_rep_depth4]) {
					mus_repeats4[mus_rep_depth4] = note;
					mus_data4 = mus_rep4[mus_rep_depth4];
				}
				mus_repeats4[mus_rep_depth4]--;
				if(mus_repeats4[mus_rep_depth4]) {
					mus_data4 = mus_rep4[mus_rep_depth4];
				} else {
					mus_rep_depth4--;
				}
				break;
			case T_EOF:
				mus_data4 = mus_loop4;
				if(*mus_data4 == T_EOF) {
					mus_wait4 = 255U;
					return;
				}
				break;
		}
	}
}