/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Thu, Mar, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     DLLoader                                                                         *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#ifndef ARCADE_DLLOADER_HPP_
    #define ARCADE_DLLOADER_HPP_

#include <cstddef>
#include <string>
#include <vector>

namespace Arcade {

    class DLLoader {

    public:
        DLLoader() = default;
        explicit DLLoader(const std::string &path, bool keepResident = false);
        ~DLLoader();

        DLLoader(const DLLoader &) = delete;
        DLLoader &operator=(const DLLoader &) = delete;

        DLLoader(DLLoader &&other) noexcept;
        DLLoader &operator=(DLLoader &&other) noexcept;

        void open(const std::string &path, bool keepResident = false);
        void close() noexcept;

        void scanLibraries(const std::string &directory = "./lib");

        bool isOpen() const noexcept;
        const std::string &getPath() const noexcept;
        const std::vector<std::string> &getLibraries() const noexcept;
        std::string selectLibrary(std::size_t index) const;

        template <typename SymbolType>
        SymbolType getSymbol(const std::string &symbolName) const
        {
            return reinterpret_cast<SymbolType>(getSymbolRaw(symbolName));
        }

    private:
        void *getSymbolRaw(const std::string &symbolName) const;

        void *_handle = nullptr;
        std::string _path;
        std::vector<std::string> _libraries;
    };

}

#endif
