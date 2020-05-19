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

#include <memory>
#include <switch.h>

#include "Image.hpp"

#define Point(x, y) { x, y }
#define Size(w, h) { w, h }
#define Rect(x, y, w, h) { x, y, w, h }
#define Colour(r, g, b, a) { r, g, b, a }

#pragma once

namespace HekateUpdater {
    struct Point {
        u16 x;
        u16 y;
    };

    struct Size {
        u16 width;
        u16 height;
    };

    struct Rect {
        u16 x;
        u16 y;
        u16 width;
        u16 height;
    };

    struct Colour {
        u8 red;
        u8 green;
        u8 blue;
        u8 alpha;
    };

    class Draw {
        public:
            static void pixel(Point point, Colour Colour);
            static void fill(Rect rect, Colour Colour);
            static void image(Point point, std::shared_ptr<Image> image);

        private:
            static u8 _blend(u32 source, u32 destination, u8 alpha);
    };
}
