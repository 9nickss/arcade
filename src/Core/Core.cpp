/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Wed, Mar, 2026                                                     *
 * Title           - G-OOP-400-NCE-4-1-arcade-3                                         *
 * Description     -                                                                    *
 *     Core                                                                             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *       _|_|_|_|  _|_|_|    _|_|_|  _|_|_|_|_|  _|_|_|_|    _|_|_|  _|    _|           *
 *       _|        _|    _|    _|        _|      _|        _|        _|    _|           *
 *       _|_|_|    _|_|_|      _|        _|      _|_|_|    _|        _|_|_|_|           *
 *       _|        _|          _|        _|      _|        _|        _|    _|           *
 *       _|_|_|_|  _|        _|_|_|      _|      _|_|_|_|    _|_|_|  _|    _|           *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include "Core/Core.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

namespace Arcade {

    namespace {
        constexpr int TARGET_FPS = 30;
        constexpr std::chrono::milliseconds FRAME_TIME_MS(1000 / TARGET_FPS);

        void capFrameRate(const std::chrono::steady_clock::time_point &frameStart)
        {
            const auto frameDuration = std::chrono::steady_clock::now() - frameStart;

            if (frameDuration < FRAME_TIME_MS)
                std::this_thread::sleep_for(FRAME_TIME_MS - frameDuration);
        }
    }

    Core::Core(const std::string &initialLib)
    {
        _displayLoader.open(initialLib, initialLib.find("qt5") != std::string::npos);
        auto factory = _displayLoader.getSymbol<IDisplayModule *(*)()>("entryPointDisplay");
        if (!factory)
            throw std::runtime_error("'" + initialLib + "' not a graphical library");
        _display = factory();

        scanLibs();
        loadScores();

        auto it = std::find(_graphicLibs.begin(), _graphicLibs.end(), initialLib);
        if (it != _graphicLibs.end())
            _currentGraphic = std::distance(_graphicLibs.begin(), it);
    }

    Core::~Core()
    {
        delete _display;
        delete _game;
        delete _menu;
    }

    void Core::scanLibs()
    {
        DLLoader scanner;
        scanner.scanLibraries("./lib");

        for (const auto &path : scanner.getLibraries()) {
            try {
                DLLoader tmp(path);
                auto f = tmp.getSymbol<IDisplayModule *(*)()>("entryPointDisplay");
                if (f) {
                    _graphicLibs.push_back(path);
                    continue;
                }
            } catch (...) {}

            try {
                DLLoader tmp(path);
                auto f = tmp.getSymbol<IGameModule *(*)()>("entryPointGame");
                if (f)
                    _gameLibs.push_back(path);
            } catch (...) {}
        }
    }

    void Core::loadDisplay(const std::string &path)
    {
        delete _display;
        _display = nullptr;
        _displayLoader.open(path, path.find("qt5") != std::string::npos);
        auto factory = _displayLoader.getSymbol<IDisplayModule *(*)()>("entryPointDisplay");
        _display = factory();
        _display->init();
    }

    void Core::loadGame(const std::string &path)
    {
        delete _game;
        _game = nullptr;
        _gameLoader.open(path);
        auto factory = _gameLoader.getSymbol<IGameModule *(*)()>("entryPointGame");
        _game = factory();
        _game->init();
    }

    void Core::run()
    {
        _display->init();
        runMenu();
        _display->close();
    }

    void Core::loadMenu()
    {
        loadScores();
        delete _menu;
        _menu = nullptr;
        _menuLoader.open("./lib/arcade_menu.so");
        auto factory = _menuLoader.getSymbol<IMenuModule *(*)()>("createMenu");
        _menu = factory();
        _menu->setGameLibs(_gameLibs);
        _menu->setGraphicLibs(_graphicLibs);
        _menu->setScores(_scores);
        _menu->init();
    }

    void Core::runMenu()
    {
        loadMenu();

        while (!_menu->isGameOver()) {
            const auto frameStart = std::chrono::steady_clock::now();
            Key key = _display->pollEvent();

            if (key == Key::QUIT)
                return;

            //ClickableArea *clickedArea = _display->getLastClickableArea();
            _menu->handleInput(key);
            _menu->update();

            if (!_menu->getSelectedGame().empty()) {
                loadGame(_menu->getSelectedGame());
                _playerName = _menu->getPlayerName();
                runGame();
                loadMenu();
            }
            if (!_menu->getSelectedLib().empty()) {
                const std::string selectedLib = _menu->getSelectedLib();
                auto it = std::find(_graphicLibs.begin(), _graphicLibs.end(), selectedLib);

                if (it != _graphicLibs.end())
                    _currentGraphic = static_cast<std::size_t>(std::distance(_graphicLibs.begin(), it));
                loadDisplay(selectedLib);
                _menu->reset();
                capFrameRate(frameStart);
                continue;
            }

            _display->clear();
            _display->render(_menu->getRenderData());
            _display->display();
            capFrameRate(frameStart);
        }
    }

    void Core::runGame()
    {
        while (!_game->isGameOver()) {
            const auto frameStart = std::chrono::steady_clock::now();
            Key key = _display->pollEvent();

            if (key == Key::QUIT)
                break;
            if (key == Key::NEXT_LIB) {
                _currentGraphic = (_currentGraphic + 1) % _graphicLibs.size();
                loadDisplay(_graphicLibs[_currentGraphic]);
                capFrameRate(frameStart);
                continue;
            }
            if (key == Key::PREV_LIB) {
                _currentGraphic = (_currentGraphic + _graphicLibs.size() - 1) % _graphicLibs.size();
                loadDisplay(_graphicLibs[_currentGraphic]);
                capFrameRate(frameStart);
                continue;
            }
            if (key == Key::NEXT_GAME) {
                _currentGame = (_currentGame + 1) % _gameLibs.size();
                loadGame(_gameLibs[_currentGame]);
                capFrameRate(frameStart);
                continue;
            }
            if (key == Key::PREV_GAME) {
                _currentGame = (_currentGame + _gameLibs.size() - 1) % _gameLibs.size();
                loadGame(_gameLibs[_currentGame]);
                capFrameRate(frameStart);
                continue;
            }
            if (key == Key::RESTART) {
                _game->reset();
                capFrameRate(frameStart);
                continue;
            }
            if (key == Key::MENU) {
                runMenu();
                capFrameRate(frameStart);
                return;
            }

            _game->handleInput(key);
            _game->update();

            _display->clear();
            _display->render(_game->getRenderData());
            _display->display();
            capFrameRate(frameStart);
        }
        saveScores();
    }

    void Core::saveScores()
    {
        std::ofstream file("scores.txt", std::ios::app);
        if (!file)
            return;
        std::string name = _playerName.empty() ? "Anonymous" : _playerName;
        file << name << " "
            << _game->getName() << " "
            << _game->getScore() << "\n";
    }

    void Core::loadScores()
    {
        _scores.clear();
        std::ifstream file("scores.txt");
        if (!file)
            return;
        ScoreEntry entry;
        while (file >> entry.playerName >> entry.gameName >> entry.score)
            _scores.push_back(entry);

        std::sort(_scores.begin(), _scores.end(), [](const ScoreEntry &a, const ScoreEntry &b) {
            return a.score > b.score;
        });

        if (_scores.size() > 10)
            _scores.resize(10);
    }

}
