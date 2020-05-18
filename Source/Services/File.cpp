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

#include "File.hpp"
#include <fstream>
#include <sys/stat.h>

namespace HekateUpdater::Services {
    bool File::exists(std::string path) {
        struct stat buf;
        return (stat(path.c_str(), &buf) == 0);
    }

    std::vector<char> File::read(std::string path) {
        if (!File::exists(path)) {
            std::vector<char> empty;
            return empty;
        }

        std::ifstream file;
        file.open(path, std::ios::in | std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            std::vector<char> empty;
            return empty;
        }

        auto size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        file.read(buffer.data(), size);
        file.close();

        return buffer;
    }

    void File::write(std::string path, std::vector<char> data) {
        std::ofstream file;
        file.open(path, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!file.is_open()) {
            return;
        }

        file.write((char *)&data[0], data.size());

        file.flush();
        file.close();
    }

    void File::unlink(std::string path) {
        if (File::exists(path)) {
            remove(path.c_str()) == 0;
        }
    }

    void File::createFolder(std::string path) {
        mkdir(path.c_str(), 0775);
    }
}
