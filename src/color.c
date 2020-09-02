/* 
 *  This file is part of Aptdec.
 *  Copyright (c) 2004-2009 Thierry Leconte (F4DWV), Xerbo (xerbo@protonmail.com) 2019-2020
 *
 *  Aptdec is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "color.h"

rgb_t applyPalette(char *palette, int val){
	return (rgb_t){
		palette[(int)CLIP(val, 0, 255)*3 + 0],
		palette[(int)CLIP(val, 0, 255)*3 + 1],
		palette[(int)CLIP(val, 0, 255)*3 + 2]
	};
}

rgb_t RGBcomposite(rgb_t top, float top_a, rgb_t bottom, float bottom_a){
	return (rgb_t){
		MCOMPOSITE(top.r, top_a, bottom.r, bottom_a),
		MCOMPOSITE(top.g, top_a, bottom.g, bottom_a),
		MCOMPOSITE(top.b, top_a, bottom.b, bottom_a)
	};
}

// The "I totally didn't just steal this from WXtoImg" palette
char TempPalette[256*3] = {
	"\x45\x0\x8f\x46\x0\x91\x47\x0\x92\x48\x0\x94\x49\x0\x96\x4a\x0\x98\x4b\x0\x9b\x4d\x0\x9d"
	"\x4e\x0\xa0\x50\x0\xa2\x51\x0\xa5\x52\x0\xa7\x54\x0\xaa\x56\x0\xae\x57\x0\xb1"
	"\x58\x0\xb4\x5a\x0\xb7\x5c\x0\xba\x5e\x0\xbd\x5f\x0\xc0\x61\x0\xc4\x64\x0\xc8"
	"\x66\x0\xcb\x68\x0\xce\x69\x0\xd1\x68\x0\xd4\x65\x0\xd7\x63\x0\xda\x61\x0\xdd"
	"\x5d\x0\xe1\x5b\x0\xe4\x59\x0\xe6\x56\x0\xe9\x53\x0\xeb\x50\x0\xee\x4d\x0\xf0"
	"\x49\x0\xf3\x47\x0\xfc\x43\x0\xfa\x31\x0\xbf\x20\x0\x89\x20\x0\x92\x1e\x0\x95"
	"\x1b\x0\x97\x19\x0\x9a\x17\x0\x9c\x15\x0\x9e\x12\x0\xa0\xf\x0\xa3\xf\x2\xa5"
	"\xe\x6\xa8\xe\xa\xab\xe\xd\xad\xe\x11\xb1\xd\x15\xb4\xd\x18\xb7\xd\x1c\xba"
	"\xb\x21\xbd\xa\x25\xc0\xa\x29\xc3\x9\x2d\xc6\x8\x33\xca\x7\x36\xcd\x7\x3b\xd0"
	"\x7\x41\xd3\x5\x45\xd6\x4\x4b\xd9\x4\x50\xdc\x3\x55\xde\x2\x5d\xe2\x1\x61\xe5"
	"\x0\x66\xe7\x0\x6c\xea\x0\x72\xec\x0\x78\xee\x0\x7d\xf0\x0\x82\xf3\x0\x8d\xfc"
	"\x0\x90\xfa\x0\x71\xbf\x0\x54\x89\x0\x5c\x91\x0\x61\x94\x0\x64\x96\x0\x68\x97"
	"\x0\x6d\x99\x0\x71\x9b\x0\x75\x9d\x0\x79\x9f\x0\x7e\xa0\x0\x82\xa2\x0\x87\xa4"
	"\x0\x8c\xa6\x0\x92\xaa\x0\x96\xac\x0\x9c\xae\x0\xa2\xb1\x0\xa6\xb3\x0\xaa\xb5"
	"\x0\xad\xb7\x0\xb1\xba\x0\xb6\xbe\x0\xba\xc0\x0\xbe\xc2\x0\xc2\xc5\x0\xc6\xc6"
	"\x0\xca\xc9\x0\xcc\xca\x0\xcf\xcb\x0\xd2\xcc\x0\xd4\xcc\x0\xd6\xcc\x0\xd9\xcb"
	"\x0\xdb\xcb\x0\xde\xcb\x0\xe0\xcb\x0\xe2\xcc\x0\xea\xd2\x0\xea\xcf\x0\xb9\xa4"
	"\x0\x8e\x7a\x1\x94\x7c\x4\x97\x79\x7\x99\x75\x9\x9b\x71\xd\x9d\x6b\x10\x9f\x67"
	"\x12\xa1\x63\x15\xa3\x5f\x17\xa5\x59\x1a\xa8\x55\x1d\xaa\x50\x20\xac\x4b\x24\xaf\x45"
	"\x28\xb2\x41\x2b\xb5\x3b\x2e\xb8\x35\x31\xba\x30\x34\xbd\x2b\x39\xbf\x24\x3f\xc1\x17"
	"\x49\xc5\x8\x4f\xc8\x1\x4f\xca\x0\x4e\xcd\x0\x4e\xcf\x0\x4f\xd2\x0\x54\xd5\x0"
	"\x5d\xd8\x0\x68\xdb\x0\x6e\xdd\x0\x74\xdf\x0\x7a\xe2\x0\x7f\xe4\x0\x85\xe7\x0"
	"\x8b\xe9\x0\x8f\xeb\x0\x9b\xf3\x0\x9e\xf2\x0\x7e\xbb\x0\x60\x8a\x0\x68\x92\x0"
	"\x6d\x95\x0\x71\x96\x0\x75\x98\x0\x7b\x9a\x0\x7f\x9d\x0\x83\x9f\x0\x87\xa1\x0"
	"\x8c\xa2\x0\x8f\xa5\x0\x92\xa7\x0\x96\xa9\x0\x9a\xad\x0\x9d\xb0\x0\xa1\xb2\x0"
	"\xa5\xb5\x0\xa9\xb7\x0\xad\xba\x0\xb2\xbd\x0\xb6\xbf\x0\xbb\xc3\x0\xbf\xc6\x0"
	"\xc3\xc8\x0\xc8\xcb\x0\xcc\xce\x0\xd0\xd1\x0\xd3\xd2\x0\xd5\xd4\x0\xd9\xd4\x0"
	"\xdc\xd4\x0\xde\xd5\x0\xe1\xd5\x0\xe3\xd5\x0\xe6\xd4\x0\xe8\xd1\x0\xea\xce\x0"
	"\xf2\xcf\x0\xf2\xca\x0\xbb\x99\x0\x8a\x6e\x0\x92\x72\x0\x95\x72\x0\x97\x71\x0"
	"\x9a\x70\x0\x9c\x6e\x0\x9e\x6d\x0\xa0\x6b\x0\xa3\x6a\x0\xa5\x68\x0\xa8\x67\x0"
	"\xab\x66\x0\xae\x65\x0\xb2\x63\x0\xb4\x61\x0\xb7\x5f\x0\xba\x5d\x0\xbd\x5c\x0"
	"\xc0\x59\x0\xc3\x57\x0\xc6\x54\x0\xca\x50\x0\xcd\x4d\x0\xd0\x4a\x0\xd3\x47\x0"
	"\xd6\x43\x0\xd9\x40\x0\xdc\x3d\x0\xde\x39\x0\xe2\x33\x0\xe5\x2f\x0\xe7\x2c\x0"
	"\xea\x28\x0\xec\x23\x0\xef\x1f\x0\xf1\x1a\x0\xf3\x14\x0\xfb\xf\x0\xfa\xd\x0"
	"\xc1\x5\x0\x8e\x0\x0\x97\x0\x0\x9b\x0\x0\x9e\x0\x0\xa1\x0\x0\xa5\x0\x0"
	"\xa9\x0\x0\xad\x0\x0\xb1\x0\x0\xb6\x0\x0\xba\x0\x0\xbd\x0\x0\xc2\x0\x0"
	"\xc8\x0\x0\xcc\x0\x0\xcc\x0\x0"
};

char PrecipPalette[58*3] = {
    "\x8\x89\x41\x0\xc5\x44\x0\xd1\x2c\x0\xe3\x1c\x0\xf9\x6\x14\xff\x0\x3e\xff\x0\x5d\xff\x0"
    "\x80\xff\x0\xab\xff\x0\xcd\xfe\x0\xf8\xff\x0\xff\xe6\x0\xff\xb8\x0\xff\x98\x0"
    "\xff\x75\x0\xff\x49\x0\xfe\x26\x0\xff\x4\x0\xdf\x0\x0\xa8\x0\x0\x87\x0\x0"
    "\x5a\x0\x0\x39\x0\x0\x11\x0\x0\xe\x10\x10\x23\x22\x22\x33\x33\x33\x41\x41\x41"
    "\x53\x53\x53\x60\x60\x60\x6e\x6e\x6e\x80\x80\x80\x8e\x8e\x8e\xa0\xa0\xa0\xae\xae\xae"
    "\xc0\xc0\xc0\xce\xce\xce\xdc\xdc\xdc\xef\xef\xef\xfa\xfa\xfa\xff\xff\xff\xff\xff\xff"
    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
    "\xff\xff\xff"
};
