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

#include <cstring>
#include "Image.hpp"
#include <png.h>
#include "Services/File.hpp"

namespace HekateUpdater {
    Image::Image(std::string path) {
        auto data = Services::File::read(path);
        this->imageLoaded = this->_readPNG(data);
    }

    Image::~Image() {
        if (this->rawImage != NULL) {
            free(this->rawImage);
        }
    }

    bool Image::_readPNG(std::vector<char> file) {
        png_image image;

        memset(&image, 0, sizeof(image));
        image.version = PNG_IMAGE_VERSION;

        if (png_image_begin_read_from_memory(&image, &file[0], file.size()) == 0) {
            return false;
        }

        this->width = image.width;
        this->height = image.height;
        image.format = PNG_FORMAT_RGB;

        this->rawImage = (u8*) malloc(image.width * image.height * 3);
        memset(this->rawImage, 0, image.width * image.height * 3);

        if (png_image_finish_read(&image, NULL, this->rawImage, 0, NULL) == 0) {
            return false;
        }

        png_image_free(&image);

        return true;
    }
}
