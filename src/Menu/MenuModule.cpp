/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Wed, Mar, 2026                                                     *
 * Title           - G-OOP-400-NCE-4-1-arcade-3                                         *
 * Description     -                                                                    *
 *     MenuModule                                                                       *
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

#include "Menu/MenuModule.hpp"

namespace Arcade {

    void MenuModule::init()
    {
        _selectedGame = "";
        _selectedLib = "";
        _playerName = "";
        _gameIndex = 0;
        _libIndex = 0;
        _quit = false;
    }

    void MenuModule::reset()
    {
        _selectedGame = "";
        _selectedLib = "";
    }

    void MenuModule::close()
    {
    }

    const std::string &MenuModule::getName() const
    {
        static std::string name = "menu";
        return name;
    }

    void MenuModule::handleInput(Key key)
    {
        if (key == Key::DOWN)
            _gameIndex = (_gameIndex + 1) % _gameLibs.size();
        if (key == Key::UP)
            _gameIndex = (_gameIndex + _gameLibs.size() - 1) % _gameLibs.size();

        if (key == Key::RIGHT)
            _libIndex = (_libIndex + 1) % _graphicLibs.size();
        if (key == Key::LEFT)
            _libIndex = (_libIndex + _graphicLibs.size() - 1) % _graphicLibs.size();

        if (key >= Key::KEY_A && key <= Key::KEY_Z)
            _playerName += (char)('A' + (int)(key) - (int)(Key::KEY_A));
        if (key == Key::RESTART)
            _playerName += (char)('R');
        if (key == Key::PREV_LIB)
            _playerName += (char)('P');
        if (key == Key::NEXT_LIB)
            _playerName += (char)('N');
        if (key == Key::BACKSPACE && !_playerName.empty())
            _playerName.pop_back();

        if (key == Key::ENTER && !_gameLibs.empty())
            _selectedGame = _gameLibs[_gameIndex];

        if (key == Key::SPACE && !_graphicLibs.empty())
            _selectedLib = _graphicLibs[_libIndex];

        if (key == Key::QUIT)
            _quit = true;
    }

    //void MenuModule::handleClickableArea(const ClickableArea &area)
    //{
    //    if (area.type == ClickableArea::GAME_SELECTION) {
    //        _gameIndex = area.index;
    //        _selectedGame = _gameLibs[_gameIndex];
    //    } else if (area.type == ClickableArea::GRAPHIC_SELECTION) {
    //        _libIndex = area.index;
    //        _selectedLib = _graphicLibs[_libIndex];
    //    }
    //}

    void MenuModule::update()
    {
    }

    const RenderData &MenuModule::getRenderData()
    {
        _renderData = RenderData();
        _renderData.gridWidth = 80;
        _renderData.gridHeight = 24;
        _renderData.grid.assign(
            _renderData.gridHeight,
            std::vector<Cell>(_renderData.gridWidth, {' ', Color::WHITE, Color::BLACK})
        );

        _renderData.texts.push_back({"=== ARCADE ===", 33, 0, Color::YELLOW});

        _renderData.texts.push_back({"-- GAMES --", 2, 2, Color::CYAN});
        for (std::size_t i = 0; i < _gameLibs.size(); ++i) {
            std::string prefix = (i == _gameIndex) ? "> " : "  ";
            _renderData.texts.push_back({prefix + _gameLibs[i], 2, (int)(4 + i), Color::WHITE});
            // int itemWidth = (int)(_gameLibs[i].length() + 2);
            //_renderData.clickableAreas.push_back({2, (int)(4 + i), itemWidth, 1, ClickableArea::GAME_SELECTION, (int)i, Key::ENTER});
        }

        _renderData.texts.push_back({"-- GRAPHICS --", 30, 2, Color::CYAN});
        for (std::size_t i = 0; i < _graphicLibs.size(); ++i) {
            std::string prefix = (i == _libIndex) ? "> " : "  ";
            _renderData.texts.push_back({prefix + _graphicLibs[i], 30, (int)(4 + i), Color::WHITE});
            // int itemWidth = (int)(_graphicLibs[i].length() + 2);
            //_renderData.clickableAreas.push_back({30, (int)(4 + i), itemWidth, 1, ClickableArea::GRAPHIC_SELECTION, (int)i, Key::SPACE});
        }

        _renderData.texts.push_back({"-- SCORES --", 58, 2, Color::CYAN});
        for (std::size_t i = 0; i < _scores.size(); ++i) {
            std::string entry = _scores[i].playerName + " "
                + _scores[i].gameName + " "
                + std::to_string(_scores[i].score);
            _renderData.texts.push_back({entry, 58, (int)(4 + i), Color::WHITE});
        }

        _renderData.texts.push_back({"-- PLAYER NAME --", 2, 18, Color::CYAN});
        _renderData.texts.push_back({"> " + _playerName + "_", 2, 19, Color::WHITE});

        _renderData.texts.push_back({"ENTER: play  UP/DOWN ARROW: select game", 2 , 22, Color::YELLOW}); 
        _renderData.texts.push_back({"LEFT/RIGHT ARROW: select graphical lib  SPACE: select lib", 2, 23, Color::YELLOW});

        return _renderData;
    }

    int MenuModule::getScore() const
    {
        return 0;
    }

    bool MenuModule::isGameOver() const
    {
        return _quit;
    }

    std::string MenuModule::getSelectedGame() const
    {
        return _selectedGame;
    }

    std::string MenuModule::getSelectedLib() const
    {
        return _selectedLib;
    }

    std::string MenuModule::getPlayerName() const
    {
        return _playerName;
    }

    void MenuModule::setGameLibs(const std::vector<std::string> &libs)
    {
        _gameLibs = libs;
    }

    void MenuModule::setGraphicLibs(const std::vector<std::string> &libs)
    {
        _graphicLibs = libs;
    }

    void MenuModule::setScores(const std::vector<ScoreEntry> &scores)
    {
        _scores = scores;
    }

    extern "C" IMenuModule *createMenu()
    {
        return new MenuModule();
    }

}
