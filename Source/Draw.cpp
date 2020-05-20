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

#include "Application.hpp"
#include <cwctype>
#include "Draw.hpp"

namespace HekateUpdater {
    void Draw::pixel(Point point, Colour colour) {
        u32 position = point.y * Application::Stride + point.x * sizeof(u32);
        u8 * framebuffer = Application::CurrentFramebuffer;

        framebuffer[position] = Draw::_blend(framebuffer[position], colour.red, colour.alpha);
        framebuffer[position + 1] = Draw::_blend(framebuffer[position + 1], colour.green, colour.alpha);
        framebuffer[position + 2] = Draw::_blend(framebuffer[position + 2], colour.blue, colour.alpha);
        framebuffer[position + 3] = 255;
    }
    
    void Draw::fill(Rect rect, Colour colour) {
        for (u16 x = rect.x; x < rect.x + rect.width; x++) {
            for (u16 y = rect.y; y < rect.y + rect.height; y++) {
                Draw::pixel(Point(x, y), colour);
            }
        }
    }

    void Draw::image(Point point, std::shared_ptr<Image> image) {
        if (!image->imageLoaded || image->rawImage == nullptr)
            return;

        for (u16 x = 0; x < image->width; x++) {
            for (u16 y = 0; y < image->height; y++) {
                u32 pos = ((y * image->width) + x) * 3;
                Draw::pixel(Point(x + point.x, y + point.y), Colour(image->rawImage[pos], image->rawImage[pos + 1], image->rawImage[pos + 2], 255));
            }
        }
    }

    void Draw::text(Point point, std::string text, float size, Colour colour) {
        auto font = Managers::Font::Instance();

        const char * string = text.c_str();
        u32 currentX = point.x;
        u32 currentY = point.y;

        do {
            u32 currentCharacter;
            ssize_t codepointWidth = decode_utf8(&currentCharacter, reinterpret_cast<const u8*>(string));

            if (codepointWidth <= 0)
                break;

            string += codepointWidth;

            stbtt_fontinfo * currentFont = font->forGlyph(currentCharacter);
            float currentFontSize = stbtt_ScaleForPixelHeight(currentFont, size);

            if (currentCharacter == '\n') {
                currentX = point.x;
                currentY += static_cast<u32>(size);

                continue;
            }

            int bounds[4] = { 0 };
            stbtt_GetCodepointBitmapBoxSubpixel(
                currentFont,
                currentCharacter,
                currentFontSize,
                currentFontSize,
                0,
                0,
                &bounds[0],
                &bounds[1],
                &bounds[2],
                &bounds[3]);

            s32 x = 0, y = 0;
            stbtt_GetCodepointHMetrics(currentFont, currentCharacter, &x, &y);

            if (!std::iswspace(currentCharacter))
                Draw::_glyph(
                    currentCharacter,
                    currentX + bounds[0],
                    currentY + bounds[1],
                    colour, currentFont,
                    currentFontSize);

            currentX += static_cast<u32>(x * currentFontSize);
        } while(*string != '\0');
    }

    u8 Draw::_blend(u32 source, u32 destination, u8 alpha) {
        return (destination * alpha + source * (255 - alpha)) / 255;
    }

    void Draw::_glyph(u32 character, u32 x, u32 y, Colour color, stbtt_fontinfo * font, float size) {
        int width = 10, height = 10;

        u8 * glyphBmp = stbtt_GetCodepointBitmap(font, size, size, character, &width, &height, nullptr, nullptr);
        
        if (glyphBmp == nullptr)
            return;

        for (u32 bmpY = 0; bmpY < height; bmpY++) {
            for (u32 bmpX = 0; bmpX < width; bmpX++) {
                Colour tmpColor = color;
                tmpColor.alpha = (glyphBmp[width * bmpY + bmpX] >> 4) * (float(tmpColor.alpha) / 0xF);
                Draw::pixel(Point(x + bmpX, y + bmpY), tmpColor);
            }
        }

        std::free(glyphBmp);
    }
}
