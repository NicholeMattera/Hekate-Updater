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

#include "Footer.hpp"
#include "../Managers/Theme.hpp"

namespace HekateUpdater::Views {
    Footer::Footer(Point origin) : View() {
        this->frame = Rect(origin.x, origin.y, 1280, 73);
    }

    void Footer::render(Rect rect) {
        auto theme = Managers::Theme::Instance();

        Draw::fill(Rect(rect.x + 30, rect.y, 1220, 1), theme->text);

        // TODO: Render controller icon.

        // TODO: Render buttons.
    }
}
