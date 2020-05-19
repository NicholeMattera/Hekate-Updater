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

#include "View.hpp"

namespace HekateUpdater {
    void View::tick() {
        for (auto const& view : subviews) {
            if (auto viewTemp = view.lock()) {
                viewTemp->tick();
            }
        }
    }

    void View::render(Rect rect) {
        if (background.alpha != 0) {
            Draw::fill(rect, background);
        }

        for (auto const& view : subviews) {
            if (auto viewTemp = view.lock()) {
                if (viewTemp->isHidden)
                    continue;

                auto subviewFrame = viewTemp->frame;

                viewTemp->render(
                    Rect(
                        (u16) (rect.x + subviewFrame.x),
                        (u16) (rect.y + subviewFrame.y),
                        subviewFrame.width,
                        subviewFrame.height
                    )
                );
            }
        }
    }

    void View::addSubView(std::shared_ptr<View> view) {
        this->subviews.push_back(view);
    }
}
