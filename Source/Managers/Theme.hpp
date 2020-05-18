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

#include "../Draw.hpp"

#pragma once

namespace HekateUpdater::Managers {
    class Theme {
        public:
            bool isLight = false;

            Colour background;
            Colour text;
            Colour modalOverlay;
            Colour focusedBackground;
            Colour focusedText;
            Colour focusedBorderOne;
            Colour focusedBorderTwo;

            void updateTheme();

            static Theme * Instance();

        private:
            static inline Theme * _instance = nullptr;

            Theme(){};
            Theme(Theme const&){};
        
    };
}
