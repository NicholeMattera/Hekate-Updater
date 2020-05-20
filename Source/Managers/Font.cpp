/*
 * Hekate Updater
 * Copyright (c) 2020 Nichole Mattera
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#define STB_TRUETYPE_IMPLEMENTATION

#include "Font.hpp"
#include <switch.h>

namespace HekateUpdater::Managers {
    Font * Font::Instance() {
        if (_instance == nullptr) {
            _instance = new Font;
        }

        return _instance;
    }

    stbtt_fontinfo * Font::forGlyph(u32 character) {
        if (stbtt_FindGlyphIndex(&this->_extFont, character)) {
            return &this->_extFont;
        }

        return &this->_stdFont;
    }

    Font::Font() {
        PlFontData stdFontData, extFontData;

        plGetSharedFontByType(&stdFontData, PlSharedFontType_Standard);
        u8 * fontBuffer = reinterpret_cast<u8 *>(stdFontData.address);
        stbtt_InitFont(&this->_stdFont, fontBuffer, stbtt_GetFontOffsetForIndex(fontBuffer, 0));

        plGetSharedFontByType(&extFontData, PlSharedFontType_NintendoExt);
        fontBuffer = reinterpret_cast<u8 *>(extFontData.address);
        stbtt_InitFont(&this->_extFont, fontBuffer, stbtt_GetFontOffsetForIndex(fontBuffer, 0));
    }
}
