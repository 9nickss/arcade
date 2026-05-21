/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Wed, Mar, 2026                                                     *
 * Title           - G-OOP-400-NCE-4-1-arcade-3                                         *
 * Description     -                                                                    *
 *     MenuModule                                                                       *
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

#ifndef INCLUDED_MENUMODULE_HPP
    #define INCLUDED_MENUMODULE_HPP

#include "Menu/IMenuModule.hpp"

namespace Arcade {

    class MenuModule : public IMenuModule {
    public:
        void init() override;
        void reset() override;
        void close() override;
        const std::string &getName() const override;
        void handleInput(Key key) override;
        //void handleClickableArea(const ClickableArea &area);
        void update() override;
        const RenderData &getRenderData() override;
        int getScore() const override;
        bool isGameOver() const override;

        std::string getSelectedLib() const override;
        std::string getSelectedGame() const override;
        std::string getPlayerName() const override;

        void setGameLibs(const std::vector<std::string> &libs) override;
        void setGraphicLibs(const std::vector<std::string> &libs) override;
        void setScores(const std::vector<ScoreEntry> &scores) override;

    private:
        std::vector<std::string> _gameLibs;
        std::vector<std::string> _graphicLibs;
        std::vector<ScoreEntry> _scores;

        std::string _selectedGame;
        std::string _selectedLib;
        std::string _playerName;

        std::size_t _gameIndex = 0;
        std::size_t _libIndex = 0;

        RenderData _renderData;
        bool _quit = false;
    };

}

#endif