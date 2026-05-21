/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Wed, Mar, 2026                                                     *
 * Title           - G-OOP-400-NCE-4-1-arcade-3                                         *
 * Description     -                                                                    *
 *     Core                                                                             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *         ░        ░       ░░        ░        ░        ░░      ░░  ░░░░  ░             *
 *         ▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒▒▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒             *
 *         ▓      ▓▓▓       ▓▓▓▓▓  ▓▓▓▓▓▓▓  ▓▓▓▓      ▓▓▓  ▓▓▓▓▓▓▓        ▓             *
 *         █  ███████  ██████████  ███████  ████  ███████  ████  █  ████  █             *
 *         █        █  ███████        ████  ████        ██      ██  ████  █             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#ifndef INCLUDED_CORE_HPP
    #define INCLUDED_CORE_HPP

#include <string>
#include <vector>

#include "IDisplayModule/IDisplayModule.hpp"
#include "IGameModule/IGameModule.hpp"
#include "Arcade/DLLoader.hpp"
#include "Menu/IMenuModule.hpp"

namespace Arcade {
    class Core {
        private:
            DLLoader _displayLoader;
            DLLoader _gameLoader;
            DLLoader _menuLoader;
            IDisplayModule *_display = nullptr;
            IGameModule *_game = nullptr;

            std::vector<std::string> _graphicLibs;
            std::vector<std::string> _gameLibs;

            std::string _playerName;
            std::size_t _currentGraphic = 0;
            std::size_t _currentGame = 0;

            IMenuModule *_menu = nullptr;
            std::vector<ScoreEntry> _scores;
        public:
            Core(const std::string &initialLib);
            ~Core();

            void run();

            void scanLibs();
            void loadDisplay(const std::string &path);
            void loadGame(const std::string &path);
            void runMenu();
            void runGame();
            void saveScores();
            void loadScores();
            void loadMenu();
        };
}

#endif
