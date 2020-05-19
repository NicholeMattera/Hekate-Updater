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

#include <vector>
#include <memory>
#include <switch.h>

#include "Draw.hpp"

#pragma once

namespace HekateUpdater {
    class View {
        public:
            Rect frame = Rect(0, 0, 0, 0);
            Colour background = Colour(0, 0, 0, 0);
            bool isHidden = false;

            View(){};
            virtual void tick();
            virtual void render(Rect rect);

            /* View Hierarchy */
            std::vector<std::weak_ptr<View>> subviews;
            void addSubView(std::shared_ptr<View> view);

        private:

    };
}
