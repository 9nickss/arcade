/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Thu, Mar, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     DLLoader                                                                         *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include "Arcade/DLLoader.hpp"

#include <dirent.h>
#include <dlfcn.h>

#include <algorithm>
#include <stdexcept>

namespace Arcade {

    DLLoader::DLLoader(const std::string &path, bool keepResident)
    {
        open(path, keepResident);
    }

    DLLoader::~DLLoader()
    {
        close();
    }

    DLLoader::DLLoader(DLLoader &&other) noexcept
        : _handle(other._handle), _path(std::move(other._path))
    {
        other._handle = nullptr;
    }

    DLLoader &DLLoader::operator=(DLLoader &&other) noexcept
    {
        if (this == &other)
            return *this;
        close();
        _handle = other._handle;
        _path = std::move(other._path);
        other._handle = nullptr;
        return *this;
    }

    void DLLoader::open(const std::string &path, bool keepResident)
    {
        close();
        int flags = RTLD_LAZY | RTLD_LOCAL;

        if (keepResident)
            flags |= RTLD_NODELETE;

        _handle = ::dlopen(path.c_str(), flags);
        if (_handle == nullptr)
            throw std::runtime_error(::dlerror());
        _path = path;
    }

    void DLLoader::close() noexcept
    {
        if (_handle != nullptr) {
            ::dlclose(_handle);
            _handle = nullptr;
        }
        _path.clear();
    }

    void DLLoader::scanLibraries(const std::string &directory)
    {
        _libraries.clear();

        DIR *dir = ::opendir(directory.c_str());

        if (dir == nullptr)
            throw std::runtime_error("cannot open directory: " + directory);

        struct dirent *entry = nullptr;

        while ((entry = ::readdir(dir)) != nullptr) {
            const std::string name = entry->d_name;

            if (name == "." || name == "..")
                continue;
            if (name.size() < 3)
                continue;
            if (name.rfind(".so") != name.size() - 3)
                continue;
            _libraries.push_back(directory + "/" + name);
        }

        ::closedir(dir);

        std::sort(_libraries.begin(), _libraries.end());
    }

    bool DLLoader::isOpen() const noexcept
    {
        return _handle != nullptr;
    }

    const std::string &DLLoader::getPath() const noexcept
    {
        return _path;
    }

    const std::vector<std::string> &DLLoader::getLibraries() const noexcept
    {
        return _libraries;
    }

    std::string DLLoader::selectLibrary(std::size_t index) const
    {
        if (index >= _libraries.size())
            throw std::runtime_error("invalid library index");
        return _libraries[index];
    }

    void *DLLoader::getSymbolRaw(const std::string &symbolName) const
    {
        if (_handle == nullptr)
            throw std::runtime_error("dlopen handle is null");

        ::dlerror();
        void *symbol = ::dlsym(_handle, symbolName.c_str());
        const char *error = ::dlerror();

        if (error != nullptr)
            throw std::runtime_error(error);
        return symbol;
    }

}
