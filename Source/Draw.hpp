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

#pragma once

namespace HekateUpdater {
    class Point {
        public:
            u16 x, y;
            Point() : x(0), y(0) {}
            Point(u16 x, u16 y) : x(x), y(y) {}
    };

    class Size {
        public:
            u16 width, height;
            Size() : width(0), height(0) {}
            Size(u16 w, u16 h) : width(w), height(h) {}
    };

    class Rect {
        public:
            u16 x, y;
            u16 width, height;
            Rect() : x(0), y(0), width(0), height(0) {}
            Rect(Point origin, Size size) : x(origin.x), y(origin.y), width(size.width), height(size.height) {}
            Rect(u16 x, u16 y, u16 w, u16 h) : x(x), y(y), width(w), height(h) {}
    };

    class Colour {
        public:
            u8 red, green, blue, alpha;
            Colour() : red(0), green(0), blue(0), alpha(255) {}
            Colour(u8 r, u8 g, u8 b, u8 a) : red(r), green(g), blue(b), alpha(a) {}
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
