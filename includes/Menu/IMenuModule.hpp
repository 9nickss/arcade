/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Wed, Mar, 2026                                                     *
 * Title           - G-OOP-400-NCE-4-1-arcade-3                                         *
 * Description     -                                                                    *
 *     IMenuModule                                                                      *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *       ▄▀▀█▄▄▄▄  ▄▀▀▄▀▀▀▄  ▄▀▀█▀▄    ▄▀▀▀█▀▀▄  ▄▀▀█▄▄▄▄  ▄▀▄▄▄▄   ▄▀▀▄ ▄▄             *
 *      ▐  ▄▀   ▐ █   █   █ █   █  █  █    █  ▐ ▐  ▄▀   ▐ █ █    ▌ █  █   ▄▀            *
 *        █▄▄▄▄▄  ▐  █▀▀▀▀  ▐   █  ▐  ▐   █       █▄▄▄▄▄  ▐ █      ▐  █▄▄▄█             *
 *        █    ▌     █          █        █        █    ▌    █         █   █             *
 *       ▄▀▄▄▄▄    ▄▀        ▄▀▀▀▀▀▄   ▄▀        ▄▀▄▄▄▄    ▄▀▄▄▄▄▀   ▄▀  ▄▀             *
 *       █    ▐   █         █       █ █          █    ▐   █     ▐   █   █               *
 *       ▐        ▐         ▐       ▐ ▐          ▐        ▐         ▐   ▐               *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#ifndef INCLUDED_IMENUMODULE_HPP
    #define INCLUDED_IMENUMODULE_HPP

#include "IGameModule/IGameModule.hpp"

namespace Arcade {
    class IMenuModule : public IGameModule {
        public:
            virtual ~IMenuModule() = default;

            virtual std::string getSelectedLib() const = 0;
            virtual std::string getSelectedGame() const = 0;
            virtual std::string getPlayerName() const = 0;
            virtual void setGameLibs(const std::vector<std::string> &libs) = 0;
            virtual void setGraphicLibs(const std::vector<std::string> &libs) = 0;
            virtual void setScores(const std::vector<ScoreEntry> &scores) = 0;
            //virtual void handleClickableArea(const ClickableArea &area) = 0;
    };
}

#endif
