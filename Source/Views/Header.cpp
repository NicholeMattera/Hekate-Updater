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

#include "Header.hpp"
#include "../Managers/Theme.hpp"

namespace HekateUpdater::Views {
    Header::Header(Point origin, std::string title, bool showIcon) : View() {
        this->frame = Rect(origin.x, origin.y, 1280, 88);
        this->_showIcon = showIcon;
        this->_title = title;

        if (this->_showIcon)
            this->_icon = std::make_unique<Image>("romfs:/images/0_icon.png");
    }

    void Header::render(Rect rect) {
        auto theme = Managers::Theme::Instance();

        if (this->_showIcon) {
            Draw::image(Point(rect.x + 75, rect.y + 29), this->_icon);
            Draw::text(Point(rect.x + 130, rect.y + 62), this->_title, 28, theme->text);
        } else {
            Draw::text(Point(rect.x + 74, rect.y + 62), this->_title, 28, theme->text);
        }

        Draw::fill(Rect(rect.x + 30, rect.y + 87, 1220, 1), theme->text);
    }
}
